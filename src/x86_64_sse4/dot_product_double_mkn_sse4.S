# SSE4 plan for dot_product_double_mkn

# RAX	out_0 and N
# RBX	out_1 and address offset
# RCX	out_2 and h and address offset
# RDX	out_3 
# RSI	i and OutS and In0S
# RDI	j and In0s and In1s
# R08	in0_0 
# R09	in0_1
# R10	in0_2 
# R11	in0_3 
# R12	in1_0 
# R13	in1_1 
# R14	in1_2 and M
# R15	in1_3 and K

# SIMD register plan

# xmm0-4:	out and in_0
# xmm4-7:	in0
# xmm8-15:	in1

# Gary Bhumbra

//------------------------------------------------------------------------------
# include "common_sse4.S"

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
	# _Out _In0 _In1 m   k   n  OutS In0S In0s In1S
	# rdi  rsi  rdx  rcx r8  r9 r10  r11  r12  r13

	movq %rdi, RSP_Out_     # _Out
	movq %rsi, RSP_In0_     # _In0
	movq %rdx, RSP_In1_     # _In1
	movq %rcx, RSP_m        # m
	movq %r8, RSP_k	        # k
	movq %r9, RSP_n	        # n

	xorq %r14, %r14
	addq $1, %r14

	testq %r10, %r10      # if (!OutS) {OutS = n;}
	cmove %r9, %r10
	shlq $3, %r10
	movq %r10, RSP_OutS
	testq %r11, %r11      # if (!In0S) {In0S = k;}
	cmove %r8, %r11
	shlq $3, %r11
	movq %r11, RSP_In0S
	testq %r12, %r12      # if (!In0s) {In1S = 1;}
	cmove %r14, %r12
	shlq $3, %r12
	movq %r12, RSP_In0s
	testq %r13, %r13      # if (!In1S) {In1S = n;}
	cmove %r9, %r13
	shlq $3, %r13
	movq %r13, RSP_In1S

	movq %rcx, RSP_M      # M = m;
	movq %r8, RSP_K       # K = k;
	movq %r9, RSP_N       # N = n;

	movq %rdi, RSP_Out    # Out = _Out; 
	movq %rsi, RSP_In0    # In0 = _In0; 

	test %rcx, %rcx       # for (h = M; h; h--) {
	je 5f

0:
	movq %rcx, RSP_h
	movq RSP_Out, %rax    # Out_0 = Out + OutS * 0;
	movq RSP_OutS, %rsi
	movq %rax, RSP_Out_0
	addq %rax, %rsi       # Out += OutS * 1;
	movq %rsi, RSP_Out
	movq RSP_In0, %r8     # in0_0 = In0 + In0S * 0;
	movq RSP_In0S, %rsi
	movq %r8, RSP_in0_0
	addq %r8, %rsi        # In0 += In0S * 1;
	movq %rsi, RSP_In0
	movq RSP_In1_, %r12   # In1 = _In1;
	movq %r12, RSP_In1

	movq RSP_K, %rsi      # for (i = K; i; i--) {
	testq %rsi, %rsi
	je 4f

1:
	movq RSP_Out_0, %rax     # out_0 = Out_0;
	movq RSP_in0_0, %r8      # in0_0_0 = *(in0_0 + In0s * 0);
	movq RSP_In0s, %rdi
	movsd 0x000(%r8), %xmm12
	addq %r8, %rdi           # in0_0 += In0s * 1;
	movq %rdi, RSP_in0_0
	movq RSP_In1, %r12       # in1_0 = In1 + In1S * 0;
	movq RSP_In1S, %rdi
	addq %r12, %rdi          # In1 += In1S * 1;
	movq %rdi, RSP_In1
	
	movq RSP_N, %rdi         # for (j = N; j; j--) {
	testq %rdi, %rdi
	je 3f

2:
	movsd 0x000(%r12), %xmm8 # in1_0_0 = *(in1_0 + 0);
	addq $8, %r12            # in1_0 += 1;
	movsd %xmm12, %xmm4      # i0 = in0_0_0;
	mulsd %xmm8, %xmm4       # o0 = i0 * in1_0_0;
	movsd 0x000(%rax), %xmm0 # *(out_0 + 0) += o0;
	addsd %xmm4, %xmm0
	movsd %xmm0, 0x000(%rax)
	addq $8, %rax            # out_0 += 1;

	subq $1, %rdi            # } // for (j = N; j; j--) {
	jne 2b

3:
	subq $1, %rsi            # } // for (i = K; k; k--) {
	jne 1b

4:
	movq RSP_h, %rcx         # } // for (h = M; h; h--) {
	subq $1, %rcx
	jne 0b

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
dot_product_double_mkn_1x1x2_sse4:
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
	# _Out _In0 _In1 m   k   n  OutS In0S In0s In1S
	# rdi  rsi  rdx  rcx r8  r9 r10  r11  r12  r13

	movq %rdi, RSP_Out_     # _Out
	movq %rsi, RSP_In0_     # _In0
	movq %rdx, RSP_In1_     # _In1
	movq %rcx, RSP_m        # m
	movq %r8, RSP_k	        # k
	movq %r9, RSP_n	        # n

	xorq %r14, %r14
	addq $1, %r14

	testq %r10, %r10      # if (!OutS) {OutS = n;}
	cmove %r9, %r10
	shlq $3, %r10
	movq %r10, RSP_OutS
	testq %r11, %r11      # if (!In0S) {In0S = k;}
	cmove %r8, %r11
	shlq $3, %r11
	movq %r11, RSP_In0S
	testq %r12, %r12      # if (!In0s) {In1S = 1;}
	cmove %r14, %r12
	shlq $3, %r12
	movq %r12, RSP_In0s
	testq %r13, %r13      # if (!In1S) {In1S = n;}
	cmove %r9, %r13
	shlq $3, %r13
	movq %r13, RSP_In1S

	movq %rcx, RSP_M      # M = m;
	movq %r8, RSP_K       # K = k;
	shrq $1, %r9          # N = n >> 1
	movq %r9, RSP_N 

	movq %rdi, RSP_Out    # Out = _Out; 
	movq %rsi, RSP_In0    # In0 = _In0; 

	test %rcx, %rcx       # for (h = M; h; h--) {
	je 5f

