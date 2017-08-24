# SSE4 plan for dot_product_double_mkn

# RAX	out_0 and h
# RBX	out_1
# RCX	out_2
# RDX	out_3 
# RSI	i
# RDI	j
# R08	in0_0 
# R09	in0_1
# R10	in0_2 and subtrahend
# R11	in0_3 and minuend
# R12	in1_0
# R13	in1_1
# R14	in1_2
# R15	in1_3

# SIMD register plan

# xmm0-4:	out and in_0
# xmm4-7:	in0
# xmm8-15:	in1

# Stack allocation of 256 bytes (no red zone)

# 0x08(%rsp)	h
# 0x10(%rsp)	_Out
# 0x18(%rsp)	_In0 
# 0x20(%rsp)	_In1 
# 0x28(%rsp)	m
# 0x30(%rsp)	k
# 0x38(%rsp)	n

# 0x40(%rsp)	OutS
# 0x48(%rsp)	Outs 
# 0x50(%rsp)	In0S 
# 0x58(%rsp)	In0s 
# 0x60(%rsp)	In1S 
# 0x68(%rsp)	In1s 
# 0x70(%rsp)	Out 
# 0x78(%rsp)	In0 

# 0x80(%rsp)	In1 
# 0x88(%rsp)	M
# 0x90(%rsp)	K 
# 0x98(%rsp)	N 

# 0xA0(%rsp)	Out_0
# 0xA8(%rsp)	Out_1
# 0xB0(%rsp)	Out_2
# 0xB8(%rsp)	Out_3

# 0xC0(%rsp)	in0_0
# 0xC8(%rsp)	in0_1
# 0xD0(%rsp)	in0_2
# 0xD8(%rsp)	in0_3

# 0xE0(%rsp)	in1_0
# 0xE8(%rsp)	in1_1
# 0xF0(%rsp)	in1_2
# 0xF8(%rsp)	in1_3

# 0x100(%rsp)	in0_0_0
# ...
# 0x1F8(%rsp)	in0_3_3

//------------------------------------------------------------------------------
	.globl dot_product_double_mkn_1x1x1_sse4
	.globl dot_product_double_mkn_1x1x2_sse4
	.globl dot_product_double_mkn_1x1x4_sse4
	.globl dot_product_double_mkn_1x1x8_sse4
	.globl dot_product_double_mkn_2x2x2_sse4
	.globl dot_product_double_mkn_4x4x4_sse4

	.text

//------------------------------------------------------------------------------
dot_product_double_mkn_1x1x1_sse4:
	mov %rsp, %rax
	push %rsp
	push %rbp
	push %rbx
	push %r12
	push %r13
	push %r14
	push %r15
	movq %rsp, %rbp
	subq $640, %rsp
	andq $-64, %rsp

	mov 0x08(%rax), %r10
	mov 0x10(%rax), %r11
	mov 0x18(%rax), %r12
	mov 0x20(%rax), %r13
	# Out _In0 _In1 m   k   n  OutS In0S In0s In1S
	# rdi rsi  rdx  rcx r8  r9 r10  r11  r12  r13

	movq %rdi, 0x10(%rsp) 	# _Out
	movq %rsi, 0x18(%rsp) 	# _In0
	movq %rdx, 0x20(%rsp) 	# _In1
	movq %rcx, 0x28(%rsp) 	# m
	movq %r8,  0x30(%rsp) 	# k
	movq %r9,  0x38(%rsp) 	# n
	shlq $3, %r10		# OutS
	movq %r10, 0x40(%rsp)
	shlq $3, %r11		# In0S
	movq %r11, 0x50(%rsp)
	shlq $3, %r12		# In0s
	movq %r12, 0x58(%rsp)
	shlq $3, %r13		# In1S
	movq %r13, 0x60(%rsp)

	movq 0x10(%rsp), %rax	# Out = _Out;
	movq %rax, 0x70(%rsp)
	movq 0x18(%rsp), %r8	# In0 = _In0;
	movq %r8, 0x78(%rsp)

	movq 0x28(%rsp), %rax 	# for (h = m; h; h--) {
	test %rax, %rax
	je 5f

	.p2align 3,,4
	.p2align 4
0:
	movq %rax, 0x08(%rsp)	# h

	movq 0x70(%rsp), %rax	# Out_0 = Out + OutS * 0;
	movq 0x40(%rsp), %rcx
	movq %rax, 0xA0(%rsp)
	addq %rcx, %rax		# Out += OutS;
	movq %rax, 0x70(%rsp)
	movq 0x78(%rsp), %r8	# in0_0 = In0 + In0S * 0;
	movq 0x50(%rsp), %r10
	movq %r8, 0xC0(%rsp)
	addq %r10, %r8		# In0 += In0S;
	movq %r8, 0x78(%rsp)
	movq 0x20(%rsp), %r12	# In1 = _In1;
	movq %r12, 0x80(%rsp)
	
	movq 0x30(%rsp), %rsi 	# for (i = k; i; i--) {
	test %rsi, %rsi
	je 4f

	.p2align 4,,8
	.p2align 5
1:
	movq 0xA0(%rsp), %rax	# out_0 = Out_0;
	movq 0xC0(%rsp), %r8	# in0_0_0 = *(in0_0 + In0s * 0);
	movq 0x58(%rsp), %r10
	movsd 0x000(%r8), %xmm12
	addq %r10, %r8		# in0_0 += In0s * 1;
	movq %r8, 0xC0(%rsp)
	movq 0x80(%rsp), %r12	# in1_0 = In1 + In1S * 0;
	movq 0x60(%rsp), %r11
	addq %r12, %r11		# In1 += In1S * 1;
	movq %r11, 0x80(%rsp)

	movq 0x38(%rsp), %rdi	# for (j = n; j; j--) {
	test %rdi, %rdi
	je 3f

	.p2align 5,,16
	.p2align 6
