# MNK Register Plan
#
# Registers:

# rax out 
# rbx in0 
# rcx m -> M -> h -> in1 
# rdx In1
# rsi In0
# rdi Out 
# r8  k -> K -> j
# r9  n -> N -> i
# r10 OutS (bytes)
# r11 In0S (bytes)
# r12 In1S (bytes)
# r13 _out
# r14 _in0 
# r15 unused
 
//------------------------------------------------------------------------------
# include "common_sse4.S"

//------------------------------------------------------------------------------
	.globl dot_product_double_mnk_1x8x8_sse4
	.globl dot_product_double_MNK_1x8x8_sse4
	.globl dot_product_double_mnk_2x1x8_sse4
	.globl dot_product_double_MNK_2x1x8_sse4
//------------------------------------------------------------------------------
	.text

//------------------------------------------------------------------------------
dot_product_double_mnk_1x8x8_sse4:
	movq %rsp, %rax
	push %rsp
	push %rbp
	push %rbx
	push %r12
	push %r13
	push %r14
	push %r15
	movq %rsp, %rbp
	mov 0x08(%rax), %r10
	mov 0x10(%rax), %r11
	mov 0x18(%rax), %r12

	# Out In0 In1  m   k  n  OutS
	# rdi rsi rdx  rcx r8 r9 r10 
	movq %rdi, RZP_Out    # Out
	movq %rsi, RZP_In0    # In0
	movq %rdx, RZP_In1    # In1

	testq %r10, %r10      # if (!OutS) {OutS = n;}
	cmove %r9, %r10
	shlq $3, %r10
	testq %r11, %r11      # if (!In0S) {In0S = k;}
	cmove %r8, %r11
	shlq $3, %r11
	testq %r12, %r12      # if (!In1S) {In1S = n;}
	cmove %r9, %r12
	shlq $3, %r12

	movq %rcx, RZP_M      # M
	shrq $3, %r8          # K = k >> 3;
	movq %r8, RZP_K
	shrq $3, %r9          # N = n >> 3;
	movq %r9, RZP_N

	movq RZP_M, %rcx      # for (h = M; h; h--) {
	testq %rcx, %rcx       
	je 5f

0:
	movq %rcx, RZP_h      # h
	movq RZP_Out, %rax    # _out = Out;
	movq %rax, %rdi
	addq %r10, %rax       # Out += OutS;
	movq %rax, RZP_Out 
	movq RZP_In0, %rbx    # _in0 = In0;
	movq %rbx, %rsi
	addq %r11, %rbx       # In0 += In0S;
	movq %rbx, RZP_In0 
	movq RZP_In1, %rdx    # _in1 = In1;

	movq RZP_N, %r9       # for (i = N; i; i--) {
	testq %r9, %r9
	je 4f

1:
	movq %rdi, %rax       # out = _out;
	addq $64, %rdi        # _out += (U)8
	movq %rsi, %rbx       # in0 = _in0
	movq %rdx, %rcx       # in1 = _in1
	addq $64, %rdx        # _in1 += (U)8
	# o0 = *(out + 0)
	# ...
	# o7 = *(out + 7)
	movupd 0x00(%rax), %xmm0
	movupd 0x10(%rax), %xmm1
	movupd 0x20(%rax), %xmm2
	movupd 0x30(%rax), %xmm3
	
	movq RZP_K, %r8       # for (j = K; j; j--) {
	test %r8, %r8
	je 3f

