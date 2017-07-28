
	.globl vmdot_product_double_4x1
	.globl vmdot_product_double_4x2
	.globl vmdot_product_double_4x4
	.globl vmdot_product_double_4x8
	.globl vmdot_product_double_4x16
	.globl vmdot_product_double_4x32

	.text

//------------------------------------------------------------------------------
vmdot_product_double_4x1:
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

	movq 0x08(%rsp), %rdi	# Out0 = Oua + In1s * 0
	movq %rdi, 0x80(%rsp)
	addq %r9, %rdi		# Out1 = Out + In1s * 1
	movq %rdi, 0x88(%rsp)
	addq %r9, %rdi		# Out2 = Out + In1s * 2
	movq %rdi, 0x90(%rsp)
	addq %r9, %rdi		# Out3 = Out + In1s * 2
	movq %rdi, 0x98(%rsp)
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
	movsd 0(%rsi), %xmm8		# in0_0 = *In0
	movq 0x60(%rsp), %r11		# j = In0S
	movsd (%rsi, %r11), %xmm9	# in0_1 = *(in0 + j)
	addq 0x60(%rsp), %r11		# j += In0S
	movsd (%rsi, %r11), %xmm10	# in0_2 = *(in0 + j)
	addq 0x60(%rsp), %r11		# j += In0S
	movsd (%rsi, %r11), %xmm11	# in0_3 = *(in0 + j)
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
	movsd %xmm12, %xmm4
	movsd 0 (%rbx), %xmm0
	mulsd %xmm9, %xmm4
	addsd %xmm4, %xmm0
	movsd %xmm0, 0 (%rbx)

	# *(out2 +  0) += in0_2 * in1_0; 
	movsd %xmm12, %xmm4
	movsd 0 (%rcx), %xmm0
	mulsd %xmm10, %xmm4
	addsd %xmm4, %xmm0
	movsd %xmm0, 0 (%rcx)

	# *(out3 +  0) += in0_3 * in1_0; 
	movsd 0 (%rdx), %xmm0
	mulsd %xmm11, %xmm12
	addsd %xmm12, %xmm0
	movsd %xmm0, 0 (%rdx)

	addq $8, %rax	# out0 ++
	addq $8, %rbx	# out1 ++
	addq $8, %rcx	# out0 ++
	addq $8, %rdx	# out1 ++
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
vmdot_product_double_4x2:
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

	movq 0x08(%rsp), %rdi	# Out0 = Oua + In1s * 0
	movq %rdi, 0x80(%rsp)
	addq %r9, %rdi		# Out1 = Out + In1s * 1
	movq %rdi, 0x88(%rsp)
	addq %r9, %rdi		# Out2 = Out + In1s * 2
	movq %rdi, 0x90(%rsp)
	addq %r9, %rdi		# Out3 = Out + In1s * 2
	movq %rdi, 0x98(%rsp)
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
	movddup 0(%rsi), %xmm8		# in0_0 = *In0
	movq 0x60(%rsp), %r11		# j = In0S
	movddup (%rsi, %r11), %xmm9	# in0_1 = *(in0 + j)
	addq 0x60(%rsp), %r11		# j += In0S
	movddup (%rsi, %r11), %xmm10	# in0_2 = *(in0 + j)
	addq 0x60(%rsp), %r11		# j += In0S
	movddup (%rsi, %r11), %xmm11	# in0_3 = *(in0 + j)
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
	movapd %xmm4, %xmm12

	# *(out0 +  0) += in0_0 * in1_0; 
	# *(out0 +  1) += in0_0 * in1_1; 
	movupd 0 (%rax), %xmm0
	mulpd %xmm8, %xmm4
	addpd %xmm4, %xmm0
	movupd %xmm0, 0 (%rax)

	# *(out1 +  0) += in0_1 * in1_0; 
	# *(out1 +  1) += in0_1 * in1_1; 
	movapd %xmm12, %xmm4
	movupd 0 (%rbx), %xmm0
	mulpd %xmm9, %xmm4
	addpd %xmm4, %xmm0
	movupd %xmm0, 0 (%rbx)

	# *(out2 +  0) += in0_2 * in1_0; 
	# *(out2 +  1) += in0_2 * in1_1; 
	movapd %xmm12, %xmm4
	movupd 0 (%rcx), %xmm0
	mulpd %xmm10, %xmm4
	addpd %xmm4, %xmm0
	movupd %xmm0, 0 (%rcx)

	# *(out3 +  0) += in0_3 * in1_0; 
	# *(out3 +  1) += in0_3 * in1_1; 
	movupd 0 (%rdx), %xmm0
	mulpd %xmm11, %xmm12
	addpd %xmm12, %xmm0
	movupd %xmm0, 0 (%rdx)

	addq $16, %rax   	# out0 += 2
	addq $16, %rbx   	# out1 += 2
	addq $16, %rcx   	# out2 += 2
	addq $16, %rdx   	# out3 += 2
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

	# vmdot_product_4x1(Out + div, In0, _In1 + div, k, mod, In0S, In0s, In1s);
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
	call vmdot_product_double_4x1

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
vmdot_product_double_4x4:
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

	movq 0x08(%rsp), %rdi	# Out0 = Oua + In1s * 0
	movq %rdi, 0x80(%rsp)
	addq %r9, %rdi		# Out1 = Out + In1s * 1
	movq %rdi, 0x88(%rsp)
	addq %r9, %rdi		# Out2 = Out + In1s * 2
	movq %rdi, 0x90(%rsp)
	addq %r9, %rdi		# Out3 = Out + In1s * 2
	movq %rdi, 0x98(%rsp)
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
	movddup 0(%rsi), %xmm8		# in0_0 = *In0
	movq 0x60(%rsp), %r11		# j = In0S
	movddup (%rsi, %r11), %xmm9	# in0_1 = *(in0 + j)
	addq 0x60(%rsp), %r11		# j += In0S
	movddup (%rsi, %r11), %xmm10	# in0_2 = *(in0 + j)
	addq 0x60(%rsp), %r11		# j += In0S
	movddup (%rsi, %r11), %xmm11	# in0_3 = *(in0 + j)
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
	movapd %xmm12, %xmm4
	movapd %xmm13, %xmm5

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
	movapd %xmm12, %xmm4
	movapd %xmm13, %xmm5

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
	movupd 0 (%rdx), %xmm0
	movupd 16(%rdx), %xmm1

	mulpd %xmm11, %xmm12
	addpd %xmm12, %xmm0
	mulpd %xmm11, %xmm13
	addpd %xmm13, %xmm1

	movupd %xmm0, 0 (%rdx)
	movupd %xmm1, 16(%rdx)

	addq $32, %rax   	# out0 += 4
	addq $32, %rbx   	# out1 += 4
	addq $32, %rcx   	# out2 += 4
	addq $32, %rdx   	# out3 += 4
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

	# vmdot_product_4x2(Out + div, In0, _In1 + div, k, mod, In0S, In0s, In1s);
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
	call vmdot_product_double_4x2

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
vmdot_product_double_4x8:
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

	movq 0x08(%rsp), %rdi	# Out0 = Oua + In1s * 0
	movq %rdi, 0x80(%rsp)
	addq %r9, %rdi		# Out1 = Out + In1s * 1
	movq %rdi, 0x88(%rsp)
	addq %r9, %rdi		# Out2 = Out + In1s * 2
	movq %rdi, 0x90(%rsp)
	addq %r9, %rdi		# Out3 = Out + In1s * 2
	movq %rdi, 0x98(%rsp)
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
	movddup 0(%rsi), %xmm8		# in0_0 = *In0
	movq 0x60(%rsp), %r11		# j = In0S
	movddup (%rsi, %r11), %xmm9	# in0_1 = *(in0 + j)
	addq 0x60(%rsp), %r11		# j += In0S
	movddup (%rsi, %r11), %xmm10	# in0_2 = *(in0 + j)
	addq 0x60(%rsp), %r11		# j += In0S
	movddup (%rsi, %r11), %xmm11	# in0_3 = *(in0 + j)
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
	movapd %xmm4, %xmm12
	movupd 16(%rdi), %xmm5
	movapd %xmm5, %xmm13
	movupd 32(%rdi), %xmm6
	movapd %xmm6, %xmm14
	movupd 48(%rdi), %xmm7
	movapd %xmm7, %xmm15

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
	movapd %xmm12, %xmm4
	movapd %xmm13, %xmm5
	movapd %xmm14, %xmm6
	movapd %xmm15, %xmm7

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
	movapd %xmm12, %xmm4
	movapd %xmm13, %xmm5
	movapd %xmm14, %xmm6
	movapd %xmm15, %xmm7

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
	movupd 0 (%rdx), %xmm0
	movupd 16(%rdx), %xmm1
	movupd 32(%rdx), %xmm2
	movupd 48(%rdx), %xmm3

	mulpd %xmm11, %xmm12
	addpd %xmm12, %xmm0
	mulpd %xmm11, %xmm13
	addpd %xmm13, %xmm1
	mulpd %xmm11, %xmm14
	addpd %xmm14, %xmm2
	mulpd %xmm11, %xmm15
	addpd %xmm15, %xmm3

	movupd %xmm0, 0 (%rdx)
	movupd %xmm1, 16(%rdx)
	movupd %xmm2, 32(%rdx)
	movupd %xmm3, 48(%rdx)

	addq $64, %rax   	# out0 += 8
	addq $64, %rbx   	# out1 += 8
	addq $64, %rcx   	# out2 += 8
	addq $64, %rdx   	# out3 += 8
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

	# vmdot_product_4x4(Out + div, In0, _In1 + div, k, mod, In0S, In0s, In1s);
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
	call vmdot_product_double_4x4

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
vmdot_product_double_4x16:
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

	movq 0x08(%rsp), %rdi	# Out0 = Oua + In1s * 0
	movq %rdi, 0x80(%rsp)
	addq %r9, %rdi		# Out1 = Out + In1s * 1
	movq %rdi, 0x88(%rsp)
	addq %r9, %rdi		# Out2 = Out + In1s * 2
	movq %rdi, 0x90(%rsp)
	addq %r9, %rdi		# Out3 = Out + In1s * 2
	movq %rdi, 0x98(%rsp)
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
	movddup 0(%rsi), %xmm8		# in0_0 = *In0
	movq 0x60(%rsp), %r11		# j = In0S
	movddup (%rsi, %r11), %xmm9	# in0_1 = *(in0 + j)
	addq 0x60(%rsp), %r11		# j += In0S
	movddup (%rsi, %r11), %xmm10	# in0_2 = *(in0 + j)
	addq 0x60(%rsp), %r11		# j += In0S
	movddup (%rsi, %r11), %xmm11	# in0_3 = *(in0 + j)
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
	movapd %xmm4, %xmm12
	movupd 16(%rdi), %xmm5
	movapd %xmm5, %xmm13
	movupd 32(%rdi), %xmm6
	movapd %xmm6, %xmm14
	movupd 48(%rdi), %xmm7
	movapd %xmm7, %xmm15

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
	movapd %xmm12, %xmm4
	movapd %xmm13, %xmm5
	movapd %xmm14, %xmm6
	movapd %xmm15, %xmm7

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
	movapd %xmm12, %xmm4
	movapd %xmm13, %xmm5
	movapd %xmm14, %xmm6
	movapd %xmm15, %xmm7

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
	movupd 0 (%rdx), %xmm0
	movupd 16(%rdx), %xmm1
	movupd 32(%rdx), %xmm2
	movupd 48(%rdx), %xmm3

	mulpd %xmm11, %xmm12
	addpd %xmm12, %xmm0
	mulpd %xmm11, %xmm13
	addpd %xmm13, %xmm1
	mulpd %xmm11, %xmm14
	addpd %xmm14, %xmm2
	mulpd %xmm11, %xmm15
	addpd %xmm15, %xmm3

	movupd %xmm0, 0 (%rdx)
	movupd %xmm1, 16(%rdx)
	movupd %xmm2, 32(%rdx)
	movupd %xmm3, 48(%rdx)

	addq $64, %rax   	# out0 += 8
	addq $64, %rbx   	# out1 += 8
	addq $64, %rcx   	# out2 += 8
	addq $64, %rdx   	# out3 += 8
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
	movapd %xmm4, %xmm12
	movupd 16(%rdi), %xmm5
	movapd %xmm5, %xmm13
	movupd 32(%rdi), %xmm6
	movapd %xmm6, %xmm14
	movupd 48(%rdi), %xmm7
	movapd %xmm7, %xmm15

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
	movapd %xmm12, %xmm4
	movapd %xmm13, %xmm5
	movapd %xmm14, %xmm6
	movapd %xmm15, %xmm7

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
	movapd %xmm12, %xmm4
	movapd %xmm13, %xmm5
	movapd %xmm14, %xmm6
	movapd %xmm15, %xmm7

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
	movupd 0 (%rdx), %xmm0
	movupd 16(%rdx), %xmm1
	movupd 32(%rdx), %xmm2
	movupd 48(%rdx), %xmm3

	mulpd %xmm11, %xmm12
	addpd %xmm12, %xmm0
	mulpd %xmm11, %xmm13
	addpd %xmm13, %xmm1
	mulpd %xmm11, %xmm14
	addpd %xmm14, %xmm2
	mulpd %xmm11, %xmm15
	addpd %xmm15, %xmm3

	movupd %xmm0, 0 (%rdx)
	movupd %xmm1, 16(%rdx)
	movupd %xmm2, 32(%rdx)
	movupd %xmm3, 48(%rdx)

	addq $64, %rax   	# out0 += 8
	addq $64, %rbx   	# out1 += 8
	addq $64, %rcx   	# out2 += 8
	addq $64, %rdx   	# out3 += 8
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

	# vmdot_product_4x8(Out + div, In0, _In1 + div, k, mod, In0S, In0s, In1s);
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
	call vmdot_product_double_4x8

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
vmdot_product_double_4x32:
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

	movq 0x08(%rsp), %rdi	# Out0 = Oua + In1s * 0
	movq %rdi, 0x80(%rsp)
	addq %r9, %rdi		# Out1 = Out + In1s * 1
	movq %rdi, 0x88(%rsp)
	addq %r9, %rdi		# Out2 = Out + In1s * 2
	movq %rdi, 0x90(%rsp)
	addq %r9, %rdi		# Out3 = Out + In1s * 2
	movq %rdi, 0x98(%rsp)
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
	movddup 0(%rsi), %xmm8		# in0_0 = *In0
	movq 0x60(%rsp), %r11		# j = In0S
	movddup (%rsi, %r11), %xmm9	# in0_1 = *(in0 + j)
	addq 0x60(%rsp), %r11		# j += In0S
	movddup (%rsi, %r11), %xmm10	# in0_2 = *(in0 + j)
	addq 0x60(%rsp), %r11		# j += In0S
	movddup (%rsi, %r11), %xmm11	# in0_3 = *(in0 + j)
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
	movapd %xmm4, %xmm12
	movupd 16(%rdi), %xmm5
	movapd %xmm5, %xmm13
	movupd 32(%rdi), %xmm6
	movapd %xmm6, %xmm14
	movupd 48(%rdi), %xmm7
	movapd %xmm7, %xmm15

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
	movapd %xmm12, %xmm4
	movapd %xmm13, %xmm5
	movapd %xmm14, %xmm6
	movapd %xmm15, %xmm7

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
	movapd %xmm12, %xmm4
	movapd %xmm13, %xmm5
	movapd %xmm14, %xmm6
	movapd %xmm15, %xmm7

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
	movupd 0 (%rdx), %xmm0
	movupd 16(%rdx), %xmm1
	movupd 32(%rdx), %xmm2
	movupd 48(%rdx), %xmm3

	mulpd %xmm11, %xmm12
	addpd %xmm12, %xmm0
	mulpd %xmm11, %xmm13
	addpd %xmm13, %xmm1
	mulpd %xmm11, %xmm14
	addpd %xmm14, %xmm2
	mulpd %xmm11, %xmm15
	addpd %xmm15, %xmm3

	movupd %xmm0, 0 (%rdx)
	movupd %xmm1, 16(%rdx)
	movupd %xmm2, 32(%rdx)
	movupd %xmm3, 48(%rdx)

	addq $64, %rax   	# out0 += 8
	addq $64, %rbx   	# out1 += 8
	addq $64, %rcx   	# out2 += 8
	addq $64, %rdx   	# out3 += 8
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
	movapd %xmm4, %xmm12
	movupd 16(%rdi), %xmm5
	movapd %xmm5, %xmm13
	movupd 32(%rdi), %xmm6
	movapd %xmm6, %xmm14
	movupd 48(%rdi), %xmm7
	movapd %xmm7, %xmm15

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
	movapd %xmm12, %xmm4
	movapd %xmm13, %xmm5
	movapd %xmm14, %xmm6
	movapd %xmm15, %xmm7

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
	movapd %xmm12, %xmm4
	movapd %xmm13, %xmm5
	movapd %xmm14, %xmm6
	movapd %xmm15, %xmm7

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
	movupd 0 (%rdx), %xmm0
	movupd 16(%rdx), %xmm1
	movupd 32(%rdx), %xmm2
	movupd 48(%rdx), %xmm3

	mulpd %xmm11, %xmm12
	addpd %xmm12, %xmm0
	mulpd %xmm11, %xmm13
	addpd %xmm13, %xmm1
	mulpd %xmm11, %xmm14
	addpd %xmm14, %xmm2
	mulpd %xmm11, %xmm15
	addpd %xmm15, %xmm3

	movupd %xmm0, 0 (%rdx)
	movupd %xmm1, 16(%rdx)
	movupd %xmm2, 32(%rdx)
	movupd %xmm3, 48(%rdx)

	addq $64, %rax   	# out0 += 8
	addq $64, %rbx   	# out1 += 8
	addq $64, %rcx   	# out2 += 8
	addq $64, %rdx   	# out3 += 8
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
	movapd %xmm4, %xmm12
	movupd 16(%rdi), %xmm5
	movapd %xmm5, %xmm13
	movupd 32(%rdi), %xmm6
	movapd %xmm6, %xmm14
	movupd 48(%rdi), %xmm7
	movapd %xmm7, %xmm15

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
	movapd %xmm12, %xmm4
	movapd %xmm13, %xmm5
	movapd %xmm14, %xmm6
	movapd %xmm15, %xmm7

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
	movapd %xmm12, %xmm4
	movapd %xmm13, %xmm5
	movapd %xmm14, %xmm6
	movapd %xmm15, %xmm7

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
	movupd 0 (%rdx), %xmm0
	movupd 16(%rdx), %xmm1
	movupd 32(%rdx), %xmm2
	movupd 48(%rdx), %xmm3

	mulpd %xmm11, %xmm12
	addpd %xmm12, %xmm0
	mulpd %xmm11, %xmm13
	addpd %xmm13, %xmm1
	mulpd %xmm11, %xmm14
	addpd %xmm14, %xmm2
	mulpd %xmm11, %xmm15
	addpd %xmm15, %xmm3

	movupd %xmm0, 0 (%rdx)
	movupd %xmm1, 16(%rdx)
	movupd %xmm2, 32(%rdx)
	movupd %xmm3, 48(%rdx)

	addq $64, %rax   	# out0 += 8
	addq $64, %rbx   	# out1 += 8
	addq $64, %rcx   	# out2 += 8
	addq $64, %rdx   	# out3 += 8
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
	movapd %xmm4, %xmm12
	movupd 16(%rdi), %xmm5
	movapd %xmm5, %xmm13
	movupd 32(%rdi), %xmm6
	movapd %xmm6, %xmm14
	movupd 48(%rdi), %xmm7
	movapd %xmm7, %xmm15

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
	movapd %xmm12, %xmm4
	movapd %xmm13, %xmm5
	movapd %xmm14, %xmm6
	movapd %xmm15, %xmm7

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
	movapd %xmm12, %xmm4
	movapd %xmm13, %xmm5
	movapd %xmm14, %xmm6
	movapd %xmm15, %xmm7

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
	movupd 0 (%rdx), %xmm0
	movupd 16(%rdx), %xmm1
	movupd 32(%rdx), %xmm2
	movupd 48(%rdx), %xmm3

	mulpd %xmm11, %xmm12
	addpd %xmm12, %xmm0
	mulpd %xmm11, %xmm13
	addpd %xmm13, %xmm1
	mulpd %xmm11, %xmm14
	addpd %xmm14, %xmm2
	mulpd %xmm11, %xmm15
	addpd %xmm15, %xmm3

	movupd %xmm0, 0 (%rdx)
	movupd %xmm1, 16(%rdx)
	movupd %xmm2, 32(%rdx)
	movupd %xmm3, 48(%rdx)

	addq $64, %rax   	# out0 += 8
	addq $64, %rbx   	# out1 += 8
	addq $64, %rcx   	# out2 += 8
	addq $64, %rdx   	# out3 += 8
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

	# vmdot_product_4x16(Out + div, In0, _In1 + div, k, mod, In0S, In0s, In1s);
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
	call vmdot_product_double_4x16

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