0:
	movq %rcx, RSP_h
	movq RSP_Out, %rax    # Out_0 = Out + OutS * 0;
	movq RSP_OutS, %rsi
	movq %rax, RSP_Out_0
	addq %rax, %rsi       # Out += OutS * 1;
	movq %rsi, RSP_Out
	movq RSP_In0, %r8     # in0_0 = In0 + In0S * 0;
	movq RSP_In0S, %rsi
	movq %r8, RSP_in0_0
	addq %r8, %rsi        # In0 += In0S * 1;
	movq %rsi, RSP_In0
	movq RSP_In1_, %r12   # In1 = _In1;
	movq %r12, RSP_In1

	movq RSP_K, %rsi      # for (i = K; i; i--) {
	testq %rsi, %rsi
	je 4f

1:
	movq RSP_Out_0, %rax     # out_0 = Out_0;
	movq RSP_in0_0, %r8      # in0_0_0 = *(in0_0 + In0s * 0);
	movq RSP_In0s, %rdi
	movddup 0x000(%r8), %xmm12
	addq %r8, %rdi           # in0_0 += In0s * 1;
	movq %rdi, RSP_in0_0
	movq RSP_In1, %r12       # in1_0 = In1 + In1S * 0;
	movq RSP_In1S, %rdi
	addq %r12, %rdi          # In1 += In1S * 1;
	movq %rdi, RSP_In1
	
	movq RSP_N, %rdi         # for (j = N; j; j--) {
	testq %rdi, %rdi
	je 3f

2:
	# in1_0_0 = *(in1_0 + 0);
	# in1_0_1 = *(in1_0 + 1);
	# in1_0 += 2;
	movupd 0x000(%r12), %xmm8 
	addq $16, %r12
	# i0 = in0_0_0;
	# o0 = i0 * in1_0_0
	# o1 = i0 * in1_0_1
	movapd %xmm12, %xmm4
	mulpd %xmm8, %xmm4
	# *(out_0 + 0) += o0;
	# *(out_0 + 1) += o1;
	# out_0 += 2;
	movupd 0x000(%rax), %xmm0
	addpd %xmm4, %xmm0
	movupd %xmm0, 0x000(%rax)
	addq $16, %rax

	subq $1, %rdi            # } // for (j = N; j; j--) {
	jne 2b

3:
	subq $1, %rsi            # } // for (i = K; k; k--) {
	jne 1b

4:
	movq RSP_h, %rcx         # } // for (h = M; h; h--) {
	subq $1, %rcx
	jne 0b

5:
	# _Out _In0 _In1 m   k   n  OutS In0S In0s In1S
	# rdi  rsi  rdx  rcx r8  r9 r10  r11  r12  r13
	movq RSP_Out_, %rdi      # Out = _Out;
	movq RSP_In0_, %rsi      # In0 = _In0;
	movq RSP_In1_, %rdx      # In1 = _In1;
	movq RSP_m, %rcx         # m
	movq RSP_k, %r8          # k
	movq RSP_n, %r9          # n
	movq RSP_OutS, %r10      # OutS
	shrq $3, %r10
	movq %r10, 0x08(%rsp)
	movq RSP_In0S, %r11      # In0S
	shrq $3, %r11
	movq %r11, 0x10(%rsp)
	movq RSP_In0s, %r12      # In0s
	shrq $3, %r12
	movq %r12, 0x18(%rsp)
	movq RSP_In1S, %r13      # In1S
	shrq $3, %r13
	movq %r13, 0x20(%rsp)

	movq %r9, %rbx           # j = n;
	movq RSP_N, %rax         # N <<= 1
	shlq $1, %rax
	cmpq %r9, %rax           # if (N < n) {
	jge 6f

	movq %r9, %rax           # N = n & 1;
	andq $1, %rax
	subq %rax, %rbx          # j -= N;
	shlq $3, %rbx
	addq %rbx, %rdi          # Out += j;
	addq %rbx, %rdx          # In1 += j;
	# dot_product_mkn_1x1x1(Out, In0, In1, m, k, N, OutS, In0S, In0s, In1s);
	movq %rax, %r9
	addq $8, %rsp
	call dot_product_double_mkn_1x1x1_sse4
	subq $8, %rsp

6:                               # } // if (N < n) {
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
dot_product_double_mkn_1x1x4_sse4:
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
	# _Out _In0 _In1 m   k   n  OutS In0S In0s In1S
	# rdi  rsi  rdx  rcx r8  r9 r10  r11  r12  r13

	movq %rdi, RSP_Out_     # _Out
	movq %rsi, RSP_In0_     # _In0
	movq %rdx, RSP_In1_     # _In1
	movq %rcx, RSP_m        # m
	movq %r8, RSP_k	        # k
	movq %r9, RSP_n	        # n

	xorq %r14, %r14
	addq $1, %r14

	testq %r10, %r10      # if (!OutS) {OutS = n;}
	cmove %r9, %r10
	shlq $3, %r10
	movq %r10, RSP_OutS
	testq %r11, %r11      # if (!In0S) {In0S = k;}
	cmove %r8, %r11
	shlq $3, %r11
	movq %r11, RSP_In0S
	testq %r12, %r12      # if (!In0s) {In1S = 1;}
	cmove %r14, %r12
	shlq $3, %r12
	movq %r12, RSP_In0s
	testq %r13, %r13      # if (!In1S) {In1S = n;}
	cmove %r9, %r13
	shlq $3, %r13
	movq %r13, RSP_In1S

	movq %rcx, RSP_M      # M = m;
	movq %r8, RSP_K       # K = k;
	shrq $2, %r9          # N = n >> 2
	movq %r9, RSP_N 

	movq %rdi, RSP_Out    # Out = _Out; 
	movq %rsi, RSP_In0    # In0 = _In0; 

	test %rcx, %rcx       # for (h = M; h; h--) {
	je 5f

0:
	movq %rcx, RSP_h
	movq RSP_Out, %rax    # Out_0 = Out + OutS * 0;
	movq RSP_OutS, %rsi
	movq %rax, RSP_Out_0
	addq %rax, %rsi       # Out += OutS * 1;
	movq %rsi, RSP_Out
	movq RSP_In0, %r8     # in0_0 = In0 + In0S * 0;
	movq RSP_In0S, %rsi
	movq %r8, RSP_in0_0
	addq %r8, %rsi        # In0 += In0S * 1;
	movq %rsi, RSP_In0
	movq RSP_In1_, %r12   # In1 = _In1;
	movq %r12, RSP_In1

	movq RSP_K, %rsi      # for (i = K; i; i--) {
	testq %rsi, %rsi
	je 4f