2:
	# in1_0_0 = *(in1_0 + 0);
	movsd 0x000(%r12), %xmm8
	# in1_0 += 1;
	addq $8, %r12
	# i0 = in0_0_0;
	movapd %xmm12, %xmm4
	# o0  = i0 * in1_0_0;
	mulsd %xmm8, %xmm4
	# *(out_0 + 0) += o0;
	movsd 0x000(%rax), %xmm0
	addsd %xmm4, %xmm0
	movsd %xmm0, 0x000(%rax)
	# out_0 += 1;
	addq $8, %rax

	subq $1, %rdi		# } // for (j = n; j; j--) {
	jnz 2b

3:
	subq $1, %rsi		# } // for (i = k; i; i--) {
	jnz 1b

4:
	movq 0x08(%rsp), %rax	# } // for (h = m; h; h--) {
	subq $1, %rax
	jnz 0b

5:
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
dot_product_double_mkn_2x2x2_sse4:
	mov %rsp, %rax
	push %rsp
	push %rbp
	push %rbx
	push %r12
	push %r13
	push %r14
	push %r15
	movq %rsp, %rbp
	subq $640, %rsp
	andq $-64, %rsp

	mov 0x08(%rax), %r10
	mov 0x10(%rax), %r11
	mov 0x18(%rax), %r12
	mov 0x20(%rax), %r13
	# Out _In0 _In1 m   k   n  OutS In0S In0s In1S
	# rdi rsi  rdx  rcx r8  r9 r10  r11  r12  r13

	movq %rdi, 0x10(%rsp) 	# _Out
	movq %rsi, 0x18(%rsp) 	# _In0
	movq %rdx, 0x20(%rsp) 	# _In1
	movq %rcx, 0x28(%rsp) 	# m
	movq %r8,  0x30(%rsp) 	# k
	movq %r9,  0x38(%rsp) 	# n
	shlq $3, %r10		# OutS
	movq %r10, 0x40(%rsp)
	shlq $3, %r11		# In0S
	movq %r11, 0x50(%rsp)
	shlq $3, %r12		# In0s
	movq %r12, 0x58(%rsp)
	shlq $3, %r13		# In1S
	movq %r13, 0x60(%rsp)

	movq 0x28(%rsp), %rdx	# M = m >> 1
	shrq $1, %rdx
	movq %rdx, 0x88(%rsp)
	movq 0x30(%rsp), %rsi	# K = k >> 1
	shrq $1, %rsi
	movq %rsi, 0x90(%rsp)
	movq 0x38(%rsp), %rdi	# N = n >> 1
	shrq $1, %rdi
	movq %rdi, 0x98(%rsp)

	movq 0x10(%rsp), %rax	# Out = _Out;
	movq %rax, 0x70(%rsp)
	movq 0x18(%rsp), %r8	# In0 = _In0;
	movq %r8, 0x78(%rsp)

	movq 0x88(%rsp), %rax 	# for (h = m; h; h--) {
	test %rax, %rax
	je 5f

	.p2align 3,,4
	.p2align 4
0:
	movq %rax, 0x08(%rsp)	# h

	movq 0x70(%rsp), %rax	# Out_0 = Out + OutS * 0;
	movq 0x40(%rsp), %rcx
	movq %rax, 0xA0(%rsp)
	leaq (%rax, %rcx), %rbx # Out_1 = Out + OutS * 1
	movq %rbx, 0xA8(%rsp)
	addq %rcx, %rbx		# Out += OutS * 2;
	movq %rbx, 0x70(%rsp)
	movq 0x78(%rsp), %r8	# in0_0 = In0 + In0S * 0;
	movq 0x50(%rsp), %r10
	movq %r8, 0xC0(%rsp)
	leaq (%r8, %r10), %r9	# in0_1 = In0 + In0S * 1
	movq %r9, 0xC8(%rsp)
	addq %r10, %r9		# In0 += In0S * 2;
	movq %r9, 0x78(%rsp)
	movq 0x20(%rsp), %r12	# In1 = _In1;
	movq %r12, 0x80(%rsp)
	
	movq 0x90(%rsp), %rsi 	# for (i = K; i; i--) {
	test %rsi, %rsi
	je 4f

	.p2align 4,,8
	.p2align 5
1:
	movq 0xA0(%rsp), %rax		# out_0 = Out_0;
	movq 0xA8(%rsp), %rbx		# out_1 = Out_1;

	movq 0xC0(%rsp), %r8		# in0_0_0 = *(in0_0 + In0s * 0);
	movq 0x58(%rsp), %r10
	movddup 0x000(%r8), %xmm12
	movddup (%r8, %r10), %xmm13 	# in0_0_1 = *(in0_0 + In0s * 1)
	leaq (%r8, %r10, 2), %r9	# in0_0 += In0s * 2
	movq %r9, 0xC0(%rsp)

	movq 0xC8(%rsp), %r8		# in0_1_0 = *(in0_1 + In0s * 0);
	movddup 0x000(%r8), %xmm14
	movddup (%r8, %r10), %xmm15	# in0_1_1 = *(in0_1 + In0s * 1)
	leaq (%r8, %r10, 2), %r9	# in0_1 += In0s * 2
	movq %r9, 0xC8(%rsp)

	movq 0x80(%rsp), %r12		# in1_0 = In1 + In1S * 0;
	movq 0x60(%rsp), %r11
	leaq (%r12, %r11), %r13		# in1_1 = In1 + In1S * 1;
	addq %r13, %r11
	movq %r11, 0x80(%rsp)		# In1 += In1S * 2;

	movq 0x98(%rsp), %rdi		# for (j = N; j; j--) {
	test %rdi, %rdi
	je 3f

	.p2align 5,,16
	.p2align 6
