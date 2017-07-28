
# General register plan

# RAX	out0 & in1_0
# RBX	out1 & in1_1
# RCX	out2 & in1_2
# RDX	out3 & in1_3
# RSI	in0 or In0
# RDI	in1
# R08	In1
# R09	In1s
# R10 	mod > i
# R11 	div > j
# R12	out4 & in1_4
# R13	out5 & in1_5
# R14	out6 & in1_6
# R15	out7 & in1_7

# SIMD register plan

# xmm0-4:	out_0-8
# xmm4-7:	in1_0-8
# xmm8-15:	in0_0-8

# Stack allocation of 256 bytes (no red zone)

# 0x08(%rsp)	Out
# 0x10(%rsp)	_In0 
# 0x18(%rsp)	_In1 
# 0x20(%rsp)	m
# 0x28(%rsp)	k
# 0x30(%rsp)	n
# 0x38(%rsp)	In0

# 0x40(%rsp)	mod
# 0x48(%rsp)	div
# 0x50(%rsp)	Outs0
# 0x58(%rsp)	Outs1 
# 0x60(%rsp)	In0S 
# 0x68(%rsp)	In0s 
# 0x70(%rsp)	In1S 
# 0x78(%rsp)	In1s 

# 0x80(%rsp)	Out0
# 0x88(%rsp)	Out1
# 0x90(%rsp)	Out2
# 0x98(%rsp)	Out3
# 0xA0(%rsp)	Out4
# 0xA8(%rsp)	Out5
# 0xB0(%rsp)	Out6
# 0xB8(%rsp)	Out7

# 0xC0(%rsp)	in1_0
# 0xC8(%rsp)	in1_1
# 0xD0(%rsp)	in1_2
# 0xD8(%rsp)	in1_3
# 0xE0(%rsp)	in1_4
# 0xE8(%rsp)	in1_5
# 0xF0(%rsp)	in1_6
# 0xF8(%rsp)	in1_7

