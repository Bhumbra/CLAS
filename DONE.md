Completed: template code for following array products:  ewise (element wise), outer, and inner.

Different implementations of matrix-matrix multiplication (mmdot) have been tested for all 8 possible transposition
permutations, but will be improved by cache manager classes which are currently being coded. Unfortunately gcc still
cannot SIMD-compile code from these manager classes so a combination of inline assembler (for copying) and native
assembler need to be coded.