2:
	# in1_0_0 = *(in1_0 + 0);
	# in1_0_1 = *(in1_0 + 1);
	movupd 0x000(%r12), %xmm8
	# in1_0 += 2;
	addq $16, %r12
	# in1_1_0 = *(in1_1 + 0);
	# in1_1_1 = *(in1_1 + 1);
	movupd 0x000(%r13), %xmm9
	# in1_1 += 2;
	addq $16, %r13

	# i0 = in0_0_0;
	# i1 = in0_0_1;
	movapd %xmm12, %xmm4
	movapd %xmm13, %xmm5
	# o0  = i0 * in1_0_0;
	# o1  = i0 * in1_0_1;
	mulpd %xmm8, %xmm4
	# o0  += i1 * in1_0_0;
	# o1  += i1 * in1_0_1;
	mulpd %xmm9, %xmm5
	addpd %xmm5, %xmm4
	# *(out_0 + 0) += o0;
	# *(out_0 + 1) += o1;
	movupd 0x000(%rax), %xmm0
	addpd %xmm4, %xmm0
	movupd %xmm0, 0x000(%rax)
	# out_0 += 2;
	addq $16, %rax

	# i0 = in0_1_0;
	# i1 = in0_1_1;
	movapd %xmm14, %xmm4
	movapd %xmm15, %xmm5
	# o0  = i0 * in1_0_0;
	# o1  = i0 * in1_0_1;
	mulpd %xmm8, %xmm4
	# o0  += i1 * in1_0_0;
	# o1  += i1 * in1_0_1;
	mulpd %xmm9, %xmm5
	addpd %xmm5, %xmm4
	# *(out_1 + 0) += o0;
	# *(out_1 + 1) += o1;
	movupd 0x000(%rbx), %xmm0
	addpd %xmm4, %xmm0
	movupd %xmm0, 0x000(%rbx)
	# out_1 += 2;
	addq $16, %rbx

	subq $1, %rdi		# } // for (j = n; j; j--) {
	jnz 2b

3:
	subq $1, %rsi		# } // for (i = k; i; i--) {
	jnz 1b

4:
	movq 0x08(%rsp), %rax	# } // for (h = m; h; h--) {
	subq $1, %rax
	jnz 0b

5:

	movq 0x10(%rsp), %rax	# Out = _Out
	movq %rax, 0x70(%rsp)
	movq 0x18(%rsp), %r8	# In0 = _In0
	movq %r8,  0x78(%rsp)
	movq 0x20(%rsp), %r12	# In1 = _In1
	movq %r12, 0x80(%rsp)

	movq 0x28(%rsp), %rax	# M = m & 1
	andq $1, %rax
	movq 0x30(%rsp), %r14	# K = k & 1
	andq $1, %r14
	movq 0x38(%rsp), %r15	# N = n & 1
	andq $1, %r15

	# Out _In0 _In1 m   k   n  OutS In0S In0s In1S
	# rdi rsi  rdx  rcx r8  r9 r10  r11  r12  r13
	movq 0x70(%rsp), %rdi	# Out
	movq 0x78(%rsp), %rsi	# In0
	movq 0x80(%rsp), %rdx	# In1
	movq 0x28(%rsp), %rcx	# m
	movq 0x30(%rsp), %r8	# k
	movq 0x38(%rsp), %r9	# n
	movq 0x40(%rsp), %r10	# OutS
	shrq $3, %r10
	movq %r10, 0x08(%rsp)
	movq 0x50(%rsp), %r11	# In0S
	shrq $3, %r11
	movq %r11, 0x10(%rsp)
	movq 0x58(%rsp), %r12	# In0s
	shrq $3, %r12
	movq %r12, 0x18(%rsp)
	movq 0x60(%rsp), %r13	# In1S
	shrq $3, %r13
	movq %r13, 0x20(%rsp)

	movq %rcx, %r10		# h = m;
	movq %r8, %r11		# i = k;
	movq %r9, %r12		# j = n;

	test %rax, %rax		# if (M) {
	jz 6f

	subq %rax, %r10		# h -= M;
	movq 0x40(%rsp), %rbx	# OutS
	movq 0x50(%rsp), %r13	# In0S

	imulq %r10, %rbx 	# Out += OutS * h
	addq %rbx, %rdi
	imulq %r10, %r13	# In0 += In0S * h
	addq %r13, %rsi
	movq %rax, %rcx		# M

	# dot_product_mkn_1x1x1(Out, In0, In1, M, k, n, OutS, In0S, In0s, In1S);
	movq %rax, 0xA0(%rsp)
	movq %rcx, 0xA8(%rsp)
	movq %rdx, 0xB0(%rsp)
	movq %rsi, 0xB8(%rsp)
	movq %rdi, 0xC0(%rsp)
	movq %r8,  0xC8(%rsp)
	movq %r9,  0xD0(%rsp)
	movq %r10, 0xD8(%rsp)
	movq %r11, 0xE0(%rsp)
	addq $8, %rsp
	call dot_product_double_mkn_1x1x1_sse4
	subq $8, %rsp
	movq 0xA0(%rsp), %rax
	movq 0xA8(%rsp), %rcx
	movq 0xB0(%rsp), %rdx
	movq 0xB8(%rsp), %rsi
	movq 0xC0(%rsp), %rdi
	movq 0xC8(%rsp), %r8
	movq 0xD0(%rsp), %r9
	movq 0xD8(%rsp), %r10
	movq 0xE0(%rsp), %r11

	movq 0x70(%rsp), %rdi	# Out = _Out
	movq 0x78(%rsp), %rsi	# In0 = _In0

