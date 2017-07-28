
	.globl vmdot_product_double_2x1
	.globl vmdot_product_double_2x2
	.globl vmdot_product_double_2x4
	.globl vmdot_product_double_2x8
	.globl vmdot_product_double_2x16
	.globl vmdot_product_double_2x32

	.text

//------------------------------------------------------------------------------
vmdot_product_double_2x1:
	mov 0x08(%rsp), %r10
	mov 0x10(%rsp), %r11
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

	# Out _In0 _In1 k   n   In0S In0s In1s
	# rdi rsi  rdx  rcx r8  r9   r10  r11 

	movq %rdi, 0x08(%rsp) 	# Out
	movq %rsi, 0x10(%rsp) 	# In0
	movq %rdx, 0x18(%rsp) 	# _In1
	movq %rcx, 0x28(%rsp) 	# k
	movq %r8 , 0x30(%rsp) 	# n
	shlq $3, %r9		# In0S
	movq %r9 , 0x60(%rsp)
	shlq $3, %r10		# In0s
	movq %r10, 0x68(%rsp)
	movq %r11, 0x78(%rsp)	# In1s
	movq %r11, %r9	
	shlq $3, %r9

	movq 0x08(%rsp), %rdi	# Out0 = Out
	movq %rdi, 0x80(%rsp)
	addq %r9, %rdi		# Out1 = Out + In1s;
	movq %rdi, 0x88(%rsp)
	movq 0x10(%rsp), %rsi 	# in0 = In0
	movq 0x18(%rsp), %r8	# In1 = _In1

	movq 0x28(%rsp), %r10 	# for (i = k; i; i--)
	test %r10, %r10
	je 3f
0:
	movq 0x80(%rsp), %rax		# out0 = Out0
	movq 0x88(%rsp), %rbx		# out1 = Out1
	movsd 0(%rsi), %xmm8		# in0_0 = *In0
	movq 0x60(%rsp), %r11		# j = In0S
	movsd (%rsi, %r11), %xmm9	# in0_1 = *(in0 + j)
	addq 0x68(%rsp), %rsi		# in0 += In0s
	movq %r8, %rdi			# in1 = In1
	addq %r9, %r8			# In1 += In1s

	movq 0x30(%rsp), %r11	# for (j = n; j; j--)
	test %r11, %r11
	je 2f
1:
	# in1_0 = *(in1 + 0)
	movsd 0 (%rdi), %xmm4
	movsd %xmm4, %xmm12

	# *(out0 +  0) += in0_0 * in1_0; 
	movsd 0 (%rax), %xmm0
	mulsd %xmm8, %xmm4
	addsd %xmm4, %xmm0
	movsd %xmm0, 0 (%rax)

	# *(out1 +  0) += in0_1 * in1_0; 
	movsd 0 (%rbx), %xmm0
	mulsd %xmm9, %xmm12
	addsd %xmm12, %xmm0
	movsd %xmm0, 0 (%rbx)

	addq $8, %rax	# out0 ++
	addq $8, %rbx	# out1 ++
	addq $8, %rdi	# in1 ++

	subq $1, %r11	# }
	jnz 1b
2:
	subq $1, %r10	# }
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
vmdot_product_double_2x2:
	mov 0x08(%rsp), %r10
	mov 0x10(%rsp), %r11
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

	# Out _In0 _In1 k   n   In0S In0s In1s
	# rdi rsi  rdx  rcx r8  r9   r10  r11 
	movq %rdi, 0x08(%rsp) 	# Out
	movq %rsi, 0x10(%rsp) 	# In0
	movq %rdx, 0x18(%rsp) 	# _In1
	movq %rcx, 0x28(%rsp) 	# k
	movq %r8 , 0x30(%rsp) 	# n
	shlq $3, %r9		# In0S
	movq %r9 , 0x60(%rsp)
	shlq $3, %r10		# In0s
	movq %r10, 0x68(%rsp)
	movq %r11, 0x78(%rsp)	# In1s
	movq %r11, %r9	
	shlq $3, %r9

	movq 0x08(%rsp), %rdi	# Out0 = Out
	movq %rdi, 0x80(%rsp)
	addq %r9, %rdi		# Out1 = Out + In1s;
	movq %rdi, 0x88(%rsp)
	movq 0x10(%rsp), %rsi 	# in0 = In0
	movq 0x18(%rsp), %r8	# In1 = _In1

	movq 0x30(%rsp), %r10	# n
	movq %r10, %r11
	andq $1, %r10		# mod = n & 1
	shrq $1, %r11		# div = n >> 1
	movq %r10, 0x40(%rsp)	# mod
	movq %r11, 0x48(%rsp)	# div

	movq 0x28(%rsp), %r10 	# for (i = k; i; i--)
	test %r10, %r10
	je 3f
	.p2align 5,,16
	.p2align 4
