# 1 "src/vmdot_product_double_1.S"
# 1 "/home/admin/code/cxx/clas//"
# 1 "<built-in>"
# 1 "<command-line>"
# 1 "/usr/include/stdc-predef.h" 1 3 4
# 1 "<command-line>" 2
# 1 "src/vmdot_product_double_1.S"

# General register plan

# RAX out0 & in1_0
# RBX out1 & in1_1
# RCX out2 & in1_2
# RDX out3 & in1_3
# RSI in0 or In0
# RDI in1
# R08 In1
# R09 In1s
# R10 mod > i
# R11 div > j
# R12 out4 & in1_4
# R13 out5 & in1_5
# R14 out6 & in1_6
# R15 out7 & in1_7

# SIMD register plan

# xmm0-4: out_0-8
# xmm4-7: in1_0-8
# xmm8-15: in0_0-8

# Stack allocation of 256 bytes (no red zone)

# 0x08(%rsp) Out
# 0x10(%rsp) _In0
# 0x18(%rsp) _In1
# 0x20(%rsp) m
# 0x28(%rsp) k
# 0x30(%rsp) n
# 0x38(%rsp) In0

# 0x40(%rsp) mod
# 0x48(%rsp) div
# 0x50(%rsp) Outs0
# 0x58(%rsp) Outs1
# 0x60(%rsp) In0S
# 0x68(%rsp) In0s
# 0x70(%rsp) In1S
# 0x78(%rsp) In1s

# 0x80(%rsp) Out0
# 0x88(%rsp) Out1
# 0x90(%rsp) Out2
# 0x98(%rsp) Out3
# 0xA0(%rsp) Out4
# 0xA8(%rsp) Out5
# 0xB0(%rsp) Out6
# 0xB8(%rsp) Out7

# 0xC0(%rsp) in1_0
# 0xC8(%rsp) in1_1
# 0xD0(%rsp) in1_2
# 0xD8(%rsp) in1_3
# 0xE0(%rsp) in1_4
# 0xE8(%rsp) in1_5
# 0xF0(%rsp) in1_6
# 0xF8(%rsp) in1_7

 .globl vmdot_product_double_1x1
 .globl vmdot_product_double_1x2
 .globl vmdot_product_double_1x4
 .globl vmdot_product_double_1x8
 .globl vmdot_product_double_1x16
 .globl vmdot_product_double_1x32

 .text

vmdot_product_double_1x1:
 mov 0x08(%rsp), %r10
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

 # Out _In0 _In1 k n In0s In1s
 # rdi rsi rdx rcx r8 r9 r10

 movq %rdi, 0x08(%rsp) # Out
 movq %rsi, 0x10(%rsp) # _In0
 movq %rdx, 0x18(%rsp) # _In1
 movq %rcx, 0x28(%rsp) # k
 movq %r8 , 0x30(%rsp) # n
 shlq $3, %r9 # In0s
 movq %r9 , 0x68(%rsp)
 movq %r10 , 0x78(%rsp) # In1s
 movq %r10, %r9
 shlq $3, %r9

 movq 0x10(%rsp), %rsi # in0 = In0
 movq 0x18(%rsp), %r8 # In1 = _In1

 movq 0x28(%rsp), %r10 # for (i = k; i; i--)
 test %r10, %r10
 je 3f
0:

 movq 0x08(%rsp), %rax # out = Out
 movsd 0(%rsi), %xmm8 # in0_0 = *In0
 addq 0x68(%rsp), %rsi # in0 += In0s
 movq %r8, %rdi # in1 = In1
 addq %r9, %r8 # In1 += In1s

 movq 0x30(%rsp), %r11 # for (j = n; j; j--)
 test %r11, %r11
 je 2f
1:

 # *(out + 0) += in0_0 * *(in1 + 0);
 movsd 0(%rax), %xmm0

 movsd 0(%rdi), %xmm4
 mulsd %xmm8, %xmm4
 addsd %xmm4, %xmm0

 movsd %xmm0, 0(%rax)

 addq $8, %rax # out ++
 addq $8, %rdi # in1 ++

 subq $1, %r11 # }
 jnz 1b
2:
 subq $1, %r10 # }
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