6:
	movq %r10, %rcx		# } h
	test %r14, %r14		# if (K) {
	jz 7f

	subq %r14, %r11		# i -= K;
	movq 0x58(%rsp), %rbx	# In0s
	movq 0x60(%rsp), %r13	# In1S

	imulq %r11, %rbx	# In0 += In0s * i	
	addq %rbx, %rsi
	imulq %r11, %r13	# In1 += In1S * i	
	addq %r13, %rdx
	movq %r14, %r8		# K

	# dot_product_mkn_1x1x1(Out, In0, In1, h, K, n, OutS, In0S, In0s, In1S);
	movq %rax, 0xA0(%rsp)
	movq %rcx, 0xA8(%rsp)
	movq %rdx, 0xB0(%rsp)
	movq %rsi, 0xB8(%rsp)
	movq %rdi, 0xC0(%rsp)
	movq %r8,  0xC8(%rsp)
	movq %r9,  0xD0(%rsp)
	movq %r10, 0xD8(%rsp)
	movq %r11, 0xE0(%rsp)
	addq $8, %rsp
	call dot_product_double_mkn_1x1x1_sse4
	subq $8, %rsp
	movq 0xA0(%rsp), %rax
	movq 0xA8(%rsp), %rcx
	movq 0xB0(%rsp), %rdx
	movq 0xB8(%rsp), %rsi
	movq 0xC0(%rsp), %rdi
	movq 0xC8(%rsp), %r8
	movq 0xD0(%rsp), %r9
	movq 0xD8(%rsp), %r10
	movq 0xE0(%rsp), %r11

	movq 0x78(%rsp), %rsi	# In0 = _In0
	movq 0x80(%rsp), %rdx	# In1 = _In1

7:
	movq %r11, %r8		# } i
	test %r15, %r15		# if (N) {
	jz 8f

	subq %r15, %r12		# j -= N;
	shlq $3, %r12
	addq %r12, %rdi		# Out += j;
	addq %r12, %rdx		# In1 += j;
	movq %r15, %r9		# N

	# dot_product_mkn_1x1x1(Out, In0, In1, h, i, N, OutS, In0S, In0s, In1S);
	addq $8, %rsp
	call dot_product_double_mkn_1x1x1_sse4
	subq $8, %rsp
8:				# }

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
dot_product_double_mkn_4x4x4_sse4:
	mov %rsp, %rax
	push %rsp
	push %rbp
	push %rbx
	push %r12
	push %r13
	push %r14
	push %r15
	movq %rsp, %rbp
	subq $640, %rsp
	andq $-64, %rsp

	mov 0x08(%rax), %r10
	mov 0x10(%rax), %r11
	mov 0x18(%rax), %r12
	mov 0x20(%rax), %r13
	# Out _In0 _In1 m   k   n  OutS In0S In0s In1S
	# rdi rsi  rdx  rcx r8  r9 r10  r11  r12  r13

	movq %rdi, 0x10(%rsp) 	# _Out
	movq %rsi, 0x18(%rsp) 	# _In0
	movq %rdx, 0x20(%rsp) 	# _In1
	movq %rcx, 0x28(%rsp) 	# m
	movq %r8,  0x30(%rsp) 	# k
	movq %r9,  0x38(%rsp) 	# n
	shlq $3, %r10		# OutS
	movq %r10, 0x40(%rsp)
	shlq $3, %r11		# In0S
	movq %r11, 0x50(%rsp)
	shlq $3, %r12		# In0s
	movq %r12, 0x58(%rsp)
	shlq $3, %r13		# In1S
	movq %r13, 0x60(%rsp)

	movq 0x28(%rsp), %rdx	# M = m >> 2
	shrq $2, %rdx
	movq %rdx, 0x88(%rsp)
	movq 0x30(%rsp), %rsi	# K = k >> 2
	shrq $2, %rsi
	movq %rsi, 0x90(%rsp)
	movq 0x38(%rsp), %rdi	# N = n >> 2
	shrq $2, %rdi
	movq %rdi, 0x98(%rsp)

	movq 0x10(%rsp), %rax	# Out = _Out;
	movq %rax, 0x70(%rsp)
	movq 0x18(%rsp), %r8	# In0 = _In0;
	movq %r8, 0x78(%rsp)

	movq 0x88(%rsp), %rax 	# for (h = m; h; h--) {
	test %rax, %rax
	je 5f

	.p2align 3,,4
	.p2align 4