1:
	movq RSP_Out_0, %rax     # out_0 = Out_0;
	movq RSP_in0_0, %r8      # in0_0_0 = *(in0_0 + In0s * 0);
	movq RSP_In0s, %rdi
	movddup 0x000(%r8), %xmm12
	addq %r8, %rdi           # in0_0 += In0s * 1;
	movq %rdi, RSP_in0_0
	movq RSP_In1, %r12       # in1_0 = In1 + In1S * 0;
	movq RSP_In1S, %rdi
	addq %r12, %rdi          # In1 += In1S * 1;
	movq %rdi, RSP_In1
	
	movq RSP_N, %rdi         # for (j = N; j; j--) {
	testq %rdi, %rdi
	je 3f

2:
	# in1_0_0 = *(in1_0 + 0);
	# in1_0_1 = *(in1_0 + 1);
	# in1_0_2 = *(in1_0 + 2);
	# in1_0_3 = *(in1_0 + 3);
	# in1_0 += 4;
	movupd 0x000(%r12), %xmm8 
	movupd 0x010(%r12), %xmm9 
	addq $32, %r12
	# i0 = in0_0_0;
	# o0 = i0 * in1_0_0
	# o1 = i0 * in1_0_1
	# o2 = i0 * in1_0_2
	# o3 = i0 * in1_0_3
	movapd %xmm12, %xmm4
	movapd %xmm12, %xmm5
	mulpd %xmm8, %xmm4
	mulpd %xmm9, %xmm5
	# *(out_0 + 0) += o0;
	# *(out_0 + 1) += o1;
	# *(out_0 + 2) += o2;
	# *(out_0 + 3) += o3;
	# out_0 += 4;
	movupd 0x000(%rax), %xmm0
	movupd 0x010(%rax), %xmm1
	addpd %xmm4, %xmm0
	addpd %xmm5, %xmm1
	movupd %xmm0, 0x000(%rax)
	movupd %xmm1, 0x010(%rax)
	addq $32, %rax

	subq $1, %rdi            # } // for (j = N; j; j--) {
	jne 2b

3:
	subq $1, %rsi            # } // for (i = K; k; k--) {
	jne 1b

4:
	movq RSP_h, %rcx         # } // for (h = M; h; h--) {
	subq $1, %rcx
	jne 0b

5:
	# _Out _In0 _In1 m   k   n  OutS In0S In0s In1S
	# rdi  rsi  rdx  rcx r8  r9 r10  r11  r12  r13
	movq RSP_Out_, %rdi      # Out = _Out;
	movq RSP_In0_, %rsi      # In0 = _In0;
	movq RSP_In1_, %rdx      # In1 = _In1;
	movq RSP_m, %rcx         # m
	movq RSP_k, %r8          # k
	movq RSP_n, %r9          # n
	movq RSP_OutS, %r10      # OutS
	shrq $3, %r10
	movq %r10, 0x08(%rsp)
	movq RSP_In0S, %r11      # In0S
	shrq $3, %r11
	movq %r11, 0x10(%rsp)
	movq RSP_In0s, %r12      # In0s
	shrq $3, %r12
	movq %r12, 0x18(%rsp)
	movq RSP_In1S, %r13      # In1S
	shrq $3, %r13
	movq %r13, 0x20(%rsp)

	movq %r9, %rbx           # j = n;
	movq RSP_N, %rax         # N <<= 2
	shlq $2, %rax
	cmpq %r9, %rax           # if (N < n) {
	jge 6f

	movq %r9, %rax           # N = n & 3;
	andq $3, %rax
	subq %rax, %rbx          # j -= N;
	shlq $3, %rbx
	addq %rbx, %rdi          # Out += j;
	addq %rbx, %rdx          # In1 += j;
	# dot_product_mkn_1x1x2(Out, In0, In1, m, k, N, OutS, In0S, In0s, In1s);
	movq %rax, %r9
	addq $8, %rsp
	call dot_product_double_mkn_1x1x2_sse4
	subq $8, %rsp

6:                               # } // if (N < n) {
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
dot_product_double_mkn_1x1x8_sse4:
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
	# _Out _In0 _In1 m   k   n  OutS In0S In0s In1S
	# rdi  rsi  rdx  rcx r8  r9 r10  r11  r12  r13

	movq %rdi, RSP_Out_     # _Out
	movq %rsi, RSP_In0_     # _In0
	movq %rdx, RSP_In1_     # _In1
	movq %rcx, RSP_m        # m
	movq %r8, RSP_k	        # k
	movq %r9, RSP_n	        # n

	xorq %r14, %r14
	addq $1, %r14

	testq %r10, %r10      # if (!OutS) {OutS = n;}
	cmove %r9, %r10
	shlq $3, %r10
	movq %r10, RSP_OutS
	testq %r11, %r11      # if (!In0S) {In0S = k;}
	cmove %r8, %r11
	shlq $3, %r11
	movq %r11, RSP_In0S
	testq %r12, %r12      # if (!In0s) {In1S = 1;}
	cmove %r14, %r12
	shlq $3, %r12
	movq %r12, RSP_In0s
	testq %r13, %r13      # if (!In1S) {In1S = n;}
	cmove %r9, %r13
	shlq $3, %r13
	movq %r13, RSP_In1S

	movq %rcx, RSP_M      # M = m;
	movq %r8, RSP_K       # K = k;
	shrq $3, %r9          # N = n >> 3
	movq %r9, RSP_N 

	movq %rdi, RSP_Out    # Out = _Out; 
	movq %rsi, RSP_In0    # In0 = _In0; 

	test %rcx, %rcx       # for (h = M; h; h--) {
	je 5f

0:
	movq %rcx, RSP_h
	movq RSP_Out, %rax    # Out_0 = Out + OutS * 0;
	movq RSP_OutS, %rsi
	movq %rax, RSP_Out_0
	addq %rax, %rsi       # Out += OutS * 1;
	movq %rsi, RSP_Out
	movq RSP_In0, %r8     # in0_0 = In0 + In0S * 0;
	movq RSP_In0S, %rsi
	movq %r8, RSP_in0_0
	addq %r8, %rsi        # In0 += In0S * 1;
	movq %rsi, RSP_In0
	movq RSP_In1_, %r12   # In1 = _In1;
	movq %r12, RSP_In1

	movq RSP_K, %rsi      # for (i = K; i; i--) {
	testq %rsi, %rsi
	je 4f