2:
	# i0 = *(in0 + 0);
	# ...
	# i7 = *(in0 + 7); 
	movddup 0x00(%rbx), %xmm8
	movddup 0x08(%rbx), %xmm9
	movddup 0x10(%rbx), %xmm10
	movddup 0x18(%rbx), %xmm11
	movddup 0x20(%rbx), %xmm12
	movddup 0x28(%rbx), %xmm13
	movddup 0x30(%rbx), %xmm14
	movddup 0x38(%rbx), %xmm15
	# in0 += (U)8
	addq $64, %rbx		

	# o0 += i0 * *(in1 + 0);
	# ...
	# o7 += i0 * *(in1 + 7);
	# in1 += In1S
	# .
	# .
	# .
	# o0 += i7 * *(in1 + 0);
	# ...
	# o7 += i7 * *(in1 + 7);
	# in1 += In1S
	movupd 0x00(%rcx), %xmm4
	movupd 0x10(%rcx), %xmm5
	movupd 0x20(%rcx), %xmm6
	movupd 0x30(%rcx), %xmm7
	mulpd %xmm8 , %xmm4
	addpd %xmm4 , %xmm0
	mulpd %xmm8 , %xmm5
	addpd %xmm5 , %xmm1
	mulpd %xmm8 , %xmm6
	addpd %xmm6 , %xmm2
	mulpd %xmm8 , %xmm7
	addpd %xmm7 , %xmm3
	addq %r12, %rcx
	movupd 0x00(%rcx), %xmm4
	movupd 0x10(%rcx), %xmm5
	movupd 0x20(%rcx), %xmm6
	movupd 0x30(%rcx), %xmm7
	mulpd %xmm9 , %xmm4
	addpd %xmm4 , %xmm0
	mulpd %xmm9 , %xmm5
	addpd %xmm5 , %xmm1
	mulpd %xmm9 , %xmm6
	addpd %xmm6 , %xmm2
	mulpd %xmm9 , %xmm7
	addpd %xmm7 , %xmm3
	addq %r12, %rcx
	movupd 0x00(%rcx), %xmm4
	movupd 0x10(%rcx), %xmm5
	movupd 0x20(%rcx), %xmm6
	movupd 0x30(%rcx), %xmm7
	mulpd %xmm10, %xmm4
	addpd %xmm4 , %xmm0
	mulpd %xmm10, %xmm5
	addpd %xmm5 , %xmm1
	mulpd %xmm10, %xmm6
	addpd %xmm6 , %xmm2
	mulpd %xmm10, %xmm7
	addpd %xmm7 , %xmm3
	addq %r12, %rcx
	movupd 0x00(%rcx), %xmm4
	movupd 0x10(%rcx), %xmm5
	movupd 0x20(%rcx), %xmm6
	movupd 0x30(%rcx), %xmm7
	mulpd %xmm11, %xmm4
	addpd %xmm4 , %xmm0
	mulpd %xmm11, %xmm5
	addpd %xmm5 , %xmm1
	mulpd %xmm11, %xmm6
	addpd %xmm6 , %xmm2
	mulpd %xmm11, %xmm7
	addpd %xmm7 , %xmm3
	addq %r12, %rcx
	movupd 0x00(%rcx), %xmm4
	movupd 0x10(%rcx), %xmm5
	movupd 0x20(%rcx), %xmm6
	movupd 0x30(%rcx), %xmm7
	mulpd %xmm12, %xmm4
	addpd %xmm4 , %xmm0
	mulpd %xmm12, %xmm5
	addpd %xmm5 , %xmm1
	mulpd %xmm12, %xmm6
	addpd %xmm6 , %xmm2
	mulpd %xmm12, %xmm7
	addpd %xmm7 , %xmm3
	addq %r12, %rcx
	movupd 0x00(%rcx), %xmm4
	movupd 0x10(%rcx), %xmm5
	movupd 0x20(%rcx), %xmm6
	movupd 0x30(%rcx), %xmm7
	mulpd %xmm13, %xmm4
	addpd %xmm4 , %xmm0
	mulpd %xmm13, %xmm5
	addpd %xmm5 , %xmm1
	mulpd %xmm13, %xmm6
	addpd %xmm6 , %xmm2
	mulpd %xmm13, %xmm7
	addpd %xmm7 , %xmm3
	addq %r12, %rcx
	movupd 0x00(%rcx), %xmm4
	movupd 0x10(%rcx), %xmm5
	movupd 0x20(%rcx), %xmm6
	movupd 0x30(%rcx), %xmm7
	mulpd %xmm14, %xmm4
	addpd %xmm4 , %xmm0
	mulpd %xmm14, %xmm5
	addpd %xmm5 , %xmm1
	mulpd %xmm14, %xmm6
	addpd %xmm6 , %xmm2
	mulpd %xmm14, %xmm7
	addpd %xmm7 , %xmm3
	addq %r12, %rcx
	movupd 0x00(%rcx), %xmm4
	movupd 0x10(%rcx), %xmm5
	movupd 0x20(%rcx), %xmm6
	movupd 0x30(%rcx), %xmm7
	mulpd %xmm15, %xmm4
	addpd %xmm4 , %xmm0
	mulpd %xmm15, %xmm5
	addpd %xmm5 , %xmm1
	mulpd %xmm15, %xmm6
	addpd %xmm6 , %xmm2
	mulpd %xmm15, %xmm7
	addpd %xmm7 , %xmm3
	addq %r12, %rcx
	
	subq $1, %r8     # } // for (j = K; j; j--) {
	jnz 2b