0:
	movq %rax, 0x08(%rsp)	# h

	movq 0x70(%rsp), %rax	# Out_0 = Out + OutS * 0;
	movq 0x40(%rsp), %rcx
	movq %rax, 0xA0(%rsp)
	leaq (%rax, %rcx), %rbx # Out_1 = Out + OutS * 1
	movq %rbx, 0xA8(%rsp)
	leaq (%rbx, %rcx), %rax # Out_2 = Out + OutS * 2
	movq %rax, 0xB0(%rsp)
	leaq (%rax, %rcx), %rbx # Out_3 = Out + OutS * 3
	movq %rbx, 0xB8(%rsp)
	addq %rcx, %rbx		# Out += OutS * 4;
	movq %rbx, 0x70(%rsp)
	movq 0x78(%rsp), %r8	# in0_0 = In0 + In0S * 0;
	movq 0x50(%rsp), %r10
	movq %r8, 0xC0(%rsp)
	leaq (%r8, %r10), %r9	# in0_1 = In0 + In0S * 1
	movq %r9, 0xC8(%rsp)
	leaq (%r9, %r10), %r8	# in0_2 = In0 + In0S * 2
	movq %r8, 0xD0(%rsp)
	leaq (%r8, %r10), %r9	# in0_3 = In0 + In0S * 3
	movq %r9, 0xD8(%rsp)
	addq %r10, %r9		# In0 += In0S * 4;
	movq %r9, 0x78(%rsp)
	movq 0x20(%rsp), %r12	# In1 = _In1;
	movq %r12, 0x80(%rsp)
	
	movq 0x90(%rsp), %rsi 	# for (i = K; i; i--) {
	test %rsi, %rsi
	je 4f

	.p2align 4,,8
	.p2align 5
1:
	movq 0xA0(%rsp), %rax		# out_0 = Out_0;
	movq 0xA8(%rsp), %rbx		# out_1 = Out_1;
	movq 0xB0(%rsp), %rcx		# out_2 = Out_2;
	movq 0xB8(%rsp), %rdx		# out_3 = Out_3;

	movq 0x58(%rsp), %r10		# In0s
	movq %r10, %r11
	shlq $1, %r11

	movq 0xC0(%rsp), %r8		# in0_0_0 = *(in0_0 + In0s * 0);
	movddup 0x000(%r8), %xmm0
	movapd %xmm0, 0x100(%rsp)
	movddup (%r8, %r10), %xmm1 	# in0_0_1 = *(in0_0 + In0s * 1)
	movapd %xmm1, 0x110(%rsp)
	addq %r11, %r8
	movddup 0x000(%r8), %xmm2 	# in0_0_2 = *(in0_0 + In0s * 2)
	movapd %xmm2, 0x120(%rsp)
	movddup (%r8, %r10), %xmm3 	# in0_0_3 = *(in0_0 + In0s * 3)
	movapd %xmm3, 0x130(%rsp)
	addq %r11, %r8			# in0_0 += In0s * 4
	movq %r8, 0xC0(%rsp)

	movq 0xC8(%rsp), %r8		# in0_1_0 = *(in0_1 + In0s * 0);
	movddup 0x000(%r8), %xmm4
	movapd %xmm4, 0x140(%rsp)
	movddup (%r8, %r10), %xmm5 	# in0_1_1 = *(in0_1 + In0s * 1)
	movapd %xmm5, 0x150(%rsp)
	addq %r11, %r8
	movddup 0x000(%r8), %xmm6 	# in0_1_2 = *(in0_1 + In0s * 2)
	movapd %xmm6, 0x160(%rsp)
	movddup (%r8, %r10), %xmm7 	# in0_1_3 = *(in0_1 + In0s * 3)
	movapd %xmm7, 0x170(%rsp)
	addq %r11, %r8			# in0_1 += In0s * 4
	movq %r8, 0xC8(%rsp)

	movq 0xD0(%rsp), %r8		# in0_2_0 = *(in0_2 + In0s * 0);
	movddup 0x000(%r8), %xmm8
	movapd %xmm8, 0x180(%rsp)
	movddup (%r8, %r10), %xmm9 	# in0_2_1 = *(in0_2 + In0s * 1)
	movapd %xmm9, 0x190(%rsp)
	addq %r11, %r8
	movddup 0x000(%r8), %xmm10 	# in0_2_2 = *(in0_2 + In0s * 2)
	movapd %xmm10, 0x1A0(%rsp)
	movddup (%r8, %r10), %xmm11 	# in0_2_3 = *(in0_2 + In0s * 3)
	movapd %xmm11, 0x1B0(%rsp)
	addq %r11, %r8			# in0_2 += In0s * 4
	movq %r8, 0xD0(%rsp)

	movq 0xD8(%rsp), %r8		# in0_3_0 = *(in0_3 + In0s * 0);
	movddup 0x000(%r8), %xmm12
	movapd %xmm12, 0x1C0(%rsp)
	movddup (%r8, %r10), %xmm13 	# in0_3_1 = *(in0_3 + In0s * 1)
	movapd %xmm13, 0x1D0(%rsp)
	addq %r11, %r8
	movddup 0x000(%r8), %xmm14 	# in0_3_2 = *(in0_3 + In0s * 2)
	movapd %xmm14, 0x1E0(%rsp)
	movddup (%r8, %r10), %xmm15 	# in0_3_3 = *(in0_3 + In0s * 3)
	movapd %xmm15, 0x1F0(%rsp)
	addq %r11, %r8			# in0_3 += In0s * 4
	movq %r8, 0xD8(%rsp)


	movq 0x80(%rsp), %r12		# in1_0 = In1 + In1S * 0;
	movq 0x60(%rsp), %r11
	leaq (%r12, %r11), %r13		# in1_1 = In1 + In1S * 1;
	leaq (%r13, %r11), %r14		# in1_2 = In1 + In1S * 2;
	leaq (%r14, %r11), %r15		# in1_3 = In1 + In1S * 3;
	addq %r15, %r11
	movq %r11, 0x80(%rsp)		# In1 += In1S * 4;

	movq 0x98(%rsp), %rdi		# for (j = N; j; j--) {
	test %rdi, %rdi
	je 3f

	.p2align 5,,16
	.p2align 6