1:
	movq RSP_Out_0, %rax     # out_0 = Out_0;
	movq RSP_in0_0, %r8      # in0_0_0 = *(in0_0 + In0s * 0);
	movq RSP_In0s, %rdi
	movddup 0x000(%r8), %xmm12
	addq %r8, %rdi           # in0_0 += In0s * 1;
	movq %rdi, RSP_in0_0
	movq RSP_In1, %r12       # in1_0 = In1 + In1S * 0;
	movq RSP_In1S, %rdi
	addq %r12, %rdi          # In1 += In1S * 1;
	movq %rdi, RSP_In1
	
	movq RSP_N, %rdi         # for (j = N; j; j--) {
	testq %rdi, %rdi
	je 3f

2:
	# in1_0_0 = *(in1_0 + 0);
	# in1_0_1 = *(in1_0 + 1);
	# in1_0_2 = *(in1_0 + 2);
	# in1_0_3 = *(in1_0 + 3);
	# in1_0_4 = *(in1_0 + 4);
	# in1_0_5 = *(in1_0 + 5);
	# in1_0_6 = *(in1_0 + 6);
	# in1_0_7 = *(in1_0 + 7);
	# in1_0 += 8;
	movupd 0x000(%r12), %xmm8 
	movupd 0x010(%r12), %xmm9 
	movupd 0x020(%r12), %xmm10 
	movupd 0x030(%r12), %xmm11 
	addq $64, %r12
	# i0 = in0_0_0;
	# o0 = i0 * in1_0_0
	# o1 = i0 * in1_0_1
	# o2 = i0 * in1_0_2
	# o3 = i0 * in1_0_3
	# o4 = i0 * in1_0_4
	# o5 = i0 * in1_0_5
	# o6 = i0 * in1_0_6
	# o7 = i0 * in1_0_7
	movapd %xmm12, %xmm4
	movapd %xmm12, %xmm5
	movapd %xmm12, %xmm6
	movapd %xmm12, %xmm7
	mulpd %xmm8, %xmm4
	mulpd %xmm9, %xmm5
	mulpd %xmm10, %xmm6
	mulpd %xmm11, %xmm7
	# *(out_0 + 0) += o0;
	# *(out_0 + 1) += o1;
	# *(out_0 + 2) += o2;
	# *(out_0 + 3) += o3;
	# *(out_0 + 4) += o4;
	# *(out_0 + 5) += o5;
	# *(out_0 + 6) += o6;
	# *(out_0 + 7) += o7;
	# out_0 += 8;
	movupd 0x000(%rax), %xmm0
	movupd 0x010(%rax), %xmm1
	movupd 0x020(%rax), %xmm2
	movupd 0x030(%rax), %xmm3
	addpd %xmm4, %xmm0
	addpd %xmm5, %xmm1
	addpd %xmm6, %xmm2
	addpd %xmm7, %xmm3
	movupd %xmm0, 0x000(%rax)
	movupd %xmm1, 0x010(%rax)
	movupd %xmm2, 0x020(%rax)
	movupd %xmm3, 0x030(%rax)
	addq $64, %rax

	subq $1, %rdi            # } // for (j = N; j; j--) {
	jne 2b

3:
	subq $1, %rsi            # } // for (i = K; k; k--) {
	jne 1b

4:
	movq RSP_h, %rcx         # } // for (h = M; h; h--) {
	subq $1, %rcx
	jne 0b

5:
	# _Out _In0 _In1 m   k   n  OutS In0S In0s In1S
	# rdi  rsi  rdx  rcx r8  r9 r10  r11  r12  r13
	movq RSP_Out_, %rdi      # Out = _Out;
	movq RSP_In0_, %rsi      # In0 = _In0;
	movq RSP_In1_, %rdx      # In1 = _In1;
	movq RSP_m, %rcx         # m
	movq RSP_k, %r8          # k
	movq RSP_n, %r9          # n
	movq RSP_OutS, %r10      # OutS
	shrq $3, %r10
	movq %r10, 0x08(%rsp)
	movq RSP_In0S, %r11      # In0S
	shrq $3, %r11
	movq %r11, 0x10(%rsp)
	movq RSP_In0s, %r12      # In0s
	shrq $3, %r12
	movq %r12, 0x18(%rsp)
	movq RSP_In1S, %r13      # In1S
	shrq $3, %r13
	movq %r13, 0x20(%rsp)

	movq %r9, %rbx           # j = n;
	movq RSP_N, %rax         # N <<= 3
	shlq $3, %rax
	cmpq %r9, %rax           # if (N < n) {
	jge 6f

	movq %r9, %rax           # N = n & 7;
	andq $7, %rax
	subq %rax, %rbx          # j -= N;
	shlq $3, %rbx
	addq %rbx, %rdi          # Out += j;
	addq %rbx, %rdx          # In1 += j;
	# dot_product_mkn_1x1x4(Out, In0, In1, m, k, N, OutS, In0S, In0s, In1s);
	movq %rax, %r9
	addq $8, %rsp
	call dot_product_double_mkn_1x1x4_sse4
	subq $8, %rsp

6:                               # } // if (N < n) {
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
	# _Out _In0 _In1 m   k   n  OutS In0S In0s In1S
	# rdi  rsi  rdx  rcx r8  r9 r10  r11  r12  r13

	movq %rdi, RSP_Out_     # _Out
	movq %rsi, RSP_In0_     # _In0
	movq %rdx, RSP_In1_     # _In1
	movq %rcx, RSP_m        # m
	movq %r8, RSP_k	        # k
	movq %r9, RSP_n	        # n

	xorq %r14, %r14
	addq $1, %r14

	testq %r10, %r10      # if (!OutS) {OutS = n;}
	cmove %r9, %r10
	shlq $3, %r10
	movq %r10, RSP_OutS
	testq %r11, %r11      # if (!In0S) {In0S = k;}
	cmove %r8, %r11
	shlq $3, %r11
	movq %r11, RSP_In0S
	testq %r12, %r12      # if (!In0s) {In1S = 1;}
	cmove %r14, %r12
	shlq $3, %r12
	movq %r12, RSP_In0s
	testq %r13, %r13      # if (!In1S) {In1S = n;}
	cmove %r9, %r13
	shlq $3, %r13
	movq %r13, RSP_In1S

	shrq $1, %rcx         # M = m >> 1;
	movq %rcx, RSP_M
	shrq $1, %r8          # K = k >> 1;
	movq %r8, RSP_K
	shrq $1, %r9          # N = n >> 1
	movq %r9, RSP_N 

	movq %rdi, RSP_Out    # Out = _Out; 
	movq %rsi, RSP_In0    # In0 = _In0; 

	test %rcx, %rcx       # for (h = M; h; h--) {
	je 5f