3:
	# *(out + 0) = o0;
	# ...
	# *(out + 7) = o7;
	movupd %xmm0, 0x00(%rax)
	movupd %xmm1, 0x10(%rax)
	movupd %xmm2, 0x20(%rax)
	movupd %xmm3, 0x30(%rax)
	
	subq $1, %r9     # } // for (i = N; i; i--) {
	jnz 1b

4:
	movq RZP_h, %rcx # } // for (h = M; h; h--) {
	subq $1, %rcx 	
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
dot_product_double_MNK_1x8x8_sse4:
	movq %rsp, %rax
	push %rsp
	push %rbp
	push %rbx
	push %r12
	push %r13
	push %r14
	push %r15
	movq %rsp, %rbp
	movq 0x08(%rax), %r10

	# Out In0 In1  m   k  n  OutS
	# rdi rsi rdx  rcx r8 r9 r10 
	movq %rdi, RZP_Out    # Out
	movq %rsi, RZP_In0    # In0
	movq %rdx, RZP_In1    # In1

	testq %r10, %r10      # if (!OutS) {OutS = n;}
	cmove %r9, %r10
	shlq $3, %r10
	movq %r8, %r11        # In0S = k
	shlq $3, %r11
	movq %r9, %r12        # In1S = n
	shlq $3, %r12

	movq %rcx, RZP_M      # M
	shrq $3, %r8          # K = k >> 3;
	movq %r8, RZP_K
	shrq $3, %r9          # N = n >> 3;
	movq %r9, RZP_N

	movq RZP_M, %rcx      # for (h = M; h; h--) {
	testq %rcx, %rcx       
	je 5f

0:
	movq %rcx, RZP_h      # h
	movq RZP_Out, %rax    # _out = Out;
	movq %rax, %rdi
	addq %r10, %rax       # Out += OutS;
	movq %rax, RZP_Out 
	movq RZP_In0, %rbx    # _in0 = In0;
	movq %rbx, %rsi
	addq %r11, %rbx       # In0 += In0S;
	movq %rbx, RZP_In0 
	movq RZP_In1, %rdx    # _in1 = In1;

	movq RZP_N, %r9       # for (i = N; i; i--) {
	testq %r9, %r9
	je 4f

1:
	movq %rdi, %rax       # out = _out;
	addq $64, %rdi        # _out += (U)8
	movq %rsi, %rbx       # in0 = _in0
	movq %rdx, %rcx       # in1 = _in1
	addq $64, %rdx        # _in1 += (U)8
	# o0 = *(out + 0)
	# ...
	# o7 = *(out + 7)
	movupd 0x00(%rax), %xmm0
	movupd 0x10(%rax), %xmm1
	movupd 0x20(%rax), %xmm2
	movupd 0x30(%rax), %xmm3
	
	movq RZP_K, %r8       # for (j = K; j; j--) {
	testq %r8, %r8
	je 3f

