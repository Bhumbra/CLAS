Todo:

Accelerating execution performed by template code using x86_64 using SIMD assembler implementing SSE_X or AVX_X
extensions (latter will require a new computer!). Two important issues must be considered

1. Caching

The template code has been improved to reduce the L1 read/write frequency and cache-miss rate without comprising
multi-threaded optimisation. This has necessitated slight changes in design:

- replication without creating a new array must precede a partial multiplication for entire affected output memory space.
- outer and inner unroll regimens must be sensitive to 64-byte boundaries in the input/output arrays.
- optimal choice between (matrix x many columns) and (many rows x matrix) is dependent on data dimensions and alignment.
- as a first solution unrolls have been targetted first in attempt to improve data alignment along cache boundaries for
  rmdot, cmdot, mcdot, and mrdot.

2. SIMD

For vmdot_8xN, and all of mcdot and mrdot, gcc-compiled assembler is poorly optimised with absolutely refusal to
implement SIMD instructions (in contrast to e.g. vmdot_4). Txhere will be no getting around having to write SSE4/AVX2
assembler.

The assembler code for vmdot, mcdot, and mrdot must be coded to optimise caching and efficient register handling before
further unroll strategies have been devised. Interestingly assembly code for rmdot_double_1 is complete with a
performance similar to C++, showing gcc -O3 optimisation is very good for vectors even if not for matrices.