2:
	# in1_0_0 = *(in1_0 + 0);
	# in1_0_1 = *(in1_0 + 1);
	# in1_0_2 = *(in1_0 + 2);
	# in1_0_3 = *(in1_0 + 3);
	# in1_0 += 4;
	movupd 0x000(%r12), %xmm8
	movupd 0x010(%r12), %xmm9
	addq $32, %r12
	# in1_1_0 = *(in1_1 + 0);
	# in1_1_1 = *(in1_1 + 1);
	# in1_1_2 = *(in1_1 + 2);
	# in1_1_3 = *(in1_1 + 3);
	# in1_1 += 4;
	movupd 0x000(%r13), %xmm10
	movupd 0x010(%r13), %xmm11
	addq $32, %r13
	# in1_2_0 = *(in1_2 + 0);
	# in1_2_1 = *(in1_2 + 1);
	# in1_2_2 = *(in1_2 + 2);
	# in1_2_3 = *(in1_2 + 3);
	# in1_2 += 4;
	movupd 0x000(%r14), %xmm12
	movupd 0x010(%r14), %xmm13
	addq $32, %r14
	# in1_3_0 = *(in1_3 + 0);
	# in1_3_1 = *(in1_3 + 1);
	# in1_3_2 = *(in1_3 + 2);
	# in1_3_3 = *(in1_3 + 3);
	# in1_3 += 4;
	movupd 0x000(%r15), %xmm14
	movupd 0x010(%r15), %xmm15
	addq $32, %r15

	# i0 = in0_0_0;
	# i1 = in0_0_1;
	# i2 = in0_0_2;
	# i3 = in0_0_3;
	movapd 0x100(%rsp), %xmm0
	movapd 0x100(%rsp), %xmm1
	movapd 0x110(%rsp), %xmm2
	movapd 0x110(%rsp), %xmm3
	movapd 0x120(%rsp), %xmm4
	movapd 0x120(%rsp), %xmm5
	movapd 0x130(%rsp), %xmm6
	movapd 0x130(%rsp), %xmm7
	# o0  = i0 * in1_0_0;
	# o1  = i0 * in1_0_1;
	# o2  = i0 * in1_0_2;
	# o3  = i0 * in1_0_3;
	mulpd %xmm8, %xmm0
	mulpd %xmm9, %xmm1
	# o0  += i1 * in1_1_0;
	# o1  += i1 * in1_1_1;
	# o2  += i1 * in1_1_2;
	# o3  += i1 * in1_1_3;
	mulpd %xmm10, %xmm2
	addpd %xmm0, %xmm2
	mulpd %xmm11, %xmm3
	addpd %xmm1, %xmm3
	# o0  += i2 * in1_2_0;
	# o1  += i2 * in1_2_1;
	# o2  += i2 * in1_2_2;
	# o3  += i2 * in1_2_3;
	mulpd %xmm12, %xmm4
	addpd %xmm4, %xmm2
	mulpd %xmm13, %xmm5
	addpd %xmm5, %xmm3
	# o0  += i3 * in1_3_0;
	# o1  += i3 * in1_3_1;
	# o2  += i3 * in1_3_2;
	# o3  += i3 * in1_3_3;
	mulpd %xmm14, %xmm6
	addpd %xmm6, %xmm2
	mulpd %xmm15, %xmm7
	addpd %xmm7, %xmm3
	# *(out_0 + 0) += o0;
	# *(out_0 + 1) += o1;
	# *(out_0 + 2) += o2;
	# *(out_0 + 3) += o3;
	movupd 0x000(%rax), %xmm0
	movupd 0x010(%rax), %xmm1
	addpd %xmm2, %xmm0
	addpd %xmm3, %xmm1
	movupd %xmm0, 0x000(%rax)
	movupd %xmm1, 0x010(%rax)
	# out_0 += 4;
	addq $32, %rax

	# i0 = in0_1_0;
	# i1 = in0_1_1;
	# i2 = in0_1_2;
	# i3 = in0_1_3;
	movapd 0x140(%rsp), %xmm0
	movapd 0x140(%rsp), %xmm1
	movapd 0x150(%rsp), %xmm2
	movapd 0x150(%rsp), %xmm3
	movapd 0x160(%rsp), %xmm4
	movapd 0x160(%rsp), %xmm5
	movapd 0x170(%rsp), %xmm6
	movapd 0x170(%rsp), %xmm7
	# o0  = i0 * in1_0_0;
	# o1  = i0 * in1_0_1;
	# o2  = i0 * in1_0_2;
	# o3  = i0 * in1_0_3;
	mulpd %xmm8, %xmm0
	mulpd %xmm9, %xmm1
	# o0  += i1 * in1_1_0;
	# o1  += i1 * in1_1_1;
	# o2  += i1 * in1_1_2;
	# o3  += i1 * in1_1_3;
	mulpd %xmm10, %xmm2
	addpd %xmm0, %xmm2
	mulpd %xmm11, %xmm3
	addpd %xmm1, %xmm3
	# o0  += i2 * in1_2_0;
	# o1  += i2 * in1_2_1;
	# o2  += i2 * in1_2_2;
	# o3  += i2 * in1_2_3;
	mulpd %xmm12, %xmm4
	addpd %xmm4, %xmm2
	mulpd %xmm13, %xmm5
	addpd %xmm5, %xmm3
	# o0  += i3 * in1_3_0;
	# o1  += i3 * in1_3_1;
	# o2  += i3 * in1_3_2;
	# o3  += i3 * in1_3_3;
	mulpd %xmm14, %xmm6
	addpd %xmm6, %xmm2
	mulpd %xmm15, %xmm7
	addpd %xmm7, %xmm3
	# *(out_1 + 0) += o0;
	# *(out_1 + 1) += o1;
	# *(out_1 + 2) += o2;
	# *(out_1 + 3) += o3;
	movupd 0x000(%rbx), %xmm0
	movupd 0x010(%rbx), %xmm1
	addpd %xmm2, %xmm0
	addpd %xmm3, %xmm1
	movupd %xmm0, 0x000(%rbx)
	movupd %xmm1, 0x010(%rbx)
	# out_1 += 4;
	addq $32, %rbx

	# i0 = in0_2_0;
	# i1 = in0_2_1;
	# i2 = in0_2_2;
	# i3 = in0_2_3;
	movapd 0x180(%rsp), %xmm0
	movapd 0x180(%rsp), %xmm1
	movapd 0x190(%rsp), %xmm2
	movapd 0x190(%rsp), %xmm3
	movapd 0x1A0(%rsp), %xmm4
	movapd 0x1A0(%rsp), %xmm5
	movapd 0x1B0(%rsp), %xmm6
	movapd 0x1B0(%rsp), %xmm7
	# o0  = i0 * in1_0_0;
	# o1  = i0 * in1_0_1;
	# o2  = i0 * in1_0_2;
	# o3  = i0 * in1_0_3;
	mulpd %xmm8, %xmm0
	mulpd %xmm9, %xmm1
	# o0  += i1 * in1_1_0;
	# o1  += i1 * in1_1_1;
	# o2  += i1 * in1_1_2;
	# o3  += i1 * in1_1_3;
	mulpd %xmm10, %xmm2
	addpd %xmm0, %xmm2
	mulpd %xmm11, %xmm3
	addpd %xmm1, %xmm3
	# o0  += i2 * in1_2_0;
	# o1  += i2 * in1_2_1;
	# o2  += i2 * in1_2_2;
	# o3  += i2 * in1_2_3;
	mulpd %xmm12, %xmm4
	addpd %xmm4, %xmm2
	mulpd %xmm13, %xmm5
	addpd %xmm5, %xmm3
	# o0  += i3 * in1_3_0;
	# o1  += i3 * in1_3_1;
	# o2  += i3 * in1_3_2;
	# o3  += i3 * in1_3_3;
	mulpd %xmm14, %xmm6
	addpd %xmm6, %xmm2
	mulpd %xmm15, %xmm7
	addpd %xmm7, %xmm3
	# *(out_2 + 0) += o0;
	# *(out_2 + 1) += o1;
	# *(out_2 + 2) += o2;
	# *(out_2 + 3) += o3;
	movupd 0x000(%rcx), %xmm0
	movupd 0x010(%rcx), %xmm1
	addpd %xmm2, %xmm0
	addpd %xmm3, %xmm1
	movupd %xmm0, 0x000(%rcx)
	movupd %xmm1, 0x010(%rcx)
	# out_2 += 4;
	addq $32, %rcx

	# i0 = in0_3_0;
	# i1 = in0_3_1;
	# i2 = in0_3_2;
	# i3 = in0_3_3;
	movapd 0x1C0(%rsp), %xmm0
	movapd 0x1C0(%rsp), %xmm1
	movapd 0x1D0(%rsp), %xmm2
	movapd 0x1D0(%rsp), %xmm3
	movapd 0x1E0(%rsp), %xmm4
	movapd 0x1E0(%rsp), %xmm5
	movapd 0x1F0(%rsp), %xmm6
	movapd 0x1F0(%rsp), %xmm7
	# o0  = i0 * in1_0_0;
	# o1  = i0 * in1_0_1;
	# o2  = i0 * in1_0_2;
	# o3  = i0 * in1_0_3;
	mulpd %xmm8, %xmm0
	mulpd %xmm9, %xmm1
	# o0  += i1 * in1_1_0;
	# o1  += i1 * in1_1_1;
	# o2  += i1 * in1_1_2;
	# o3  += i1 * in1_1_3;
	mulpd %xmm10, %xmm2
	addpd %xmm0, %xmm2
	mulpd %xmm11, %xmm3
	addpd %xmm1, %xmm3
	# o0  += i2 * in1_2_0;
	# o1  += i2 * in1_2_1;
	# o2  += i2 * in1_2_2;
	# o3  += i2 * in1_2_3;
	mulpd %xmm12, %xmm4
	addpd %xmm4, %xmm2
	mulpd %xmm13, %xmm5
	addpd %xmm5, %xmm3
	# o0  += i3 * in1_3_0;
	# o1  += i3 * in1_3_1;
	# o2  += i3 * in1_3_2;
	# o3  += i3 * in1_3_3;
	mulpd %xmm14, %xmm6
	addpd %xmm6, %xmm2
	mulpd %xmm15, %xmm7
	addpd %xmm7, %xmm3
	# *(out_3 + 0) += o0;
	# *(out_3 + 1) += o1;
	# *(out_3 + 2) += o2;
	# *(out_3 + 3) += o3;
	movupd 0x000(%rdx), %xmm0
	movupd 0x010(%rdx), %xmm1
	addpd %xmm2, %xmm0
	addpd %xmm3, %xmm1
	movupd %xmm0, 0x000(%rdx)
	movupd %xmm1, 0x010(%rdx)
	# out_3 += 4;
	addq $32, %rdx

	subq $1, %rdi		# } // for (j = n; j; j--) {
	jnz 2b