vmdot_product_double_1x2:
 mov 0x08(%rsp), %r10
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

 # Out _In0 _In1 k n In0s In1s
 # rdi rsi rdx rcx r8 r9 r10

 movq %rdi, 0x08(%rsp) # Out
 movq %rsi, 0x10(%rsp) # In0
 movq %rdx, 0x18(%rsp) # _In1
 movq %rcx, 0x28(%rsp) # k
 movq %r8 , 0x30(%rsp) # n
 shlq $3, %r9 # In0s
 movq %r9 , 0x68(%rsp)
 movq %r10 , 0x78(%rsp) # In1s
 movq %r10, %r9
 shlq $3, %r9

 movq 0x30(%rsp), %r10 # n
 movq %r10, %r11 # n
 andq $1, %r10 # mod = n & 1
 shrq $1, %r11 # div = n >> 1
 movq %r10, 0x40(%rsp) # mod
 movq %r11, 0x48(%rsp) # div

 movq 0x10(%rsp), %rsi # in0 = In0
 movq 0x18(%rsp), %r8 # In1 = _In1

 movq 0x28(%rsp), %r10 # for (i = k; i; i--)
 test %r10, %r10
 je 3f
 .p2align 5,,16
 .p2align 4
0:

 movq 0x08(%rsp), %rax # out = Out
 movsd 0(%rsi), %xmm8 # in0_0 = *in0
 unpcklpd %xmm8, %xmm8
 addq 0x68(%rsp), %rsi # in0 += In0s
 movq %r8, %rdi # in1 = In1
 addq %r9, %r8 # In1 += In1s

 movq 0x48(%rsp), %r11 # for (j = div; j; j--)
 test %r11, %r11
 je 2f
 .p2align 6
1:
 # *(out + 0) += in0_0 * *(in1 + 0);
 # *(out + 1) += in0_0 * *(in1 + 1);
 movupd 0(%rax), %xmm0

 movupd 0(%rdi), %xmm4
 mulpd %xmm8, %xmm4
 addpd %xmm4, %xmm0

 movupd %xmm0, 0(%rax)

 addq $16, %rax # out += 2
 addq $16, %rdi # in1 += 2

 subq $1, %r11 # }
 jnz 1b
2:
 subq $1, %r10 # }
 jnz 0b
3:
 movq 0x40(%rsp), %r8 # mod
 test %r8, %r8 # if (mod)
 je 4f

 movq 0x30(%rsp), %rbx # n
 subq %r8, %rbx # div = n - mod
 shlq $3, %rbx

 # Out _In0 _In1 k n In0s In1s
 # rdi rsi rdx rcx r8 r9 r10

 #vmdot_product_1x1(Out + div, _In0, _In1 + div, k, mod, In0s, In1s)
 movq 0x08(%rsp), %rdi
 addq %rbx, %rdi
 movq 0x10(%rsp), %rsi
 movq 0x18(%rsp), %rdx
 addq %rbx, %rdx
 movq 0x28(%rsp), %rcx
 movq 0x68(%rsp), %r9
 shrq $3, %r9
 movq 0x78(%rsp), %r10
 movq %r10, 0x08(%rsp)
 addq $8, %rsp
 call vmdot_product_double_1x1

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


vmdot_product_double_1x4:
 mov 0x08(%rsp), %r10
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

 # Out _In0 _In1 k n In0s In1s
 # rdi rsi rdx rcx r8 r9 r10

 movq %rdi, 0x08(%rsp) # Out
 movq %rsi, 0x10(%rsp) # In0
 movq %rdx, 0x18(%rsp) # _In1
 movq %rcx, 0x28(%rsp) # k
 movq %r8 , 0x30(%rsp) # n
 shlq $3, %r9 # In0s
 movq %r9 , 0x68(%rsp)
 movq %r10 , 0x78(%rsp) # In1s
 movq %r10, %r9
 shlq $3, %r9

 movq 0x30(%rsp), %r10 # n
 movq %r10, %r11 # n
 andq $3, %r10 # mod = n & 3
 shrq $2, %r11 # div = n >> 2
 movq %r10, 0x40(%rsp) # mod
 movq %r11, 0x48(%rsp) # div

 movq 0x10(%rsp), %rsi # in0 = In0
 movq 0x18(%rsp), %r8 # In1 = _In1

 movq 0x28(%rsp), %r10 # for (i = k; i; i--)
 test %r10, %r10
 je 3f
 .p2align 5,,16
 .p2align 4
