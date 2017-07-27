Completed:

Template code for following array products:

- ewise (element wise).
- outer
- inner
- rmdot (row vector x matrix): 1x1 to 8x32 - using vmdot
- cmdot (col vector x matrix): 1x1 to 8x32 - using vmdot
- mrdot (matrix x row vector): 1x1 to 8x32
- mcdot (matrix x col vector): 1x1 to 8x32

Template code for mmdot single- and multi-threaded products accommodating all 8 possible transposition permutations.

With mcdot and mrdot, template code has been improved to attempt unroll scheme to follow data alignment along cache line
boundaries (see TODO).

With rmdot and cmdot, the unrolled template functions have been fused so that both functional forms call vmdot which
accommodates for both stride specifications with neglible overhead. No such fusion is possible or desired for mcdot or
mrdot.

The makefiles have been modified to archive built objects from C++, C, and assembler sources.

The following scheme has been devised:

C++ template calls C code for a given data type if a specific archetecture has been detected by the C pre-processor.
The C will then perform the third loop from the inner-most calling assembler functions.
The assembler functions (e.g. see vmdot_product_1.S) will then perform the two inner-most loops.
