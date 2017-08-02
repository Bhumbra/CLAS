
	.globl vmdot_product_double_8x1
	.globl vmdot_product_double_8x2
	.globl vmdot_product_double_8x4
	.globl vmdot_product_double_8x8
	.globl vmdot_product_double_8x8_new
	.globl vmdot_product_double_8x8_exp
	.globl vmdot_product_double_8x16
	.globl vmdot_product_double_8x32
	.globl vmdot_product_double_8x32_new

	.text

//------------------------------------------------------------------------------
vmdot_product_double_8x1:
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

	movq 0x08(%rsp), %rdi	# Out0 = Out + In1s * 0
	movq %rdi, 0x80(%rsp)
	addq %r9, %rdi		# Out1 = Out + In1s * 1
	movq %rdi, 0x88(%rsp)
	addq %r9, %rdi		# Out2 = Out + In1s * 2
	movq %rdi, 0x90(%rsp)
	addq %r9, %rdi		# Out3 = Out + In1s * 3
	movq %rdi, 0x98(%rsp)
	addq %r9, %rdi		# Out4 = Out + In1s * 4
	movq %rdi, 0xA0(%rsp)
	addq %r9, %rdi		# Out5 = Out + In1s * 5
	movq %rdi, 0xA8(%rsp)
	addq %r9, %rdi		# Out6 = Out + In1s * 6
	movq %rdi, 0xB0(%rsp)
	addq %r9, %rdi		# Out7 = Out + In1s * 7
	movq %rdi, 0xB8(%rsp)
	movq 0x10(%rsp), %rsi 	# in0 = In0
	movq 0x18(%rsp), %r8	# In1 = _In1

	movq 0x28(%rsp), %r10 	# for (i = k; i; i--)
	test %r10, %r10
	je 3f
0:
	movq 0x80(%rsp), %rax		# out0 = Out0
	movq 0x88(%rsp), %rbx		# out1 = Out1
	movq 0x90(%rsp), %rcx		# out2 = Out2
	movq 0x98(%rsp), %rdx		# out3 = Out3
	movq 0xA0(%rsp), %r12		# out4 = Out4
	movq 0xA8(%rsp), %r13		# out5 = Out5
	movq 0xB0(%rsp), %r14		# out6 = Out6
	movq 0xB8(%rsp), %r15		# out7 = Out7
	movsd 0(%rsi), %xmm8		# in0_0 = *In0
	movq 0x60(%rsp), %r11		# j = In0S
	movsd (%rsi, %r11), %xmm9	# in0_1 = *(in0 + j)
	addq 0x60(%rsp), %r11		# j += In0S
	movsd (%rsi, %r11), %xmm10	# in0_2 = *(in0 + j)
	addq 0x60(%rsp), %r11		# j += In0S
	movsd (%rsi, %r11), %xmm11	# in0_3 = *(in0 + j)
	addq 0x60(%rsp), %r11		# j += In0S
	movsd (%rsi, %r11), %xmm12	# in0_4 = *(in0 + j)
	addq 0x60(%rsp), %r11		# j += In0S
	movsd (%rsi, %r11), %xmm13	# in0_5 = *(in0 + j)
	addq 0x60(%rsp), %r11		# j += In0S
	movsd (%rsi, %r11), %xmm14	# in0_6 = *(in0 + j)
	addq 0x60(%rsp), %r11		# j += In0S
	movsd (%rsi, %r11), %xmm15	# in0_7 = *(in0 + j)
	addq 0x68(%rsp), %rsi		# in0 += In0s
	movq %r8, %rdi			# in1 = In1
	addq %r9, %r8			# In1 += In1s

	movq 0x30(%rsp), %r11	# for (j = n; j; j--)
	test %r11, %r11
	je 2f