0:
 movq 0x08(%rsp), %rax # out = Out
 movsd 0(%rsi), %xmm8 # in0_0 = *in0
 unpcklpd %xmm8, %xmm8
 addq 0x68(%rsp), %rsi # in0 += In0s
 movq %r8, %rdi # in1 = In1
 addq %r9, %r8 # In1 += In1s

 movq 0x48(%rsp), %r11 # for (j = div; j; j--)
 test %r11, %r11
 je 2f
 .p2align 6
1:

 # *(out + 0) += in0_0 * *(in1 + 0);
 # *(out + 1) += in0_0 * *(in1 + 1);
 # *(out + 2) += in0_0 * *(in1 + 2);
 # *(out + 3) += in0_0 * *(in1 + 3);
 movupd 0 (%rax), %xmm0
 movupd 16(%rax), %xmm1

 movupd 0 (%rdi), %xmm4
 mulpd %xmm8, %xmm4
 addpd %xmm4, %xmm0
 movupd 16(%rdi), %xmm5
 mulpd %xmm8, %xmm5
 addpd %xmm5, %xmm1

 movups %xmm0, 0 (%rax)
 movups %xmm1, 16(%rax)

 addq $32, %rax # out += 4
 addq $32, %rdi # in1 += 4

 subq $1, %r11 # }
 jnz 1b
2:
 subq $1, %r10 # }
 jnz 0b
3:
 movq 0x40(%rsp), %r8 # mod
 test %r8, %r8 # if (mod)
 je 4f

 movq 0x30(%rsp), %rbx # n
 subq %r8, %rbx # div = n - mod
 shlq $3, %rbx

 # Out _In0 _In1 k n In0s In1s
 # rdi rsi rdx rcx r8 r9 r10

 #vmdot_product_1x2(Out + div, _In0, _In1 + div, k, mod, In0s, In1s)
 movq 0x08(%rsp), %rdi
 addq %rbx, %rdi
 movq 0x10(%rsp), %rsi
 movq 0x18(%rsp), %rdx
 addq %rbx, %rdx
 movq 0x28(%rsp), %rcx
 movq 0x68(%rsp), %r9
 shrq $3, %r9
 movq 0x78(%rsp), %r10
 movq %r10, 0x08(%rsp)
 addq $8, %rsp
 call vmdot_product_double_1x2

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


vmdot_product_double_1x8:
 mov 0x08(%rsp), %r10
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

 # Out _In0 _In1 k n In0s In1s
 # rdi rsi rdx rcx r8 r9 r10

 movq %rdi, 0x08(%rsp) # Out
 movq %rsi, 0x10(%rsp) # In0
 movq %rdx, 0x18(%rsp) # _In1
 movq %rcx, 0x28(%rsp) # k
 movq %r8 , 0x30(%rsp) # n
 shlq $3, %r9 # In0s
 movq %r9 , 0x68(%rsp)
 movq %r10 , 0x78(%rsp) # In1s
 movq %r10, %r9
 shlq $3, %r9

 movq 0x30(%rsp), %r10 # n
 movq %r10, %r11 # n
 andq $7, %r10 # mod = n & 7
 shrq $3, %r11 # div = n >> 3
 movq %r10, 0x40(%rsp) # mod
 movq %r11, 0x48(%rsp) # div

 movq 0x10(%rsp), %rsi # in0 = In0
 movq 0x18(%rsp), %r8 # In1 = _In1

 movq 0x28(%rsp), %r10 # for (i = k; i; i--)
 test %r10, %r10
 je 3f
 .p2align 5,,16
 .p2align 4
0:
 movq 0x08(%rsp), %rax # out = Out
 movsd 0(%rsi), %xmm8 # in0_0 = *in0
 unpcklpd %xmm8, %xmm8
 addq 0x68(%rsp), %rsi # in0 += In0s
 movq %r8, %rdi # in1 = In1
 addq %r9, %r8 # In1 += In1s

 movq 0x48(%rsp), %r11 # for (j = div; j; j--)
 test %r11, %r11
 je 2f
 .p2align 6