0:
	movq %rcx, RSP_h
	movq RSP_Out, %rax       # Out_0 = Out + OutS * 0;
	movq RSP_OutS, %rsi
	movq %rax, RSP_Out_0
	leaq 0(%rax, %rsi), %rbx # Out_1 = Out + Outs * 1;
	movq %rbx, RSP_Out_1
	addq %rbx, %rsi          # Out += OutS * 2;
	movq %rsi, RSP_Out
	movq RSP_In0, %r8        # in0_0 = In0 + In0S * 0;
	movq RSP_In0S, %rsi
	movq %r8, RSP_in0_0
	leaq 0(%r8, %rsi), %r9   # in0_1 = In0 + In1S * 1; 
	movq %r9, RSP_in0_1
	addq %r9, %rsi           # In0 += In0S * 2;
	movq %rsi, RSP_In0
	movq RSP_In1_, %r12      # In1 = _In1;
	movq %r12, RSP_In1

	movq RSP_K, %rsi         # for (i = K; i; i--) {
	testq %rsi, %rsi
	je 4f

1:
	movq RSP_Out_0, %rax     # out_0 = Out_0;
	movq RSP_Out_1, %rbx     # out_1 = Out_1;
	movq RSP_in0_0, %r8      # in0_0_0 = *(in0_0 + In0s * 0);
	movq RSP_In0s, %rdi
	movddup 0x000(%r8), %xmm12
	addq %rdi, %r8           # in0_0_1 = *(in0_0 + In0s * 1);
	movddup 0x000(%r8), %xmm13
	addq %rdi, %r8           # in0_0 += In0s * 2
	movq %r8, RSP_in0_0
	movq RSP_in0_1, %r9      # in0_1_0 = *(in0_1 + In0s * 0);
	movddup 0x000(%r9), %xmm14
	addq %rdi, %r9           # in0_1_1 = *(in0_1 + In0s * 1);
	movddup 0x000(%r9), %xmm15
	addq %rdi, %r9           # in0_1 += In0s * 2
	movq %r9, RSP_in0_1
	movq RSP_In1, %r12       # in1_0 = In1 + In1S * 0;
	movq RSP_In1S, %rdi
	leaq 0(%r12, %rdi), %r13 # in1_1 = In1 + In1S * 1;
	addq %r13, %rdi          # In1 += In1S * 2;
	movq %rdi, RSP_In1
	
	movq RSP_N, %rdi         # for (j = N; j; j--) {
	testq %rdi, %rdi
	je 3f

2:
	# in1_0_0 = *(in1_0 + 0);
	# in1_0_1 = *(in1_0 + 1);
	# in1_0 += 2;
	# in1_1_0 = *(in1_1 + 0);
	# in1_1_1 = *(in1_1 + 1);
	# in1_1 += 2;
	movupd 0x000(%r12), %xmm8 
	addq $16, %r12
	movupd 0x000(%r13), %xmm9 
	addq $16, %r13
	# i0  = in0_0_0;
	# i1  = in0_0_1;
	# o0  = i0 * in1_0_0
	# o1  = i0 * in1_0_1
	# o0 += i1 * in1_0_0
	# o1 += i1 * in1_0_1
	# *(out_0 + 0) += o0;
	# *(out_0 + 1) += o1;
	# out_0 += 2;
	movapd %xmm12, %xmm4
	movapd %xmm13, %xmm5
	mulpd %xmm8, %xmm4
	mulpd %xmm9, %xmm5
	addpd %xmm5, %xmm4
	movupd 0x000(%rax), %xmm0
	addpd %xmm4, %xmm0
	movupd %xmm0, 0x000(%rax)
	addq $16, %rax
	# i0  = in0_1_0;
	# i1  = in0_1_1;
	# o0  = i0 * in1_0_0
	# o1  = i0 * in1_0_1
	# o0 += i1 * in1_0_0
	# o1 += i1 * in1_0_1
	# *(out_1 + 0) += o0;
	# *(out_1 + 1) += o1;
	# out_1 += 2;
	movapd %xmm14, %xmm6
	movapd %xmm15, %xmm7
	mulpd %xmm8, %xmm6
	mulpd %xmm9, %xmm7
	addpd %xmm7, %xmm6
	movupd 0x000(%rbx), %xmm2
	addpd %xmm6, %xmm2
	movupd %xmm2, 0x000(%rbx)
	addq $16, %rbx

	subq $1, %rdi            # } // for (j = N; j; j--) {
	jne 2b

3:
	subq $1, %rsi            # } // for (i = K; k; k--) {
	jne 1b

4:
	movq RSP_h, %rcx         # } // for (h = M; h; h--) {
	subq $1, %rcx
	jne 0b

5:
	# _Out _In0 _In1 m   k   n  OutS In0S In0s In1S
	# rdi  rsi  rdx  rcx r8  r9 r10  r11  r12  r13
	movq RSP_Out_, %rdi      # Out = _Out;
	movq RSP_In0_, %rsi      # In0 = _In0;
	movq RSP_In1_, %rdx      # In1 = _In1;
	movq RSP_m, %rcx         # m
	movq RSP_k, %r8          # k
	movq RSP_n, %r9          # n
	movq RSP_OutS, %r10      # OutS
	shrq $3, %r10
	movq %r10, 0x08(%rsp)
	movq RSP_In0S, %r11      # In0S
	shrq $3, %r11
	movq %r11, 0x10(%rsp)
	movq RSP_In0s, %r12      # In0s
	shrq $3, %r12
	movq %r12, 0x18(%rsp)
	movq RSP_In1S, %r13      # In1S
	shrq $3, %r13
	movq %r13, 0x20(%rsp)

	movq RSP_M, %r14         # M <<= 1
	shlq $1, %r14
	movq RSP_K, %r15         # K <<= 1
	shlq $1, %r15
	movq RSP_N, %rax         # N <<= 1
	shlq $1, %rax

	movq %r9, %rbx           # j = n;
	cmpq %rbx, %rax          # if (N < j) {
	jge 6f

	movq %rbx, %rax          # N = j & 1;
	andq $1, %rax
	subq %rax, %rbx          # j -= N;
	shlq $3, %rbx
	addq %rbx, %rdi          # Out += j;
	addq %rbx, %rdx          # In1 += j;
	# dot_product_mkn_1x1x1(Out, In0, In1, M, K, N, OutS, In0S, In0s, In1s);
	movq %r14, %rcx
	movq %r15, %r8
	movq %rax, %r9
	addq $8, %rsp
	call dot_product_double_mkn_1x1x1_sse4
	subq $8, %rsp
	movq RSP_Out_, %rdi      # Out = _Out;
	movq RSP_In0_, %rsi      # In0 = _In0;
	movq RSP_In1_, %rdx      # In1 = _In1;
	movq RSP_m, %rcx
	movq RSP_k, %r8
	movq RSP_n, %r9
	movq 0x08(%rsp), %r10
	movq 0x10(%rsp), %r11
	movq 0x18(%rsp), %r12
	movq 0x20(%rsp), %r13