0:

	movq 0x80(%rsp), %rax		# out0 = Out0
	movq 0x88(%rsp), %rbx		# out1 = Out1
	movsd 0(%rsi), %xmm8		# in0_0 = *In0
	unpcklpd %xmm8, %xmm8
	movq 0x60(%rsp), %r11		# j = In0S
	movsd (%rsi, %r11), %xmm9	# in0_1 = *(in0 + j)
	unpcklpd %xmm9, %xmm9
	addq 0x68(%rsp), %rsi		# in0 += In0s
	movq %r8, %rdi			# in1 = In1
	addq %r9, %r8			# In1 += In1s

	movq 0x48(%rsp), %r11  		# for (j = div; j; j--)
	test %r11, %r11
	je 2f
	.p2align 6
1:
	# in1_0 = *(in1 + 0)
	# in1_1 = *(in1 + 0)
	movupd 0 (%rdi), %xmm4
	movapd %xmm4, %xmm12

	# *(out0 +  0) += in0_0 * in1_0; 
	movupd 0 (%rax), %xmm0
	mulpd  %xmm8, %xmm4
	addpd  %xmm4, %xmm0
	movupd %xmm0, 0 (%rax)

	# *(out1 +  0) += in0_1 * in1_0; 
	movupd 0 (%rbx), %xmm0
	mulpd  %xmm9, %xmm12
	addpd  %xmm12, %xmm0
	movupd %xmm0, 0 (%rbx)

	addq $16, %rax   	# out0 += 2
	addq $16, %rbx   	# out1 += 2
	addq $16, %rdi   	# in1 += 2

	subq $1, %r11   	# }
	jnz 1b
2:
	subq $1, %r10     	# }
	jnz 0b 
3: 
	movq 0x40(%rsp), %r8	# mod
	test %r8, %r8		# if (mod)
	je 4f

	movq 0x30(%rsp), %rbx   # n
	subq %r8, %rbx		# div = n - mod
	shlq $3, %rbx
	
	# Out _In0 _In1 k   n   In0S In0s In1s
	# rdi rsi  rdx  rcx r8  r9   r10  r11 

	# vmdot_product_2x1(Out + div, In0, _In1 + div, k, mod, In0S, In0s, In1s);
	movq 0x08(%rsp), %rdi
	addq %rbx, %rdi
	movq 0x10(%rsp), %rsi
	movq 0x18(%rsp), %rdx
	addq %rbx, %rdx
	movq 0x28(%rsp), %rcx
	movq 0x60(%rsp), %r9
	shrq $3, %r9
	movq 0x68(%rsp), %r10
	shrq $3, %r10
	movq 0x78(%rsp), %r11
	movq %r10, 0x08(%rsp)
	movq %r11, 0x10(%rsp)
	addq $8, %rsp
	call vmdot_product_double_2x1

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
vmdot_product_double_2x4:
	mov 0x08(%rsp), %r10
	mov 0x10(%rsp), %r11
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

	# Out _In0 _In1 k   n   In0S In0s In1s
	# rdi rsi  rdx  rcx r8  r9   r10  r11 
	movq %rdi, 0x08(%rsp) 	# Out
	movq %rsi, 0x10(%rsp) 	# In0
	movq %rdx, 0x18(%rsp) 	# _In1
	movq %rcx, 0x28(%rsp) 	# k
	movq %r8 , 0x30(%rsp) 	# n
	shlq $3, %r9		# In0S
	movq %r9 , 0x60(%rsp)
	shlq $3, %r10		# In0s
	movq %r10, 0x68(%rsp)
	movq %r11, 0x78(%rsp)	# In1s
	movq %r11, %r9	
	shlq $3, %r9

	movq 0x08(%rsp), %rdi	# Out0 = Out
	movq %rdi, 0x80(%rsp)
	addq %r9, %rdi		# Out1 = Out + In1s;
	movq %rdi, 0x88(%rsp)
	movq 0x10(%rsp), %rsi 	# in0 = In0
	movq 0x18(%rsp), %r8	# In1 = _In1

	movq 0x30(%rsp), %r10	# n
	movq %r10, %r11
	andq $3, %r10		# mod = n & 3
	shrq $2, %r11		# div = n >> 2
	movq %r10, 0x40(%rsp)	# mod
	movq %r11, 0x48(%rsp)	# div

	movq 0x28(%rsp), %r10 	# for (i = k; i; i--)
	test %r10, %r10
	je 3f
	.p2align 5,,16
	.p2align 4