1:

 # *(out + 0) += in0_0 * *(in1 + 0);
 # *(out + 1) += in0_0 * *(in1 + 1);
 # *(out + 2) += in0_0 * *(in1 + 2);
 # *(out + 3) += in0_0 * *(in1 + 3);
 # *(out + 4) += in0_0 * *(in1 + 4);
 # *(out + 5) += in0_0 * *(in1 + 5);
 # *(out + 6) += in0_0 * *(in1 + 6);
 # *(out + 7) += in0_0 * *(in1 + 7);
 movupd 0 (%rax), %xmm0
 movupd 16(%rax), %xmm1
 movupd 32(%rax), %xmm2
 movupd 48(%rax), %xmm3

 movupd 0 (%rdi), %xmm4
 mulpd %xmm8, %xmm4
 addpd %xmm4, %xmm0
 movupd 16(%rdi), %xmm5
 mulpd %xmm8, %xmm5
 addpd %xmm5, %xmm1
 movupd 32(%rdi), %xmm6
 mulpd %xmm8, %xmm6
 addpd %xmm6, %xmm2
 movupd 48(%rdi), %xmm7
 mulpd %xmm8, %xmm7
 addpd %xmm7, %xmm3

 movups %xmm0, 0 (%rax)
 movups %xmm1, 16(%rax)
 movups %xmm2, 32(%rax)
 movups %xmm3, 48(%rax)

 addq $64, %rax # out += 8
 addq $64, %rdi # in1 += 8

 subq $1, %r11 # }
 jnz 1b
2:
 subq $1, %r10 # }
 jnz 0b
3:
 movq 0x40(%rsp), %r8 # mod
 test %r8, %r8 # if (mod)
 je 4f

 movq 0x30(%rsp), %rbx # n
 subq %r8, %rbx # div = n - mod
 shlq $3, %rbx

 # Out _In0 _In1 k n In0s In1s
 # rdi rsi rdx rcx r8 r9 r10

 #vmdot_product_1x4(Out + div, _In0, _In1 + div, k, mod, In0s, In1s)
 movq 0x08(%rsp), %rdi
 addq %rbx, %rdi
 movq 0x10(%rsp), %rsi
 movq 0x18(%rsp), %rdx
 addq %rbx, %rdx
 movq 0x28(%rsp), %rcx
 movq 0x68(%rsp), %r9
 shrq $3, %r9
 movq 0x78(%rsp), %r10
 movq %r10, 0x08(%rsp)
 addq $8, %rsp
 call vmdot_product_double_1x4

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


vmdot_product_double_1x16:
 mov 0x08(%rsp), %r10
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

 # Out _In0 _In1 k n In0s In1s
 # rdi rsi rdx rcx r8 r9 r10

 movq %rdi, 0x08(%rsp) # Out
 movq %rsi, 0x10(%rsp) # In0
 movq %rdx, 0x18(%rsp) # _In1
 movq %rcx, 0x28(%rsp) # k
 movq %r8 , 0x30(%rsp) # n
 shlq $3, %r9 # In0s
 movq %r9 , 0x68(%rsp)
 movq %r10 , 0x78(%rsp) # In1s
 movq %r10, %r9
 shlq $3, %r9

 movq 0x30(%rsp), %r10 # n
 movq %r10, %r11 # n
 andq $15, %r10 # mod = n & 15
 shrq $4, %r11 # div = n >> 4
 movq %r10, 0x40(%rsp) # mod
 movq %r11, 0x48(%rsp) # div

 movq 0x10(%rsp), %rsi # in0 = In0
 movq 0x18(%rsp), %r8 # In1 = _In1

 movq 0x28(%rsp), %r10 # for (i = k; i; i--)
 test %r10, %r10
 je 3f
 .p2align 5,,16
 .p2align 4
0:
 movq 0x08(%rsp), %rax # out = Out
 movsd 0(%rsi), %xmm8 # in0_0 = *in0
 unpcklpd %xmm8, %xmm8
 addq 0x68(%rsp), %rsi # in0 += In0s
 movq %r8, %rdi # in1 = In1
 addq %r9, %r8 # In1 += In1s

 movq 0x48(%rsp), %r11 # for (j = div; j; j--)
 test %r11, %r11
 je 2f
 .p2align 6