6:                               # } // if (N < n) {

	movq %r8, %rbx           # i = k
	cmpq %rbx, %r15          # if (K < i) {
	jge 7f

	movq %rbx, %r15          # K = i & 1
	andq $1, %r15
	subq %r15, %rbx          # i -= K;
	shlq $3, %rbx
	movq %rbx, %rcx          # In0 += In0s * i;
	imul %r12, %rcx 
	addq %rcx, %rsi
	imul %r13, %rbx          # In1 += In1S * i;
	addq %rbx, %rdx
	# dot_product_mkn_1x1x8(Out, In0, In1, M, K, n, OutS, In0S, In0s, In1s);
	movq %r14, %rcx
	movq %r15, %r8
	addq $8, %rsp
	call dot_product_double_mkn_1x1x8_sse4
	subq $8, %rsp
	movq RSP_Out_, %rdi      # Out = _Out;
	movq RSP_In0_, %rsi      # In0 = _In0;
	movq RSP_In1_, %rdx      # In1 = _In1;
	movq RSP_m, %rcx
	movq RSP_k, %r8
	movq RSP_n, %r9
	movq 0x08(%rsp), %r10
	movq 0x10(%rsp), %r11
	movq 0x18(%rsp), %r12
	movq 0x20(%rsp), %r13

7:
	movq %rcx, %rbx          # h = m
	cmpq %rbx, %r14          # if (M < h) {
	jge 8f

	movq %rbx, %r14          # M = h & 1
	andq $1, %r14
	subq %r15, %rbx          # h -= M;
	shlq $3, %rbx
	movq %rbx, %rcx          # Out += OutS * h;
	imul %r10, %rcx 
	addq %rcx, %rdi
	imul %r11, %rbx          # In0 += In0S * i;
	addq %rbx, %rsi
	# dot_product_mkn_1x1x8(Out, In0, In1, M, k, n, OutS, In0S, In0s, In1s);
	movq %r14, %rcx
	addq $8, %rsp
	call dot_product_double_mkn_1x1x8_sse4
	subq $8, %rsp
	movq RSP_Out_, %rdi      # Out = _Out;
	movq RSP_In0_, %rsi      # In0 = _In0;
	movq RSP_In1_, %rdx      # In1 = _In1;
	movq RSP_m, %rcx
	movq RSP_k, %r8
	movq RSP_n, %r9
	movq 0x08(%rsp), %r10
	movq 0x10(%rsp), %r11
	movq 0x18(%rsp), %r12
	movq 0x20(%rsp), %r13
8:
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
	andq $-256, %rsp

	mov 0x08(%rax), %r10
	mov 0x10(%rax), %r11
	mov 0x18(%rax), %r12
	mov 0x20(%rax), %r13
	# _Out _In0 _In1 m   k   n  OutS In0S In0s In1S
	# rdi  rsi  rdx  rcx r8  r9 r10  r11  r12  r13

	movq %rdi, RSP_Out_     # _Out
	movq %rsi, RSP_In0_     # _In0
	movq %rdx, RSP_In1_     # _In1
	movq %rcx, RSP_m        # m
	movq %r8, RSP_k	        # k
	movq %r9, RSP_n	        # n

	xorq %r14, %r14
	addq $1, %r14

	testq %r10, %r10      # if (!OutS) {OutS = n;}
	cmove %r9, %r10
	shlq $3, %r10
	movq %r10, RSP_OutS
	testq %r11, %r11      # if (!In0S) {In0S = k;}
	cmove %r8, %r11
	shlq $3, %r11
	movq %r11, RSP_In0S
	testq %r12, %r12      # if (!In0s) {In1S = 1;}
	cmove %r14, %r12
	shlq $3, %r12
	movq %r12, RSP_In0s
	testq %r13, %r13      # if (!In1S) {In1S = n;}
	cmove %r9, %r13
	shlq $3, %r13
	movq %r13, RSP_In1S

	shrq $2, %rcx         # M = m >> 2;
	movq %rcx, RSP_M
	shrq $2, %r8          # K = k >> 2;
	movq %r8, RSP_K
	shrq $2, %r9          # N = n >> 2
	movq %r9, RSP_N 

	movq %rdi, RSP_Out    # Out = _Out; 
	movq %rsi, RSP_In0    # In0 = _In0; 

	test %rcx, %rcx       # for (h = M; h; h--) {
	je 5f

0:
	movq %rcx, RSP_h
	movq RSP_Out, %rax       # Out_0 = Out + OutS * 0;
	movq RSP_OutS, %rsi
	movq %rax, RSP_Out_0
	leaq 0(%rax, %rsi), %rbx # Out_1 = Out + Outs * 1;
	movq %rbx, RSP_Out_1
	leaq 0(%rbx, %rsi), %rcx # Out_2 = Out + Outs * 2;
	movq %rcx, RSP_Out_2
	leaq 0(%rcx, %rsi), %rdx # Out_3 = Out + Outs * 3;
	movq %rdx, RSP_Out_3
	addq %rdx, %rsi          # Out += OutS * 4;
	movq %rsi, RSP_Out
	movq RSP_In0, %r8        # in0_0 = In0 + In0S * 0;
	movq RSP_In0S, %rsi
	movq %r8, RSP_in0_0
	leaq 0(%r8, %rsi), %r9   # in0_1 = In0 + In1S * 1; 
	movq %r9, RSP_in0_1
	leaq 0(%r9, %rsi), %r10  # in0_2 = In0 + In1S * 2; 
	movq %r10, RSP_in0_2
	leaq 0(%r10, %rsi), %r11 # in0_3 = In0 + In1S * 3; 
	movq %r11, RSP_in0_3
	addq %r11, %rsi          # In0 += In0S * 4;
	movq %rsi, RSP_In0
	movq RSP_In1_, %r12      # In1 = _In1;
	movq %r12, RSP_In1

	movq RSP_K, %rsi         # for (i = K; i; i--) {
	testq %rsi, %rsi
	je 4f