1:
	# in1_0 = *(in1 + 0)
	movsd 0 (%rdi), %xmm4
	movsd %xmm4, %xmm6

	# *(out0 +  0) += in0_0 * in1_0; 
	movsd 0 (%rax), %xmm0
	mulsd %xmm8, %xmm4
	addsd %xmm4, %xmm0
	movsd %xmm0, 0 (%rax)

	# *(out1 +  0) += in0_1 * in1_0; 
	movsd %xmm6, %xmm4
	movsd 0 (%rbx), %xmm0
	mulsd %xmm9, %xmm4
	addsd %xmm4, %xmm0
	movsd %xmm0, 0 (%rbx)

	# *(out2 +  0) += in0_2 * in1_0; 
	movsd %xmm6, %xmm4
	movsd 0 (%rcx), %xmm0
	mulsd %xmm10, %xmm4
	addsd %xmm4, %xmm0
	movsd %xmm0, 0 (%rcx)

	# *(out3 +  0) += in0_3 * in1_0; 
	movsd %xmm6, %xmm4
	movsd 0 (%rdx), %xmm0
	mulsd %xmm11, %xmm4
	addsd %xmm4, %xmm0
	movsd %xmm0, 0 (%rdx)

	# *(out4 +  0) += in0_4 * in1_0; 
	movsd %xmm6, %xmm4
	movsd 0 (%r12), %xmm0
	mulsd %xmm12, %xmm4
	addsd %xmm4, %xmm0
	movsd %xmm0, 0 (%r12)

	# *(out5 +  0) += in0_5 * in1_0; 
	movsd %xmm6, %xmm4
	movsd 0 (%r13), %xmm0
	mulsd %xmm13, %xmm4
	addsd %xmm4, %xmm0
	movsd %xmm0, 0 (%r13)

	# *(out6 +  0) += in0_6 * in1_0; 
	movsd %xmm6, %xmm4
	movsd 0 (%r14), %xmm0
	mulsd %xmm14, %xmm4
	addsd %xmm4, %xmm0
	movsd %xmm0, 0 (%r14)

	# *(out7 +  0) += in0_7 * in1_0; 
	movsd 0 (%r15), %xmm0
	mulsd %xmm15, %xmm6
	addsd %xmm6, %xmm0
	movsd %xmm0, 0 (%r15)

	addq $8, %rax	# out0 ++
	addq $8, %rbx	# out1 ++
	addq $8, %rcx	# out2 ++
	addq $8, %rdx	# out3 ++
	addq $8, %r12	# out4 ++
	addq $8, %r13	# out5 ++
	addq $8, %r14	# out6 ++
	addq $8, %r15	# out7 ++
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
vmdot_product_double_8x2:
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

	movq 0x08(%rsp), %rdi	# Out0 = Out + In1s * 0
	movq %rdi, 0x80(%rsp)
	addq %r9, %rdi		# Out1 = Out + In1s * 1
	movq %rdi, 0x88(%rsp)
	addq %r9, %rdi		# Out2 = Out + In1s * 2
	movq %rdi, 0x90(%rsp)
	addq %r9, %rdi		# Out3 = Out + In1s * 3
	movq %rdi, 0x98(%rsp)
	addq %r9, %rdi		# Out4 = Out + In1s * 4
	movq %rdi, 0xA0(%rsp)
	addq %r9, %rdi		# Out5 = Out + In1s * 5
	movq %rdi, 0xA8(%rsp)
	addq %r9, %rdi		# Out6 = Out + In1s * 6
	movq %rdi, 0xB0(%rsp)
	addq %r9, %rdi		# Out7 = Out + In1s * 7
	movq %rdi, 0xB8(%rsp)

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
	movq 0x90(%rsp), %rcx		# out2 = Out2
	movq 0x98(%rsp), %rdx		# out3 = Out3
	movq 0xA0(%rsp), %r12		# out4 = Out4
	movq 0xA8(%rsp), %r13		# out5 = Out5
	movq 0xB0(%rsp), %r14		# out6 = Out6
	movq 0xB8(%rsp), %r15		# out7 = Out7
	movddup 0(%rsi), %xmm8		# in0_0 = *In0
	movq 0x60(%rsp), %r11		# j = In0S
	movddup (%rsi, %r11), %xmm9	# in0_1 = *(in0 + j)
	addq 0x60(%rsp), %r11		# j += In0S
	movddup (%rsi, %r11), %xmm10	# in0_2 = *(in0 + j)
	addq 0x60(%rsp), %r11		# j += In0S
	movddup (%rsi, %r11), %xmm11	# in0_3 = *(in0 + j)
	addq 0x60(%rsp), %r11		# j += In0S
	movddup (%rsi, %r11), %xmm12	# in0_4 = *(in0 + j)
	addq 0x60(%rsp), %r11		# j += In0S
	movddup (%rsi, %r11), %xmm13	# in0_5 = *(in0 + j)
	addq 0x60(%rsp), %r11		# j += In0S
	movddup (%rsi, %r11), %xmm14	# in0_6 = *(in0 + j)
	addq 0x60(%rsp), %r11		# j += In0S
	movddup (%rsi, %r11), %xmm15	# in0_7 = *(in0 + j)
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
	movupd 0 (%rdi), %xmm4
	movapd %xmm4, %xmm6

	# *(out0 +  0) += in0_0 * in1_0; 
	# *(out0 +  1) += in0_0 * in1_1; 
	movupd 0 (%rax), %xmm0
	mulpd %xmm8, %xmm4
	addpd %xmm4, %xmm0
	movupd %xmm0, 0 (%rax)

	# *(out1 +  0) += in0_1 * in1_0; 
	# *(out1 +  1) += in0_1 * in1_1; 
	movapd %xmm6, %xmm4
	movupd 0 (%rbx), %xmm0
	mulpd %xmm9, %xmm4
	addpd %xmm4, %xmm0
	movupd %xmm0, 0 (%rbx)

	# *(out2 +  0) += in0_2 * in1_0; 
	# *(out2 +  1) += in0_2 * in1_1; 
	movapd %xmm6, %xmm4
	movupd 0 (%rcx), %xmm0
	mulpd %xmm10, %xmm4
	addpd %xmm4, %xmm0
	movupd %xmm0, 0 (%rcx)

	# *(out3 +  0) += in0_3 * in1_0; 
	# *(out3 +  1) += in0_3 * in1_1; 
	movapd %xmm6, %xmm4
	movupd 0 (%rdx), %xmm0
	mulpd %xmm11, %xmm4
	addpd %xmm4, %xmm0
	movupd %xmm0, 0 (%rdx)

	# *(out4 +  0) += in0_4 * in1_0; 
	# *(out4 +  1) += in0_4 * in1_1; 
	movapd %xmm6, %xmm4
	movupd 0 (%r12), %xmm0
	mulpd %xmm12, %xmm4
	addpd %xmm4, %xmm0
	movupd %xmm0, 0 (%r12)

	# *(out5 +  0) += in0_5 * in1_0; 
	# *(out5 +  1) += in0_5 * in1_1; 
	movapd %xmm6, %xmm4
	movupd 0 (%r13), %xmm0
	mulpd %xmm13, %xmm4
	addpd %xmm4, %xmm0
	movupd %xmm0, 0 (%r13)

	# *(out6 +  0) += in0_6 * in1_0; 
	# *(out6 +  1) += in0_6 * in1_1; 
	movapd %xmm6, %xmm4
	movupd 0 (%r14), %xmm0
	mulpd %xmm14, %xmm4
	addpd %xmm4, %xmm0
	movupd %xmm0, 0 (%r14)

	# *(out7 +  0) += in0_7 * in1_0; 
	# *(out7 +  1) += in0_7 * in1_1; 
	movupd 0 (%r15), %xmm0
	mulpd %xmm15, %xmm6
	addpd %xmm6, %xmm0
	movupd %xmm0, 0 (%r15)

	addq $16, %rax   	# out0 += 2
	addq $16, %rbx   	# out1 += 2
	addq $16, %rcx   	# out2 += 2
	addq $16, %rdx   	# out3 += 2
	addq $16, %r12   	# out4 += 2
	addq $16, %r13   	# out5 += 2
	addq $16, %r14   	# out6 += 2
	addq $16, %r15   	# out7 += 2
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

	# vmdot_product_8x1(Out + div, In0, _In1 + div, k, mod, In0S, In0s, In1s);
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
	call vmdot_product_double_8x1

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
vmdot_product_double_8x4:
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

	movq 0x08(%rsp), %rdi	# Out0 = Out + In1s * 0
	movq %rdi, 0x80(%rsp)
	addq %r9, %rdi		# Out1 = Out + In1s * 1
	movq %rdi, 0x88(%rsp)
	addq %r9, %rdi		# Out2 = Out + In1s * 2
	movq %rdi, 0x90(%rsp)
	addq %r9, %rdi		# Out3 = Out + In1s * 3
	movq %rdi, 0x98(%rsp)
	addq %r9, %rdi		# Out4 = Out + In1s * 4
	movq %rdi, 0xA0(%rsp)
	addq %r9, %rdi		# Out5 = Out + In1s * 5
	movq %rdi, 0xA8(%rsp)
	addq %r9, %rdi		# Out6 = Out + In1s * 6
	movq %rdi, 0xB0(%rsp)
	addq %r9, %rdi		# Out7 = Out + In1s * 7
	movq %rdi, 0xB8(%rsp)

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
	movq 0x90(%rsp), %rcx		# out2 = Out2
	movq 0x98(%rsp), %rdx		# out3 = Out3
	movq 0xA0(%rsp), %r12		# out4 = Out4
	movq 0xA8(%rsp), %r13		# out5 = Out5
	movq 0xB0(%rsp), %r14		# out6 = Out6
	movq 0xB8(%rsp), %r15		# out7 = Out7
	movddup 0(%rsi), %xmm8		# in0_0 = *In0
	movq 0x60(%rsp), %r11		# j = In0S
	movddup (%rsi, %r11), %xmm9	# in0_1 = *(in0 + j)
	addq 0x60(%rsp), %r11		# j += In0S
	movddup (%rsi, %r11), %xmm10	# in0_2 = *(in0 + j)
	addq 0x60(%rsp), %r11		# j += In0S
	movddup (%rsi, %r11), %xmm11	# in0_3 = *(in0 + j)
	addq 0x60(%rsp), %r11		# j += In0S
	movddup (%rsi, %r11), %xmm12	# in0_4 = *(in0 + j)
	addq 0x60(%rsp), %r11		# j += In0S
	movddup (%rsi, %r11), %xmm13	# in0_5 = *(in0 + j)
	addq 0x60(%rsp), %r11		# j += In0S
	movddup (%rsi, %r11), %xmm14	# in0_6 = *(in0 + j)
	addq 0x60(%rsp), %r11		# j += In0S
	movddup (%rsi, %r11), %xmm15	# in0_7 = *(in0 + j)
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
	movapd %xmm4, %xmm6
	movupd 16(%rdi), %xmm5
	movapd %xmm5, %xmm7

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
	movapd %xmm6, %xmm4
	movapd %xmm7, %xmm5

	movupd 0 (%rbx), %xmm0
	movupd 16(%rbx), %xmm1

	mulpd %xmm9, %xmm4
	addpd %xmm4, %xmm0
	mulpd %xmm9, %xmm5
	addpd %xmm5, %xmm1

	movupd %xmm0, 0 (%rbx)
	movupd %xmm1, 16(%rbx)

	# *(out2 +  0) += in0_2 * in1_0; 
	# *(out2 +  1) += in0_2 * in1_1; 
	# *(out2 +  2) += in0_2 * in1_2; 
	# *(out2 +  3) += in0_2 * in1_3; 
	movapd %xmm6, %xmm4
	movapd %xmm7, %xmm5

	movupd 0 (%rcx), %xmm0
	movupd 16(%rcx), %xmm1

	mulpd %xmm10, %xmm4
	addpd %xmm4, %xmm0
	mulpd %xmm10, %xmm5
	addpd %xmm5, %xmm1

	movupd %xmm0, 0 (%rcx)
	movupd %xmm1, 16(%rcx)

	# *(out3 +  0) += in0_3 * in1_0; 
	# *(out3 +  1) += in0_3 * in1_1; 
	# *(out3 +  2) += in0_3 * in1_2; 
	# *(out3 +  3) += in0_3 * in1_3; 
	movapd %xmm6, %xmm4
	movapd %xmm7, %xmm5

	movupd 0 (%rdx), %xmm0
	movupd 16(%rdx), %xmm1

	mulpd %xmm11, %xmm4
	addpd %xmm4, %xmm0
	mulpd %xmm11, %xmm5
	addpd %xmm5, %xmm1

	movupd %xmm0, 0 (%rdx)
	movupd %xmm1, 16(%rdx)

	# *(out4 +  0) += in0_4 * in1_0; 
	# *(out4 +  1) += in0_4 * in1_1; 
	# *(out4 +  2) += in0_4 * in1_2; 
	# *(out4 +  3) += in0_4 * in1_3; 
	movapd %xmm6, %xmm4
	movapd %xmm7, %xmm5

	movupd 0 (%r12), %xmm0
	movupd 16(%r12), %xmm1

	mulpd %xmm12, %xmm4
	addpd %xmm4, %xmm0
	mulpd %xmm12, %xmm5
	addpd %xmm5, %xmm1

	movupd %xmm0, 0 (%r12)
	movupd %xmm1, 16(%r12)

	# *(out5 +  0) += in0_5 * in1_0; 
	# *(out5 +  1) += in0_5 * in1_1; 
	# *(out5 +  2) += in0_5 * in1_2; 
	# *(out5 +  3) += in0_5 * in1_3; 
	movapd %xmm6, %xmm4
	movapd %xmm7, %xmm5

	movupd 0 (%r13), %xmm0
	movupd 16(%r13), %xmm1

	mulpd %xmm13, %xmm4
	addpd %xmm4, %xmm0
	mulpd %xmm13, %xmm5
	addpd %xmm5, %xmm1

	movupd %xmm0, 0 (%r13)
	movupd %xmm1, 16(%r13)

	# *(out6 +  0) += in0_6 * in1_0; 
	# *(out6 +  1) += in0_6 * in1_1; 
	# *(out6 +  2) += in0_6 * in1_2; 
	# *(out6 +  3) += in0_6 * in1_3; 
	movapd %xmm6, %xmm4
	movapd %xmm7, %xmm5

	movupd 0 (%r14), %xmm0
	movupd 16(%r14), %xmm1

	mulpd %xmm14, %xmm4
	addpd %xmm4, %xmm0
	mulpd %xmm14, %xmm5
	addpd %xmm5, %xmm1

	movupd %xmm0, 0 (%r14)
	movupd %xmm1, 16(%r14)

	# *(out7 +  0) += in0_7 * in1_0; 
	# *(out7 +  1) += in0_7 * in1_1; 
	# *(out7 +  2) += in0_7 * in1_2; 
	# *(out7 +  3) += in0_7 * in1_3; 
	movupd 0 (%r15), %xmm0
	movupd 16(%r15), %xmm1

	mulpd %xmm15, %xmm6
	addpd %xmm6, %xmm0
	mulpd %xmm15, %xmm7
	addpd %xmm7, %xmm1

	movupd %xmm0, 0 (%r15)
	movupd %xmm1, 16(%r15)

	addq $32, %rax   	# out0 += 4
	addq $32, %rbx   	# out1 += 4
	addq $32, %rcx   	# out2 += 4
	addq $32, %rdx   	# out3 += 4
	addq $32, %r12   	# out4 += 4
	addq $32, %r13   	# out5 += 4
	addq $32, %r14   	# out6 += 4
	addq $32, %r15   	# out7 += 4
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

	# vmdot_product_8x2(Out + div, In0, _In1 + div, k, mod, In0S, In0s, In1s);
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
	call vmdot_product_double_8x2

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
vmdot_product_double_8x8:
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

	movq 0x08(%rsp), %rdi	# Out0 = Out + In1s * 0
	movq %rdi, 0x80(%rsp)
	addq %r9, %rdi		# Out1 = Out + In1s * 1
	movq %rdi, 0x88(%rsp)
	addq %r9, %rdi		# Out2 = Out + In1s * 2
	movq %rdi, 0x90(%rsp)
	addq %r9, %rdi		# Out3 = Out + In1s * 3
	movq %rdi, 0x98(%rsp)
	addq %r9, %rdi		# Out4 = Out + In1s * 4
	movq %rdi, 0xA0(%rsp)
	addq %r9, %rdi		# Out5 = Out + In1s * 5
	movq %rdi, 0xA8(%rsp)
	addq %r9, %rdi		# Out6 = Out + In1s * 6
	movq %rdi, 0xB0(%rsp)
	addq %r9, %rdi		# Out7 = Out + In1s * 7
	movq %rdi, 0xB8(%rsp)

	movq 0x10(%rsp), %rsi 	# in0 = In0
	movq 0x18(%rsp), %r8	# In1 = _In1

	movq 0x30(%rsp), %r10	# n
	movq %r10, %r11
	andq $7, %r10		# mod = n & 7
	shrq $3, %r11		# div = n >> 3
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
	movq 0x90(%rsp), %rcx		# out2 = Out2
	movq 0x98(%rsp), %rdx		# out3 = Out3
	movq 0xA0(%rsp), %r12		# out4 = Out4
	movq 0xA8(%rsp), %r13		# out5 = Out5
	movq 0xB0(%rsp), %r14		# out6 = Out6
	movq 0xB8(%rsp), %r15		# out7 = Out7
	movddup 0(%rsi), %xmm8		# in0_0 = *In0
	movq 0x60(%rsp), %r11		# j = In0S
	movddup (%rsi, %r11), %xmm9	# in0_1 = *(in0 + j)
	addq 0x60(%rsp), %r11		# j += In0S
	movddup (%rsi, %r11), %xmm10	# in0_2 = *(in0 + j)
	addq 0x60(%rsp), %r11		# j += In0S
	movddup (%rsi, %r11), %xmm11	# in0_3 = *(in0 + j)
	addq 0x60(%rsp), %r11		# j += In0S
	movddup (%rsi, %r11), %xmm12	# in0_4 = *(in0 + j)
	addq 0x60(%rsp), %r11		# j += In0S
	movddup (%rsi, %r11), %xmm13	# in0_5 = *(in0 + j)
	addq 0x60(%rsp), %r11		# j += In0S
	movddup (%rsi, %r11), %xmm14	# in0_6 = *(in0 + j)
	addq 0x60(%rsp), %r11		# j += In0S
	movddup (%rsi, %r11), %xmm15	# in0_7 = *(in0 + j)
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
	# in1_4 = *(in1 + 4)
	# in1_5 = *(in1 + 5)
	# in1_6 = *(in1 + 6)
	# in1_7 = *(in1 + 7)
	movupd 0 (%rdi), %xmm4
	movapd %xmm4, 0xC0(%rsp)
	movupd 16(%rdi), %xmm5
	movapd %xmm5, 0xD0(%rsp)
	movupd 32(%rdi), %xmm6
	movapd %xmm6, 0xE0(%rsp)
	movupd 48(%rdi), %xmm7
	movapd %xmm7, 0xF0(%rsp)

	# *(out0 +  0) += in0_0 * in1_0; 
	# *(out0 +  1) += in0_0 * in1_1; 
	# *(out0 +  2) += in0_0 * in1_2; 
	# *(out0 +  3) += in0_0 * in1_3; 
	# *(out0 +  4) += in0_0 * in1_4; 
	# *(out0 +  5) += in0_0 * in1_5; 
	# *(out0 +  6) += in0_0 * in1_6; 
	# *(out0 +  7) += in0_0 * in1_7; 
	movupd 0 (%rax), %xmm0
	movupd 16(%rax), %xmm1
	movupd 32(%rax), %xmm2
	movupd 48(%rax), %xmm3

	mulpd %xmm8, %xmm4
	addpd %xmm4, %xmm0
	mulpd %xmm8, %xmm5
	addpd %xmm5, %xmm1
	mulpd %xmm8, %xmm6
	addpd %xmm6, %xmm2
	mulpd %xmm8, %xmm7
	addpd %xmm7, %xmm3

	movupd %xmm0, 0 (%rax)
	movupd %xmm1, 16(%rax)
	movupd %xmm2, 32(%rax)
	movupd %xmm3, 48(%rax)

	# *(out1 +  0) += in0_1 * in1_0; 
	# *(out1 +  1) += in0_1 * in1_1; 
	# *(out1 +  2) += in0_1 * in1_2; 
	# *(out1 +  3) += in0_1 * in1_3; 
	# *(out1 +  4) += in0_1 * in1_4; 
	# *(out1 +  5) += in0_1 * in1_5; 
	# *(out1 +  6) += in0_1 * in1_6; 
	# *(out1 +  7) += in0_1 * in1_7; 
	movapd 0xC0(%rsp), %xmm4
	movapd 0xD0(%rsp), %xmm5
	movapd 0xE0(%rsp), %xmm6
	movapd 0xF0(%rsp), %xmm7

	movupd 0 (%rbx), %xmm0
	movupd 16(%rbx), %xmm1
	movupd 32(%rbx), %xmm2
	movupd 48(%rbx), %xmm3

	mulpd %xmm9, %xmm4
	addpd %xmm4, %xmm0
	mulpd %xmm9, %xmm5
	addpd %xmm5, %xmm1
	mulpd %xmm9, %xmm6
	addpd %xmm6, %xmm2
	mulpd %xmm9, %xmm7
	addpd %xmm7, %xmm3

	movupd %xmm0, 0 (%rbx)
	movupd %xmm1, 16(%rbx)
	movupd %xmm2, 32(%rbx)
	movupd %xmm3, 48(%rbx)

	# *(out2 +  0) += in0_2 * in1_0; 
	# *(out2 +  1) += in0_2 * in1_1; 
	# *(out2 +  2) += in0_2 * in1_2; 
	# *(out2 +  3) += in0_2 * in1_3; 
	# *(out2 +  4) += in0_2 * in1_4; 
	# *(out2 +  5) += in0_2 * in1_5; 
	# *(out2 +  6) += in0_2 * in1_6; 
	# *(out2 +  7) += in0_2 * in1_7; 
	movapd 0xC0(%rsp), %xmm4
	movapd 0xD0(%rsp), %xmm5
	movapd 0xE0(%rsp), %xmm6
	movapd 0xF0(%rsp), %xmm7

	movupd 0 (%rcx), %xmm0
	movupd 16(%rcx), %xmm1
	movupd 32(%rcx), %xmm2
	movupd 48(%rcx), %xmm3

	mulpd %xmm10, %xmm4
	addpd %xmm4, %xmm0
	mulpd %xmm10, %xmm5
	addpd %xmm5, %xmm1
	mulpd %xmm10, %xmm6
	addpd %xmm6, %xmm2
	mulpd %xmm10, %xmm7
	addpd %xmm7, %xmm3

	movupd %xmm0, 0 (%rcx)
	movupd %xmm1, 16(%rcx)
	movupd %xmm2, 32(%rcx)
	movupd %xmm3, 48(%rcx)

	# *(out3 +  0) += in0_3 * in1_0; 
	# *(out3 +  1) += in0_3 * in1_1; 
	# *(out3 +  2) += in0_3 * in1_2; 
	# *(out3 +  3) += in0_3 * in1_3; 
	# *(out3 +  4) += in0_3 * in1_4; 
	# *(out3 +  5) += in0_3 * in1_5; 
	# *(out3 +  6) += in0_3 * in1_6; 
	# *(out3 +  7) += in0_3 * in1_7; 
	movapd 0xC0(%rsp), %xmm4
	movapd 0xD0(%rsp), %xmm5
	movapd 0xE0(%rsp), %xmm6
	movapd 0xF0(%rsp), %xmm7

	movupd 0 (%rdx), %xmm0
	movupd 16(%rdx), %xmm1
	movupd 32(%rdx), %xmm2
	movupd 48(%rdx), %xmm3

	mulpd %xmm11, %xmm4
	addpd %xmm4, %xmm0
	mulpd %xmm11, %xmm5
	addpd %xmm5, %xmm1
	mulpd %xmm11, %xmm6
	addpd %xmm6, %xmm2
	mulpd %xmm11, %xmm7
	addpd %xmm7, %xmm3

	movupd %xmm0, 0 (%rdx)
	movupd %xmm1, 16(%rdx)
	movupd %xmm2, 32(%rdx)
	movupd %xmm3, 48(%rdx)

	# *(out4 +  0) += in0_4 * in1_0; 
	# *(out4 +  1) += in0_4 * in1_1; 
	# *(out4 +  2) += in0_4 * in1_2; 
	# *(out4 +  3) += in0_4 * in1_3; 
	# *(out4 +  4) += in0_4 * in1_4; 
	# *(out4 +  5) += in0_4 * in1_5; 
	# *(out4 +  6) += in0_4 * in1_6; 
	# *(out4 +  7) += in0_4 * in1_7; 
	movapd 0xC0(%rsp), %xmm4
	movapd 0xD0(%rsp), %xmm5
	movapd 0xE0(%rsp), %xmm6
	movapd 0xF0(%rsp), %xmm7

	movupd 0 (%r12), %xmm0
	movupd 16(%r12), %xmm1
	movupd 32(%r12), %xmm2
	movupd 48(%r12), %xmm3

	mulpd %xmm12, %xmm4
	addpd %xmm4, %xmm0
	mulpd %xmm12, %xmm5
	addpd %xmm5, %xmm1
	mulpd %xmm12, %xmm6
	addpd %xmm6, %xmm2
	mulpd %xmm12, %xmm7
	addpd %xmm7, %xmm3

	movupd %xmm0, 0 (%r12)
	movupd %xmm1, 16(%r12)
	movupd %xmm2, 32(%r12)
	movupd %xmm3, 48(%r12)

	# *(out5 +  0) += in0_5 * in1_0; 
	# *(out5 +  1) += in0_5 * in1_1; 
	# *(out5 +  2) += in0_5 * in1_2; 
	# *(out5 +  3) += in0_5 * in1_3; 
	# *(out5 +  4) += in0_5 * in1_4; 
	# *(out5 +  5) += in0_5 * in1_5; 
	# *(out5 +  6) += in0_5 * in1_6; 
	# *(out5 +  7) += in0_5 * in1_7; 
	movapd 0xC0(%rsp), %xmm4
	movapd 0xD0(%rsp), %xmm5
	movapd 0xE0(%rsp), %xmm6
	movapd 0xF0(%rsp), %xmm7

	movupd 0 (%r13), %xmm0
	movupd 16(%r13), %xmm1
	movupd 32(%r13), %xmm2
	movupd 48(%r13), %xmm3

	mulpd %xmm13, %xmm4
	addpd %xmm4, %xmm0
	mulpd %xmm13, %xmm5
	addpd %xmm5, %xmm1
	mulpd %xmm13, %xmm6
	addpd %xmm6, %xmm2
	mulpd %xmm13, %xmm7
	addpd %xmm7, %xmm3

	movupd %xmm0, 0 (%r13)
	movupd %xmm1, 16(%r13)
	movupd %xmm2, 32(%r13)
	movupd %xmm3, 48(%r13)

	# *(out6 +  0) += in0_6 * in1_0; 
	# *(out6 +  1) += in0_6 * in1_1; 
	# *(out6 +  2) += in0_6 * in1_2; 
	# *(out6 +  3) += in0_6 * in1_3; 
	# *(out6 +  4) += in0_6 * in1_4; 
	# *(out6 +  5) += in0_6 * in1_5; 
	# *(out6 +  6) += in0_6 * in1_6; 
	# *(out6 +  7) += in0_6 * in1_7; 
	movapd 0xC0(%rsp), %xmm4
	movapd 0xD0(%rsp), %xmm5
	movapd 0xE0(%rsp), %xmm6
	movapd 0xF0(%rsp), %xmm7

	movupd 0 (%r14), %xmm0
	movupd 16(%r14), %xmm1
	movupd 32(%r14), %xmm2
	movupd 48(%r14), %xmm3

	mulpd %xmm14, %xmm4
	addpd %xmm4, %xmm0
	mulpd %xmm14, %xmm5
	addpd %xmm5, %xmm1
	mulpd %xmm14, %xmm6
	addpd %xmm6, %xmm2
	mulpd %xmm14, %xmm7
	addpd %xmm7, %xmm3

	movupd %xmm0, 0 (%r14)
	movupd %xmm1, 16(%r14)
	movupd %xmm2, 32(%r14)
	movupd %xmm3, 48(%r14)

	# *(out7 +  0) += in0_7 * in1_0; 
	# *(out7 +  1) += in0_7 * in1_1; 
	# *(out7 +  2) += in0_7 * in1_2; 
	# *(out7 +  3) += in0_7 * in1_3; 
	# *(out7 +  4) += in0_7 * in1_4; 
	# *(out7 +  5) += in0_7 * in1_5; 
	# *(out7 +  6) += in0_7 * in1_6; 
	# *(out7 +  7) += in0_7 * in1_7; 
	movapd 0xC0(%rsp), %xmm4
	movapd 0xD0(%rsp), %xmm5
	movapd 0xE0(%rsp), %xmm6
	movapd 0xF0(%rsp), %xmm7

	movupd 0 (%r15), %xmm0
	movupd 16(%r15), %xmm1
	movupd 32(%r15), %xmm2
	movupd 48(%r15), %xmm3

	mulpd %xmm15, %xmm4
	addpd %xmm4, %xmm0
	mulpd %xmm15, %xmm5
	addpd %xmm5, %xmm1
	mulpd %xmm15, %xmm6
	addpd %xmm6, %xmm2
	mulpd %xmm15, %xmm7
	addpd %xmm7, %xmm3

	movupd %xmm0, 0 (%r15)
	movupd %xmm1, 16(%r15)
	movupd %xmm2, 32(%r15)
	movupd %xmm3, 48(%r15)

	addq $64, %rax   	# out0 += 8
	addq $64, %rbx   	# out1 += 8
	addq $64, %rcx   	# out2 += 8
	addq $64, %rdx   	# out3 += 8
	addq $64, %r12   	# out4 += 8
	addq $64, %r13   	# out5 += 8
	addq $64, %r14   	# out6 += 8
	addq $64, %r15   	# out7 += 8
	addq $64, %rdi   	# in1 += 8

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

	# vmdot_product_8x4(Out + div, In0, _In1 + div, k, mod, In0S, In0s, In1s);
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
	call vmdot_product_double_8x4

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
vmdot_product_double_8x8_exp:
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

	movq 0x08(%rsp), %rdi	# Out0 = Out + In1s * 0
	movq %rdi, 0x80(%rsp)
	addq %r9, %rdi		# Out1 = Out + In1s * 1
	movq %rdi, 0x88(%rsp)
	addq %r9, %rdi		# Out2 = Out + In1s * 2
	movq %rdi, 0x90(%rsp)
	addq %r9, %rdi		# Out3 = Out + In1s * 3
	movq %rdi, 0x98(%rsp)
	addq %r9, %rdi		# Out4 = Out + In1s * 4
	movq %rdi, 0xA0(%rsp)
	addq %r9, %rdi		# Out5 = Out + In1s * 5
	movq %rdi, 0xA8(%rsp)
	addq %r9, %rdi		# Out6 = Out + In1s * 6
	movq %rdi, 0xB0(%rsp)
	addq %r9, %rdi		# Out7 = Out + In1s * 7
	movq %rdi, 0xB8(%rsp)

	movq 0x10(%rsp), %rsi 	# in0 = In0
	movq 0x18(%rsp), %r8	# In1 = _In1

	movq 0x30(%rsp), %r10	# n
	movq %r10, %r11
	andq $7, %r10		# mod = n & 7
	shrq $3, %r11		# div = n >> 3
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
	movq 0x90(%rsp), %rcx		# out2 = Out2
	movq 0x98(%rsp), %rdx		# out3 = Out3
	movq 0xA0(%rsp), %r12		# out4 = Out4
	movq 0xA8(%rsp), %r13		# out5 = Out5
	movq 0xB0(%rsp), %r14		# out6 = Out6
	movq 0xB8(%rsp), %r15		# out7 = Out7
	movlpd (%rsi      ), %xmm8	# in0_0 = *In0
	movq 0x60(%rsp), %r11		# j = In0S
	movhpd (%rsi, %r11), %xmm8	# in0_1 = *(in0 + j)
	addq 0x60(%rsp), %r11		# j += In0S
	movlpd (%rsi, %r11), %xmm9	# in0_2 = *(in0 + j)
	addq 0x60(%rsp), %r11		# j += In0S
	movhpd (%rsi, %r11), %xmm9	# in0_3 = *(in0 + j)
	addq 0x60(%rsp), %r11		# j += In0S
	movlpd (%rsi, %r11), %xmm10	# in0_4 = *(in0 + j)
	addq 0x60(%rsp), %r11		# j += In0S
	movhpd (%rsi, %r11), %xmm10	# in0_5 = *(in0 + j)
	addq 0x60(%rsp), %r11		# j += In0S
	movlpd (%rsi, %r11), %xmm11	# in0_6 = *(in0 + j)
	addq 0x60(%rsp), %r11		# j += In0S
	movhpd (%rsi, %r11), %xmm11	# in0_7 = *(in0 + j)
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
	# in1_4 = *(in1 + 4)
	# in1_5 = *(in1 + 5)
	# in1_6 = *(in1 + 6)
	# in1_7 = *(in1 + 7)
	movupd 0 (%rdi), %xmm12
	movupd 16(%rdi), %xmm13
	movupd 32(%rdi), %xmm14
	movupd 48(%rdi), %xmm15

	# *(out0 +  0) += in0_0 * in1_0; 
	# *(out0 +  1) += in0_0 * in1_1; 
	# *(out0 +  2) += in0_0 * in1_2; 
	# *(out0 +  3) += in0_0 * in1_3; 
	# *(out0 +  4) += in0_0 * in1_4; 
	# *(out0 +  5) += in0_0 * in1_5; 
	# *(out0 +  6) += in0_0 * in1_6; 
	# *(out0 +  7) += in0_0 * in1_7; 
	movddup %xmm8, %xmm4
	movapd  %xmm4, %xmm5
	movapd  %xmm4, %xmm6
	movapd  %xmm5, %xmm7
	pshufd  $0x4E, %xmm8, %xmm8

	movupd  0x00(%rax), %xmm0
	movupd  0x10(%rax), %xmm1
	movupd  0x20(%rax), %xmm2
	movupd  0x30(%rax), %xmm3
	mulpd   %xmm12, %xmm4
	addpd   %xmm4, %xmm0
	mulpd   %xmm13, %xmm5
	addpd   %xmm5, %xmm1
	mulpd   %xmm14, %xmm6
	addpd   %xmm6, %xmm2
	mulpd   %xmm15, %xmm7
	addpd   %xmm7, %xmm3
	movupd  %xmm0, 0x00(%rax)
	movupd  %xmm1, 0x10(%rax)
	movupd  %xmm2, 0x20(%rax)
	movupd  %xmm3, 0x30(%rax)

	# *(out1 +  0) += in0_1 * in1_0; 
	# *(out1 +  1) += in0_1 * in1_1; 
	# *(out1 +  2) += in0_1 * in1_2; 
	# *(out1 +  3) += in0_1 * in1_3; 
	# *(out1 +  4) += in0_1 * in1_4; 
	# *(out1 +  5) += in0_1 * in1_5; 
	# *(out1 +  6) += in0_1 * in1_6; 
	# *(out1 +  7) += in0_1 * in1_7; 
	movddup %xmm8, %xmm4
	movapd  %xmm4, %xmm5
	movapd  %xmm4, %xmm6
	movapd  %xmm5, %xmm7
	pshufd  $0x4E, %xmm8, %xmm8

	movupd  0x00(%rbx), %xmm0
	movupd  0x10(%rbx), %xmm1
	movupd  0x20(%rbx), %xmm2
	movupd  0x30(%rbx), %xmm3
	mulpd   %xmm12, %xmm4
	addpd   %xmm4, %xmm0
	mulpd   %xmm13, %xmm5
	addpd   %xmm5, %xmm1
	mulpd   %xmm14, %xmm6
	addpd   %xmm6, %xmm2
	mulpd   %xmm15, %xmm7
	addpd   %xmm7, %xmm3
	movupd  %xmm0, 0x00(%rbx)
	movupd  %xmm1, 0x10(%rbx)
	movupd  %xmm2, 0x20(%rbx)
	movupd  %xmm3, 0x30(%rbx)

	# *(out2 +  0) += in0_2 * in1_0; 
	# *(out2 +  1) += in0_2 * in1_1; 
	# *(out2 +  2) += in0_2 * in1_2; 
	# *(out2 +  3) += in0_2 * in1_3; 
	# *(out2 +  4) += in0_2 * in1_4; 
	# *(out2 +  5) += in0_2 * in1_5; 
	# *(out2 +  6) += in0_2 * in1_6; 
	# *(out2 +  7) += in0_2 * in1_7; 
	movddup %xmm9, %xmm4
	movapd  %xmm4, %xmm5
	movapd  %xmm4, %xmm6
	movapd  %xmm5, %xmm7
	pshufd  $0x4E, %xmm9, %xmm9

	movupd  0x00(%rcx), %xmm0
	movupd  0x10(%rcx), %xmm1
	movupd  0x20(%rcx), %xmm2
	movupd  0x30(%rcx), %xmm3
	mulpd   %xmm12, %xmm4
	addpd   %xmm4, %xmm0
	mulpd   %xmm13, %xmm5
	addpd   %xmm5, %xmm1
	mulpd   %xmm14, %xmm6
	addpd   %xmm6, %xmm2
	mulpd   %xmm15, %xmm7
	addpd   %xmm7, %xmm3
	movupd  %xmm0, 0x00(%rcx)
	movupd  %xmm1, 0x10(%rcx)
	movupd  %xmm2, 0x20(%rcx)
	movupd  %xmm3, 0x30(%rcx)

	# *(out3 +  0) += in0_3 * in1_0; 
	# *(out3 +  1) += in0_3 * in1_1; 
	# *(out3 +  2) += in0_3 * in1_2; 
	# *(out3 +  3) += in0_3 * in1_3; 
	# *(out3 +  4) += in0_3 * in1_4; 
	# *(out3 +  5) += in0_3 * in1_5; 
	# *(out3 +  6) += in0_3 * in1_6; 
	# *(out3 +  7) += in0_3 * in1_7; 
	movddup %xmm9, %xmm4
	movapd  %xmm4, %xmm5
	movapd  %xmm4, %xmm6
	movapd  %xmm5, %xmm7
	pshufd  $0x4E, %xmm9, %xmm9

	movupd  0x00(%rdx), %xmm0
	movupd  0x10(%rdx), %xmm1
	movupd  0x20(%rdx), %xmm2
	movupd  0x30(%rdx), %xmm3
	mulpd   %xmm12, %xmm4
	addpd   %xmm4, %xmm0
	mulpd   %xmm13, %xmm5
	addpd   %xmm5, %xmm1
	mulpd   %xmm14, %xmm6
	addpd   %xmm6, %xmm2
	mulpd   %xmm15, %xmm7
	addpd   %xmm7, %xmm3
	movupd  %xmm0, 0x00(%rdx)
	movupd  %xmm1, 0x10(%rdx)
	movupd  %xmm2, 0x20(%rdx)
	movupd  %xmm3, 0x30(%rdx)

	# *(out4 +  0) += in0_4 * in1_0; 
	# *(out4 +  1) += in0_4 * in1_1; 
	# *(out4 +  2) += in0_4 * in1_2; 
	# *(out4 +  3) += in0_4 * in1_3; 
	# *(out4 +  4) += in0_4 * in1_4; 
	# *(out4 +  5) += in0_4 * in1_5; 
	# *(out4 +  6) += in0_4 * in1_6; 
	# *(out4 +  7) += in0_4 * in1_7; 
	movddup %xmm10, %xmm4
	movapd  %xmm4, %xmm5
	movapd  %xmm4, %xmm6
	movapd  %xmm5, %xmm7
	pshufd  $0x4E, %xmm10, %xmm10

	movupd  0x00(%r12), %xmm0
	movupd  0x10(%r12), %xmm1
	movupd  0x20(%r12), %xmm2
	movupd  0x30(%r12), %xmm3
	mulpd   %xmm12, %xmm4
	addpd   %xmm4, %xmm0
	mulpd   %xmm13, %xmm5
	addpd   %xmm5, %xmm1
	mulpd   %xmm14, %xmm6
	addpd   %xmm6, %xmm2
	mulpd   %xmm15, %xmm7
	addpd   %xmm7, %xmm3
	movupd  %xmm0, 0x00(%r12)
	movupd  %xmm1, 0x10(%r12)
	movupd  %xmm2, 0x20(%r12)
	movupd  %xmm3, 0x30(%r12)

	# *(out5 +  0) += in0_5 * in1_0; 
	# *(out5 +  1) += in0_5 * in1_1; 
	# *(out5 +  2) += in0_5 * in1_2; 
	# *(out5 +  3) += in0_5 * in1_3; 
	# *(out5 +  4) += in0_5 * in1_4; 
	# *(out5 +  5) += in0_5 * in1_5; 
	# *(out5 +  6) += in0_5 * in1_6; 
	# *(out5 +  7) += in0_5 * in1_7; 
	movddup %xmm10, %xmm4
	movapd  %xmm4, %xmm5
	movapd  %xmm4, %xmm6
	movapd  %xmm5, %xmm7
	pshufd  $0x4E, %xmm10, %xmm10

	movupd  0x00(%r13), %xmm0
	movupd  0x10(%r13), %xmm1
	movupd  0x20(%r13), %xmm2
	movupd  0x30(%r13), %xmm3
	mulpd   %xmm12, %xmm4
	addpd   %xmm4, %xmm0
	mulpd   %xmm13, %xmm5
	addpd   %xmm5, %xmm1
	mulpd   %xmm14, %xmm6
	addpd   %xmm6, %xmm2
	mulpd   %xmm15, %xmm7
	addpd   %xmm7, %xmm3
	movupd  %xmm0, 0x00(%r13)
	movupd  %xmm1, 0x10(%r13)
	movupd  %xmm2, 0x20(%r13)
	movupd  %xmm3, 0x30(%r13)

	# *(out6 +  0) += in0_6 * in1_0; 
	# *(out6 +  1) += in0_6 * in1_1; 
	# *(out6 +  2) += in0_6 * in1_2; 
	# *(out6 +  3) += in0_6 * in1_3; 
	# *(out6 +  4) += in0_6 * in1_4; 
	# *(out6 +  5) += in0_6 * in1_5; 
	# *(out6 +  6) += in0_6 * in1_6; 
	# *(out6 +  7) += in0_6 * in1_7; 
	movddup %xmm11, %xmm4
	movapd  %xmm4, %xmm5
	movapd  %xmm4, %xmm6
	movapd  %xmm5, %xmm7
	pshufd  $0x4E, %xmm11, %xmm11

	movupd  0x00(%r14), %xmm0
	movupd  0x10(%r14), %xmm1
	movupd  0x20(%r14), %xmm2
	movupd  0x30(%r14), %xmm3
	mulpd   %xmm12, %xmm4
	addpd   %xmm4, %xmm0
	mulpd   %xmm13, %xmm5
	addpd   %xmm5, %xmm1
	mulpd   %xmm14, %xmm6
	addpd   %xmm6, %xmm2
	mulpd   %xmm15, %xmm7
	addpd   %xmm7, %xmm3
	movupd  %xmm0, 0x00(%r14)
	movupd  %xmm1, 0x10(%r14)
	movupd  %xmm2, 0x20(%r14)
	movupd  %xmm3, 0x30(%r14)

	# *(out7 +  0) += in0_7 * in1_0; 
	# *(out7 +  1) += in0_7 * in1_1; 
	# *(out7 +  2) += in0_7 * in1_2; 
	# *(out7 +  3) += in0_7 * in1_3; 
	# *(out7 +  4) += in0_7 * in1_4; 
	# *(out7 +  5) += in0_7 * in1_5; 
	# *(out7 +  6) += in0_7 * in1_6; 
	# *(out7 +  7) += in0_7 * in1_7; 
	movddup %xmm11, %xmm4
	movapd  %xmm4, %xmm5
	movapd  %xmm4, %xmm6
	movapd  %xmm5, %xmm7
	pshufd  $0x4E, %xmm11, %xmm11

	movupd  0x00(%r15), %xmm0
	movupd  0x10(%r15), %xmm1
	movupd  0x20(%r15), %xmm2
	movupd  0x30(%r15), %xmm3
	mulpd   %xmm12, %xmm4
	addpd   %xmm4, %xmm0
	mulpd   %xmm13, %xmm5
	addpd   %xmm5, %xmm1
	mulpd   %xmm14, %xmm6
	addpd   %xmm6, %xmm2
	mulpd   %xmm15, %xmm7
	addpd   %xmm7, %xmm3
	movupd  %xmm0, 0x00(%r15)
	movupd  %xmm1, 0x10(%r15)
	movupd  %xmm2, 0x20(%r15)
	movupd  %xmm3, 0x30(%r15)

	addq $64, %rax   	# out0 += 8
	addq $64, %rbx   	# out1 += 8
	addq $64, %rcx   	# out2 += 8
	addq $64, %rdx   	# out3 += 8
	addq $64, %r12   	# out4 += 8
	addq $64, %r13   	# out5 += 8
	addq $64, %r14   	# out6 += 8
	addq $64, %r15   	# out7 += 8
	addq $64, %rdi   	# in1 += 8

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

	# vmdot_product_8x4(Out + div, In0, _In1 + div, k, mod, In0S, In0s, In1s);
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
	call vmdot_product_double_8x4

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
vmdot_product_double_8x8_new:
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

	movq 0x08(%rsp), %rdi	# Out0 = Out + In1s * 0
	movq %rdi, 0x80(%rsp)
	addq %r9, %rdi		# Out1 = Out + In1s * 1
	movq %rdi, 0x88(%rsp)
	addq %r9, %rdi		# Out2 = Out + In1s * 2
	movq %rdi, 0x90(%rsp)
	addq %r9, %rdi		# Out3 = Out + In1s * 3
	movq %rdi, 0x98(%rsp)
	addq %r9, %rdi		# Out4 = Out + In1s * 4
	movq %rdi, 0xA0(%rsp)
	addq %r9, %rdi		# Out5 = Out + In1s * 5
	movq %rdi, 0xA8(%rsp)
	addq %r9, %rdi		# Out6 = Out + In1s * 6
	movq %rdi, 0xB0(%rsp)
	addq %r9, %rdi		# Out7 = Out + In1s * 7
	movq %rdi, 0xB8(%rsp)

	movq 0x10(%rsp), %rsi 	# in0 = In0
	movq 0x18(%rsp), %r8	# In1 = _In1

	movq 0x30(%rsp), %r10	# n
	movq %r10, %r11
	andq $7, %r10		# mod = n & 7
	shrq $3, %r11		# div = n >> 3
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
	movq 0x90(%rsp), %rcx		# out2 = Out2
	movq 0x98(%rsp), %rdx		# out3 = Out3
	movq 0xA0(%rsp), %r12		# out4 = Out4
	movq 0xA8(%rsp), %r13		# out5 = Out5
	movq 0xB0(%rsp), %r14		# out6 = Out6
	movq 0xB8(%rsp), %r15		# out7 = Out7
	movlpd (%rsi      ), %xmm8	# in0_0 = *In0
	movq 0x60(%rsp), %r11		# j = In0S
	movhpd (%rsi, %r11), %xmm8	# in0_1 = *(in0 + j)
	addq 0x60(%rsp), %r11		# j += In0S
	movlpd (%rsi, %r11), %xmm9	# in0_2 = *(in0 + j)
	addq 0x60(%rsp), %r11		# j += In0S
	movhpd (%rsi, %r11), %xmm9	# in0_3 = *(in0 + j)
	addq 0x60(%rsp), %r11		# j += In0S
	movlpd (%rsi, %r11), %xmm10	# in0_4 = *(in0 + j)
	addq 0x60(%rsp), %r11		# j += In0S
	movhpd (%rsi, %r11), %xmm10	# in0_5 = *(in0 + j)
	addq 0x60(%rsp), %r11		# j += In0S
	movlpd (%rsi, %r11), %xmm11	# in0_6 = *(in0 + j)
	addq 0x60(%rsp), %r11		# j += In0S
	movhpd (%rsi, %r11), %xmm11	# in0_7 = *(in0 + j)
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
	# in1_4 = *(in1 + 4)
	# in1_5 = *(in1 + 5)
	# in1_6 = *(in1 + 6)
	# in1_7 = *(in1 + 7)
	movupd 0 (%rdi), %xmm12
	movupd 16(%rdi), %xmm13
	movupd 32(%rdi), %xmm14
	movupd 48(%rdi), %xmm15

	# *(out0 +  0) += in0_0 * in1_0; 
	# *(out0 +  1) += in0_0 * in1_1; 
	# *(out0 +  2) += in0_0 * in1_2; 
	# *(out0 +  3) += in0_0 * in1_3; 
	# *(out0 +  4) += in0_0 * in1_4; 
	# *(out0 +  5) += in0_0 * in1_5; 
	# *(out0 +  6) += in0_0 * in1_6; 
	# *(out0 +  7) += in0_0 * in1_7; 
	movddup %xmm8, %xmm4
	movapd  %xmm4, %xmm5
	movapd  %xmm4, %xmm6
	movapd  %xmm5, %xmm7
	pshufd  $0x4E, %xmm8, %xmm8

	movupd  0x00(%rax), %xmm0
	mulpd   %xmm12, %xmm4
	addpd   %xmm4, %xmm0
	movupd  %xmm0, 0x00(%rax)
	movupd  0x10(%rax), %xmm1
	mulpd   %xmm13, %xmm5
	addpd   %xmm5, %xmm1
	movupd  %xmm1, 0x10(%rax)
	movupd  0x20(%rax), %xmm2
	mulpd   %xmm14, %xmm6
	addpd   %xmm6, %xmm2
	movupd  %xmm2, 0x20(%rax)
	movupd  0x30(%rax), %xmm3
	mulpd   %xmm15, %xmm7
	addpd   %xmm7, %xmm3
	movupd  %xmm3, 0x30(%rax)

	# *(out1 +  0) += in0_1 * in1_0; 
	# *(out1 +  1) += in0_1 * in1_1; 
	# *(out1 +  2) += in0_1 * in1_2; 
	# *(out1 +  3) += in0_1 * in1_3; 
	# *(out1 +  4) += in0_1 * in1_4; 
	# *(out1 +  5) += in0_1 * in1_5; 
	# *(out1 +  6) += in0_1 * in1_6; 
	# *(out1 +  7) += in0_1 * in1_7; 
	movddup %xmm8, %xmm4
	movapd  %xmm4, %xmm5
	movapd  %xmm4, %xmm6
	movapd  %xmm5, %xmm7
	pshufd  $0x4E, %xmm8, %xmm8

	movupd  0x00(%rbx), %xmm0
	mulpd   %xmm12, %xmm4
	addpd   %xmm4, %xmm0
	movupd  %xmm0, 0x00(%rbx)
	movupd  0x10(%rbx), %xmm1
	mulpd   %xmm13, %xmm5
	addpd   %xmm5, %xmm1
	movupd  %xmm1, 0x10(%rbx)
	movupd  0x20(%rbx), %xmm2
	mulpd   %xmm14, %xmm6
	addpd   %xmm6, %xmm2
	movupd  %xmm2, 0x20(%rbx)
	movupd  0x30(%rbx), %xmm3
	mulpd   %xmm15, %xmm7
	addpd   %xmm7, %xmm3
	movupd  %xmm3, 0x30(%rbx)

	# *(out2 +  0) += in0_2 * in1_0; 
	# *(out2 +  1) += in0_2 * in1_1; 
	# *(out2 +  2) += in0_2 * in1_2; 
	# *(out2 +  3) += in0_2 * in1_3; 
	# *(out2 +  4) += in0_2 * in1_4; 
	# *(out2 +  5) += in0_2 * in1_5; 
	# *(out2 +  6) += in0_2 * in1_6; 
	# *(out2 +  7) += in0_2 * in1_7; 
	movddup %xmm9, %xmm4
	movapd  %xmm4, %xmm5
	movapd  %xmm4, %xmm6
	movapd  %xmm5, %xmm7
	pshufd  $0x4E, %xmm9, %xmm9

	movupd  0x00(%rcx), %xmm0
	mulpd   %xmm12, %xmm4
	addpd   %xmm4, %xmm0
	movupd  %xmm0, 0x00(%rcx)
	movupd  0x10(%rcx), %xmm1
	mulpd   %xmm13, %xmm5
	addpd   %xmm5, %xmm1
	movupd  %xmm1, 0x10(%rcx)
	movupd  0x20(%rcx), %xmm2
	mulpd   %xmm14, %xmm6
	addpd   %xmm6, %xmm2
	movupd  %xmm2, 0x20(%rcx)
	movupd  0x30(%rcx), %xmm3
	mulpd   %xmm15, %xmm7
	addpd   %xmm7, %xmm3
	movupd  %xmm3, 0x30(%rcx)

	# *(out3 +  0) += in0_3 * in1_0; 
	# *(out3 +  1) += in0_3 * in1_1; 
	# *(out3 +  2) += in0_3 * in1_2; 
	# *(out3 +  3) += in0_3 * in1_3; 
	# *(out3 +  4) += in0_3 * in1_4; 
	# *(out3 +  5) += in0_3 * in1_5; 
	# *(out3 +  6) += in0_3 * in1_6; 
	# *(out3 +  7) += in0_3 * in1_7; 
	movddup %xmm9, %xmm4
	movapd  %xmm4, %xmm5
	movapd  %xmm4, %xmm6
	movapd  %xmm5, %xmm7
	pshufd  $0x4E, %xmm9, %xmm9

	movupd  0x00(%rdx), %xmm0
	mulpd   %xmm12, %xmm4
	addpd   %xmm4, %xmm0
	movupd  %xmm0, 0x00(%rdx)
	movupd  0x10(%rdx), %xmm1
	mulpd   %xmm13, %xmm5
	addpd   %xmm5, %xmm1
	movupd  %xmm1, 0x10(%rdx)
	movupd  0x20(%rdx), %xmm2
	mulpd   %xmm14, %xmm6
	addpd   %xmm6, %xmm2
	movupd  %xmm2, 0x20(%rdx)
	movupd  0x30(%rdx), %xmm3
	mulpd   %xmm15, %xmm7
	addpd   %xmm7, %xmm3
	movupd  %xmm3, 0x30(%rdx)

	# *(out4 +  0) += in0_4 * in1_0; 
	# *(out4 +  1) += in0_4 * in1_1; 
	# *(out4 +  2) += in0_4 * in1_2; 
	# *(out4 +  3) += in0_4 * in1_3; 
	# *(out4 +  4) += in0_4 * in1_4; 
	# *(out4 +  5) += in0_4 * in1_5; 
	# *(out4 +  6) += in0_4 * in1_6; 
	# *(out4 +  7) += in0_4 * in1_7; 
	movddup %xmm10, %xmm4
	movapd  %xmm4, %xmm5
	movapd  %xmm4, %xmm6
	movapd  %xmm5, %xmm7
	pshufd  $0x4E, %xmm10, %xmm10

	movupd  0x00(%r12), %xmm0
	mulpd   %xmm12, %xmm4
	addpd   %xmm4, %xmm0
	movupd  %xmm0, 0x00(%r12)
	movupd  0x10(%r12), %xmm1
	mulpd   %xmm13, %xmm5
	addpd   %xmm5, %xmm1
	movupd  %xmm1, 0x10(%r12)
	movupd  0x20(%r12), %xmm2
	mulpd   %xmm14, %xmm6
	addpd   %xmm6, %xmm2
	movupd  %xmm2, 0x20(%r12)
	movupd  0x30(%r12), %xmm3
	mulpd   %xmm15, %xmm7
	addpd   %xmm7, %xmm3
	movupd  %xmm3, 0x30(%r12)

	# *(out5 +  0) += in0_5 * in1_0; 
	# *(out5 +  1) += in0_5 * in1_1; 
	# *(out5 +  2) += in0_5 * in1_2; 
	# *(out5 +  3) += in0_5 * in1_3; 
	# *(out5 +  4) += in0_5 * in1_4; 
	# *(out5 +  5) += in0_5 * in1_5; 
	# *(out5 +  6) += in0_5 * in1_6; 
	# *(out5 +  7) += in0_5 * in1_7; 
	movddup %xmm10, %xmm4
	movapd  %xmm4, %xmm5
	movapd  %xmm4, %xmm6
	movapd  %xmm5, %xmm7
	pshufd  $0x4E, %xmm10, %xmm10

	movupd  0x00(%r13), %xmm0
	mulpd   %xmm12, %xmm4
	addpd   %xmm4, %xmm0
	movupd  %xmm0, 0x00(%r13)
	movupd  0x10(%r13), %xmm1
	mulpd   %xmm13, %xmm5
	addpd   %xmm5, %xmm1
	movupd  %xmm1, 0x10(%r13)
	movupd  0x20(%r13), %xmm2
	mulpd   %xmm14, %xmm6
	addpd   %xmm6, %xmm2
	movupd  %xmm2, 0x20(%r13)
	movupd  0x30(%r13), %xmm3
	mulpd   %xmm15, %xmm7
	addpd   %xmm7, %xmm3
	movupd  %xmm3, 0x30(%r13)

	# *(out6 +  0) += in0_6 * in1_0; 
	# *(out6 +  1) += in0_6 * in1_1; 
	# *(out6 +  2) += in0_6 * in1_2; 
	# *(out6 +  3) += in0_6 * in1_3; 
	# *(out6 +  4) += in0_6 * in1_4; 
	# *(out6 +  5) += in0_6 * in1_5; 
	# *(out6 +  6) += in0_6 * in1_6; 
	# *(out6 +  7) += in0_6 * in1_7; 
	movddup %xmm11, %xmm4
	movapd  %xmm4, %xmm5
	movapd  %xmm4, %xmm6
	movapd  %xmm5, %xmm7
	pshufd  $0x4E, %xmm11, %xmm11

	movupd  0x00(%r14), %xmm0
	mulpd   %xmm12, %xmm4
	addpd   %xmm4, %xmm0
	movupd  %xmm0, 0x00(%r14)
	movupd  0x10(%r14), %xmm1
	mulpd   %xmm13, %xmm5
	addpd   %xmm5, %xmm1
	movupd  %xmm1, 0x10(%r14)
	movupd  0x20(%r14), %xmm2
	mulpd   %xmm14, %xmm6
	addpd   %xmm6, %xmm2
	movupd  %xmm2, 0x20(%r14)
	movupd  0x30(%r14), %xmm3
	mulpd   %xmm15, %xmm7
	addpd   %xmm7, %xmm3
	movupd  %xmm3, 0x30(%r14)

	# *(out7 +  0) += in0_7 * in1_0; 
	# *(out7 +  1) += in0_7 * in1_1; 
	# *(out7 +  2) += in0_7 * in1_2; 
	# *(out7 +  3) += in0_7 * in1_3; 
	# *(out7 +  4) += in0_7 * in1_4; 
	# *(out7 +  5) += in0_7 * in1_5; 
	# *(out7 +  6) += in0_7 * in1_6; 
	# *(out7 +  7) += in0_7 * in1_7; 
	movddup %xmm11, %xmm4
	movapd  %xmm4, %xmm5
	movapd  %xmm4, %xmm6
	movapd  %xmm5, %xmm7
	pshufd  $0x4E, %xmm11, %xmm11

	movupd  0x00(%r15), %xmm0
	mulpd   %xmm12, %xmm4
	addpd   %xmm4, %xmm0
	movupd  %xmm0, 0x00(%r15)
	movupd  0x10(%r15), %xmm1
	mulpd   %xmm13, %xmm5
	addpd   %xmm5, %xmm1
	movupd  %xmm1, 0x10(%r15)
	movupd  0x20(%r15), %xmm2
	mulpd   %xmm14, %xmm6
	addpd   %xmm6, %xmm2
	movupd  %xmm2, 0x20(%r15)
	movupd  0x30(%r15), %xmm3
	mulpd   %xmm15, %xmm7
	addpd   %xmm7, %xmm3
	movupd  %xmm3, 0x30(%r15)

	addq $64, %rax   	# out0 += 8
	addq $64, %rbx   	# out1 += 8
	addq $64, %rcx   	# out2 += 8
	addq $64, %rdx   	# out3 += 8
	addq $64, %r12   	# out4 += 8
	addq $64, %r13   	# out5 += 8
	addq $64, %r14   	# out6 += 8
	addq $64, %r15   	# out7 += 8
	addq $64, %rdi   	# in1 += 8

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

	# vmdot_product_8x4(Out + div, In0, _In1 + div, k, mod, In0S, In0s, In1s);
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
	call vmdot_product_double_8x4

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
vmdot_product_double_8x16:
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

	movq 0x08(%rsp), %rdi	# Out0 = Out + In1s * 0
	movq %rdi, 0x80(%rsp)
	addq %r9, %rdi		# Out1 = Out + In1s * 1
	movq %rdi, 0x88(%rsp)
	addq %r9, %rdi		# Out2 = Out + In1s * 2
	movq %rdi, 0x90(%rsp)
	addq %r9, %rdi		# Out3 = Out + In1s * 3
	movq %rdi, 0x98(%rsp)
	addq %r9, %rdi		# Out4 = Out + In1s * 4
	movq %rdi, 0xA0(%rsp)
	addq %r9, %rdi		# Out5 = Out + In1s * 5
	movq %rdi, 0xA8(%rsp)
	addq %r9, %rdi		# Out6 = Out + In1s * 6
	movq %rdi, 0xB0(%rsp)
	addq %r9, %rdi		# Out7 = Out + In1s * 7
	movq %rdi, 0xB8(%rsp)

	movq 0x10(%rsp), %rsi 	# in0 = In0
	movq 0x18(%rsp), %r8	# In1 = _In1

	movq 0x30(%rsp), %r10	# n
	movq %r10, %r11
	andq $15, %r10		# mod = n & 15
	shrq $4, %r11		# div = n >> 4
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
	movq 0x90(%rsp), %rcx		# out2 = Out2
	movq 0x98(%rsp), %rdx		# out3 = Out3
	movq 0xA0(%rsp), %r12		# out4 = Out4
	movq 0xA8(%rsp), %r13		# out5 = Out5
	movq 0xB0(%rsp), %r14		# out6 = Out6
	movq 0xB8(%rsp), %r15		# out7 = Out7
	movddup 0(%rsi), %xmm8		# in0_0 = *In0
	movq 0x60(%rsp), %r11		# j = In0S
	movddup (%rsi, %r11), %xmm9	# in0_1 = *(in0 + j)
	addq 0x60(%rsp), %r11		# j += In0S
	movddup (%rsi, %r11), %xmm10	# in0_2 = *(in0 + j)
	addq 0x60(%rsp), %r11		# j += In0S
	movddup (%rsi, %r11), %xmm11	# in0_3 = *(in0 + j)
	addq 0x60(%rsp), %r11		# j += In0S
	movddup (%rsi, %r11), %xmm12	# in0_4 = *(in0 + j)
	addq 0x60(%rsp), %r11		# j += In0S
	movddup (%rsi, %r11), %xmm13	# in0_5 = *(in0 + j)
	addq 0x60(%rsp), %r11		# j += In0S
	movddup (%rsi, %r11), %xmm14	# in0_6 = *(in0 + j)
	addq 0x60(%rsp), %r11		# j += In0S
	movddup (%rsi, %r11), %xmm15	# in0_7 = *(in0 + j)
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
	# in1_4 = *(in1 + 4)
	# in1_5 = *(in1 + 5)
	# in1_6 = *(in1 + 6)
	# in1_7 = *(in1 + 7)
	movupd 0 (%rdi), %xmm4
	movapd %xmm4, 0xC0(%rsp)
	movupd 16(%rdi), %xmm5
	movapd %xmm5, 0xD0(%rsp)
	movupd 32(%rdi), %xmm6
	movapd %xmm6, 0xE0(%rsp)
	movupd 48(%rdi), %xmm7
	movapd %xmm7, 0xF0(%rsp)

	# *(out0 +  0) += in0_0 * in1_0; 
	# *(out0 +  1) += in0_0 * in1_1; 
	# *(out0 +  2) += in0_0 * in1_2; 
	# *(out0 +  3) += in0_0 * in1_3; 
	# *(out0 +  4) += in0_0 * in1_4; 
	# *(out0 +  5) += in0_0 * in1_5; 
	# *(out0 +  6) += in0_0 * in1_6; 
	# *(out0 +  7) += in0_0 * in1_7; 
	movupd 0 (%rax), %xmm0
	movupd 16(%rax), %xmm1
	movupd 32(%rax), %xmm2
	movupd 48(%rax), %xmm3

	mulpd %xmm8, %xmm4
	addpd %xmm4, %xmm0
	mulpd %xmm8, %xmm5
	addpd %xmm5, %xmm1
	mulpd %xmm8, %xmm6
	addpd %xmm6, %xmm2
	mulpd %xmm8, %xmm7
	addpd %xmm7, %xmm3

	movupd %xmm0, 0 (%rax)
	movupd %xmm1, 16(%rax)
	movupd %xmm2, 32(%rax)
	movupd %xmm3, 48(%rax)

	# *(out1 +  0) += in0_1 * in1_0; 
	# *(out1 +  1) += in0_1 * in1_1; 
	# *(out1 +  2) += in0_1 * in1_2; 
	# *(out1 +  3) += in0_1 * in1_3; 
	# *(out1 +  4) += in0_1 * in1_4; 
	# *(out1 +  5) += in0_1 * in1_5; 
	# *(out1 +  6) += in0_1 * in1_6; 
	# *(out1 +  7) += in0_1 * in1_7; 
	movapd 0xC0(%rsp), %xmm4
	movapd 0xD0(%rsp), %xmm5
	movapd 0xE0(%rsp), %xmm6
	movapd 0xF0(%rsp), %xmm7

	movupd 0 (%rbx), %xmm0
	movupd 16(%rbx), %xmm1
	movupd 32(%rbx), %xmm2
	movupd 48(%rbx), %xmm3

	mulpd %xmm9, %xmm4
	addpd %xmm4, %xmm0
	mulpd %xmm9, %xmm5
	addpd %xmm5, %xmm1
	mulpd %xmm9, %xmm6
	addpd %xmm6, %xmm2
	mulpd %xmm9, %xmm7
	addpd %xmm7, %xmm3

	movupd %xmm0, 0 (%rbx)
	movupd %xmm1, 16(%rbx)
	movupd %xmm2, 32(%rbx)
	movupd %xmm3, 48(%rbx)

	# *(out2 +  0) += in0_2 * in1_0; 
	# *(out2 +  1) += in0_2 * in1_1; 
	# *(out2 +  2) += in0_2 * in1_2; 
	# *(out2 +  3) += in0_2 * in1_3; 
	# *(out2 +  4) += in0_2 * in1_4; 
	# *(out2 +  5) += in0_2 * in1_5; 
	# *(out2 +  6) += in0_2 * in1_6; 
	# *(out2 +  7) += in0_2 * in1_7; 
	movapd 0xC0(%rsp), %xmm4
	movapd 0xD0(%rsp), %xmm5
	movapd 0xE0(%rsp), %xmm6
	movapd 0xF0(%rsp), %xmm7

	movupd 0 (%rcx), %xmm0
	movupd 16(%rcx), %xmm1
	movupd 32(%rcx), %xmm2
	movupd 48(%rcx), %xmm3

	mulpd %xmm10, %xmm4
	addpd %xmm4, %xmm0
	mulpd %xmm10, %xmm5
	addpd %xmm5, %xmm1
	mulpd %xmm10, %xmm6
	addpd %xmm6, %xmm2
	mulpd %xmm10, %xmm7
	addpd %xmm7, %xmm3

	movupd %xmm0, 0 (%rcx)
	movupd %xmm1, 16(%rcx)
	movupd %xmm2, 32(%rcx)
	movupd %xmm3, 48(%rcx)

	# *(out3 +  0) += in0_3 * in1_0; 
	# *(out3 +  1) += in0_3 * in1_1; 
	# *(out3 +  2) += in0_3 * in1_2; 
	# *(out3 +  3) += in0_3 * in1_3; 
	# *(out3 +  4) += in0_3 * in1_4; 
	# *(out3 +  5) += in0_3 * in1_5; 
	# *(out3 +  6) += in0_3 * in1_6; 
	# *(out3 +  7) += in0_3 * in1_7; 
	movapd 0xC0(%rsp), %xmm4
	movapd 0xD0(%rsp), %xmm5
	movapd 0xE0(%rsp), %xmm6
	movapd 0xF0(%rsp), %xmm7

	movupd 0 (%rdx), %xmm0
	movupd 16(%rdx), %xmm1
	movupd 32(%rdx), %xmm2
	movupd 48(%rdx), %xmm3

	mulpd %xmm11, %xmm4
	addpd %xmm4, %xmm0
	mulpd %xmm11, %xmm5
	addpd %xmm5, %xmm1
	mulpd %xmm11, %xmm6
	addpd %xmm6, %xmm2
	mulpd %xmm11, %xmm7
	addpd %xmm7, %xmm3

	movupd %xmm0, 0 (%rdx)
	movupd %xmm1, 16(%rdx)
	movupd %xmm2, 32(%rdx)
	movupd %xmm3, 48(%rdx)

	# *(out4 +  0) += in0_4 * in1_0; 
	# *(out4 +  1) += in0_4 * in1_1; 
	# *(out4 +  2) += in0_4 * in1_2; 
	# *(out4 +  3) += in0_4 * in1_3; 
	# *(out4 +  4) += in0_4 * in1_4; 
	# *(out4 +  5) += in0_4 * in1_5; 
	# *(out4 +  6) += in0_4 * in1_6; 
	# *(out4 +  7) += in0_4 * in1_7; 
	movapd 0xC0(%rsp), %xmm4
	movapd 0xD0(%rsp), %xmm5
	movapd 0xE0(%rsp), %xmm6
	movapd 0xF0(%rsp), %xmm7

	movupd 0 (%r12), %xmm0
	movupd 16(%r12), %xmm1
	movupd 32(%r12), %xmm2
	movupd 48(%r12), %xmm3

	mulpd %xmm12, %xmm4
	addpd %xmm4, %xmm0
	mulpd %xmm12, %xmm5
	addpd %xmm5, %xmm1
	mulpd %xmm12, %xmm6
	addpd %xmm6, %xmm2
	mulpd %xmm12, %xmm7
	addpd %xmm7, %xmm3

	movupd %xmm0, 0 (%r12)
	movupd %xmm1, 16(%r12)
	movupd %xmm2, 32(%r12)
	movupd %xmm3, 48(%r12)

	# *(out5 +  0) += in0_5 * in1_0; 
	# *(out5 +  1) += in0_5 * in1_1; 
	# *(out5 +  2) += in0_5 * in1_2; 
	# *(out5 +  3) += in0_5 * in1_3; 
	# *(out5 +  4) += in0_5 * in1_4; 
	# *(out5 +  5) += in0_5 * in1_5; 
	# *(out5 +  6) += in0_5 * in1_6; 
	# *(out5 +  7) += in0_5 * in1_7; 
	movapd 0xC0(%rsp), %xmm4
	movapd 0xD0(%rsp), %xmm5
	movapd 0xE0(%rsp), %xmm6
	movapd 0xF0(%rsp), %xmm7

	movupd 0 (%r13), %xmm0
	movupd 16(%r13), %xmm1
	movupd 32(%r13), %xmm2
	movupd 48(%r13), %xmm3

	mulpd %xmm13, %xmm4
	addpd %xmm4, %xmm0
	mulpd %xmm13, %xmm5
	addpd %xmm5, %xmm1
	mulpd %xmm13, %xmm6
	addpd %xmm6, %xmm2
	mulpd %xmm13, %xmm7
	addpd %xmm7, %xmm3

	movupd %xmm0, 0 (%r13)
	movupd %xmm1, 16(%r13)
	movupd %xmm2, 32(%r13)
	movupd %xmm3, 48(%r13)

	# *(out6 +  0) += in0_6 * in1_0; 
	# *(out6 +  1) += in0_6 * in1_1; 
	# *(out6 +  2) += in0_6 * in1_2; 
	# *(out6 +  3) += in0_6 * in1_3; 
	# *(out6 +  4) += in0_6 * in1_4; 
	# *(out6 +  5) += in0_6 * in1_5; 
	# *(out6 +  6) += in0_6 * in1_6; 
	# *(out6 +  7) += in0_6 * in1_7; 
	movapd 0xC0(%rsp), %xmm4
	movapd 0xD0(%rsp), %xmm5
	movapd 0xE0(%rsp), %xmm6
	movapd 0xF0(%rsp), %xmm7

	movupd 0 (%r14), %xmm0
	movupd 16(%r14), %xmm1
	movupd 32(%r14), %xmm2
	movupd 48(%r14), %xmm3

	mulpd %xmm14, %xmm4
	addpd %xmm4, %xmm0
	mulpd %xmm14, %xmm5
	addpd %xmm5, %xmm1
	mulpd %xmm14, %xmm6
	addpd %xmm6, %xmm2
	mulpd %xmm14, %xmm7
	addpd %xmm7, %xmm3

	movupd %xmm0, 0 (%r14)
	movupd %xmm1, 16(%r14)
	movupd %xmm2, 32(%r14)
	movupd %xmm3, 48(%r14)

	# *(out7 +  0) += in0_7 * in1_0; 
	# *(out7 +  1) += in0_7 * in1_1; 
	# *(out7 +  2) += in0_7 * in1_2; 
	# *(out7 +  3) += in0_7 * in1_3; 
	# *(out7 +  4) += in0_7 * in1_4; 
	# *(out7 +  5) += in0_7 * in1_5; 
	# *(out7 +  6) += in0_7 * in1_6; 
	# *(out7 +  7) += in0_7 * in1_7; 
	movapd 0xC0(%rsp), %xmm4
	movapd 0xD0(%rsp), %xmm5
	movapd 0xE0(%rsp), %xmm6
	movapd 0xF0(%rsp), %xmm7

	movupd 0 (%r15), %xmm0
	movupd 16(%r15), %xmm1
	movupd 32(%r15), %xmm2
	movupd 48(%r15), %xmm3

	mulpd %xmm15, %xmm4
	addpd %xmm4, %xmm0
	mulpd %xmm15, %xmm5
	addpd %xmm5, %xmm1
	mulpd %xmm15, %xmm6
	addpd %xmm6, %xmm2
	mulpd %xmm15, %xmm7
	addpd %xmm7, %xmm3

	movupd %xmm0, 0 (%r15)
	movupd %xmm1, 16(%r15)
	movupd %xmm2, 32(%r15)
	movupd %xmm3, 48(%r15)

	addq $64, %rax   	# out0 += 8
	addq $64, %rbx   	# out1 += 8
	addq $64, %rcx   	# out2 += 8
	addq $64, %rdx   	# out3 += 8
	addq $64, %r12   	# out4 += 8
	addq $64, %r13   	# out5 += 8
	addq $64, %r14   	# out6 += 8
	addq $64, %r15   	# out7 += 8
	addq $64, %rdi   	# in1 += 8

	# in1_0 = *(in1 + 0)
	# in1_1 = *(in1 + 1)
	# in1_2 = *(in1 + 2)
	# in1_3 = *(in1 + 3)
	# in1_4 = *(in1 + 4)
	# in1_5 = *(in1 + 5)
	# in1_6 = *(in1 + 6)
	# in1_7 = *(in1 + 7)
	movupd 0 (%rdi), %xmm4
	movapd %xmm4, 0xC0(%rsp)
	movupd 16(%rdi), %xmm5
	movapd %xmm5, 0xD0(%rsp)
	movupd 32(%rdi), %xmm6
	movapd %xmm6, 0xE0(%rsp)
	movupd 48(%rdi), %xmm7
	movapd %xmm7, 0xF0(%rsp)

	# *(out0 +  0) += in0_0 * in1_0; 
	# *(out0 +  1) += in0_0 * in1_1; 
	# *(out0 +  2) += in0_0 * in1_2; 
	# *(out0 +  3) += in0_0 * in1_3; 
	# *(out0 +  4) += in0_0 * in1_4; 
	# *(out0 +  5) += in0_0 * in1_5; 
	# *(out0 +  6) += in0_0 * in1_6; 
	# *(out0 +  7) += in0_0 * in1_7; 
	movupd 0 (%rax), %xmm0
	movupd 16(%rax), %xmm1
	movupd 32(%rax), %xmm2
	movupd 48(%rax), %xmm3

	mulpd %xmm8, %xmm4
	addpd %xmm4, %xmm0
	mulpd %xmm8, %xmm5
	addpd %xmm5, %xmm1
	mulpd %xmm8, %xmm6
	addpd %xmm6, %xmm2
	mulpd %xmm8, %xmm7
	addpd %xmm7, %xmm3

	movupd %xmm0, 0 (%rax)
	movupd %xmm1, 16(%rax)
	movupd %xmm2, 32(%rax)
	movupd %xmm3, 48(%rax)

	# *(out1 +  0) += in0_1 * in1_0; 
	# *(out1 +  1) += in0_1 * in1_1; 
	# *(out1 +  2) += in0_1 * in1_2; 
	# *(out1 +  3) += in0_1 * in1_3; 
	# *(out1 +  4) += in0_1 * in1_4; 
	# *(out1 +  5) += in0_1 * in1_5; 
	# *(out1 +  6) += in0_1 * in1_6; 
	# *(out1 +  7) += in0_1 * in1_7; 
	movapd 0xC0(%rsp), %xmm4
	movapd 0xD0(%rsp), %xmm5
	movapd 0xE0(%rsp), %xmm6
	movapd 0xF0(%rsp), %xmm7

	movupd 0 (%rbx), %xmm0
	movupd 16(%rbx), %xmm1
	movupd 32(%rbx), %xmm2
	movupd 48(%rbx), %xmm3

	mulpd %xmm9, %xmm4
	addpd %xmm4, %xmm0
	mulpd %xmm9, %xmm5
	addpd %xmm5, %xmm1
	mulpd %xmm9, %xmm6
	addpd %xmm6, %xmm2
	mulpd %xmm9, %xmm7
	addpd %xmm7, %xmm3

	movupd %xmm0, 0 (%rbx)
	movupd %xmm1, 16(%rbx)
	movupd %xmm2, 32(%rbx)
	movupd %xmm3, 48(%rbx)

	# *(out2 +  0) += in0_2 * in1_0; 
	# *(out2 +  1) += in0_2 * in1_1; 
	# *(out2 +  2) += in0_2 * in1_2; 
	# *(out2 +  3) += in0_2 * in1_3; 
	# *(out2 +  4) += in0_2 * in1_4; 
	# *(out2 +  5) += in0_2 * in1_5; 
	# *(out2 +  6) += in0_2 * in1_6; 
	# *(out2 +  7) += in0_2 * in1_7; 
	movapd 0xC0(%rsp), %xmm4
	movapd 0xD0(%rsp), %xmm5
	movapd 0xE0(%rsp), %xmm6
	movapd 0xF0(%rsp), %xmm7

	movupd 0 (%rcx), %xmm0
	movupd 16(%rcx), %xmm1
	movupd 32(%rcx), %xmm2
	movupd 48(%rcx), %xmm3

	mulpd %xmm10, %xmm4
	addpd %xmm4, %xmm0
	mulpd %xmm10, %xmm5
	addpd %xmm5, %xmm1
	mulpd %xmm10, %xmm6
	addpd %xmm6, %xmm2
	mulpd %xmm10, %xmm7
	addpd %xmm7, %xmm3

	movupd %xmm0, 0 (%rcx)
	movupd %xmm1, 16(%rcx)
	movupd %xmm2, 32(%rcx)
	movupd %xmm3, 48(%rcx)

	# *(out3 +  0) += in0_3 * in1_0; 
	# *(out3 +  1) += in0_3 * in1_1; 
	# *(out3 +  2) += in0_3 * in1_2; 
	# *(out3 +  3) += in0_3 * in1_3; 
	# *(out3 +  4) += in0_3 * in1_4; 
	# *(out3 +  5) += in0_3 * in1_5; 
	# *(out3 +  6) += in0_3 * in1_6; 
	# *(out3 +  7) += in0_3 * in1_7; 
	movapd 0xC0(%rsp), %xmm4
	movapd 0xD0(%rsp), %xmm5
	movapd 0xE0(%rsp), %xmm6
	movapd 0xF0(%rsp), %xmm7

	movupd 0 (%rdx), %xmm0
	movupd 16(%rdx), %xmm1
	movupd 32(%rdx), %xmm2
	movupd 48(%rdx), %xmm3

	mulpd %xmm11, %xmm4
	addpd %xmm4, %xmm0
	mulpd %xmm11, %xmm5
	addpd %xmm5, %xmm1
	mulpd %xmm11, %xmm6
	addpd %xmm6, %xmm2
	mulpd %xmm11, %xmm7
	addpd %xmm7, %xmm3

	movupd %xmm0, 0 (%rdx)
	movupd %xmm1, 16(%rdx)
	movupd %xmm2, 32(%rdx)
	movupd %xmm3, 48(%rdx)

	# *(out4 +  0) += in0_4 * in1_0; 
	# *(out4 +  1) += in0_4 * in1_1; 
	# *(out4 +  2) += in0_4 * in1_2; 
	# *(out4 +  3) += in0_4 * in1_3; 
	# *(out4 +  4) += in0_4 * in1_4; 
	# *(out4 +  5) += in0_4 * in1_5; 
	# *(out4 +  6) += in0_4 * in1_6; 
	# *(out4 +  7) += in0_4 * in1_7; 
	movapd 0xC0(%rsp), %xmm4
	movapd 0xD0(%rsp), %xmm5
	movapd 0xE0(%rsp), %xmm6
	movapd 0xF0(%rsp), %xmm7

	movupd 0 (%r12), %xmm0
	movupd 16(%r12), %xmm1
	movupd 32(%r12), %xmm2
	movupd 48(%r12), %xmm3

	mulpd %xmm12, %xmm4
	addpd %xmm4, %xmm0
	mulpd %xmm12, %xmm5
	addpd %xmm5, %xmm1
	mulpd %xmm12, %xmm6
	addpd %xmm6, %xmm2
	mulpd %xmm12, %xmm7
	addpd %xmm7, %xmm3

	movupd %xmm0, 0 (%r12)
	movupd %xmm1, 16(%r12)
	movupd %xmm2, 32(%r12)
	movupd %xmm3, 48(%r12)

	# *(out5 +  0) += in0_5 * in1_0; 
	# *(out5 +  1) += in0_5 * in1_1; 
	# *(out5 +  2) += in0_5 * in1_2; 
	# *(out5 +  3) += in0_5 * in1_3; 
	# *(out5 +  4) += in0_5 * in1_4; 
	# *(out5 +  5) += in0_5 * in1_5; 
	# *(out5 +  6) += in0_5 * in1_6; 
	# *(out5 +  7) += in0_5 * in1_7; 
	movapd 0xC0(%rsp), %xmm4
	movapd 0xD0(%rsp), %xmm5
	movapd 0xE0(%rsp), %xmm6
	movapd 0xF0(%rsp), %xmm7

	movupd 0 (%r13), %xmm0
	movupd 16(%r13), %xmm1
	movupd 32(%r13), %xmm2
	movupd 48(%r13), %xmm3

	mulpd %xmm13, %xmm4
	addpd %xmm4, %xmm0
	mulpd %xmm13, %xmm5
	addpd %xmm5, %xmm1
	mulpd %xmm13, %xmm6
	addpd %xmm6, %xmm2
	mulpd %xmm13, %xmm7
	addpd %xmm7, %xmm3

	movupd %xmm0, 0 (%r13)
	movupd %xmm1, 16(%r13)
	movupd %xmm2, 32(%r13)
	movupd %xmm3, 48(%r13)

	# *(out6 +  0) += in0_6 * in1_0; 
	# *(out6 +  1) += in0_6 * in1_1; 
	# *(out6 +  2) += in0_6 * in1_2; 
	# *(out6 +  3) += in0_6 * in1_3; 
	# *(out6 +  4) += in0_6 * in1_4; 
	# *(out6 +  5) += in0_6 * in1_5; 
	# *(out6 +  6) += in0_6 * in1_6; 
	# *(out6 +  7) += in0_6 * in1_7; 
	movapd 0xC0(%rsp), %xmm4
	movapd 0xD0(%rsp), %xmm5
	movapd 0xE0(%rsp), %xmm6
	movapd 0xF0(%rsp), %xmm7

	movupd 0 (%r14), %xmm0
	movupd 16(%r14), %xmm1
	movupd 32(%r14), %xmm2
	movupd 48(%r14), %xmm3

	mulpd %xmm14, %xmm4
	addpd %xmm4, %xmm0
	mulpd %xmm14, %xmm5
	addpd %xmm5, %xmm1
	mulpd %xmm14, %xmm6
	addpd %xmm6, %xmm2
	mulpd %xmm14, %xmm7
	addpd %xmm7, %xmm3

	movupd %xmm0, 0 (%r14)
	movupd %xmm1, 16(%r14)
	movupd %xmm2, 32(%r14)
	movupd %xmm3, 48(%r14)

	# *(out7 +  0) += in0_7 * in1_0; 
	# *(out7 +  1) += in0_7 * in1_1; 
	# *(out7 +  2) += in0_7 * in1_2; 
	# *(out7 +  3) += in0_7 * in1_3; 
	# *(out7 +  4) += in0_7 * in1_4; 
	# *(out7 +  5) += in0_7 * in1_5; 
	# *(out7 +  6) += in0_7 * in1_6; 
	# *(out7 +  7) += in0_7 * in1_7; 
	movapd 0xC0(%rsp), %xmm4
	movapd 0xD0(%rsp), %xmm5
	movapd 0xE0(%rsp), %xmm6
	movapd 0xF0(%rsp), %xmm7

	movupd 0 (%r15), %xmm0
	movupd 16(%r15), %xmm1
	movupd 32(%r15), %xmm2
	movupd 48(%r15), %xmm3

	mulpd %xmm15, %xmm4
	addpd %xmm4, %xmm0
	mulpd %xmm15, %xmm5
	addpd %xmm5, %xmm1
	mulpd %xmm15, %xmm6
	addpd %xmm6, %xmm2
	mulpd %xmm15, %xmm7
	addpd %xmm7, %xmm3

	movupd %xmm0, 0 (%r15)
	movupd %xmm1, 16(%r15)
	movupd %xmm2, 32(%r15)
	movupd %xmm3, 48(%r15)

	addq $64, %rax   	# out0 += 8
	addq $64, %rbx   	# out1 += 8
	addq $64, %rcx   	# out2 += 8
	addq $64, %rdx   	# out3 += 8
	addq $64, %r12   	# out4 += 8
	addq $64, %r13   	# out5 += 8
	addq $64, %r14   	# out6 += 8
	addq $64, %r15   	# out7 += 8
	addq $64, %rdi   	# in1 += 8

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

	# vmdot_product_8x8(Out + div, In0, _In1 + div, k, mod, In0S, In0s, In1s);
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
	call vmdot_product_double_8x8

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
vmdot_product_double_8x32:
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

	movq 0x08(%rsp), %rdi	# Out0 = Out + In1s * 0
	movq %rdi, 0x80(%rsp)
	addq %r9, %rdi		# Out1 = Out + In1s * 1
	movq %rdi, 0x88(%rsp)
	addq %r9, %rdi		# Out2 = Out + In1s * 2
	movq %rdi, 0x90(%rsp)
	addq %r9, %rdi		# Out3 = Out + In1s * 3
	movq %rdi, 0x98(%rsp)
	addq %r9, %rdi		# Out4 = Out + In1s * 4
	movq %rdi, 0xA0(%rsp)
	addq %r9, %rdi		# Out5 = Out + In1s * 5
	movq %rdi, 0xA8(%rsp)
	addq %r9, %rdi		# Out6 = Out + In1s * 6
	movq %rdi, 0xB0(%rsp)
	addq %r9, %rdi		# Out7 = Out + In1s * 7
	movq %rdi, 0xB8(%rsp)

	movq 0x10(%rsp), %rsi 	# in0 = In0
	movq 0x18(%rsp), %r8	# In1 = _In1

	movq 0x30(%rsp), %r10	# n
	movq %r10, %r11
	andq $31, %r10		# mod = n & 31
	shrq $5, %r11		# div = n >> 5
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
	movq 0x90(%rsp), %rcx		# out2 = Out2
	movq 0x98(%rsp), %rdx		# out3 = Out3
	movq 0xA0(%rsp), %r12		# out4 = Out4
	movq 0xA8(%rsp), %r13		# out5 = Out5
	movq 0xB0(%rsp), %r14		# out6 = Out6
	movq 0xB8(%rsp), %r15		# out7 = Out7
	movddup 0(%rsi), %xmm8		# in0_0 = *In0
	movq 0x60(%rsp), %r11		# j = In0S
	movddup (%rsi, %r11), %xmm9	# in0_1 = *(in0 + j)
	addq 0x60(%rsp), %r11		# j += In0S
	movddup (%rsi, %r11), %xmm10	# in0_2 = *(in0 + j)
	addq 0x60(%rsp), %r11		# j += In0S
	movddup (%rsi, %r11), %xmm11	# in0_3 = *(in0 + j)
	addq 0x60(%rsp), %r11		# j += In0S
	movddup (%rsi, %r11), %xmm12	# in0_4 = *(in0 + j)
	addq 0x60(%rsp), %r11		# j += In0S
	movddup (%rsi, %r11), %xmm13	# in0_5 = *(in0 + j)
	addq 0x60(%rsp), %r11		# j += In0S
	movddup (%rsi, %r11), %xmm14	# in0_6 = *(in0 + j)
	addq 0x60(%rsp), %r11		# j += In0S
	movddup (%rsi, %r11), %xmm15	# in0_7 = *(in0 + j)
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
	# in1_4 = *(in1 + 4)
	# in1_5 = *(in1 + 5)
	# in1_6 = *(in1 + 6)
	# in1_7 = *(in1 + 7)
	movupd 0 (%rdi), %xmm4
	movapd %xmm4, 0xC0(%rsp)
	movupd 16(%rdi), %xmm5
	movapd %xmm5, 0xD0(%rsp)
	movupd 32(%rdi), %xmm6
	movapd %xmm6, 0xE0(%rsp)
	movupd 48(%rdi), %xmm7
	movapd %xmm7, 0xF0(%rsp)

	# *(out0 +  0) += in0_0 * in1_0; 
	# *(out0 +  1) += in0_0 * in1_1; 
	# *(out0 +  2) += in0_0 * in1_2; 
	# *(out0 +  3) += in0_0 * in1_3; 
	# *(out0 +  4) += in0_0 * in1_4; 
	# *(out0 +  5) += in0_0 * in1_5; 
	# *(out0 +  6) += in0_0 * in1_6; 
	# *(out0 +  7) += in0_0 * in1_7; 
	movupd 0 (%rax), %xmm0
	movupd 16(%rax), %xmm1
	movupd 32(%rax), %xmm2
	movupd 48(%rax), %xmm3

	mulpd %xmm8, %xmm4
	addpd %xmm4, %xmm0
	mulpd %xmm8, %xmm5
	addpd %xmm5, %xmm1
	mulpd %xmm8, %xmm6
	addpd %xmm6, %xmm2
	mulpd %xmm8, %xmm7
	addpd %xmm7, %xmm3

	movupd %xmm0, 0 (%rax)
	movupd %xmm1, 16(%rax)
	movupd %xmm2, 32(%rax)
	movupd %xmm3, 48(%rax)

	# *(out1 +  0) += in0_1 * in1_0; 
	# *(out1 +  1) += in0_1 * in1_1; 
	# *(out1 +  2) += in0_1 * in1_2; 
	# *(out1 +  3) += in0_1 * in1_3; 
	# *(out1 +  4) += in0_1 * in1_4; 
	# *(out1 +  5) += in0_1 * in1_5; 
	# *(out1 +  6) += in0_1 * in1_6; 
	# *(out1 +  7) += in0_1 * in1_7; 
	movapd 0xC0(%rsp), %xmm4
	movapd 0xD0(%rsp), %xmm5
	movapd 0xE0(%rsp), %xmm6
	movapd 0xF0(%rsp), %xmm7

	movupd 0 (%rbx), %xmm0
	movupd 16(%rbx), %xmm1
	movupd 32(%rbx), %xmm2
	movupd 48(%rbx), %xmm3

	mulpd %xmm9, %xmm4
	addpd %xmm4, %xmm0
	mulpd %xmm9, %xmm5
	addpd %xmm5, %xmm1
	mulpd %xmm9, %xmm6
	addpd %xmm6, %xmm2
	mulpd %xmm9, %xmm7
	addpd %xmm7, %xmm3

	movupd %xmm0, 0 (%rbx)
	movupd %xmm1, 16(%rbx)
	movupd %xmm2, 32(%rbx)
	movupd %xmm3, 48(%rbx)

	# *(out2 +  0) += in0_2 * in1_0; 
	# *(out2 +  1) += in0_2 * in1_1; 
	# *(out2 +  2) += in0_2 * in1_2; 
	# *(out2 +  3) += in0_2 * in1_3; 
	# *(out2 +  4) += in0_2 * in1_4; 
	# *(out2 +  5) += in0_2 * in1_5; 
	# *(out2 +  6) += in0_2 * in1_6; 
	# *(out2 +  7) += in0_2 * in1_7; 
	movapd 0xC0(%rsp), %xmm4
	movapd 0xD0(%rsp), %xmm5
	movapd 0xE0(%rsp), %xmm6
	movapd 0xF0(%rsp), %xmm7

	movupd 0 (%rcx), %xmm0
	movupd 16(%rcx), %xmm1
	movupd 32(%rcx), %xmm2
	movupd 48(%rcx), %xmm3

	mulpd %xmm10, %xmm4
	addpd %xmm4, %xmm0
	mulpd %xmm10, %xmm5
	addpd %xmm5, %xmm1
	mulpd %xmm10, %xmm6
	addpd %xmm6, %xmm2
	mulpd %xmm10, %xmm7
	addpd %xmm7, %xmm3

	movupd %xmm0, 0 (%rcx)
	movupd %xmm1, 16(%rcx)
	movupd %xmm2, 32(%rcx)
	movupd %xmm3, 48(%rcx)

	# *(out3 +  0) += in0_3 * in1_0; 
	# *(out3 +  1) += in0_3 * in1_1; 
	# *(out3 +  2) += in0_3 * in1_2; 
	# *(out3 +  3) += in0_3 * in1_3; 
	# *(out3 +  4) += in0_3 * in1_4; 
	# *(out3 +  5) += in0_3 * in1_5; 
	# *(out3 +  6) += in0_3 * in1_6; 
	# *(out3 +  7) += in0_3 * in1_7; 
	movapd 0xC0(%rsp), %xmm4
	movapd 0xD0(%rsp), %xmm5
	movapd 0xE0(%rsp), %xmm6
	movapd 0xF0(%rsp), %xmm7

	movupd 0 (%rdx), %xmm0
	movupd 16(%rdx), %xmm1
	movupd 32(%rdx), %xmm2
	movupd 48(%rdx), %xmm3

	mulpd %xmm11, %xmm4
	addpd %xmm4, %xmm0
	mulpd %xmm11, %xmm5
	addpd %xmm5, %xmm1
	mulpd %xmm11, %xmm6
	addpd %xmm6, %xmm2
	mulpd %xmm11, %xmm7
	addpd %xmm7, %xmm3

	movupd %xmm0, 0 (%rdx)
	movupd %xmm1, 16(%rdx)
	movupd %xmm2, 32(%rdx)
	movupd %xmm3, 48(%rdx)

	# *(out4 +  0) += in0_4 * in1_0; 
	# *(out4 +  1) += in0_4 * in1_1; 
	# *(out4 +  2) += in0_4 * in1_2; 
	# *(out4 +  3) += in0_4 * in1_3; 
	# *(out4 +  4) += in0_4 * in1_4; 
	# *(out4 +  5) += in0_4 * in1_5; 
	# *(out4 +  6) += in0_4 * in1_6; 
	# *(out4 +  7) += in0_4 * in1_7; 
	movapd 0xC0(%rsp), %xmm4
	movapd 0xD0(%rsp), %xmm5
	movapd 0xE0(%rsp), %xmm6
	movapd 0xF0(%rsp), %xmm7

	movupd 0 (%r12), %xmm0
	movupd 16(%r12), %xmm1
	movupd 32(%r12), %xmm2
	movupd 48(%r12), %xmm3

	mulpd %xmm12, %xmm4
	addpd %xmm4, %xmm0
	mulpd %xmm12, %xmm5
	addpd %xmm5, %xmm1
	mulpd %xmm12, %xmm6
	addpd %xmm6, %xmm2
	mulpd %xmm12, %xmm7
	addpd %xmm7, %xmm3

	movupd %xmm0, 0 (%r12)
	movupd %xmm1, 16(%r12)
	movupd %xmm2, 32(%r12)
	movupd %xmm3, 48(%r12)

	# *(out5 +  0) += in0_5 * in1_0; 
	# *(out5 +  1) += in0_5 * in1_1; 
	# *(out5 +  2) += in0_5 * in1_2; 
	# *(out5 +  3) += in0_5 * in1_3; 
	# *(out5 +  4) += in0_5 * in1_4; 
	# *(out5 +  5) += in0_5 * in1_5; 
	# *(out5 +  6) += in0_5 * in1_6; 
	# *(out5 +  7) += in0_5 * in1_7; 
	movapd 0xC0(%rsp), %xmm4
	movapd 0xD0(%rsp), %xmm5
	movapd 0xE0(%rsp), %xmm6
	movapd 0xF0(%rsp), %xmm7

	movupd 0 (%r13), %xmm0
	movupd 16(%r13), %xmm1
	movupd 32(%r13), %xmm2
	movupd 48(%r13), %xmm3

	mulpd %xmm13, %xmm4
	addpd %xmm4, %xmm0
	mulpd %xmm13, %xmm5
	addpd %xmm5, %xmm1
	mulpd %xmm13, %xmm6
	addpd %xmm6, %xmm2
	mulpd %xmm13, %xmm7
	addpd %xmm7, %xmm3

	movupd %xmm0, 0 (%r13)
	movupd %xmm1, 16(%r13)
	movupd %xmm2, 32(%r13)
	movupd %xmm3, 48(%r13)

	# *(out6 +  0) += in0_6 * in1_0; 
	# *(out6 +  1) += in0_6 * in1_1; 
	# *(out6 +  2) += in0_6 * in1_2; 
	# *(out6 +  3) += in0_6 * in1_3; 
	# *(out6 +  4) += in0_6 * in1_4; 
	# *(out6 +  5) += in0_6 * in1_5; 
	# *(out6 +  6) += in0_6 * in1_6; 
	# *(out6 +  7) += in0_6 * in1_7; 
	movapd 0xC0(%rsp), %xmm4
	movapd 0xD0(%rsp), %xmm5
	movapd 0xE0(%rsp), %xmm6
	movapd 0xF0(%rsp), %xmm7

	movupd 0 (%r14), %xmm0
	movupd 16(%r14), %xmm1
	movupd 32(%r14), %xmm2
	movupd 48(%r14), %xmm3

	mulpd %xmm14, %xmm4
	addpd %xmm4, %xmm0
	mulpd %xmm14, %xmm5
	addpd %xmm5, %xmm1
	mulpd %xmm14, %xmm6
	addpd %xmm6, %xmm2
	mulpd %xmm14, %xmm7
	addpd %xmm7, %xmm3

	movupd %xmm0, 0 (%r14)
	movupd %xmm1, 16(%r14)
	movupd %xmm2, 32(%r14)
	movupd %xmm3, 48(%r14)

	# *(out7 +  0) += in0_7 * in1_0; 
	# *(out7 +  1) += in0_7 * in1_1; 
	# *(out7 +  2) += in0_7 * in1_2; 
	# *(out7 +  3) += in0_7 * in1_3; 
	# *(out7 +  4) += in0_7 * in1_4; 
	# *(out7 +  5) += in0_7 * in1_5; 
	# *(out7 +  6) += in0_7 * in1_6; 
	# *(out7 +  7) += in0_7 * in1_7; 
	movapd 0xC0(%rsp), %xmm4
	movapd 0xD0(%rsp), %xmm5
	movapd 0xE0(%rsp), %xmm6
	movapd 0xF0(%rsp), %xmm7

	movupd 0 (%r15), %xmm0
	movupd 16(%r15), %xmm1
	movupd 32(%r15), %xmm2
	movupd 48(%r15), %xmm3

	mulpd %xmm15, %xmm4
	addpd %xmm4, %xmm0
	mulpd %xmm15, %xmm5
	addpd %xmm5, %xmm1
	mulpd %xmm15, %xmm6
	addpd %xmm6, %xmm2
	mulpd %xmm15, %xmm7
	addpd %xmm7, %xmm3

	movupd %xmm0, 0 (%r15)
	movupd %xmm1, 16(%r15)
	movupd %xmm2, 32(%r15)
	movupd %xmm3, 48(%r15)

	addq $64, %rax   	# out0 += 8
	addq $64, %rbx   	# out1 += 8
	addq $64, %rcx   	# out2 += 8
	addq $64, %rdx   	# out3 += 8
	addq $64, %r12   	# out4 += 8
	addq $64, %r13   	# out5 += 8
	addq $64, %r14   	# out6 += 8
	addq $64, %r15   	# out7 += 8
	addq $64, %rdi   	# in1 += 8

	# in1_0 = *(in1 + 0)
	# in1_1 = *(in1 + 1)
	# in1_2 = *(in1 + 2)
	# in1_3 = *(in1 + 3)
	# in1_4 = *(in1 + 4)
	# in1_5 = *(in1 + 5)
	# in1_6 = *(in1 + 6)
	# in1_7 = *(in1 + 7)
	movupd 0 (%rdi), %xmm4
	movapd %xmm4, 0xC0(%rsp)
	movupd 16(%rdi), %xmm5
	movapd %xmm5, 0xD0(%rsp)
	movupd 32(%rdi), %xmm6
	movapd %xmm6, 0xE0(%rsp)
	movupd 48(%rdi), %xmm7
	movapd %xmm7, 0xF0(%rsp)

	# *(out0 +  0) += in0_0 * in1_0; 
	# *(out0 +  1) += in0_0 * in1_1; 
	# *(out0 +  2) += in0_0 * in1_2; 
	# *(out0 +  3) += in0_0 * in1_3; 
	# *(out0 +  4) += in0_0 * in1_4; 
	# *(out0 +  5) += in0_0 * in1_5; 
	# *(out0 +  6) += in0_0 * in1_6; 
	# *(out0 +  7) += in0_0 * in1_7; 
	movupd 0 (%rax), %xmm0
	movupd 16(%rax), %xmm1
	movupd 32(%rax), %xmm2
	movupd 48(%rax), %xmm3

	mulpd %xmm8, %xmm4
	addpd %xmm4, %xmm0
	mulpd %xmm8, %xmm5
	addpd %xmm5, %xmm1
	mulpd %xmm8, %xmm6
	addpd %xmm6, %xmm2
	mulpd %xmm8, %xmm7
	addpd %xmm7, %xmm3

	movupd %xmm0, 0 (%rax)
	movupd %xmm1, 16(%rax)
	movupd %xmm2, 32(%rax)
	movupd %xmm3, 48(%rax)

	# *(out1 +  0) += in0_1 * in1_0; 
	# *(out1 +  1) += in0_1 * in1_1; 
	# *(out1 +  2) += in0_1 * in1_2; 
	# *(out1 +  3) += in0_1 * in1_3; 
	# *(out1 +  4) += in0_1 * in1_4; 
	# *(out1 +  5) += in0_1 * in1_5; 
	# *(out1 +  6) += in0_1 * in1_6; 
	# *(out1 +  7) += in0_1 * in1_7; 
	movapd 0xC0(%rsp), %xmm4
	movapd 0xD0(%rsp), %xmm5
	movapd 0xE0(%rsp), %xmm6
	movapd 0xF0(%rsp), %xmm7

	movupd 0 (%rbx), %xmm0
	movupd 16(%rbx), %xmm1
	movupd 32(%rbx), %xmm2
	movupd 48(%rbx), %xmm3

	mulpd %xmm9, %xmm4
	addpd %xmm4, %xmm0
	mulpd %xmm9, %xmm5
	addpd %xmm5, %xmm1
	mulpd %xmm9, %xmm6
	addpd %xmm6, %xmm2
	mulpd %xmm9, %xmm7
	addpd %xmm7, %xmm3

	movupd %xmm0, 0 (%rbx)
	movupd %xmm1, 16(%rbx)
	movupd %xmm2, 32(%rbx)
	movupd %xmm3, 48(%rbx)

	# *(out2 +  0) += in0_2 * in1_0; 
	# *(out2 +  1) += in0_2 * in1_1; 
	# *(out2 +  2) += in0_2 * in1_2; 
	# *(out2 +  3) += in0_2 * in1_3; 
	# *(out2 +  4) += in0_2 * in1_4; 
	# *(out2 +  5) += in0_2 * in1_5; 
	# *(out2 +  6) += in0_2 * in1_6; 
	# *(out2 +  7) += in0_2 * in1_7; 
	movapd 0xC0(%rsp), %xmm4
	movapd 0xD0(%rsp), %xmm5
	movapd 0xE0(%rsp), %xmm6
	movapd 0xF0(%rsp), %xmm7

	movupd 0 (%rcx), %xmm0
	movupd 16(%rcx), %xmm1
	movupd 32(%rcx), %xmm2
	movupd 48(%rcx), %xmm3

	mulpd %xmm10, %xmm4
	addpd %xmm4, %xmm0
	mulpd %xmm10, %xmm5
	addpd %xmm5, %xmm1
	mulpd %xmm10, %xmm6
	addpd %xmm6, %xmm2
	mulpd %xmm10, %xmm7
	addpd %xmm7, %xmm3

	movupd %xmm0, 0 (%rcx)
	movupd %xmm1, 16(%rcx)
	movupd %xmm2, 32(%rcx)
	movupd %xmm3, 48(%rcx)

	# *(out3 +  0) += in0_3 * in1_0; 
	# *(out3 +  1) += in0_3 * in1_1; 
	# *(out3 +  2) += in0_3 * in1_2; 
	# *(out3 +  3) += in0_3 * in1_3; 
	# *(out3 +  4) += in0_3 * in1_4; 
	# *(out3 +  5) += in0_3 * in1_5; 
	# *(out3 +  6) += in0_3 * in1_6; 
	# *(out3 +  7) += in0_3 * in1_7; 
	movapd 0xC0(%rsp), %xmm4
	movapd 0xD0(%rsp), %xmm5
	movapd 0xE0(%rsp), %xmm6
	movapd 0xF0(%rsp), %xmm7

	movupd 0 (%rdx), %xmm0
	movupd 16(%rdx), %xmm1
	movupd 32(%rdx), %xmm2
	movupd 48(%rdx), %xmm3

	mulpd %xmm11, %xmm4
	addpd %xmm4, %xmm0
	mulpd %xmm11, %xmm5
	addpd %xmm5, %xmm1
	mulpd %xmm11, %xmm6
	addpd %xmm6, %xmm2
	mulpd %xmm11, %xmm7
	addpd %xmm7, %xmm3

	movupd %xmm0, 0 (%rdx)
	movupd %xmm1, 16(%rdx)
	movupd %xmm2, 32(%rdx)
	movupd %xmm3, 48(%rdx)

	# *(out4 +  0) += in0_4 * in1_0; 
	# *(out4 +  1) += in0_4 * in1_1; 
	# *(out4 +  2) += in0_4 * in1_2; 
	# *(out4 +  3) += in0_4 * in1_3; 
	# *(out4 +  4) += in0_4 * in1_4; 
	# *(out4 +  5) += in0_4 * in1_5; 
	# *(out4 +  6) += in0_4 * in1_6; 
	# *(out4 +  7) += in0_4 * in1_7; 
	movapd 0xC0(%rsp), %xmm4
	movapd 0xD0(%rsp), %xmm5
	movapd 0xE0(%rsp), %xmm6
	movapd 0xF0(%rsp), %xmm7

	movupd 0 (%r12), %xmm0
	movupd 16(%r12), %xmm1
	movupd 32(%r12), %xmm2
	movupd 48(%r12), %xmm3

	mulpd %xmm12, %xmm4
	addpd %xmm4, %xmm0
	mulpd %xmm12, %xmm5
	addpd %xmm5, %xmm1
	mulpd %xmm12, %xmm6
	addpd %xmm6, %xmm2
	mulpd %xmm12, %xmm7
	addpd %xmm7, %xmm3

	movupd %xmm0, 0 (%r12)
	movupd %xmm1, 16(%r12)
	movupd %xmm2, 32(%r12)
	movupd %xmm3, 48(%r12)

	# *(out5 +  0) += in0_5 * in1_0; 
	# *(out5 +  1) += in0_5 * in1_1; 
	# *(out5 +  2) += in0_5 * in1_2; 
	# *(out5 +  3) += in0_5 * in1_3; 
	# *(out5 +  4) += in0_5 * in1_4; 
	# *(out5 +  5) += in0_5 * in1_5; 
	# *(out5 +  6) += in0_5 * in1_6; 
	# *(out5 +  7) += in0_5 * in1_7; 
	movapd 0xC0(%rsp), %xmm4
	movapd 0xD0(%rsp), %xmm5
	movapd 0xE0(%rsp), %xmm6
	movapd 0xF0(%rsp), %xmm7

	movupd 0 (%r13), %xmm0
	movupd 16(%r13), %xmm1
	movupd 32(%r13), %xmm2
	movupd 48(%r13), %xmm3

	mulpd %xmm13, %xmm4
	addpd %xmm4, %xmm0
	mulpd %xmm13, %xmm5
	addpd %xmm5, %xmm1
	mulpd %xmm13, %xmm6
	addpd %xmm6, %xmm2
	mulpd %xmm13, %xmm7
	addpd %xmm7, %xmm3

	movupd %xmm0, 0 (%r13)
	movupd %xmm1, 16(%r13)
	movupd %xmm2, 32(%r13)
	movupd %xmm3, 48(%r13)

	# *(out6 +  0) += in0_6 * in1_0; 
	# *(out6 +  1) += in0_6 * in1_1; 
	# *(out6 +  2) += in0_6 * in1_2; 
	# *(out6 +  3) += in0_6 * in1_3; 
	# *(out6 +  4) += in0_6 * in1_4; 
	# *(out6 +  5) += in0_6 * in1_5; 
	# *(out6 +  6) += in0_6 * in1_6; 
	# *(out6 +  7) += in0_6 * in1_7; 
	movapd 0xC0(%rsp), %xmm4
	movapd 0xD0(%rsp), %xmm5
	movapd 0xE0(%rsp), %xmm6
	movapd 0xF0(%rsp), %xmm7

	movupd 0 (%r14), %xmm0
	movupd 16(%r14), %xmm1
	movupd 32(%r14), %xmm2
	movupd 48(%r14), %xmm3

	mulpd %xmm14, %xmm4
	addpd %xmm4, %xmm0
	mulpd %xmm14, %xmm5
	addpd %xmm5, %xmm1
	mulpd %xmm14, %xmm6
	addpd %xmm6, %xmm2
	mulpd %xmm14, %xmm7
	addpd %xmm7, %xmm3

	movupd %xmm0, 0 (%r14)
	movupd %xmm1, 16(%r14)
	movupd %xmm2, 32(%r14)
	movupd %xmm3, 48(%r14)

	# *(out7 +  0) += in0_7 * in1_0; 
	# *(out7 +  1) += in0_7 * in1_1; 
	# *(out7 +  2) += in0_7 * in1_2; 
	# *(out7 +  3) += in0_7 * in1_3; 
	# *(out7 +  4) += in0_7 * in1_4; 
	# *(out7 +  5) += in0_7 * in1_5; 
	# *(out7 +  6) += in0_7 * in1_6; 
	# *(out7 +  7) += in0_7 * in1_7; 
	movapd 0xC0(%rsp), %xmm4
	movapd 0xD0(%rsp), %xmm5
	movapd 0xE0(%rsp), %xmm6
	movapd 0xF0(%rsp), %xmm7

	movupd 0 (%r15), %xmm0
	movupd 16(%r15), %xmm1
	movupd 32(%r15), %xmm2
	movupd 48(%r15), %xmm3

	mulpd %xmm15, %xmm4
	addpd %xmm4, %xmm0
	mulpd %xmm15, %xmm5
	addpd %xmm5, %xmm1
	mulpd %xmm15, %xmm6
	addpd %xmm6, %xmm2
	mulpd %xmm15, %xmm7
	addpd %xmm7, %xmm3

	movupd %xmm0, 0 (%r15)
	movupd %xmm1, 16(%r15)
	movupd %xmm2, 32(%r15)
	movupd %xmm3, 48(%r15)

	addq $64, %rax   	# out0 += 8
	addq $64, %rbx   	# out1 += 8
	addq $64, %rcx   	# out2 += 8
	addq $64, %rdx   	# out3 += 8
	addq $64, %r12   	# out4 += 8
	addq $64, %r13   	# out5 += 8
	addq $64, %r14   	# out6 += 8
	addq $64, %r15   	# out7 += 8
	addq $64, %rdi   	# in1 += 8

	# in1_0 = *(in1 + 0)
	# in1_1 = *(in1 + 1)
	# in1_2 = *(in1 + 2)
	# in1_3 = *(in1 + 3)
	# in1_4 = *(in1 + 4)
	# in1_5 = *(in1 + 5)
	# in1_6 = *(in1 + 6)
	# in1_7 = *(in1 + 7)
	movupd 0 (%rdi), %xmm4
	movapd %xmm4, 0xC0(%rsp)
	movupd 16(%rdi), %xmm5
	movapd %xmm5, 0xD0(%rsp)
	movupd 32(%rdi), %xmm6
	movapd %xmm6, 0xE0(%rsp)
	movupd 48(%rdi), %xmm7
	movapd %xmm7, 0xF0(%rsp)

	# *(out0 +  0) += in0_0 * in1_0; 
	# *(out0 +  1) += in0_0 * in1_1; 
	# *(out0 +  2) += in0_0 * in1_2; 
	# *(out0 +  3) += in0_0 * in1_3; 
	# *(out0 +  4) += in0_0 * in1_4; 
	# *(out0 +  5) += in0_0 * in1_5; 
	# *(out0 +  6) += in0_0 * in1_6; 
	# *(out0 +  7) += in0_0 * in1_7; 
	movupd 0 (%rax), %xmm0
	movupd 16(%rax), %xmm1
	movupd 32(%rax), %xmm2
	movupd 48(%rax), %xmm3

	mulpd %xmm8, %xmm4
	addpd %xmm4, %xmm0
	mulpd %xmm8, %xmm5
	addpd %xmm5, %xmm1
	mulpd %xmm8, %xmm6
	addpd %xmm6, %xmm2
	mulpd %xmm8, %xmm7
	addpd %xmm7, %xmm3

	movupd %xmm0, 0 (%rax)
	movupd %xmm1, 16(%rax)
	movupd %xmm2, 32(%rax)
	movupd %xmm3, 48(%rax)

	# *(out1 +  0) += in0_1 * in1_0; 
	# *(out1 +  1) += in0_1 * in1_1; 
	# *(out1 +  2) += in0_1 * in1_2; 
	# *(out1 +  3) += in0_1 * in1_3; 
	# *(out1 +  4) += in0_1 * in1_4; 
	# *(out1 +  5) += in0_1 * in1_5; 
	# *(out1 +  6) += in0_1 * in1_6; 
	# *(out1 +  7) += in0_1 * in1_7; 
	movapd 0xC0(%rsp), %xmm4
	movapd 0xD0(%rsp), %xmm5
	movapd 0xE0(%rsp), %xmm6
	movapd 0xF0(%rsp), %xmm7

	movupd 0 (%rbx), %xmm0
	movupd 16(%rbx), %xmm1
	movupd 32(%rbx), %xmm2
	movupd 48(%rbx), %xmm3

	mulpd %xmm9, %xmm4
	addpd %xmm4, %xmm0
	mulpd %xmm9, %xmm5
	addpd %xmm5, %xmm1
	mulpd %xmm9, %xmm6
	addpd %xmm6, %xmm2
	mulpd %xmm9, %xmm7
	addpd %xmm7, %xmm3

	movupd %xmm0, 0 (%rbx)
	movupd %xmm1, 16(%rbx)
	movupd %xmm2, 32(%rbx)
	movupd %xmm3, 48(%rbx)

	# *(out2 +  0) += in0_2 * in1_0; 
	# *(out2 +  1) += in0_2 * in1_1; 
	# *(out2 +  2) += in0_2 * in1_2; 
	# *(out2 +  3) += in0_2 * in1_3; 
	# *(out2 +  4) += in0_2 * in1_4; 
	# *(out2 +  5) += in0_2 * in1_5; 
	# *(out2 +  6) += in0_2 * in1_6; 
	# *(out2 +  7) += in0_2 * in1_7; 
	movapd 0xC0(%rsp), %xmm4
	movapd 0xD0(%rsp), %xmm5
	movapd 0xE0(%rsp), %xmm6
	movapd 0xF0(%rsp), %xmm7

	movupd 0 (%rcx), %xmm0
	movupd 16(%rcx), %xmm1
	movupd 32(%rcx), %xmm2
	movupd 48(%rcx), %xmm3

	mulpd %xmm10, %xmm4
	addpd %xmm4, %xmm0
	mulpd %xmm10, %xmm5
	addpd %xmm5, %xmm1
	mulpd %xmm10, %xmm6
	addpd %xmm6, %xmm2
	mulpd %xmm10, %xmm7
	addpd %xmm7, %xmm3

	movupd %xmm0, 0 (%rcx)
	movupd %xmm1, 16(%rcx)
	movupd %xmm2, 32(%rcx)
	movupd %xmm3, 48(%rcx)

	# *(out3 +  0) += in0_3 * in1_0; 
	# *(out3 +  1) += in0_3 * in1_1; 
	# *(out3 +  2) += in0_3 * in1_2; 
	# *(out3 +  3) += in0_3 * in1_3; 
	# *(out3 +  4) += in0_3 * in1_4; 
	# *(out3 +  5) += in0_3 * in1_5; 
	# *(out3 +  6) += in0_3 * in1_6; 
	# *(out3 +  7) += in0_3 * in1_7; 
	movapd 0xC0(%rsp), %xmm4
	movapd 0xD0(%rsp), %xmm5
	movapd 0xE0(%rsp), %xmm6
	movapd 0xF0(%rsp), %xmm7

	movupd 0 (%rdx), %xmm0
	movupd 16(%rdx), %xmm1
	movupd 32(%rdx), %xmm2
	movupd 48(%rdx), %xmm3

	mulpd %xmm11, %xmm4
	addpd %xmm4, %xmm0
	mulpd %xmm11, %xmm5
	addpd %xmm5, %xmm1
	mulpd %xmm11, %xmm6
	addpd %xmm6, %xmm2
	mulpd %xmm11, %xmm7
	addpd %xmm7, %xmm3

	movupd %xmm0, 0 (%rdx)
	movupd %xmm1, 16(%rdx)
	movupd %xmm2, 32(%rdx)
	movupd %xmm3, 48(%rdx)

	# *(out4 +  0) += in0_4 * in1_0; 
	# *(out4 +  1) += in0_4 * in1_1; 
	# *(out4 +  2) += in0_4 * in1_2; 
	# *(out4 +  3) += in0_4 * in1_3; 
	# *(out4 +  4) += in0_4 * in1_4; 
	# *(out4 +  5) += in0_4 * in1_5; 
	# *(out4 +  6) += in0_4 * in1_6; 
	# *(out4 +  7) += in0_4 * in1_7; 
	movapd 0xC0(%rsp), %xmm4
	movapd 0xD0(%rsp), %xmm5
	movapd 0xE0(%rsp), %xmm6
	movapd 0xF0(%rsp), %xmm7

	movupd 0 (%r12), %xmm0
	movupd 16(%r12), %xmm1
	movupd 32(%r12), %xmm2
	movupd 48(%r12), %xmm3

	mulpd %xmm12, %xmm4
	addpd %xmm4, %xmm0
	mulpd %xmm12, %xmm5
	addpd %xmm5, %xmm1
	mulpd %xmm12, %xmm6
	addpd %xmm6, %xmm2
	mulpd %xmm12, %xmm7
	addpd %xmm7, %xmm3

	movupd %xmm0, 0 (%r12)
	movupd %xmm1, 16(%r12)
	movupd %xmm2, 32(%r12)
	movupd %xmm3, 48(%r12)

	# *(out5 +  0) += in0_5 * in1_0; 
	# *(out5 +  1) += in0_5 * in1_1; 
	# *(out5 +  2) += in0_5 * in1_2; 
	# *(out5 +  3) += in0_5 * in1_3; 
	# *(out5 +  4) += in0_5 * in1_4; 
	# *(out5 +  5) += in0_5 * in1_5; 
	# *(out5 +  6) += in0_5 * in1_6; 
	# *(out5 +  7) += in0_5 * in1_7; 
	movapd 0xC0(%rsp), %xmm4
	movapd 0xD0(%rsp), %xmm5
	movapd 0xE0(%rsp), %xmm6
	movapd 0xF0(%rsp), %xmm7

	movupd 0 (%r13), %xmm0
	movupd 16(%r13), %xmm1
	movupd 32(%r13), %xmm2
	movupd 48(%r13), %xmm3

	mulpd %xmm13, %xmm4
	addpd %xmm4, %xmm0
	mulpd %xmm13, %xmm5
	addpd %xmm5, %xmm1
	mulpd %xmm13, %xmm6
	addpd %xmm6, %xmm2
	mulpd %xmm13, %xmm7
	addpd %xmm7, %xmm3

	movupd %xmm0, 0 (%r13)
	movupd %xmm1, 16(%r13)
	movupd %xmm2, 32(%r13)
	movupd %xmm3, 48(%r13)

	# *(out6 +  0) += in0_6 * in1_0; 
	# *(out6 +  1) += in0_6 * in1_1; 
	# *(out6 +  2) += in0_6 * in1_2; 
	# *(out6 +  3) += in0_6 * in1_3; 
	# *(out6 +  4) += in0_6 * in1_4; 
	# *(out6 +  5) += in0_6 * in1_5; 
	# *(out6 +  6) += in0_6 * in1_6; 
	# *(out6 +  7) += in0_6 * in1_7; 
	movapd 0xC0(%rsp), %xmm4
	movapd 0xD0(%rsp), %xmm5
	movapd 0xE0(%rsp), %xmm6
	movapd 0xF0(%rsp), %xmm7

	movupd 0 (%r14), %xmm0
	movupd 16(%r14), %xmm1
	movupd 32(%r14), %xmm2
	movupd 48(%r14), %xmm3

	mulpd %xmm14, %xmm4
	addpd %xmm4, %xmm0
	mulpd %xmm14, %xmm5
	addpd %xmm5, %xmm1
	mulpd %xmm14, %xmm6
	addpd %xmm6, %xmm2
	mulpd %xmm14, %xmm7
	addpd %xmm7, %xmm3

	movupd %xmm0, 0 (%r14)
	movupd %xmm1, 16(%r14)
	movupd %xmm2, 32(%r14)
	movupd %xmm3, 48(%r14)

	# *(out7 +  0) += in0_7 * in1_0; 
	# *(out7 +  1) += in0_7 * in1_1; 
	# *(out7 +  2) += in0_7 * in1_2; 
	# *(out7 +  3) += in0_7 * in1_3; 
	# *(out7 +  4) += in0_7 * in1_4; 
	# *(out7 +  5) += in0_7 * in1_5; 
	# *(out7 +  6) += in0_7 * in1_6; 
	# *(out7 +  7) += in0_7 * in1_7; 
	movapd 0xC0(%rsp), %xmm4
	movapd 0xD0(%rsp), %xmm5
	movapd 0xE0(%rsp), %xmm6
	movapd 0xF0(%rsp), %xmm7

	movupd 0 (%r15), %xmm0
	movupd 16(%r15), %xmm1
	movupd 32(%r15), %xmm2
	movupd 48(%r15), %xmm3

	mulpd %xmm15, %xmm4
	addpd %xmm4, %xmm0
	mulpd %xmm15, %xmm5
	addpd %xmm5, %xmm1
	mulpd %xmm15, %xmm6
	addpd %xmm6, %xmm2
	mulpd %xmm15, %xmm7
	addpd %xmm7, %xmm3

	movupd %xmm0, 0 (%r15)
	movupd %xmm1, 16(%r15)
	movupd %xmm2, 32(%r15)
	movupd %xmm3, 48(%r15)

	addq $64, %rax   	# out0 += 8
	addq $64, %rbx   	# out1 += 8
	addq $64, %rcx   	# out2 += 8
	addq $64, %rdx   	# out3 += 8
	addq $64, %r12   	# out4 += 8
	addq $64, %r13   	# out5 += 8
	addq $64, %r14   	# out6 += 8
	addq $64, %r15   	# out7 += 8
	addq $64, %rdi   	# in1 += 8

	# in1_0 = *(in1 + 0)
	# in1_1 = *(in1 + 1)
	# in1_2 = *(in1 + 2)
	# in1_3 = *(in1 + 3)
	# in1_4 = *(in1 + 4)
	# in1_5 = *(in1 + 5)
	# in1_6 = *(in1 + 6)
	# in1_7 = *(in1 + 7)
	movupd 0 (%rdi), %xmm4
	movapd %xmm4, 0xC0(%rsp)
	movupd 16(%rdi), %xmm5
	movapd %xmm5, 0xD0(%rsp)
	movupd 32(%rdi), %xmm6
	movapd %xmm6, 0xE0(%rsp)
	movupd 48(%rdi), %xmm7
	movapd %xmm7, 0xF0(%rsp)

	# *(out0 +  0) += in0_0 * in1_0; 
	# *(out0 +  1) += in0_0 * in1_1; 
	# *(out0 +  2) += in0_0 * in1_2; 
	# *(out0 +  3) += in0_0 * in1_3; 
	# *(out0 +  4) += in0_0 * in1_4; 
	# *(out0 +  5) += in0_0 * in1_5; 
	# *(out0 +  6) += in0_0 * in1_6; 
	# *(out0 +  7) += in0_0 * in1_7; 
	movupd 0 (%rax), %xmm0
	movupd 16(%rax), %xmm1
	movupd 32(%rax), %xmm2
	movupd 48(%rax), %xmm3

	mulpd %xmm8, %xmm4
	addpd %xmm4, %xmm0
	mulpd %xmm8, %xmm5
	addpd %xmm5, %xmm1
	mulpd %xmm8, %xmm6
	addpd %xmm6, %xmm2
	mulpd %xmm8, %xmm7
	addpd %xmm7, %xmm3

	movupd %xmm0, 0 (%rax)
	movupd %xmm1, 16(%rax)
	movupd %xmm2, 32(%rax)
	movupd %xmm3, 48(%rax)

	# *(out1 +  0) += in0_1 * in1_0; 
	# *(out1 +  1) += in0_1 * in1_1; 
	# *(out1 +  2) += in0_1 * in1_2; 
	# *(out1 +  3) += in0_1 * in1_3; 
	# *(out1 +  4) += in0_1 * in1_4; 
	# *(out1 +  5) += in0_1 * in1_5; 
	# *(out1 +  6) += in0_1 * in1_6; 
	# *(out1 +  7) += in0_1 * in1_7; 
	movapd 0xC0(%rsp), %xmm4
	movapd 0xD0(%rsp), %xmm5
	movapd 0xE0(%rsp), %xmm6
	movapd 0xF0(%rsp), %xmm7

	movupd 0 (%rbx), %xmm0
	movupd 16(%rbx), %xmm1
	movupd 32(%rbx), %xmm2
	movupd 48(%rbx), %xmm3

	mulpd %xmm9, %xmm4
	addpd %xmm4, %xmm0
	mulpd %xmm9, %xmm5
	addpd %xmm5, %xmm1
	mulpd %xmm9, %xmm6
	addpd %xmm6, %xmm2
	mulpd %xmm9, %xmm7
	addpd %xmm7, %xmm3

	movupd %xmm0, 0 (%rbx)
	movupd %xmm1, 16(%rbx)
	movupd %xmm2, 32(%rbx)
	movupd %xmm3, 48(%rbx)

	# *(out2 +  0) += in0_2 * in1_0; 
	# *(out2 +  1) += in0_2 * in1_1; 
	# *(out2 +  2) += in0_2 * in1_2; 
	# *(out2 +  3) += in0_2 * in1_3; 
	# *(out2 +  4) += in0_2 * in1_4; 
	# *(out2 +  5) += in0_2 * in1_5; 
	# *(out2 +  6) += in0_2 * in1_6; 
	# *(out2 +  7) += in0_2 * in1_7; 
	movapd 0xC0(%rsp), %xmm4
	movapd 0xD0(%rsp), %xmm5
	movapd 0xE0(%rsp), %xmm6
	movapd 0xF0(%rsp), %xmm7

	movupd 0 (%rcx), %xmm0
	movupd 16(%rcx), %xmm1
	movupd 32(%rcx), %xmm2
	movupd 48(%rcx), %xmm3

	mulpd %xmm10, %xmm4
	addpd %xmm4, %xmm0
	mulpd %xmm10, %xmm5
	addpd %xmm5, %xmm1
	mulpd %xmm10, %xmm6
	addpd %xmm6, %xmm2
	mulpd %xmm10, %xmm7
	addpd %xmm7, %xmm3

	movupd %xmm0, 0 (%rcx)
	movupd %xmm1, 16(%rcx)
	movupd %xmm2, 32(%rcx)
	movupd %xmm3, 48(%rcx)

	# *(out3 +  0) += in0_3 * in1_0; 
	# *(out3 +  1) += in0_3 * in1_1; 
	# *(out3 +  2) += in0_3 * in1_2; 
	# *(out3 +  3) += in0_3 * in1_3; 
	# *(out3 +  4) += in0_3 * in1_4; 
	# *(out3 +  5) += in0_3 * in1_5; 
	# *(out3 +  6) += in0_3 * in1_6; 
	# *(out3 +  7) += in0_3 * in1_7; 
	movapd 0xC0(%rsp), %xmm4
	movapd 0xD0(%rsp), %xmm5
	movapd 0xE0(%rsp), %xmm6
	movapd 0xF0(%rsp), %xmm7

	movupd 0 (%rdx), %xmm0
	movupd 16(%rdx), %xmm1
	movupd 32(%rdx), %xmm2
	movupd 48(%rdx), %xmm3

	mulpd %xmm11, %xmm4
	addpd %xmm4, %xmm0
	mulpd %xmm11, %xmm5
	addpd %xmm5, %xmm1
	mulpd %xmm11, %xmm6
	addpd %xmm6, %xmm2
	mulpd %xmm11, %xmm7
	addpd %xmm7, %xmm3

	movupd %xmm0, 0 (%rdx)
	movupd %xmm1, 16(%rdx)
	movupd %xmm2, 32(%rdx)
	movupd %xmm3, 48(%rdx)

	# *(out4 +  0) += in0_4 * in1_0; 
	# *(out4 +  1) += in0_4 * in1_1; 
	# *(out4 +  2) += in0_4 * in1_2; 
	# *(out4 +  3) += in0_4 * in1_3; 
	# *(out4 +  4) += in0_4 * in1_4; 
	# *(out4 +  5) += in0_4 * in1_5; 
	# *(out4 +  6) += in0_4 * in1_6; 
	# *(out4 +  7) += in0_4 * in1_7; 
	movapd 0xC0(%rsp), %xmm4
	movapd 0xD0(%rsp), %xmm5
	movapd 0xE0(%rsp), %xmm6
	movapd 0xF0(%rsp), %xmm7

	movupd 0 (%r12), %xmm0
	movupd 16(%r12), %xmm1
	movupd 32(%r12), %xmm2
	movupd 48(%r12), %xmm3

	mulpd %xmm12, %xmm4
	addpd %xmm4, %xmm0
	mulpd %xmm12, %xmm5
	addpd %xmm5, %xmm1
	mulpd %xmm12, %xmm6
	addpd %xmm6, %xmm2
	mulpd %xmm12, %xmm7
	addpd %xmm7, %xmm3

	movupd %xmm0, 0 (%r12)
	movupd %xmm1, 16(%r12)
	movupd %xmm2, 32(%r12)
	movupd %xmm3, 48(%r12)

	# *(out5 +  0) += in0_5 * in1_0; 
	# *(out5 +  1) += in0_5 * in1_1; 
	# *(out5 +  2) += in0_5 * in1_2; 
	# *(out5 +  3) += in0_5 * in1_3; 
	# *(out5 +  4) += in0_5 * in1_4; 
	# *(out5 +  5) += in0_5 * in1_5; 
	# *(out5 +  6) += in0_5 * in1_6; 
	# *(out5 +  7) += in0_5 * in1_7; 
	movapd 0xC0(%rsp), %xmm4
	movapd 0xD0(%rsp), %xmm5
	movapd 0xE0(%rsp), %xmm6
	movapd 0xF0(%rsp), %xmm7

	movupd 0 (%r13), %xmm0
	movupd 16(%r13), %xmm1
	movupd 32(%r13), %xmm2
	movupd 48(%r13), %xmm3

	mulpd %xmm13, %xmm4
	addpd %xmm4, %xmm0
	mulpd %xmm13, %xmm5
	addpd %xmm5, %xmm1
	mulpd %xmm13, %xmm6
	addpd %xmm6, %xmm2
	mulpd %xmm13, %xmm7
	addpd %xmm7, %xmm3

	movupd %xmm0, 0 (%r13)
	movupd %xmm1, 16(%r13)
	movupd %xmm2, 32(%r13)
	movupd %xmm3, 48(%r13)

	# *(out6 +  0) += in0_6 * in1_0; 
	# *(out6 +  1) += in0_6 * in1_1; 
	# *(out6 +  2) += in0_6 * in1_2; 
	# *(out6 +  3) += in0_6 * in1_3; 
	# *(out6 +  4) += in0_6 * in1_4; 
	# *(out6 +  5) += in0_6 * in1_5; 
	# *(out6 +  6) += in0_6 * in1_6; 
	# *(out6 +  7) += in0_6 * in1_7; 
	movapd 0xC0(%rsp), %xmm4
	movapd 0xD0(%rsp), %xmm5
	movapd 0xE0(%rsp), %xmm6
	movapd 0xF0(%rsp), %xmm7

	movupd 0 (%r14), %xmm0
	movupd 16(%r14), %xmm1
	movupd 32(%r14), %xmm2
	movupd 48(%r14), %xmm3

	mulpd %xmm14, %xmm4
	addpd %xmm4, %xmm0
	mulpd %xmm14, %xmm5
	addpd %xmm5, %xmm1
	mulpd %xmm14, %xmm6
	addpd %xmm6, %xmm2
	mulpd %xmm14, %xmm7
	addpd %xmm7, %xmm3

	movupd %xmm0, 0 (%r14)
	movupd %xmm1, 16(%r14)
	movupd %xmm2, 32(%r14)
	movupd %xmm3, 48(%r14)

	# *(out7 +  0) += in0_7 * in1_0; 
	# *(out7 +  1) += in0_7 * in1_1; 
	# *(out7 +  2) += in0_7 * in1_2; 
	# *(out7 +  3) += in0_7 * in1_3; 
	# *(out7 +  4) += in0_7 * in1_4; 
	# *(out7 +  5) += in0_7 * in1_5; 
	# *(out7 +  6) += in0_7 * in1_6; 
	# *(out7 +  7) += in0_7 * in1_7; 
	movapd 0xC0(%rsp), %xmm4
	movapd 0xD0(%rsp), %xmm5
	movapd 0xE0(%rsp), %xmm6
	movapd 0xF0(%rsp), %xmm7

	movupd 0 (%r15), %xmm0
	movupd 16(%r15), %xmm1
	movupd 32(%r15), %xmm2
	movupd 48(%r15), %xmm3

	mulpd %xmm15, %xmm4
	addpd %xmm4, %xmm0
	mulpd %xmm15, %xmm5
	addpd %xmm5, %xmm1
	mulpd %xmm15, %xmm6
	addpd %xmm6, %xmm2
	mulpd %xmm15, %xmm7
	addpd %xmm7, %xmm3

	movupd %xmm0, 0 (%r15)
	movupd %xmm1, 16(%r15)
	movupd %xmm2, 32(%r15)
	movupd %xmm3, 48(%r15)

	addq $64, %rax   	# out0 += 8
	addq $64, %rbx   	# out1 += 8
	addq $64, %rcx   	# out2 += 8
	addq $64, %rdx   	# out3 += 8
	addq $64, %r12   	# out4 += 8
	addq $64, %r13   	# out5 += 8
	addq $64, %r14   	# out6 += 8
	addq $64, %r15   	# out7 += 8
	addq $64, %rdi   	# in1 += 8

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

	# vmdot_product_8x16(Out + div, In0, _In1 + div, k, mod, In0S, In0s, In1s);
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
	call vmdot_product_double_8x16

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
vmdot_product_double_8x32_new:
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
	subq $768, %rsp
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

	movq 0x08(%rsp), %rdi	# Out0 = Out + In1s * 0
	movq %rdi, 0x80(%rsp)
	addq %r9, %rdi		# Out1 = Out + In1s * 1
	movq %rdi, 0x88(%rsp)
	addq %r9, %rdi		# Out2 = Out + In1s * 2
	movq %rdi, 0x90(%rsp)
	addq %r9, %rdi		# Out3 = Out + In1s * 3
	movq %rdi, 0x98(%rsp)
	addq %r9, %rdi		# Out4 = Out + In1s * 4
	movq %rdi, 0xA0(%rsp)
	addq %r9, %rdi		# Out5 = Out + In1s * 5
	movq %rdi, 0xA8(%rsp)
	addq %r9, %rdi		# Out6 = Out + In1s * 6
	movq %rdi, 0xB0(%rsp)
	addq %r9, %rdi		# Out7 = Out + In1s * 7
	movq %rdi, 0xB8(%rsp)

	movq 0x10(%rsp), %rsi 	# in0 = In0
	movq 0x18(%rsp), %r8	# In1 = _In1

	movq 0x30(%rsp), %r10	# n
	movq %r10, %r11
	andq $31, %r10		# mod = n & 31
	shrq $5, %r11		# div = n >> 5
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
	movq 0x90(%rsp), %rcx		# out2 = Out2
	movq 0x98(%rsp), %rdx		# out3 = Out3
	movq 0xA0(%rsp), %r12		# out4 = Out4
	movq 0xA8(%rsp), %r13		# out5 = Out5
	movq 0xB0(%rsp), %r14		# out6 = Out6
	movq 0xB8(%rsp), %r15		# out7 = Out7
	movddup 0(%rsi), %xmm0		# in0_0 = *In0
	movapd %xmm0, 0x100(%rsp)
	movq 0x60(%rsp), %r11		# j = In0S
	movddup (%rsi, %r11), %xmm1	# in0_1 = *(in0 + j)
	movapd %xmm1, 0x110(%rsp)
	addq 0x60(%rsp), %r11		# j += In0S
	movddup (%rsi, %r11), %xmm2	# in0_2 = *(in0 + j)
	movapd %xmm2, 0x120(%rsp)
	addq 0x60(%rsp), %r11		# j += In0S
	movddup (%rsi, %r11), %xmm3	# in0_3 = *(in0 + j)
	movapd %xmm3, 0x130(%rsp)
	addq 0x60(%rsp), %r11		# j += In0S
	movddup (%rsi, %r11), %xmm4	# in0_4 = *(in0 + j)
	movapd %xmm4, 0x140(%rsp)
	addq 0x60(%rsp), %r11		# j += In0S
	movddup (%rsi, %r11), %xmm5	# in0_5 = *(in0 + j)
	movapd %xmm5, 0x150(%rsp)
	addq 0x60(%rsp), %r11		# j += In0S
	movddup (%rsi, %r11), %xmm6	# in0_6 = *(in0 + j)
	movapd %xmm6, 0x160(%rsp)
	addq 0x60(%rsp), %r11		# j += In0S
	movddup (%rsi, %r11), %xmm7	# in0_7 = *(in0 + j)
	movapd %xmm7, 0x170(%rsp)
	addq 0x68(%rsp), %rsi		# in0 += In0s
	movq %r8, %rdi			# in1 = In1
	addq %r9, %r8			# In1 += In1s

	movq 0x48(%rsp), %r11  		# for (j = div; j; j--)
	test %r11, %r11
	je 2f
	.p2align 6