1:

 # *(out + 0) += in0_0 * *(in1 + 0);
 # *(out + 1) += in0_0 * *(in1 + 1);
 # *(out + 2) += in0_0 * *(in1 + 2);
 # *(out + 3) += in0_0 * *(in1 + 3);
 # *(out + 4) += in0_0 * *(in1 + 4);
 # *(out + 5) += in0_0 * *(in1 + 5);
 # *(out + 6) += in0_0 * *(in1 + 6);
 # *(out + 7) += in0_0 * *(in1 + 7);
 movupd 0 (%rax), %xmm0
 movupd 16(%rax), %xmm1
 movupd 32(%rax), %xmm2
 movupd 48(%rax), %xmm3

 movupd 0 (%rdi), %xmm4
 mulpd %xmm8, %xmm4
 addpd %xmm4, %xmm0
 movupd 16(%rdi), %xmm5
 mulpd %xmm8, %xmm5
 addpd %xmm5, %xmm1
 movupd 32(%rdi), %xmm6
 mulpd %xmm8, %xmm6
 addpd %xmm6, %xmm2
 movupd 48(%rdi), %xmm7
 mulpd %xmm8, %xmm7
 addpd %xmm7, %xmm3

 movups %xmm0, 0 (%rax)
 movups %xmm1, 16(%rax)
 movups %xmm2, 32(%rax)
 movups %xmm3, 48(%rax)

 addq $64, %rax # out += 8
 addq $64, %rdi # in1 += 8

 # *(out + 0) += in0_0 * *(in1 + 0);
 # *(out + 1) += in0_0 * *(in1 + 1);
 # *(out + 2) += in0_0 * *(in1 + 2);
 # *(out + 3) += in0_0 * *(in1 + 3);
 # *(out + 4) += in0_0 * *(in1 + 4);
 # *(out + 5) += in0_0 * *(in1 + 5);
 # *(out + 6) += in0_0 * *(in1 + 6);
 # *(out + 7) += in0_0 * *(in1 + 7);
 movupd 0 (%rax), %xmm0
 movupd 16(%rax), %xmm1
 movupd 32(%rax), %xmm2
 movupd 48(%rax), %xmm3

 movupd 0 (%rdi), %xmm4
 mulpd %xmm8, %xmm4
 addpd %xmm4, %xmm0
 movupd 16(%rdi), %xmm5
 mulpd %xmm8, %xmm5
 addpd %xmm5, %xmm1
 movupd 32(%rdi), %xmm6
 mulpd %xmm8, %xmm6
 addpd %xmm6, %xmm2
 movupd 48(%rdi), %xmm7
 mulpd %xmm8, %xmm7
 addpd %xmm7, %xmm3

 movups %xmm0, 0 (%rax)
 movups %xmm1, 16(%rax)
 movups %xmm2, 32(%rax)
 movups %xmm3, 48(%rax)

 addq $64, %rax # out += 8
 addq $64, %rdi # in1 += 8

 subq $1, %r11 # }
 jnz 1b
2:
 subq $1, %r10 # }
 jnz 0b
3:
 movq 0x40(%rsp), %r8 # mod
 test %r8, %r8 # if (mod)
 je 4f

 movq 0x30(%rsp), %rbx # n
 subq %r8, %rbx # div = n - mod
 shlq $3, %rbx

 # Out _In0 _In1 k n In0s In1s
 # rdi rsi rdx rcx r8 r9 r10

 #vmdot_product_1x8(Out + div, _In0, _In1 + div, k, mod, In0s, In1s)
 movq 0x08(%rsp), %rdi
 addq %rbx, %rdi
 movq 0x10(%rsp), %rsi
 movq 0x18(%rsp), %rdx
 addq %rbx, %rdx
 movq 0x28(%rsp), %rcx
 movq 0x68(%rsp), %r9
 shrq $3, %r9
 movq 0x78(%rsp), %r10
 movq %r10, 0x08(%rsp)
 addq $8, %rsp
 call vmdot_product_double_1x8

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


