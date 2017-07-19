
# General register plan

# RAX	out0
# RBX	out1
# RCX	out2
# RDX	out3
# RSI	in0
# RDI	in1
# R08	In1
# R09	In1s
# R10 	mod > i
# R11 	div > j
# R12	out4
# R13	out5
# R14	out6
# R15	out7

# Stack allocation (no red zone)

# 0x08(%rsp)	Out
# 0x10(%rsp)	_In0 
# 0x18(%rsp)	_In1 

# 0x20(%rsp)	m
# 0x28(%rsp)	k
# 0x30(%rsp)	n
# 0x38(%rsp)	// unroll

# 0x40(%rsp)	In0
# 0x48(%rsp)	// In1
# 0x50(%rsp)	mod
# 0x58(%rsp)	div

# 0x60(%rsp)	Outs0
# 0x68(%rsp)	Outs1 
# 0x70(%rsp)	In0s 
# 0x78(%rsp)	In1s 

# 0x80(%rsp)	Out0
# 0x88(%rsp)	Out1
# 0x90(%rsp)	Out2
# 0x98(%rsp)	Out3

# 0xA0(%rsp)	Out4
# 0xA8(%rsp)	Out5
# 0xB0(%rsp)	Out6
# 0xB8(%rsp)	Out7

	.globl rmdot_product_double_1x1
	.globl rmdot_product_double_1x2
	.globl rmdot_product_double_1x4

	.text

rmdot_product_double_1x1:
	push %rsp
	push %rbp
	push %rbx
	push %r12
	push %r13
	push %r14
	push %r15
	movq %rsp, %rbp
	subq $256, %rsp
	andq $-64, %rsp

	# Out _In0 _In1 k   n   In1s
	# rdi rsi  rdx  rcx r8  r9 

	movq %rdi, 0x08(%rsp) 	# Out
	movq %rsi, 0x10(%rsp) 	# _In0
	movq %rdx, 0x18(%rsp) 	# _In1
	movq %rcx, 0x28(%rsp) 	# k
	movq %r8 , 0x30(%rsp) 	# n
	movq %r9 , 0x58(%rsp)   # In1s
	shlq $3, %r9

	movq 0x10(%rsp), %rsi 	# In0 = _In0
	movq 0x18(%rsp), %r8 	# In1 = _In1

	movq 0x28(%rsp), %r10 	# for (i = k; i; i--)
	test %r10, %r10
	je 3f
0:

	movq 0x08(%rsp), %rax	# out = Out
	movsd 0(%rsi), %xmm4	# in0 = *In0
	addq $8, %rsi   	# In0 ++
	movq %r8, %rdi  	# in1 = In1
	addq %r9, %r8   	# In1 += In1s

	movq 0x30(%rsp), %r11	# for (j = n; j; j--)
	test %r11, %r11
	je 2f
1:

	#(out + 0) += in0 * *(in1 + 0);
	movsd 0(%rax), %xmm0
	movsd 0(%rdi), %xmm8
	mulsd %xmm4, %xmm8
	addsd %xmm8, %xmm0
	movsd %xmm0, 0(%rax)

	addq $8, %rax   	# out ++
	addq $8, %rdi   	# in1 ++

	subq $1, %r11   	# }
	jnz 1b
2:
	subq $1, %r10     	# }
	jnz 0b 

	movq %rbp, %rsp
	pop %r15
	pop %r14
	pop %r13
	pop %r12
	pop %rbx
	pop %rbp
	pop %rsp
	ret

//------------------------------------------------------------------------------
rmdot_product_double_1x2:
	push %rsp
	push %rbp
	push %rbx
	push %r12
	push %r13
	push %r14
	push %r15
	movq %rsp, %rbp
	subq $256, %rsp
	andq $-64, %rsp

	# Out _In0 _In1 k   n   In1s
	# rdi rsi  rdx  rcx r8  r9 

	movq %rdi, 0x08(%rsp) 	# Out
	movq %rsi, 0x10(%rsp) 	# _In0
	movq %rdx, 0x18(%rsp) 	# _In1
	movq %rcx, 0x28(%rsp) 	# k
	movq %r8 , 0x30(%rsp) 	# n
	movq %r9 , 0x78(%rsp)   # In1s
	shlq $3, %r9

	movq 0x30(%rsp), %r10	# n
	movq %r10, %r11		# n
	andq $1, %r10		# mod = n & 1
	shrq $1, %r11		# div = n >> 1
	movq %r10, 0x50(%rsp)	# mod
	movq %r11, 0x58(%rsp)	# div

	movq 0x10(%rsp), %rsi 	# In0 = _In0
	movq 0x18(%rsp), %r8 	# In1 = _In1

	movq 0x28(%rsp), %r10 	# for (i = k; i; i--)
	test %r10, %r10
	je 3f
	.p2align 5,,16
	.p2align 4
0:

	movq 0x08(%rsp), %rax 	# out = Out
	movsd 0(%rsi), %xmm4	# in0 = *In0
	unpcklpd %xmm4, %xmm4
	addq $8, %rsi   	# In0 ++
	movq %r8, %rdi  	# in1 = In1
	addq %r9, %r8 		# In1 += In1s

	movq 0x58(%rsp), %r11  # for (j = div; j; j--)
	test %r11, %r11
	je 2f
	.p2align 6