3:
	subq $1, %rsi		# } // for (i = k; i; i--) {
	jnz 1b

4:
	movq 0x08(%rsp), %rax	# } // for (h = m; h; h--) {
	subq $1, %rax
	jnz 0b

5:

	movq 0x10(%rsp), %rax	# Out = _Out
	movq %rax, 0x70(%rsp)
	movq 0x18(%rsp), %r8	# In0 = _In0
	movq %r8,  0x78(%rsp)
	movq 0x20(%rsp), %r12	# In1 = _In1
	movq %r12, 0x80(%rsp)

	movq 0x28(%rsp), %rax	# M = m & 3
	andq $3, %rax
	movq 0x30(%rsp), %r14	# K = k & 3
	andq $3, %r14
	movq 0x38(%rsp), %r15	# N = n & 3
	andq $3, %r15

	# Out _In0 _In1 m   k   n  OutS In0S In0s In1S
	# rdi rsi  rdx  rcx r8  r9 r10  r11  r12  r13
	movq 0x70(%rsp), %rdi	# Out
	movq 0x78(%rsp), %rsi	# In0
	movq 0x80(%rsp), %rdx	# In1
	movq 0x28(%rsp), %rcx	# m
	movq 0x30(%rsp), %r8	# k
	movq 0x38(%rsp), %r9	# n
	movq 0x40(%rsp), %r10	# OutS
	shrq $3, %r10
	movq %r10, 0x08(%rsp)
	movq 0x50(%rsp), %r11	# In0S
	shrq $3, %r11
	movq %r11, 0x10(%rsp)
	movq 0x58(%rsp), %r12	# In0s
	shrq $3, %r12
	movq %r12, 0x18(%rsp)
	movq 0x60(%rsp), %r13	# In1S
	shrq $3, %r13
	movq %r13, 0x20(%rsp)

	movq %rcx, %r10		# h = m;
	movq %r8, %r11		# i = k;
	movq %r9, %r12		# j = n;

	test %rax, %rax		# if (M) {
	jz 6f

	subq %rax, %r10		# h -= M;
	movq 0x40(%rsp), %rbx	# OutS
	movq 0x50(%rsp), %r13	# In0S

	imulq %r10, %rbx 	# Out += OutS * h
	addq %rbx, %rdi
	imulq %r10, %r13	# In0 += In0S * h
	addq %r13, %rsi
	movq %rax, %rcx		# M

	# dot_product_mkn_2x2x2(Out, In0, In1, M, k, n, OutS, In0S, In0s, In1S);
	movq %rax, 0xA0(%rsp)
	movq %rcx, 0xA8(%rsp)
	movq %rdx, 0xB0(%rsp)
	movq %rsi, 0xB8(%rsp)
	movq %rdi, 0xC0(%rsp)
	movq %r8,  0xC8(%rsp)
	movq %r9,  0xD0(%rsp)
	movq %r10, 0xD8(%rsp)
	movq %r11, 0xE0(%rsp)
	addq $8, %rsp
	call dot_product_double_mkn_2x2x2_sse4
	subq $8, %rsp
	movq 0xA0(%rsp), %rax
	movq 0xA8(%rsp), %rcx
	movq 0xB0(%rsp), %rdx
	movq 0xB8(%rsp), %rsi
	movq 0xC0(%rsp), %rdi
	movq 0xC8(%rsp), %r8
	movq 0xD0(%rsp), %r9
	movq 0xD8(%rsp), %r10
	movq 0xE0(%rsp), %r11

	movq 0x70(%rsp), %rdi	# Out = _Out
	movq 0x78(%rsp), %rsi	# In0 = _In0