2:
	# i0 = *(in0 + 0);
	# ...
	# i7 = *(in0 + 7); 
	movddup 0x00(%rbx), %xmm8
	movddup 0x08(%rbx), %xmm9
	movddup 0x10(%rbx), %xmm10
	movddup 0x18(%rbx), %xmm11
	movddup 0x20(%rbx), %xmm12
	movddup 0x28(%rbx), %xmm13
	movddup 0x30(%rbx), %xmm14
	movddup 0x38(%rbx), %xmm15
	# in0 += (U)8
	addq $64, %rbx		
	# PREFETCH_READ_3(in0)
	PREFETCHT0(0(%rbx))

	# o0 += i0 * *(in1 + 0);
	# ...
	# o7 += i0 * *(in1 + 7);
	# in1 += In1S
	# PREFETCH_READ_3(in1+In1S*8)
	# .
	# .
	# .
	# o0 += i7 * *(in1 + 0);
	# ...
	# o7 += i7 * *(in1 + 7);
	# in1 += In1S
	# PREFETCH_READ_3(in1+In1S*8)
	movupd 0x00(%rcx), %xmm4
	movupd 0x10(%rcx), %xmm5
	movupd 0x20(%rcx), %xmm6
	movupd 0x30(%rcx), %xmm7
	mulpd %xmm8 , %xmm4
	addpd %xmm4 , %xmm0
	mulpd %xmm8 , %xmm5
	addpd %xmm5 , %xmm1
	mulpd %xmm8 , %xmm6
	addpd %xmm6 , %xmm2
	mulpd %xmm8 , %xmm7
	addpd %xmm7 , %xmm3
	addq %r12, %rcx
	PREFETCHT0(0(%rcx, %r12, 8))
	movupd 0x00(%rcx), %xmm4
	movupd 0x10(%rcx), %xmm5
	movupd 0x20(%rcx), %xmm6
	movupd 0x30(%rcx), %xmm7
	mulpd %xmm9 , %xmm4
	addpd %xmm4 , %xmm0
	mulpd %xmm9 , %xmm5
	addpd %xmm5 , %xmm1
	mulpd %xmm9 , %xmm6
	addpd %xmm6 , %xmm2
	mulpd %xmm9 , %xmm7
	addpd %xmm7 , %xmm3
	addq %r12, %rcx
	PREFETCHT0(0(%rcx, %r12, 8))
	movupd 0x00(%rcx), %xmm4
	movupd 0x10(%rcx), %xmm5
	movupd 0x20(%rcx), %xmm6
	movupd 0x30(%rcx), %xmm7
	mulpd %xmm10, %xmm4
	addpd %xmm4 , %xmm0
	mulpd %xmm10, %xmm5
	addpd %xmm5 , %xmm1
	mulpd %xmm10, %xmm6
	addpd %xmm6 , %xmm2
	mulpd %xmm10, %xmm7
	addpd %xmm7 , %xmm3
	addq %r12, %rcx
	PREFETCHT0(0(%rcx, %r12, 8))
	movupd 0x00(%rcx), %xmm4
	movupd 0x10(%rcx), %xmm5
	movupd 0x20(%rcx), %xmm6
	movupd 0x30(%rcx), %xmm7
	mulpd %xmm11, %xmm4
	addpd %xmm4 , %xmm0
	mulpd %xmm11, %xmm5
	addpd %xmm5 , %xmm1
	mulpd %xmm11, %xmm6
	addpd %xmm6 , %xmm2
	mulpd %xmm11, %xmm7
	addpd %xmm7 , %xmm3
	addq %r12, %rcx
	PREFETCHT0(0(%rcx, %r12, 8))
	movupd 0x00(%rcx), %xmm4
	movupd 0x10(%rcx), %xmm5
	movupd 0x20(%rcx), %xmm6
	movupd 0x30(%rcx), %xmm7
	mulpd %xmm12, %xmm4
	addpd %xmm4 , %xmm0
	mulpd %xmm12, %xmm5
	addpd %xmm5 , %xmm1
	mulpd %xmm12, %xmm6
	addpd %xmm6 , %xmm2
	mulpd %xmm12, %xmm7
	addpd %xmm7 , %xmm3
	addq %r12, %rcx
	PREFETCHT0(0(%rcx, %r12, 8))
	movupd 0x00(%rcx), %xmm4
	movupd 0x10(%rcx), %xmm5
	movupd 0x20(%rcx), %xmm6
	movupd 0x30(%rcx), %xmm7
	mulpd %xmm13, %xmm4
	addpd %xmm4 , %xmm0
	mulpd %xmm13, %xmm5
	addpd %xmm5 , %xmm1
	mulpd %xmm13, %xmm6
	addpd %xmm6 , %xmm2
	mulpd %xmm13, %xmm7
	addpd %xmm7 , %xmm3
	addq %r12, %rcx
	PREFETCHT0(0(%rcx, %r12, 8))
	movupd 0x00(%rcx), %xmm4
	movupd 0x10(%rcx), %xmm5
	movupd 0x20(%rcx), %xmm6
	movupd 0x30(%rcx), %xmm7
	mulpd %xmm14, %xmm4
	addpd %xmm4 , %xmm0
	mulpd %xmm14, %xmm5
	addpd %xmm5 , %xmm1
	mulpd %xmm14, %xmm6
	addpd %xmm6 , %xmm2
	mulpd %xmm14, %xmm7
	addpd %xmm7 , %xmm3
	addq %r12, %rcx
	PREFETCHT0(0(%rcx, %r12, 8))
	movupd 0x00(%rcx), %xmm4
	movupd 0x10(%rcx), %xmm5
	movupd 0x20(%rcx), %xmm6
	movupd 0x30(%rcx), %xmm7
	mulpd %xmm15, %xmm4
	addpd %xmm4 , %xmm0
	mulpd %xmm15, %xmm5
	addpd %xmm5 , %xmm1
	mulpd %xmm15, %xmm6
	addpd %xmm6 , %xmm2
	mulpd %xmm15, %xmm7
	addpd %xmm7 , %xmm3
	addq %r12, %rcx
	PREFETCHT0(0(%rcx, %r12, 8))
	
	subq $1, %r8     # } // for (j = K; j; j--) {
	jnz 2b

