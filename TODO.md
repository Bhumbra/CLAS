Todo:

Accelerating execution performed by template code using x86_64 using SIMD assembler implementing SSE_X or AVX_X
extensions (latter will require a new computer!).

BUT

Before starting assembler code, the template code must be improved to reduce the L1 read/write frequency and cache-miss
rate without comprising multi-threaded optimisation. This necessitates slight changes in design:

- replication without creating a new array must precede a partial multiplication for entire affected output memory space.
- outer and inner unroll regimens must be sensitive to 64-byte boundaries in the input/output arrays.
- optimal choice between (matrix x many columns) and (many rows x matrix) is dependent on data dimensions and alignment.

So before writing assembler functions for all transposes, pre-replication of maxuend and cache alignment-sensitive
unrolling must be applied to:

rmdot
cmdot
mcdot
mrdot

The template code mcdot has been modified according the above changes but the gcc-compiled assembler is poorly optimised
with absolutely refusal to implement SIMD instructions (in contrast to e.g. rmdot_4). Also rmdot_8 gcc-compiled
assembler comprises single-data floating point instructions, so there will be no getting around having to write
SSE4/AVX2 assembler.

