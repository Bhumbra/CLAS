Completed:

Template code for following array products:

- ewise (element wise).
- outer
- inner
- rmdot (row vector x matrix): 1x1 to 8x32
- cmdot (col vector x matrix): 1x1 to 8x32
- mrdot (matrix x row vector): 1x1 to 8x32
- mcdot (matrix x col vector): 1x1 to 8x32

Template code for mmdot single- and multi-threaded products accommodating all 8 possible transposition permutations.

With mcdot and mrdot, template code has been improved to attempt unroll scheme to follow data alignment along cache line
boundaries (see TODO).

With rmdot and cmdot, the unrolled template functions have been fused so that both functional forms call vmdot which
accommodates for both stride specifications with neglible overhead. No such fusion is possible or desired for mcdot or
mrdot.

Complete template 8x32 coding for vmdot, mrdot, and mcdot. Accuracy of mrdot_8 and mcdot_8 must be tested.