3:
	# *(out + 0) = o0;
	# ...
	# *(out + 7) = o7;
	movupd %xmm0, 0x00(%rax)
	movupd %xmm1, 0x10(%rax)
	movupd %xmm2, 0x20(%rax)
	movupd %xmm3, 0x30(%rax)
	
	subq $1, %r9     # } // for (i = N; i; i--) {
	jnz 1b

4:
	movq RZP_h, %rcx # } // for (h = M; h; h--) {
	subq $1, %rcx 	
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
dot_product_double_mnk_2x1x8_sse4:
	movq %rsp, %rax
	push %rsp
	push %rbp
	push %rbx
	push %r12
	push %r13
	push %r14
	push %r15
	movq %rsp, %rbp
	mov 0x08(%rax), %r10
	mov 0x10(%rax), %r11
	mov 0x18(%rax), %r12

	# Out In0 In1  m   k  n  OutS
	# rdi rsi rdx  rcx r8 r9 r10 
	movq %rdi, RZP_Out    # Out
	movq %rsi, RZP_In0    # In0
	movq %rdx, RZP_In1    # In1

	testq %r10, %r10      # if (!OutS) {OutS = n;}
	cmove %r9, %r10
	shlq $3, %r10
	testq %r11, %r11      # if (!In0S) {In0S = k;}
	cmove %r8, %r11
	shlq $3, %r11
	testq %r12, %r12      # if (!In1S) {In1S = n;}
	cmove %r9, %r12
	shlq $3, %r12

	shrq $1, %rcx         # M = m >> 1
	movq %rcx, RZP_M
	movq %r8, RZP_K       # K = k;
	shrq $3, %r9          # N = n >> 3;
	movq %r9, RZP_N

	movq RZP_M, %rcx      # for (h = M; h; h--) {
	testq %rcx, %rcx       
	je 5f

0:
	movq %rcx, RZP_h            # h
	movq RZP_Out, %rax          # _out = Out;
	movq %rax, %rdi
	leaq 0(%rax, %r10, 2), %rax # Out += OutS;
	movq %rax, RZP_Out 
	movq RZP_In0, %rbx          # _in0 = In0;
	movq %rbx, %rsi
	leaq 0(%rbx, %r11, 2), %rbx # In0 += k
	movq %rbx, RZP_In0 
	movq RZP_In1, %rdx          # _in1 = In1;

	movq RZP_N, %r9             # for (i = N; i; i--) {
	testq %r9, %r9
	je 4f

1:
	movq %rdi, %rax             # out = _out;
	leaq 0(%rax, %r10), %r13    # out_ = out + OutS
	addq $64, %rdi              # _out += (U)8
	movq %rsi, %rbx             # in0 = _in0
	leaq 0(%rbx, %r11), %r14    # in0_ = in0 + k
	movq %rdx, %rcx             # in1 = _in1
	addq $64, %rdx              # _in1 += (U)8
	# out0_0 = *(out  + 0)
	# ...
	# out0_7 = *(out  + 7)
	# out1_0 = *(out_ + 0)
	# ...
	# out1_7 = *(out_ + 7)
	movupd 0x00(%rax), %xmm0
	movupd 0x10(%rax), %xmm1
	movupd 0x20(%rax), %xmm2
	movupd 0x30(%rax), %xmm3
	movupd 0x00(%r13), %xmm4
	movupd 0x10(%r13), %xmm5
	movupd 0x20(%r13), %xmm6
	movupd 0x30(%r13), %xmm7
	
	movq RZP_K, %r8  # for (j = K; j; j--) {
	testq %r8, %r8
	je 3f