1:

	#(out + 0) += in0 * *(in1 + 0);
	#(out + 1) += in0 * *(in1 + 1);
	movupd 0(%rax), %xmm0
	movupd 0(%rdi), %xmm8
	mulpd  %xmm4, %xmm8
	addpd  %xmm8, %xmm0
	movupd %xmm0, 0(%rax)

	addq $16, %rax   	# out += 2
	addq $16, %rdi   	# in1 += 2

	subq $1, %r11   	# }
	jnz 1b
2:
	subq $1, %r10     	# }
	jnz 0b 
3: 
	movq 0x50(%rsp), %r8	# mod
	test %r8, %r8		# if (mod)
	je 4f

	movq 0x30(%rsp), %r11   # n
	subq %r8, %r11		# div = n - mod
	shlq $3, %r11
	
	# Out _In0 _In1 k   n   In1s
	# rdi rsi  rdx  rcx r8  r9 

	#rmdot_product_1x1(Out + div, _In0, _In1 + div, k, mod, In1s)
	movq 0x08(%rsp), %rdi
	addq %r11, %rdi
	movq 0x10(%rsp), %rsi
	movq 0x18(%rsp), %rdx
	addq %r11, %rdx
	movq 0x28(%rsp), %rcx
	movq 0x78(%rsp), %r9
	call rmdot_product_double_1x1

4:
	movq %rbp, %rsp
	pop %r15
	pop %r14
	pop %r13
	pop %r12
	pop %rbx
	pop %rbp
	pop %rsp
	ret

//------------------------------------------------------------------------------
rmdot_product_double_1x4:
	push %rsp
	push %rbp
	push %rbx
	push %r12
	push %r13
	push %r14
	push %r15
	movq %rsp, %rbp
	subq $256, %rsp
	andq $-64, %rsp

	# Out _In0 _In1 k   n   In1s
	# rdi rsi  rdx  rcx r8  r9 

	movq %rdi, 0x08(%rsp) 	# Out
	movq %rsi, 0x10(%rsp) 	# _In0
	movq %rdx, 0x18(%rsp) 	# _In1
	movq %rcx, 0x28(%rsp) 	# k
	movq %r8 , 0x30(%rsp) 	# n
	movq %r9 , 0x78(%rsp)   # In1s
	shlq $3, %r9

	movq 0x30(%rsp), %r10	# n
	movq %r10, %r11		# n
	andq $3, %r10		# mod = n & 3
	shrq $2, %r11		# div = n >> 2
	movq %r10, 0x50(%rsp)	# mod
	movq %r11, 0x58(%rsp)	# div

	movq 0x10(%rsp), %rsi 	# In0 = _In0
	movq 0x18(%rsp), %r8 	# In1 = _In1

	movq 0x28(%rsp), %r10 	# for (i = k; i; i--)
	test %r10, %r10
	je 3f
	.p2align 5,,16
	.p2align 4
0:
	movq 0x08(%rsp), %rax 	# out = Out
	movsd 0(%rsi), %xmm4	# in0 = *In0
	unpcklpd %xmm4, %xmm4
	addq $8, %rsi   	# In0 ++
	movq %r8, %rdi  	# in1 = In1
	addq %r9, %r8   	# In1 += In1s

	movq 0x58(%rsp), %r11  # for (j = div; j; j--)
	test %r11, %r11
	je 2f
	.p2align 6
1:

	#(out + 0) += in0 * *(in1 + 0);
	#(out + 1) += in0 * *(in1 + 1);
	#(out + 2) += in0 * *(in1 + 2);
	#(out + 3) += in0 * *(in1 + 3);
	movupd 0 (%rax), %xmm0
	movupd 16(%rax), %xmm1
	movupd 0 (%rdi), %xmm8
	movupd 16(%rdi), %xmm9
	mulpd  %xmm4, %xmm8
	mulpd  %xmm4, %xmm9
	addpd  %xmm8, %xmm0
	addpd  %xmm9, %xmm1
	movups %xmm0, 0 (%rax)
	movups %xmm1, 16(%rax)
	addq $32, %rax   	# out += 4
	addq $32, %rdi   	# in1 += 4

	subq $1, %r11   	# }
	jnz 1b
2:
	subq $1, %r10     	# }
	jnz 0b 
3: 
	movq 0x50(%rsp), %r8	# mod
	test %r8, %r8		# if (mod)
	je 4f

	movq 0x30(%rsp), %r11   # n
	subq %r8, %r11		# div = n - mod
	shlq $3, %r11
	
	# Out _In0 _In1 k   n   In1s
	# rdi rsi  rdx  rcx r8  r9 

	#rmdot_product_1x2(Out + div, _In0, _In1 + div, k, mod, In1s)
	movq 0x08(%rsp), %rdi
	addq %r11, %rdi
	movq 0x10(%rsp), %rsi
	movq 0x18(%rsp), %rdx
	addq %r11, %rdx
	movq 0x28(%rsp), %rcx
	movq 0x78(%rsp), %r9
	call rmdot_product_double_1x2

4:
	movq %rbp, %rsp
	pop %r15
	pop %r14
	pop %r13
	pop %r12
	pop %rbx
	pop %rbp
	pop %rsp
	ret