1:
	# in1_0  = *(in1 + 0)
	# ...
	# in1_31 = *(in1 + 31)
	movupd 0x00(%rdi), %xmm8
	movapd %xmm8,  0x200(%rsp)
	movupd 0x10(%rdi), %xmm9
	movapd %xmm9,  0x210(%rsp)
	movupd 0x20(%rdi), %xmm10
	movapd %xmm10, 0x220(%rsp)
	movupd 0x30(%rdi), %xmm11
	movapd %xmm11, 0x230(%rsp)
	movupd 0x40(%rdi), %xmm12
	movapd %xmm12, 0x240(%rsp)
	movupd 0x50(%rdi), %xmm13
	movapd %xmm13, 0x250(%rsp)
	movupd 0x60(%rdi), %xmm14
	movapd %xmm14, 0x260(%rsp)
	movupd 0x70(%rdi), %xmm15
	movapd %xmm15, 0x270(%rsp)
	movupd 0x80(%rdi), %xmm0
	movapd %xmm0,  0x280(%rsp)
	movupd 0x90(%rdi), %xmm1
	movapd %xmm1,  0x290(%rsp)
	movupd 0xA0(%rdi), %xmm2
	movapd %xmm2,  0x2A0(%rsp)
	movupd 0xB0(%rdi), %xmm3
	movapd %xmm3,  0x2B0(%rsp)
	movupd 0xC0(%rdi), %xmm4
	movapd %xmm4,  0x2C0(%rsp)
	movupd 0xD0(%rdi), %xmm5
	movapd %xmm5,  0x2D0(%rsp)
	movupd 0xE0(%rdi), %xmm6
	movapd %xmm6,  0x2E0(%rsp)
	movupd 0xF0(%rdi), %xmm7
	movapd %xmm7,  0x2F0(%rsp)
	addq $256, %rdi   		# in1 += 32

	# *(out0 +  0) += in0_0 * in1_0; 
	# ...
	# *(out0 + 31) += in0_0 * in1_31; 
	movupd 0x00(%rax), %xmm0
	movupd 0x10(%rax), %xmm1
	movupd 0x20(%rax), %xmm2
	movupd 0x30(%rax), %xmm3
	movupd 0x40(%rax), %xmm4
	movupd 0x50(%rax), %xmm5
	movupd 0x60(%rax), %xmm6
	movupd 0x70(%rax), %xmm7
	mulpd 0x100(%rsp), %xmm8
	addpd %xmm8 , %xmm0
	mulpd 0x100(%rsp), %xmm9
	addpd %xmm9 , %xmm1
	mulpd 0x100(%rsp), %xmm10
	addpd %xmm10, %xmm2
	mulpd 0x100(%rsp), %xmm11
	addpd %xmm11, %xmm3
	mulpd 0x100(%rsp), %xmm12
	addpd %xmm12, %xmm4
	mulpd 0x100(%rsp), %xmm13
	addpd %xmm13, %xmm5
	mulpd 0x100(%rsp), %xmm14
	addpd %xmm14, %xmm6
	mulpd 0x100(%rsp), %xmm15
	addpd %xmm15, %xmm7
	movupd %xmm0 , 0x00(%rax)
	movupd %xmm1 , 0x10(%rax)
	movupd %xmm2 , 0x20(%rax)
	movupd %xmm3 , 0x30(%rax)
	movupd %xmm4 , 0x40(%rax)
	movupd %xmm5 , 0x50(%rax)
	movupd %xmm6 , 0x60(%rax)
	movupd %xmm7 , 0x70(%rax)

	movapd 0x280(%rsp), %xmm0
	movapd 0x290(%rsp), %xmm1
	movapd 0x2A0(%rsp), %xmm2
	movapd 0x2B0(%rsp), %xmm3
	movapd 0x2C0(%rsp), %xmm4
	movapd 0x2D0(%rsp), %xmm5
	movapd 0x2E0(%rsp), %xmm6
	movapd 0x2F0(%rsp), %xmm7
	movupd 0x80(%rax), %xmm8
	movupd 0x90(%rax), %xmm9
	movupd 0xA0(%rax), %xmm10
	movupd 0xB0(%rax), %xmm11
	movupd 0xC0(%rax), %xmm12
	movupd 0xD0(%rax), %xmm13
	movupd 0xE0(%rax), %xmm14
	movupd 0xF0(%rax), %xmm15
	mulpd 0x100(%rsp), %xmm0
	addpd %xmm0 , %xmm8
	mulpd 0x100(%rsp), %xmm1
	addpd %xmm1 , %xmm9
	mulpd 0x100(%rsp), %xmm2
	addpd %xmm2 , %xmm10
	mulpd 0x100(%rsp), %xmm3
	addpd %xmm3 , %xmm11
	mulpd 0x100(%rsp), %xmm4
	addpd %xmm4 , %xmm12
	mulpd 0x100(%rsp), %xmm5
	addpd %xmm5 , %xmm13
	mulpd 0x100(%rsp), %xmm6
	addpd %xmm6 , %xmm14
	mulpd 0x100(%rsp), %xmm7
	addpd %xmm7 , %xmm15
	movupd %xmm8 , 0x80(%rax)
	movupd %xmm9 , 0x90(%rax)
	movupd %xmm10, 0xA0(%rax)
	movupd %xmm11, 0xB0(%rax)
	movupd %xmm12, 0xC0(%rax)
	movupd %xmm13, 0xD0(%rax)
	movupd %xmm14, 0xE0(%rax)
	movupd %xmm15, 0xF0(%rax)
	addq $256, %rax   		# out0 += 8

	# *(out1 +  0) += in0_1 * in1_0; 
	# ...
	# *(out1 + 32) += in0_1 * in1_32; 
	movapd 0x200(%rsp), %xmm8
	movapd 0x210(%rsp), %xmm9
	movapd 0x220(%rsp), %xmm10
	movapd 0x230(%rsp), %xmm11
	movapd 0x240(%rsp), %xmm12
	movapd 0x250(%rsp), %xmm13
	movapd 0x260(%rsp), %xmm14
	movapd 0x270(%rsp), %xmm15
	movupd 0x00(%rbx), %xmm0
	movupd 0x10(%rbx), %xmm1
	movupd 0x20(%rbx), %xmm2
	movupd 0x30(%rbx), %xmm3
	movupd 0x40(%rbx), %xmm4
	movupd 0x50(%rbx), %xmm5
	movupd 0x60(%rbx), %xmm6
	movupd 0x70(%rbx), %xmm7
	mulpd 0x110(%rsp), %xmm8
	addpd %xmm8 , %xmm0
	mulpd 0x110(%rsp), %xmm9
	addpd %xmm9 , %xmm1
	mulpd 0x110(%rsp), %xmm10
	addpd %xmm10, %xmm2
	mulpd 0x110(%rsp), %xmm11
	addpd %xmm11, %xmm3
	mulpd 0x110(%rsp), %xmm12
	addpd %xmm12, %xmm4
	mulpd 0x110(%rsp), %xmm13
	addpd %xmm13, %xmm5
	mulpd 0x110(%rsp), %xmm14
	addpd %xmm14, %xmm6
	mulpd 0x110(%rsp), %xmm15
	addpd %xmm15, %xmm7
	movupd %xmm0 , 0x00(%rbx)
	movupd %xmm1 , 0x10(%rbx)
	movupd %xmm2 , 0x20(%rbx)
	movupd %xmm3 , 0x30(%rbx)
	movupd %xmm4 , 0x40(%rbx)
	movupd %xmm5 , 0x50(%rbx)
	movupd %xmm6 , 0x60(%rbx)
	movupd %xmm7 , 0x70(%rbx)

	movapd 0x280(%rsp), %xmm0
	movapd 0x290(%rsp), %xmm1
	movapd 0x2A0(%rsp), %xmm2
	movapd 0x2B0(%rsp), %xmm3
	movapd 0x2C0(%rsp), %xmm4
	movapd 0x2D0(%rsp), %xmm5
	movapd 0x2E0(%rsp), %xmm6
	movapd 0x2F0(%rsp), %xmm7
	movupd 0x80(%rbx), %xmm8
	movupd 0x90(%rbx), %xmm9
	movupd 0xA0(%rbx), %xmm10
	movupd 0xB0(%rbx), %xmm11
	movupd 0xC0(%rbx), %xmm12
	movupd 0xD0(%rbx), %xmm13
	movupd 0xE0(%rbx), %xmm14
	movupd 0xF0(%rbx), %xmm15
	mulpd 0x110(%rsp), %xmm0
	addpd %xmm0 , %xmm8
	mulpd 0x110(%rsp), %xmm1
	addpd %xmm1 , %xmm9
	mulpd 0x110(%rsp), %xmm2
	addpd %xmm2 , %xmm10
	mulpd 0x110(%rsp), %xmm3
	addpd %xmm3 , %xmm11
	mulpd 0x110(%rsp), %xmm4
	addpd %xmm4 , %xmm12
	mulpd 0x110(%rsp), %xmm5
	addpd %xmm5 , %xmm13
	mulpd 0x110(%rsp), %xmm6
	addpd %xmm6 , %xmm14
	mulpd 0x110(%rsp), %xmm7
	addpd %xmm7 , %xmm15
	movupd %xmm8 , 0x80(%rbx)
	movupd %xmm9 , 0x90(%rbx)
	movupd %xmm10, 0xA0(%rbx)
	movupd %xmm11, 0xB0(%rbx)
	movupd %xmm12, 0xC0(%rbx)
	movupd %xmm13, 0xD0(%rbx)
	movupd %xmm14, 0xE0(%rbx)
	movupd %xmm15, 0xF0(%rbx)
	addq $256, %rbx   		# out1 += 256

	# *(out2 +  0) += in0_2 * in1_0; 
	# ...
	# *(out2 + 31) += in0_2 * in1_31; 
	movapd 0x200(%rsp), %xmm8
	movapd 0x210(%rsp), %xmm9
	movapd 0x220(%rsp), %xmm10
	movapd 0x230(%rsp), %xmm11
	movapd 0x240(%rsp), %xmm12
	movapd 0x250(%rsp), %xmm13
	movapd 0x260(%rsp), %xmm14
	movapd 0x270(%rsp), %xmm15
	movupd 0x00(%rcx), %xmm0
	movupd 0x10(%rcx), %xmm1
	movupd 0x20(%rcx), %xmm2
	movupd 0x30(%rcx), %xmm3
	movupd 0x40(%rcx), %xmm4
	movupd 0x50(%rcx), %xmm5
	movupd 0x60(%rcx), %xmm6
	movupd 0x70(%rcx), %xmm7
	mulpd 0x120(%rsp), %xmm8
	addpd %xmm8 , %xmm0
	mulpd 0x120(%rsp), %xmm9
	addpd %xmm9 , %xmm1
	mulpd 0x120(%rsp), %xmm10
	addpd %xmm10, %xmm2
	mulpd 0x120(%rsp), %xmm11
	addpd %xmm11, %xmm3
	mulpd 0x120(%rsp), %xmm12
	addpd %xmm12, %xmm4
	mulpd 0x120(%rsp), %xmm13
	addpd %xmm13, %xmm5
	mulpd 0x120(%rsp), %xmm14
	addpd %xmm14, %xmm6
	mulpd 0x120(%rsp), %xmm15
	addpd %xmm15, %xmm7
	movupd %xmm0 , 0x00(%rcx)
	movupd %xmm1 , 0x10(%rcx)
	movupd %xmm2 , 0x20(%rcx)
	movupd %xmm3 , 0x30(%rcx)
	movupd %xmm4 , 0x40(%rcx)
	movupd %xmm5 , 0x50(%rcx)
	movupd %xmm6 , 0x60(%rcx)
	movupd %xmm7 , 0x70(%rcx)

	movapd 0x280(%rsp), %xmm0
	movapd 0x290(%rsp), %xmm1
	movapd 0x2A0(%rsp), %xmm2
	movapd 0x2B0(%rsp), %xmm3
	movapd 0x2C0(%rsp), %xmm4
	movapd 0x2D0(%rsp), %xmm5
	movapd 0x2E0(%rsp), %xmm6
	movapd 0x2F0(%rsp), %xmm7
	movupd 0x80(%rcx), %xmm8
	movupd 0x90(%rcx), %xmm9
	movupd 0xA0(%rcx), %xmm10
	movupd 0xB0(%rcx), %xmm11
	movupd 0xC0(%rcx), %xmm12
	movupd 0xD0(%rcx), %xmm13
	movupd 0xE0(%rcx), %xmm14
	movupd 0xF0(%rcx), %xmm15
	mulpd 0x120(%rsp), %xmm0
	addpd %xmm0 , %xmm8
	mulpd 0x120(%rsp), %xmm1
	addpd %xmm1 , %xmm9
	mulpd 0x120(%rsp), %xmm2
	addpd %xmm2 , %xmm10
	mulpd 0x120(%rsp), %xmm3
	addpd %xmm3 , %xmm11
	mulpd 0x120(%rsp), %xmm4
	addpd %xmm4 , %xmm12
	mulpd 0x120(%rsp), %xmm5
	addpd %xmm5 , %xmm13
	mulpd 0x120(%rsp), %xmm6
	addpd %xmm6 , %xmm14
	mulpd 0x120(%rsp), %xmm7
	addpd %xmm7 , %xmm15
	movupd %xmm8 , 0x80(%rcx)
	movupd %xmm9 , 0x90(%rcx)
	movupd %xmm10, 0xA0(%rcx)
	movupd %xmm11, 0xB0(%rcx)
	movupd %xmm12, 0xC0(%rcx)
	movupd %xmm13, 0xD0(%rcx)
	movupd %xmm14, 0xE0(%rcx)
	movupd %xmm15, 0xF0(%rcx)
	addq $256, %rcx   		# out2 += 256

	# *(out3 +  0) += in0_3 * in1_0; 
	# ...
	# *(out3 + 31) += in0_3 * in1_31; 
	movapd 0x200(%rsp), %xmm8
	movapd 0x210(%rsp), %xmm9
	movapd 0x220(%rsp), %xmm10
	movapd 0x230(%rsp), %xmm11
	movapd 0x240(%rsp), %xmm12
	movapd 0x250(%rsp), %xmm13
	movapd 0x260(%rsp), %xmm14
	movapd 0x270(%rsp), %xmm15
	movupd 0x00(%rdx), %xmm0
	movupd 0x10(%rdx), %xmm1
	movupd 0x20(%rdx), %xmm2
	movupd 0x30(%rdx), %xmm3
	movupd 0x40(%rdx), %xmm4
	movupd 0x50(%rdx), %xmm5
	movupd 0x60(%rdx), %xmm6
	movupd 0x70(%rdx), %xmm7
	mulpd 0x130(%rsp), %xmm8
	addpd %xmm8 , %xmm0
	mulpd 0x130(%rsp), %xmm9
	addpd %xmm9 , %xmm1
	mulpd 0x130(%rsp), %xmm10
	addpd %xmm10, %xmm2
	mulpd 0x130(%rsp), %xmm11
	addpd %xmm11, %xmm3
	mulpd 0x130(%rsp), %xmm12
	addpd %xmm12, %xmm4
	mulpd 0x130(%rsp), %xmm13
	addpd %xmm13, %xmm5
	mulpd 0x130(%rsp), %xmm14
	addpd %xmm14, %xmm6
	mulpd 0x130(%rsp), %xmm15
	addpd %xmm15, %xmm7
	movupd %xmm0 , 0x00(%rdx)
	movupd %xmm1 , 0x10(%rdx)
	movupd %xmm2 , 0x20(%rdx)
	movupd %xmm3 , 0x30(%rdx)
	movupd %xmm4 , 0x40(%rdx)
	movupd %xmm5 , 0x50(%rdx)
	movupd %xmm6 , 0x60(%rdx)
	movupd %xmm7 , 0x70(%rdx)

	movapd 0x280(%rsp), %xmm0
	movapd 0x290(%rsp), %xmm1
	movapd 0x2A0(%rsp), %xmm2
	movapd 0x2B0(%rsp), %xmm3
	movapd 0x2C0(%rsp), %xmm4
	movapd 0x2D0(%rsp), %xmm5
	movapd 0x2E0(%rsp), %xmm6
	movapd 0x2F0(%rsp), %xmm7
	movupd 0x80(%rdx), %xmm8
	movupd 0x90(%rdx), %xmm9
	movupd 0xA0(%rdx), %xmm10
	movupd 0xB0(%rdx), %xmm11
	movupd 0xC0(%rdx), %xmm12
	movupd 0xD0(%rdx), %xmm13
	movupd 0xE0(%rdx), %xmm14
	movupd 0xF0(%rdx), %xmm15
	mulpd 0x130(%rsp), %xmm0
	addpd %xmm0 , %xmm8
	mulpd 0x130(%rsp), %xmm1
	addpd %xmm1 , %xmm9
	mulpd 0x130(%rsp), %xmm2
	addpd %xmm2 , %xmm10
	mulpd 0x130(%rsp), %xmm3
	addpd %xmm3 , %xmm11
	mulpd 0x130(%rsp), %xmm4
	addpd %xmm4 , %xmm12
	mulpd 0x130(%rsp), %xmm5
	addpd %xmm5 , %xmm13
	mulpd 0x130(%rsp), %xmm6
	addpd %xmm6 , %xmm14
	mulpd 0x130(%rsp), %xmm7
	addpd %xmm7 , %xmm15
	movupd %xmm8 , 0x80(%rdx)
	movupd %xmm9 , 0x90(%rdx)
	movupd %xmm10, 0xA0(%rdx)
	movupd %xmm11, 0xB0(%rdx)
	movupd %xmm12, 0xC0(%rdx)
	movupd %xmm13, 0xD0(%rdx)
	movupd %xmm14, 0xE0(%rdx)
	movupd %xmm15, 0xF0(%rdx)
	addq $256, %rdx   		# out3 += 256

	# *(out4 +  0) += in0_4 * in1_0; 
	# ...
	# *(out4 + 31) += in0_4 * in1_31; 
	movapd 0x200(%rsp), %xmm8
	movapd 0x210(%rsp), %xmm9
	movapd 0x220(%rsp), %xmm10
	movapd 0x230(%rsp), %xmm11
	movapd 0x240(%rsp), %xmm12
	movapd 0x250(%rsp), %xmm13
	movapd 0x260(%rsp), %xmm14
	movapd 0x270(%rsp), %xmm15
	movupd 0x00(%r12), %xmm0
	movupd 0x10(%r12), %xmm1
	movupd 0x20(%r12), %xmm2
	movupd 0x30(%r12), %xmm3
	movupd 0x40(%r12), %xmm4
	movupd 0x50(%r12), %xmm5
	movupd 0x60(%r12), %xmm6
	movupd 0x70(%r12), %xmm7
	mulpd 0x140(%rsp), %xmm8
	addpd %xmm8 , %xmm0
	mulpd 0x140(%rsp), %xmm9
	addpd %xmm9 , %xmm1
	mulpd 0x140(%rsp), %xmm10
	addpd %xmm10, %xmm2
	mulpd 0x140(%rsp), %xmm11
	addpd %xmm11, %xmm3
	mulpd 0x140(%rsp), %xmm12
	addpd %xmm12, %xmm4
	mulpd 0x140(%rsp), %xmm13
	addpd %xmm13, %xmm5
	mulpd 0x140(%rsp), %xmm14
	addpd %xmm14, %xmm6
	mulpd 0x140(%rsp), %xmm15
	addpd %xmm15, %xmm7
	movupd %xmm0 , 0x00(%r12)
	movupd %xmm1 , 0x10(%r12)
	movupd %xmm2 , 0x20(%r12)
	movupd %xmm3 , 0x30(%r12)
	movupd %xmm4 , 0x40(%r12)
	movupd %xmm5 , 0x50(%r12)
	movupd %xmm6 , 0x60(%r12)
	movupd %xmm7 , 0x70(%r12)

	movapd 0x280(%rsp), %xmm0
	movapd 0x290(%rsp), %xmm1
	movapd 0x2A0(%rsp), %xmm2
	movapd 0x2B0(%rsp), %xmm3
	movapd 0x2C0(%rsp), %xmm4
	movapd 0x2D0(%rsp), %xmm5
	movapd 0x2E0(%rsp), %xmm6
	movapd 0x2F0(%rsp), %xmm7
	movupd 0x80(%r12), %xmm8
	movupd 0x90(%r12), %xmm9
	movupd 0xA0(%r12), %xmm10
	movupd 0xB0(%r12), %xmm11
	movupd 0xC0(%r12), %xmm12
	movupd 0xD0(%r12), %xmm13
	movupd 0xE0(%r12), %xmm14
	movupd 0xF0(%r12), %xmm15
	mulpd 0x140(%rsp), %xmm0
	addpd %xmm0 , %xmm8
	mulpd 0x140(%rsp), %xmm1
	addpd %xmm1 , %xmm9
	mulpd 0x140(%rsp), %xmm2
	addpd %xmm2 , %xmm10
	mulpd 0x140(%rsp), %xmm3
	addpd %xmm3 , %xmm11
	mulpd 0x140(%rsp), %xmm4
	addpd %xmm4 , %xmm12
	mulpd 0x140(%rsp), %xmm5
	addpd %xmm5 , %xmm13
	mulpd 0x140(%rsp), %xmm6
	addpd %xmm6 , %xmm14
	mulpd 0x140(%rsp), %xmm7
	addpd %xmm7 , %xmm15
	movupd %xmm8 , 0x80(%r12)
	movupd %xmm9 , 0x90(%r12)
	movupd %xmm10, 0xA0(%r12)
	movupd %xmm11, 0xB0(%r12)
	movupd %xmm12, 0xC0(%r12)
	movupd %xmm13, 0xD0(%r12)
	movupd %xmm14, 0xE0(%r12)
	movupd %xmm15, 0xF0(%r12)
	addq $256, %r12   		# out4 += 256

	# *(out5 +  0) += in0_5 * in1_0; 
	# ...
	# *(out5 + 31) += in0_5 * in1_31; 
	movapd 0x200(%rsp), %xmm8
	movapd 0x210(%rsp), %xmm9
	movapd 0x220(%rsp), %xmm10
	movapd 0x230(%rsp), %xmm11
	movapd 0x240(%rsp), %xmm12
	movapd 0x250(%rsp), %xmm13
	movapd 0x260(%rsp), %xmm14
	movapd 0x270(%rsp), %xmm15
	movupd 0x00(%r13), %xmm0
	movupd 0x10(%r13), %xmm1
	movupd 0x20(%r13), %xmm2
	movupd 0x30(%r13), %xmm3
	movupd 0x40(%r13), %xmm4
	movupd 0x50(%r13), %xmm5
	movupd 0x60(%r13), %xmm6
	movupd 0x70(%r13), %xmm7
	mulpd 0x150(%rsp), %xmm8
	addpd %xmm8 , %xmm0
	mulpd 0x150(%rsp), %xmm9
	addpd %xmm9 , %xmm1
	mulpd 0x150(%rsp), %xmm10
	addpd %xmm10, %xmm2
	mulpd 0x150(%rsp), %xmm11
	addpd %xmm11, %xmm3
	mulpd 0x150(%rsp), %xmm12
	addpd %xmm12, %xmm4
	mulpd 0x150(%rsp), %xmm13
	addpd %xmm13, %xmm5
	mulpd 0x150(%rsp), %xmm14
	addpd %xmm14, %xmm6
	mulpd 0x150(%rsp), %xmm15
	addpd %xmm15, %xmm7
	movupd %xmm0 , 0x00(%r13)
	movupd %xmm1 , 0x10(%r13)
	movupd %xmm2 , 0x20(%r13)
	movupd %xmm3 , 0x30(%r13)
	movupd %xmm4 , 0x40(%r13)
	movupd %xmm5 , 0x50(%r13)
	movupd %xmm6 , 0x60(%r13)
	movupd %xmm7 , 0x70(%r13)

	movapd 0x280(%rsp), %xmm0
	movapd 0x290(%rsp), %xmm1
	movapd 0x2A0(%rsp), %xmm2
	movapd 0x2B0(%rsp), %xmm3
	movapd 0x2C0(%rsp), %xmm4
	movapd 0x2D0(%rsp), %xmm5
	movapd 0x2E0(%rsp), %xmm6
	movapd 0x2F0(%rsp), %xmm7
	movupd 0x80(%r13), %xmm8
	movupd 0x90(%r13), %xmm9
	movupd 0xA0(%r13), %xmm10
	movupd 0xB0(%r13), %xmm11
	movupd 0xC0(%r13), %xmm12
	movupd 0xD0(%r13), %xmm13
	movupd 0xE0(%r13), %xmm14
	movupd 0xF0(%r13), %xmm15
	mulpd 0x150(%rsp), %xmm0
	addpd %xmm0 , %xmm8
	mulpd 0x150(%rsp), %xmm1
	addpd %xmm1 , %xmm9
	mulpd 0x150(%rsp), %xmm2
	addpd %xmm2 , %xmm10
	mulpd 0x150(%rsp), %xmm3
	addpd %xmm3 , %xmm11
	mulpd 0x150(%rsp), %xmm4
	addpd %xmm4 , %xmm12
	mulpd 0x150(%rsp), %xmm5
	addpd %xmm5 , %xmm13
	mulpd 0x150(%rsp), %xmm6
	addpd %xmm6 , %xmm14
	mulpd 0x150(%rsp), %xmm7
	addpd %xmm7 , %xmm15
	movupd %xmm8 , 0x80(%r13)
	movupd %xmm9 , 0x90(%r13)
	movupd %xmm10, 0xA0(%r13)
	movupd %xmm11, 0xB0(%r13)
	movupd %xmm12, 0xC0(%r13)
	movupd %xmm13, 0xD0(%r13)
	movupd %xmm14, 0xE0(%r13)
	movupd %xmm15, 0xF0(%r13)
	addq $256, %r13   		# out5 += 256

	# *(out6 +  0) += in0_6 * in1_0; 
	# ...
	# *(out6 + 31) += in0_6 * in1_31; 
	movapd 0x200(%rsp), %xmm8
	movapd 0x210(%rsp), %xmm9
	movapd 0x220(%rsp), %xmm10
	movapd 0x230(%rsp), %xmm11
	movapd 0x240(%rsp), %xmm12
	movapd 0x250(%rsp), %xmm13
	movapd 0x260(%rsp), %xmm14
	movapd 0x270(%rsp), %xmm15
	movupd 0x00(%r14), %xmm0
	movupd 0x10(%r14), %xmm1
	movupd 0x20(%r14), %xmm2
	movupd 0x30(%r14), %xmm3
	movupd 0x40(%r14), %xmm4
	movupd 0x50(%r14), %xmm5
	movupd 0x60(%r14), %xmm6
	movupd 0x70(%r14), %xmm7
	mulpd 0x160(%rsp), %xmm8
	addpd %xmm8 , %xmm0
	mulpd 0x160(%rsp), %xmm9
	addpd %xmm9 , %xmm1
	mulpd 0x160(%rsp), %xmm10
	addpd %xmm10, %xmm2
	mulpd 0x160(%rsp), %xmm11
	addpd %xmm11, %xmm3
	mulpd 0x160(%rsp), %xmm12
	addpd %xmm12, %xmm4
	mulpd 0x160(%rsp), %xmm13
	addpd %xmm13, %xmm5
	mulpd 0x160(%rsp), %xmm14
	addpd %xmm14, %xmm6
	mulpd 0x160(%rsp), %xmm15
	addpd %xmm15, %xmm7
	movupd %xmm0 , 0x00(%r14)
	movupd %xmm1 , 0x10(%r14)
	movupd %xmm2 , 0x20(%r14)
	movupd %xmm3 , 0x30(%r14)
	movupd %xmm4 , 0x40(%r14)
	movupd %xmm5 , 0x50(%r14)
	movupd %xmm6 , 0x60(%r14)
	movupd %xmm7 , 0x70(%r14)

	movapd 0x280(%rsp), %xmm0
	movapd 0x290(%rsp), %xmm1
	movapd 0x2A0(%rsp), %xmm2
	movapd 0x2B0(%rsp), %xmm3
	movapd 0x2C0(%rsp), %xmm4
	movapd 0x2D0(%rsp), %xmm5
	movapd 0x2E0(%rsp), %xmm6
	movapd 0x2F0(%rsp), %xmm7
	movupd 0x80(%r14), %xmm8
	movupd 0x90(%r14), %xmm9
	movupd 0xA0(%r14), %xmm10
	movupd 0xB0(%r14), %xmm11
	movupd 0xC0(%r14), %xmm12
	movupd 0xD0(%r14), %xmm13
	movupd 0xE0(%r14), %xmm14
	movupd 0xF0(%r14), %xmm15
	mulpd 0x160(%rsp), %xmm0
	addpd %xmm0 , %xmm8
	mulpd 0x160(%rsp), %xmm1
	addpd %xmm1 , %xmm9
	mulpd 0x160(%rsp), %xmm2
	addpd %xmm2 , %xmm10
	mulpd 0x160(%rsp), %xmm3
	addpd %xmm3 , %xmm11
	mulpd 0x160(%rsp), %xmm4
	addpd %xmm4 , %xmm12
	mulpd 0x160(%rsp), %xmm5
	addpd %xmm5 , %xmm13
	mulpd 0x160(%rsp), %xmm6
	addpd %xmm6 , %xmm14
	mulpd 0x160(%rsp), %xmm7
	addpd %xmm7 , %xmm15
	movupd %xmm8 , 0x80(%r14)
	movupd %xmm9 , 0x90(%r14)
	movupd %xmm10, 0xA0(%r14)
	movupd %xmm11, 0xB0(%r14)
	movupd %xmm12, 0xC0(%r14)
	movupd %xmm13, 0xD0(%r14)
	movupd %xmm14, 0xE0(%r14)
	movupd %xmm15, 0xF0(%r14)
	addq $256, %r14   		# out6 += 256

	# *(out7 +  0) += in0_7 * in1_0; 
	# ...
	# *(out7 + 31) += in0_7 * in1_31; 
	movapd 0x200(%rsp), %xmm8
	movapd 0x210(%rsp), %xmm9
	movapd 0x220(%rsp), %xmm10
	movapd 0x230(%rsp), %xmm11
	movapd 0x240(%rsp), %xmm12
	movapd 0x250(%rsp), %xmm13
	movapd 0x260(%rsp), %xmm14
	movapd 0x270(%rsp), %xmm15
	movupd 0x00(%r15), %xmm0
	movupd 0x10(%r15), %xmm1
	movupd 0x20(%r15), %xmm2
	movupd 0x30(%r15), %xmm3
	movupd 0x40(%r15), %xmm4
	movupd 0x50(%r15), %xmm5
	movupd 0x60(%r15), %xmm6
	movupd 0x70(%r15), %xmm7
	mulpd 0x170(%rsp), %xmm8
	addpd %xmm8 , %xmm0
	mulpd 0x170(%rsp), %xmm9
	addpd %xmm9 , %xmm1
	mulpd 0x170(%rsp), %xmm10
	addpd %xmm10, %xmm2
	mulpd 0x170(%rsp), %xmm11
	addpd %xmm11, %xmm3
	mulpd 0x170(%rsp), %xmm12
	addpd %xmm12, %xmm4
	mulpd 0x170(%rsp), %xmm13
	addpd %xmm13, %xmm5
	mulpd 0x170(%rsp), %xmm14
	addpd %xmm14, %xmm6
	mulpd 0x170(%rsp), %xmm15
	addpd %xmm15, %xmm7
	movupd %xmm0 , 0x00(%r15)
	movupd %xmm1 , 0x10(%r15)
	movupd %xmm2 , 0x20(%r15)
	movupd %xmm3 , 0x30(%r15)
	movupd %xmm4 , 0x40(%r15)
	movupd %xmm5 , 0x50(%r15)
	movupd %xmm6 , 0x60(%r15)
	movupd %xmm7 , 0x70(%r15)

	movapd 0x280(%rsp), %xmm0
	movapd 0x290(%rsp), %xmm1
	movapd 0x2A0(%rsp), %xmm2
	movapd 0x2B0(%rsp), %xmm3
	movapd 0x2C0(%rsp), %xmm4
	movapd 0x2D0(%rsp), %xmm5
	movapd 0x2E0(%rsp), %xmm6
	movapd 0x2F0(%rsp), %xmm7
	movupd 0x80(%r15), %xmm8
	movupd 0x90(%r15), %xmm9
	movupd 0xA0(%r15), %xmm10
	movupd 0xB0(%r15), %xmm11
	movupd 0xC0(%r15), %xmm12
	movupd 0xD0(%r15), %xmm13
	movupd 0xE0(%r15), %xmm14
	movupd 0xF0(%r15), %xmm15
	mulpd 0x170(%rsp), %xmm0
	addpd %xmm0 , %xmm8
	mulpd 0x170(%rsp), %xmm1
	addpd %xmm1 , %xmm9
	mulpd 0x170(%rsp), %xmm2
	addpd %xmm2 , %xmm10
	mulpd 0x170(%rsp), %xmm3
	addpd %xmm3 , %xmm11
	mulpd 0x170(%rsp), %xmm4
	addpd %xmm4 , %xmm12
	mulpd 0x170(%rsp), %xmm5
	addpd %xmm5 , %xmm13
	mulpd 0x170(%rsp), %xmm6
	addpd %xmm6 , %xmm14
	mulpd 0x170(%rsp), %xmm7
	addpd %xmm7 , %xmm15
	movupd %xmm8 , 0x80(%r15)
	movupd %xmm9 , 0x90(%r15)
	movupd %xmm10, 0xA0(%r15)
	movupd %xmm11, 0xB0(%r15)
	movupd %xmm12, 0xC0(%r15)
	movupd %xmm13, 0xD0(%r15)
	movupd %xmm14, 0xE0(%r15)
	movupd %xmm15, 0xF0(%r15)
	addq $256, %r15   		# out7 += 256

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

	# vmdot_product_8x16(Out + div, In0, _In1 + div, k, mod, In0S, In0s, In1s);
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
	call vmdot_product_double_8x16

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