1:
	movq RSP_Out_0, %rax     # out_0 = Out_0;
	movq RSP_Out_1, %rbx     # out_1 = Out_1;
	movq RSP_Out_2, %rcx     # out_2 = Out_2;
	movq RSP_Out_3, %rdx     # out_3 = Out_3;
	movq RSP_in0_0, %r8      # in0_0_0 = *(in0_0 + In0s * 0);
	movq RSP_In0s, %rdi
	movddup 0x000(%r8), %xmm0
	movapd %xmm0 , 0x100(%rsp)
	addq %rdi, %r8           # in0_0_1 = *(in0_0 + In0s * 1);
	movddup 0x000(%r8), %xmm1
	movapd %xmm1 , 0x110(%rsp)
	addq %rdi, %r8           # in0_0_2 = *(in0_0 + In0s * 2);
	movddup 0x000(%r8), %xmm2
	movapd %xmm2 , 0x120(%rsp)
	addq %rdi, %r8           # in0_0_3 = *(in0_0 + In0s * 3);
	movddup 0x000(%r8), %xmm3
	movapd %xmm3 , 0x130(%rsp)
	addq %rdi, %r8           # in0_0 += In0s * 4
	movq %r8, RSP_in0_0
	movq RSP_in0_1, %r9      # in0_1_0 = *(in0_1 + In0s * 0);
	movddup 0x000(%r9), %xmm4
	movapd %xmm4 , 0x140(%rsp)
	addq %rdi, %r9           # in0_1_1 = *(in0_1 + In0s * 1);
	movddup 0x000(%r9), %xmm5
	movapd %xmm5 , 0x150(%rsp)
	addq %rdi, %r9           # in0_1_2 = *(in0_1 + In0s * 2);
	movddup 0x000(%r9), %xmm6
	movapd %xmm6 , 0x160(%rsp)
	addq %rdi, %r9           # in0_1_3 = *(in0_1 + In0s * 3);
	movddup 0x000(%r9), %xmm7
	movapd %xmm7 , 0x170(%rsp)
	addq %rdi, %r9           # in0_1 += In0s * 4
	movq %r9, RSP_in0_1
	movq RSP_in0_2, %r10     # in0_2_0 = *(in0_2 + In0s * 0);
	movddup 0x000(%r10), %xmm8
	movapd %xmm8 , 0x180(%rsp)
	addq %rdi, %r10          # in0_2_1 = *(in0_2 + In0s * 1);
	movddup 0x000(%r10), %xmm9
	movapd %xmm9 , 0x190(%rsp)
	addq %rdi, %r10          # in0_2_2 = *(in0_2 + In0s * 2);
	movddup 0x000(%r10), %xmm10
	movapd %xmm10, 0x1A0(%rsp)
	addq %rdi, %r10          # in0_2_3 = *(in0_2 + In0s * 3);
	movddup 0x000(%r10), %xmm11
	movapd %xmm11, 0x1B0(%rsp)
	addq %rdi, %r10          # in0_2 += In0s * 4
	movq %r10, RSP_in0_2
	movq RSP_in0_3, %r11     # in0_3_0 = *(in0_3 + In0s * 0);
	movddup 0x000(%r11), %xmm12
	movapd %xmm12, 0x1C0(%rsp)
	addq %rdi, %r11          # in0_3_1 = *(in0_3 + In0s * 1);
	movddup 0x000(%r11), %xmm13
	movapd %xmm13, 0x1D0(%rsp)
	addq %rdi, %r11          # in0_3_2 = *(in0_3 + In0s * 2);
	movddup 0x000(%r11), %xmm14
	movapd %xmm14, 0x1E0(%rsp)
	addq %rdi, %r11          # in0_3_3 = *(in0_3 + In0s * 3);
	movddup 0x000(%r11), %xmm15
	movapd %xmm15, 0x1F0(%rsp)
	addq %rdi, %r11          # in0_3 += In0s * 4
	movq %r11, RSP_in0_3

	movq RSP_In1, %r12       # in1_0 = In1 + In1S * 0;
	movq RSP_In1S, %rdi
	leaq 0(%r12, %rdi), %r13 # in1_1 = In1 + In1S * 1;
	leaq 0(%r13, %rdi), %r14 # in1_2 = In1 + In1S * 2;
	leaq 0(%r14, %rdi), %r15 # in1_3 = In1 + In1S * 3;
	addq %r15, %rdi          # In1 += In1S * 4;
	movq %rdi, RSP_In1
	
	movq RSP_N, %rdi         # for (j = N; j; j--) {
	testq %rdi, %rdi
	je 3f

2:
	# in1_0_0 = *(in1_0 + 0);
	# in1_0_1 = *(in1_0 + 1);
	# in1_0_2 = *(in1_0 + 2);
	# in1_0_3 = *(in1_0 + 3);
	# in1_0 += 4;
	# ...
	# in1_3_0 = *(in1_3 + 0);
	# in1_3_1 = *(in1_3 + 1);
	# in1_3_0 = *(in1_3 + 0);
	# in1_1_1 = *(in1_3 + 1);
	# in1_3 += 4;
	movupd 0x000(%r12), %xmm8 
	movupd 0x010(%r12), %xmm9 
	addq $32, %r12
	movupd 0x000(%r13), %xmm10
	movupd 0x010(%r13), %xmm11
	addq $32, %r13
	movupd 0x000(%r14), %xmm12 
	movupd 0x010(%r14), %xmm13 
	addq $32, %r14
	movupd 0x000(%r15), %xmm14
	movupd 0x010(%r15), %xmm15
	addq $32, %r15
	# i0 = in0_0_0;
	# i1 = in0_0_1;
	# i2 = in0_0_2;
	# i3 = in0_0_3;
	movapd 0x100(%rsp), %xmm0
	movapd %xmm0, %xmm1
	movapd 0x110(%rsp), %xmm2
	movapd %xmm2, %xmm3
	movapd 0x120(%rsp), %xmm4
	movapd %xmm4, %xmm5
	movapd 0x130(%rsp), %xmm6
	movapd %xmm6, %xmm7
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
	movapd %xmm0, %xmm1
	movapd 0x150(%rsp), %xmm2
	movapd %xmm2, %xmm3
	movapd 0x160(%rsp), %xmm4
	movapd %xmm4, %xmm5
	movapd 0x170(%rsp), %xmm6
	movapd %xmm6, %xmm7
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
	movapd %xmm0, %xmm1
	movapd 0x190(%rsp), %xmm2
	movapd %xmm2, %xmm3
	movapd 0x1A0(%rsp), %xmm4
	movapd %xmm4, %xmm5
	movapd 0x1B0(%rsp), %xmm6
	movapd %xmm6, %xmm7
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
	movapd %xmm0, %xmm1
	movapd 0x1D0(%rsp), %xmm2
	movapd %xmm2, %xmm3
	movapd 0x1E0(%rsp), %xmm4
	movapd %xmm4, %xmm5
	movapd 0x1F0(%rsp), %xmm6
	movapd %xmm6, %xmm7
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

	subq $1, %rdi            # } // for (j = N; j; j--) {
	jne 2b