6:
	movq %r10, %rcx		# } h
	test %r14, %r14		# if (K) {
	jz 7f

	subq %r14, %r11		# i -= K;
	movq 0x58(%rsp), %rbx	# In0s
	movq 0x60(%rsp), %r13	# In1S

	imulq %r11, %rbx	# In0 += In0s * i	
	addq %rbx, %rsi
	imulq %r11, %r13	# In1 += In1S * i	
	addq %r13, %rdx
	movq %r14, %r8		# K

	# dot_product_mkn_2x2x2(Out, In0, In1, h, K, n, OutS, In0S, In0s, In1S);
	movq %rax, 0xA0(%rsp)
	movq %rcx, 0xA8(%rsp)
	movq %rdx, 0xB0(%rsp)
	movq %rsi, 0xB8(%rsp)
	movq %rdi, 0xC0(%rsp)
	movq %r8,  0xC8(%rsp)
	movq %r9,  0xD0(%rsp)
	movq %r10, 0xD8(%rsp)
	movq %r11, 0xE0(%rsp)
	addq $8, %rsp
	call dot_product_double_mkn_2x2x2_sse4
	subq $8, %rsp
	movq 0xA0(%rsp), %rax
	movq 0xA8(%rsp), %rcx
	movq 0xB0(%rsp), %rdx
	movq 0xB8(%rsp), %rsi
	movq 0xC0(%rsp), %rdi
	movq 0xC8(%rsp), %r8
	movq 0xD0(%rsp), %r9
	movq 0xD8(%rsp), %r10
	movq 0xE0(%rsp), %r11

	movq 0x78(%rsp), %rsi	# In0 = _In0
	movq 0x80(%rsp), %rdx	# In1 = _In1

7:
	movq %r11, %r8		# } i
	test %r15, %r15		# if (N) {
	jz 8f

	subq %r15, %r12		# j -= N;
	shlq $3, %r12
	addq %r12, %rdi		# Out += j;
	addq %r12, %rdx		# In1 += j;
	movq %r15, %r9		# N

	# dot_product_mkn_1x1x1(Out, In0, In1, h, i, N, OutS, In0S, In0s, In1S);
	addq $8, %rsp
	call dot_product_double_mkn_1x1x1_sse4
	subq $8, %rsp
8:				# }

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