vmdot_product_double_1x32:
 mov 0x08(%rsp), %r10
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

 # Out _In0 _In1 k n In0s In1s
 # rdi rsi rdx rcx r8 r9 r10

 movq %rdi, 0x08(%rsp) # Out
 movq %rsi, 0x10(%rsp) # In0
 movq %rdx, 0x18(%rsp) # _In1
 movq %rcx, 0x28(%rsp) # k
 movq %r8 , 0x30(%rsp) # n
 shlq $3, %r9 # In0s
 movq %r9 , 0x68(%rsp)
 movq %r10 , 0x78(%rsp) # In1s
 movq %r10, %r9
 shlq $3, %r9

 movq 0x30(%rsp), %r10 # n
 movq %r10, %r11 # n
 andq $31, %r10 # mod = n & 31
 shrq $5, %r11 # div = n >> 5
 movq %r10, 0x40(%rsp) # mod
 movq %r11, 0x48(%rsp) # div

 movq 0x10(%rsp), %rsi # in0 = In0
 movq 0x18(%rsp), %r8 # In1 = _In1

 movq 0x28(%rsp), %r10 # for (i = k; i; i--)
 test %r10, %r10
 je 3f
 .p2align 5,,16
 .p2align 4
0:
 movq 0x08(%rsp), %rax # out = Out
 movsd 0(%rsi), %xmm8 # in0_0 = *in0
 unpcklpd %xmm8, %xmm8
 addq 0x68(%rsp), %rsi # in0 += In0s
 movq %r8, %rdi # in1 = In1
 addq %r9, %r8 # In1 += In1s

 movq 0x48(%rsp), %r11 # for (j = div; j; j--)
 test %r11, %r11
 je 2f
 .p2align 6