2:
	# in1_0 = *(in1 + 0)
	# ...
	# in1_7 = *(in1 + 7)
	# in1 += In1S
	movupd 0x00(%rcx), %xmm12
	movupd 0x10(%rcx), %xmm13
	movupd 0x20(%rcx), %xmm14
	movupd 0x30(%rcx), %xmm15
	addq %r12, %rcx
	# i0 = *(in0 + 0)
	# in0  ++
	movddup 0x00(%rbx), %xmm8
	movapd %xmm8, %xmm9
	movapd %xmm8, %xmm10
	movapd %xmm9, %xmm11
	addq $8, %rbx
	# out0_0 += in0_0_0 * *(in1_0);
	# ...
	# out0_7 += in0_0_0 * *(in1_7);
	mulpd %xmm12, %xmm8
	addpd %xmm8 , %xmm0
	mulpd %xmm13, %xmm9
	addpd %xmm9 , %xmm1
	mulpd %xmm14, %xmm10
	addpd %xmm10, %xmm2
	mulpd %xmm15, %xmm11
	addpd %xmm11, %xmm3
	# i0_ = *(in0 + 0)
	# in0_ ++
	movddup 0x00(%r14), %xmm8
	movapd %xmm8, %xmm9
	movapd %xmm8, %xmm10
	movapd %xmm9, %xmm11
	addq $8, %r14
	# out1_0 += in0_1_0 * *(in1_0);
	# ...
	# out1_7 += in0_1_0 * *(in1_7);
	mulpd %xmm12, %xmm8
	addpd %xmm8 , %xmm4
	mulpd %xmm13, %xmm9
	addpd %xmm9 , %xmm5
	mulpd %xmm14, %xmm10
	addpd %xmm10, %xmm6
	mulpd %xmm15, %xmm11
	addpd %xmm11, %xmm7

	subq $1, %r8      # } // for (j = K; j; j--) {
	jnz 2b

3:
	# *(out  + 0) = out0_0;
	# ...
	# *(out  + 7) = out0_7;
	# *(out_ + 0) = out1_0;
	# ...
	# *(out_ + 7) = out1_7;
	movupd %xmm0, 0x00(%rax)
	movupd %xmm1, 0x10(%rax)
	movupd %xmm2, 0x20(%rax)
	movupd %xmm3, 0x30(%rax)
	movupd %xmm4, 0x00(%r13)
	movupd %xmm5, 0x10(%r13)
	movupd %xmm6, 0x20(%r13)
	movupd %xmm7, 0x30(%r13)
	
	subq $1, %r9     # } // for (i = N; i; i--) {
	jnz 1b

4:
	movq RZP_h, %rcx # } // for (h = M; h; h--) {
	subq $1, %rcx 	
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
dot_product_double_MNK_2x1x8_sse4:
	movq %rsp, %rax
	push %rsp
	push %rbp
	push %rbx
	push %r12
	push %r13
	push %r14
	push %r15
	movq %rsp, %rbp
	mov 0x08(%rax), %r10

	# Out In0 In1  m   k  n  OutS
	# rdi rsi rdx  rcx r8 r9 r10 
	movq %rdi, RZP_Out    # Out
	movq %rsi, RZP_In0    # In0
	movq %rdx, RZP_In1    # In1

	testq %r10, %r10      # if (!OutS) {OutS = n;}
	cmove %r9, %r10
	shlq $3, %r10
	movq %r8, %r11        # In0S = k;
	shlq $3, %r11
	movq %r9, %r12        # In1S = n;
	shlq $3, %r12

	shrq $1, %rcx         # M = m >> 1
	movq %rcx, RZP_M
	movq %r8, RZP_K       # K = k;
	shrq $3, %r9          # N = n >> 3;
	movq %r9, RZP_N

	movq RZP_M, %rcx      # for (h = M; h; h--) {
	testq %rcx, %rcx       
	je 5f

0:
	movq %rcx, RZP_h            # h
	movq RZP_Out, %rax          # _out = Out;
	movq %rax, %rdi
	leaq 0(%rax, %r10, 2), %rax # Out += OutS;
	movq %rax, RZP_Out 
	movq RZP_In0, %rbx          # _in0 = In0;
	movq %rbx, %rsi
	leaq 0(%rbx, %r11, 2), %rbx # In0 += k
	movq %rbx, RZP_In0 
	movq RZP_In1, %rdx          # _in1 = In1;

	movq RZP_N, %r9             # for (i = N; i; i--) {
	testq %r9, %r9
	je 4f

