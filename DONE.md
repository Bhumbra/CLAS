Completed:

Template code for following array products:

- ewise (element wise).
- outer
- inner
- rmdot (row vector x matrix): 1x1 to 4x32
- cmdot (col vector x matrix): 1x1 to 4x32
- mrdot (matrix x row vector): 1x1 to 4x32
- mcdot (matrix x col vector): 1x1 to 8x32

Template code for mmdot single- and multi-threaded products accommodating all 8 possible transposition permutations.

With mcdot, template code has been improved to attempt unroll scheme to follow data alignment along cache line
boundaries (see TODO).
