# ifndef common_sse4_s
# define common_sse4_s

// Prefetch macros

//# define PREFETCHT0(PREFETCH_ADDR) prefetcht0 PREFETCH_ADDR
# define PREFETCHT0(PREFETCH_ADDR)

// Red zone pointer definitions

# define RZP_h    -0x08(%rsp)
# define RZP_Out_ -0x10(%rsp)
# define RZP_In0_ -0x18(%rsp)
# define RZP_In1_ -0x20(%rsp)
# define RZP_m    -0x28(%rsp)
# define RZP_k    -0x30(%rsp)
# define RZP_n    -0x38(%rsp)
# define RZP_OutS -0x40(%rsp)
# define RZP_In0S -0x48(%rsp)
# define RZP_In1S -0x50(%rsp)
# define RZP_M    -0x58(%rsp)
# define RZP_K    -0x60(%rsp)
# define RZP_N    -0x68(%rsp)
# define RZP_Out  -0x70(%rsp)
# define RZP_In0  -0x78(%rsp)
# define RZP_In1  -0x80(%rsp)

// Black zone stack pointer definitions

# define RSP_h     0x08(%rsp)
# define RSP_Out   0x10(%rsp)
# define RSP_In0   0x18(%rsp)
# define RSP_In1   0x20(%rsp)
# define RSP_M     0x28(%rsp)
# define RSP_K     0x30(%rsp)
# define RSP_N     0x38(%rsp)

# define RSP_Out_  0x40(%rsp)
# define RSP_In0_  0x48(%rsp)
# define RSP_In1_  0x50(%rsp)
# define RSP_m     0x58(%rsp)
# define RSP_k     0x60(%rsp)
# define RSP_n     0x68(%rsp)

# define RSP_OutS  0x70(%rsp)
# define RSP_In0S  0x78(%rsp)
# define RSP_In1S  0x80(%rsp)
# define RSP_Outs  0x88(%rsp)
# define RSP_In0s  0x90(%rsp)
# define RSP_In1s  0x98(%rsp)

# define RSP_Out_0 0xA0(%rsp)
# define RSP_Out_1 0xA8(%rsp)
# define RSP_Out_2 0xB0(%rsp)
# define RSP_Out_3 0xB8(%rsp)

# define RSP_in0_0 0xC0(%rsp)
# define RSP_in0_1 0xC8(%rsp)
# define RSP_in0_2 0xD0(%rsp)
# define RSP_in0_3 0xD8(%rsp)

# define RSP_in1_0 0xE0(%rsp)
# define RSP_in1_1 0xE8(%rsp)
# define RSP_in1_2 0xF0(%rsp)
# define RSP_in1_3 0xF8(%rsp)

// %0x100(%rsp) -> %0x1F8(%rsp): in0_0_0 -> in0_3_3 

# endif