3:
	subq $1, %rsi            # } // for (i = K; k; k--) {
	jne 1b

4:
	movq RSP_h, %rcx         # } // for (h = M; h; h--) {
	subq $1, %rcx
	jne 0b

5:
	# _Out _In0 _In1 m   k   n  OutS In0S In0s In1S
	# rdi  rsi  rdx  rcx r8  r9 r10  r11  r12  r13
	movq RSP_Out_, %rdi      # Out = _Out;
	movq RSP_In0_, %rsi      # In0 = _In0;
	movq RSP_In1_, %rdx      # In1 = _In1;
	movq RSP_m, %rcx         # m
	movq RSP_k, %r8          # k
	movq RSP_n, %r9          # n
	movq RSP_OutS, %r10      # OutS
	shrq $3, %r10
	movq %r10, 0x08(%rsp)
	movq RSP_In0S, %r11      # In0S
	shrq $3, %r11
	movq %r11, 0x10(%rsp)
	movq RSP_In0s, %r12      # In0s
	shrq $3, %r12
	movq %r12, 0x18(%rsp)
	movq RSP_In1S, %r13      # In1S
	shrq $3, %r13
	movq %r13, 0x20(%rsp)

	movq RSP_M, %r14         # M <<= 2
	shlq $2, %r14
	movq RSP_K, %r15         # K <<= 2
	shlq $2, %r15
	movq RSP_N, %rax         # N <<= 2
	shlq $2, %rax

	movq %r9, %rbx           # j = n;
	cmpq %rbx, %rax          # if (N < j) {
	jge 6f

	movq %rbx, %rax          # N = j & 3;
	andq $3, %rax
	subq %rax, %rbx          # j -= N;
	shlq $3, %rbx
	addq %rbx, %rdi          # Out += j;
	addq %rbx, %rdx          # In1 += j;
	# dot_product_mkn_2x2x2(Out, In0, In1, M, K, N, OutS, In0S, In0s, In1s);
	movq %r14, %rcx
	movq %r15, %r8
	movq %rax, %r9
	addq $8, %rsp
	call dot_product_double_mkn_2x2x2_sse4
	subq $8, %rsp
	movq RSP_Out_, %rdi      # Out = _Out;
	movq RSP_In0_, %rsi      # In0 = _In0;
	movq RSP_In1_, %rdx      # In1 = _In1;
	movq RSP_m, %rcx
	movq RSP_k, %r8
	movq RSP_n, %r9
	movq 0x08(%rsp), %r10
	movq 0x10(%rsp), %r11
	movq 0x18(%rsp), %r12
	movq 0x20(%rsp), %r13

6:                               # } // if (N < n) {

	movq %r8, %rbx           # i = k
	cmpq %rbx, %r15          # if (K < i) {
	jge 7f

	movq %rbx, %r15          # K = i & 3
	andq $3, %r15
	subq %r15, %rbx          # i -= K;
	shlq $3, %rbx
	movq %rbx, %rcx          # In0 += In0s * i;
	imul %r12, %rcx 
	addq %rcx, %rsi
	imul %r13, %rbx          # In1 += In1S * i;
	addq %rbx, %rdx
	# dot_product_mkn_2x2x2(Out, In0, In1, M, K, n, OutS, In0S, In0s, In1s);
	movq %r14, %rcx
	movq %r15, %r8
	addq $8, %rsp
	call dot_product_double_mkn_2x2x2_sse4
	subq $8, %rsp
	movq RSP_Out_, %rdi      # Out = _Out;
	movq RSP_In0_, %rsi      # In0 = _In0;
	movq RSP_In1_, %rdx      # In1 = _In1;
	movq RSP_m, %rcx
	movq RSP_k, %r8
	movq RSP_n, %r9
	movq 0x08(%rsp), %r10
	movq 0x10(%rsp), %r11
	movq 0x18(%rsp), %r12
	movq 0x20(%rsp), %r13

7:
	movq %rcx, %rbx          # h = m
	cmpq %rbx, %r14          # if (M < h) {
	jge 8f

	movq %rbx, %r14          # M = h & 3
	andq $3, %r14
	subq %r15, %rbx          # h -= M;
	shlq $3, %rbx
	movq %rbx, %rcx          # Out += OutS * h;
	imul %r10, %rcx 
	addq %rcx, %rdi
	imul %r11, %rbx          # In0 += In0S * i;
	addq %rbx, %rsi
	# dot_product_mkn_2x2x2(Out, In0, In1, M, k, n, OutS, In0S, In0s, In1s);
	movq %r14, %rcx
	addq $8, %rsp
	call dot_product_double_mkn_2x2x2_sse4
	subq $8, %rsp
	movq RSP_Out_, %rdi      # Out = _Out;
	movq RSP_In0_, %rsi      # In0 = _In0;
	movq RSP_In1_, %rdx      # In1 = _In1;
	movq RSP_m, %rcx
	movq RSP_k, %r8
	movq RSP_n, %r9
	movq 0x08(%rsp), %r10
	movq 0x10(%rsp), %r11
	movq 0x18(%rsp), %r12
	movq 0x20(%rsp), %r13
8:
	movq %rbp, %rsp
	pop %r15
	pop %r14
	pop %r13
	pop %r12
	pop %rbx
	pop %rbp
	pop %rsp
	ret

// Laus deo

//------------------------------------------------------------------------------