1:

 # *(out + 0) += in0_0 * *(in1 + 0);
 # *(out + 1) += in0_0 * *(in1 + 1);
 # *(out + 2) += in0_0 * *(in1 + 2);
 # *(out + 3) += in0_0 * *(in1 + 3);
 # *(out + 4) += in0_0 * *(in1 + 4);
 # *(out + 5) += in0_0 * *(in1 + 5);
 # *(out + 6) += in0_0 * *(in1 + 6);
 # *(out + 7) += in0_0 * *(in1 + 7);
 movupd 0 (%rax), %xmm0
 movupd 16(%rax), %xmm1
 movupd 32(%rax), %xmm2
 movupd 48(%rax), %xmm3

 movupd 0 (%rdi), %xmm4
 mulpd %xmm8, %xmm4
 addpd %xmm4, %xmm0
 movupd 16(%rdi), %xmm5
 mulpd %xmm8, %xmm5
 addpd %xmm5, %xmm1
 movupd 32(%rdi), %xmm6
 mulpd %xmm8, %xmm6
 addpd %xmm6, %xmm2
 movupd 48(%rdi), %xmm7
 mulpd %xmm8, %xmm7
 addpd %xmm7, %xmm3

 movups %xmm0, 0 (%rax)
 movups %xmm1, 16(%rax)
 movups %xmm2, 32(%rax)
 movups %xmm3, 48(%rax)

 addq $64, %rax # out += 8
 addq $64, %rdi # in1 += 8

 # *(out + 0) += in0_0 * *(in1 + 0);
 # *(out + 1) += in0_0 * *(in1 + 1);
 # *(out + 2) += in0_0 * *(in1 + 2);
 # *(out + 3) += in0_0 * *(in1 + 3);
 # *(out + 4) += in0_0 * *(in1 + 4);
 # *(out + 5) += in0_0 * *(in1 + 5);
 # *(out + 6) += in0_0 * *(in1 + 6);
 # *(out + 7) += in0_0 * *(in1 + 7);
 movupd 0 (%rax), %xmm0
 movupd 16(%rax), %xmm1
 movupd 32(%rax), %xmm2
 movupd 48(%rax), %xmm3

 movupd 0 (%rdi), %xmm4
 mulpd %xmm8, %xmm4
 addpd %xmm4, %xmm0
 movupd 16(%rdi), %xmm5
 mulpd %xmm8, %xmm5
 addpd %xmm5, %xmm1
 movupd 32(%rdi), %xmm6
 mulpd %xmm8, %xmm6
 addpd %xmm6, %xmm2
 movupd 48(%rdi), %xmm7
 mulpd %xmm8, %xmm7
 addpd %xmm7, %xmm3

 movups %xmm0, 0 (%rax)
 movups %xmm1, 16(%rax)
 movups %xmm2, 32(%rax)
 movups %xmm3, 48(%rax)

 addq $64, %rax # out += 8
 addq $64, %rdi # in1 += 8

 # *(out + 0) += in0_0 * *(in1 + 0);
 # *(out + 1) += in0_0 * *(in1 + 1);
 # *(out + 2) += in0_0 * *(in1 + 2);
 # *(out + 3) += in0_0 * *(in1 + 3);
 # *(out + 4) += in0_0 * *(in1 + 4);
 # *(out + 5) += in0_0 * *(in1 + 5);
 # *(out + 6) += in0_0 * *(in1 + 6);
 # *(out + 7) += in0_0 * *(in1 + 7);
 movupd 0 (%rax), %xmm0
 movupd 16(%rax), %xmm1
 movupd 32(%rax), %xmm2
 movupd 48(%rax), %xmm3

 movupd 0 (%rdi), %xmm4
 mulpd %xmm8, %xmm4
 addpd %xmm4, %xmm0
 movupd 16(%rdi), %xmm5
 mulpd %xmm8, %xmm5
 addpd %xmm5, %xmm1
 movupd 32(%rdi), %xmm6
 mulpd %xmm8, %xmm6
 addpd %xmm6, %xmm2
 movupd 48(%rdi), %xmm7
 mulpd %xmm8, %xmm7
 addpd %xmm7, %xmm3

 movups %xmm0, 0 (%rax)
 movups %xmm1, 16(%rax)
 movups %xmm2, 32(%rax)
 movups %xmm3, 48(%rax)

 addq $64, %rax # out += 8
 addq $64, %rdi # in1 += 8

 # *(out + 0) += in0_0 * *(in1 + 0);
 # *(out + 1) += in0_0 * *(in1 + 1);
 # *(out + 2) += in0_0 * *(in1 + 2);
 # *(out + 3) += in0_0 * *(in1 + 3);
 # *(out + 4) += in0_0 * *(in1 + 4);
 # *(out + 5) += in0_0 * *(in1 + 5);
 # *(out + 6) += in0_0 * *(in1 + 6);
 # *(out + 7) += in0_0 * *(in1 + 7);
 movupd 0 (%rax), %xmm0
 movupd 16(%rax), %xmm1
 movupd 32(%rax), %xmm2
 movupd 48(%rax), %xmm3

 movupd 0 (%rdi), %xmm4
 mulpd %xmm8, %xmm4
 addpd %xmm4, %xmm0
 movupd 16(%rdi), %xmm5
 mulpd %xmm8, %xmm5
 addpd %xmm5, %xmm1
 movupd 32(%rdi), %xmm6
 mulpd %xmm8, %xmm6
 addpd %xmm6, %xmm2
 movupd 48(%rdi), %xmm7
 mulpd %xmm8, %xmm7
 addpd %xmm7, %xmm3

 movups %xmm0, 0 (%rax)
 movups %xmm1, 16(%rax)
 movups %xmm2, 32(%rax)
 movups %xmm3, 48(%rax)

 addq $64, %rax # out += 8
 addq $64, %rdi # in1 += 8

 subq $1, %r11 # }
 jnz 1b
2:
 subq $1, %r10 # }
 jnz 0b
3:
 movq 0x40(%rsp), %r8 # mod
 test %r8, %r8 # if (mod)
 je 4f

 movq 0x30(%rsp), %rbx # n
 subq %r8, %rbx # div = n - mod
 shlq $3, %rbx

 # Out _In0 _In1 k n In0s In1s
 # rdi rsi rdx rcx r8 r9 r10

 #vmdot_product_1x16(Out + div, _In0, _In1 + div, k, mod, In0s, In1s)
 movq 0x08(%rsp), %rdi
 addq %rbx, %rdi
 movq 0x10(%rsp), %rsi
 movq 0x18(%rsp), %rdx
 addq %rbx, %rdx
 movq 0x28(%rsp), %rcx
 movq 0x68(%rsp), %r9
 shrq $3, %r9
 movq 0x78(%rsp), %r10
 movq %r10, 0x08(%rsp)
 addq $8, %rsp
 call vmdot_product_double_1x16

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