1:
	movq %rdi, %rax             # out = _out;
	leaq 0(%rax, %r10), %r13    # out_ = out + OutS
	addq $64, %rdi              # _out += (U)8
	movq %rsi, %rbx             # in0 = _in0
	leaq 0(%rbx, %r11), %r14    # in0_ = in0 + k
	movq %rdx, %rcx             # in1 = _in1
	addq $64, %rdx              # _in1 += (U)8
	# out0_0 = *(out  + 0)
	# ...
	# out0_7 = *(out  + 7)
	# out1_0 = *(out_ + 0)
	# ...
	# out1_7 = *(out_ + 7)
	movupd 0x00(%rax), %xmm0
	movupd 0x10(%rax), %xmm1
	movupd 0x20(%rax), %xmm2
	movupd 0x30(%rax), %xmm3
	movupd 0x00(%r13), %xmm4
	movupd 0x10(%r13), %xmm5
	movupd 0x20(%r13), %xmm6
	movupd 0x30(%r13), %xmm7
	
	movq RZP_K, %r8  # for (j = K; j; j--) {
	testq %r8, %r8
	je 3f

2:
	# in1_0 = *(in1 + 0)
	# ...
	# in1_7 = *(in1 + 7)
	# in1 += In1S
	# PREFETCH_READ_3(in1+In1S*8)
	movupd 0x00(%rcx), %xmm12
	movupd 0x10(%rcx), %xmm13
	movupd 0x20(%rcx), %xmm14
	movupd 0x30(%rcx), %xmm15
	addq %r12, %rcx
	PREFETCHT0(0(%rcx, %r12, 8))
	# i0 = *(in0 + 0)
	# in0  ++
	# PREFETCH_READ_3(in0 + (U)8)
	movddup 0x00(%rbx), %xmm8
	movapd %xmm8, %xmm9
	movapd %xmm8, %xmm10
	movapd %xmm9, %xmm11
	addq $8, %rbx
	PREFETCHT0(0x40(%rbx))
	# out0_0 += in0_0_0 * *(in1_0);
	# ...
	# out0_7 += in0_0_0 * *(in1_7);
	mulpd %xmm12, %xmm8
	addpd %xmm8 , %xmm0
	mulpd %xmm13, %xmm9
	addpd %xmm9 , %xmm1
	mulpd %xmm14, %xmm10
	addpd %xmm10, %xmm2
	mulpd %xmm15, %xmm11
	addpd %xmm11, %xmm3
	# i0_ = *(in0 + 0)
	# in0_ ++
	# PREFETCH_READ_3(in0 + (U)8)
	movddup 0x00(%r14), %xmm8
	movapd %xmm8, %xmm9
	movapd %xmm8, %xmm10
	movapd %xmm9, %xmm11
	addq $8, %r14
	PREFETCHT0(0x40(%r14))
	# out1_0 += in0_1_0 * *(in1_0);
	# ...
	# out1_7 += in0_1_0 * *(in1_7);
	mulpd %xmm12, %xmm8
	addpd %xmm8 , %xmm4
	mulpd %xmm13, %xmm9
	addpd %xmm9 , %xmm5
	mulpd %xmm14, %xmm10
	addpd %xmm10, %xmm6
	mulpd %xmm15, %xmm11
	addpd %xmm11, %xmm7

	subq $1, %r8      # } // for (j = K; j; j--) {
	jnz 2b

3:
	# *(out  + 0) = out0_0;
	# ...
	# *(out  + 7) = out0_7;
	# *(out_ + 0) = out1_0;
	# ...
	# *(out_ + 7) = out1_7;
	movupd %xmm0, 0x00(%rax)
	movupd %xmm1, 0x10(%rax)
	movupd %xmm2, 0x20(%rax)
	movupd %xmm3, 0x30(%rax)
	movupd %xmm4, 0x00(%r13)
	movupd %xmm5, 0x10(%r13)
	movupd %xmm6, 0x20(%r13)
	movupd %xmm7, 0x30(%r13)
	
	subq $1, %r9     # } // for (i = N; i; i--) {
	jnz 1b

4:
	movq RZP_h, %rcx # } // for (h = M; h; h--) {
	subq $1, %rcx 	
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