0:

	movq 0x80(%rsp), %rax		# out0 = Out0
	movq 0x88(%rsp), %rbx		# out1 = Out1
	movsd 0(%rsi), %xmm8		# in0_0 = *In0
	unpcklpd %xmm8, %xmm8
	movq 0x60(%rsp), %r11		# j = In0S
	movsd (%rsi, %r11), %xmm9	# in0_1 = *(in0 + j)
	unpcklpd %xmm9, %xmm9
	addq 0x68(%rsp), %rsi		# in0 += In0s
	movq %r8, %rdi			# in1 = In1
	addq %r9, %r8			# In1 += In1s

	movq 0x48(%rsp), %r11  		# for (j = div; j; j--)
	test %r11, %r11
	je 2f
	.p2align 6
1:
	# in1_0 = *(in1 + 0)
	# in1_1 = *(in1 + 1)
	# in1_2 = *(in1 + 2)
	# in1_3 = *(in1 + 3)
	movupd 0 (%rdi), %xmm4
	movapd %xmm4, %xmm12
	movupd 16(%rdi), %xmm5
	movapd %xmm5, %xmm13

	# *(out0 +  0) += in0_0 * in1_0; 
	# *(out0 +  1) += in0_0 * in1_1; 
	# *(out0 +  2) += in0_0 * in1_2; 
	# *(out0 +  3) += in0_0 * in1_3; 
	movupd 0 (%rax), %xmm0
	movupd 16(%rax), %xmm1

	mulpd %xmm8, %xmm4
	addpd %xmm4, %xmm0
	mulpd %xmm8, %xmm5
	addpd %xmm5, %xmm1

	movupd %xmm0, 0 (%rax)
	movupd %xmm1, 16(%rax)

	# *(out1 +  0) += in0_1 * in1_0; 
	# *(out1 +  1) += in0_1 * in1_1; 
	# *(out1 +  2) += in0_1 * in1_2; 
	# *(out1 +  3) += in0_1 * in1_3; 
	movupd 0 (%rbx), %xmm0
	movupd 16(%rbx), %xmm1

	mulpd %xmm9, %xmm4
	addpd %xmm4, %xmm0
	mulpd %xmm9, %xmm5
	addpd %xmm5, %xmm1

	movupd %xmm0, 0 (%rbx)
	movupd %xmm1, 16(%rbx)

	addq $32, %rax   	# out0 += 4
	addq $32, %rbx   	# out1 += 4
	addq $32, %rdi   	# in1 += 4

	subq $1, %r11   	# }
	jnz 1b
2:
	subq $1, %r10     	# }
	jnz 0b 
3: 
	movq 0x40(%rsp), %r8	# mod
	test %r8, %r8		# if (mod)
	je 4f

	movq 0x30(%rsp), %rbx   # n
	subq %r8, %rbx		# div = n - mod
	shlq $3, %rbx
	
	# Out _In0 _In1 k   n   In0S In0s In1s
	# rdi rsi  rdx  rcx r8  r9   r10  r11 

	# vmdot_product_2x2(Out + div, In0, _In1 + div, k, mod, In0S, In0s, In1s);
	movq 0x08(%rsp), %rdi
	addq %rbx, %rdi
	movq 0x10(%rsp), %rsi
	movq 0x18(%rsp), %rdx
	addq %rbx, %rdx
	movq 0x28(%rsp), %rcx
	movq 0x60(%rsp), %r9
	shrq $3, %r9
	movq 0x68(%rsp), %r10
	shrq $3, %r10
	movq 0x78(%rsp), %r11
	movq %r10, 0x08(%rsp)
	movq %r11, 0x10(%rsp)
	addq $8, %rsp
	call vmdot_product_double_2x2

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

