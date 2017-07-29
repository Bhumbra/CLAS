# CLAS
------
C++ Linear Algebra Subroutines - a biologically-inspired library of linear algebra operations optimised for machine
learning.

This library has only recently been started and is at a proof-of-concept stage. Documentation is thus scant. Although
CLAS is mostly written in C++, architecture-optimised routines are coded in C and assembler.

REQUIREMENTS
------------
For the moment the minimum requirements is merely having a version of gcc that is version 5.2 or later. Double-precision
array multiplication is currently being written to be optimised for Intel x86_64 architectures with a CPU supporting
SSE4.1 instructions and multiple threads; in practice this means either an Intel Nehalem CPU or AMD Bulldozer or later
in each case (although I have not had a chance to test CLAS on any AMD machine). In principle the C++-11 standard
should be compatible with multiple threading for all CPU architectures that support it, but I do not know whether this is
true in practice.

INSTALLATION
------------
No formal installer has yet been written. However the complexities of combining C++, C, and assembler means that CLAS
should not be compiled manually but only through the makefile. Check (using `gcc -v') that your default g++ version is
5.2 or later. If so the CLAS library can be compiled using:

sh-4.3$ make 

Normally I code CLAS on a Gentoo GNU/Linux build, whose latest Portage snapshots are more than sufficiently up-to-date
to compile CLAS this way. A number of DEB-based and RPM-based GNU/Linux distributions however default to gcc 4.8.X but
accommodate gcc 5.x installations that can be evoked from /usr/bin/gcc-5. Without having to change any environment
variables or symlinks, a convenient way to compile CLAS such cases is using a different makefile call instead:

sh-4.3$ make -f makefile.gcc-5 

The library archive is outputted to path: lib/libclas.a which must be linked to use CLAS.

I'm not sure how easily CLAS can be installed by Microsoft Windows and Apple macOS users. I guess Microsoft Windows
users might be able install CLAS using the MSYS shell and MinGW environment. Apple users will probably have to use
Xcode. In either case, do use `gcc -v' to check the version of gcc is 5.2 or later.

I have not tested CLAS on non-Intel architectures and would be delighted to have the opportunity to do so.

LINKING
-------
Using CLAS requires including the CLAS header and linking with the library archive. The clas.h header is included in the
source header: # include <clas.h>

The source file must be linked to the libclas archive during compiling e.g.: 

sh-4.3$ g++ sourcefile.cc -o executable.run -L/CLAS_LIB_DIRECTORY/ -lclas

If it is desired to compare with BLAS, it is necessary to include the inclusions and linkage options specific to the
tested BLAS implementation. An example of a BLAS vs CLAS test (using PpenBLAS) is included in tests/blasvstest.cc and
can be compiled thus:

sh-4.3$ make -f maketest

or

sh-4.3$ make -f maketest.gcc-5

outputting to an executable bin/blasvsclas.run.

It may be necessary to modify maketest or maketest.gcc5 to include the relevant paths to OpenBLAS for a given system.
For a fair test, please use the most recent stable release (OpenBLAS 0.2.19) because it appears OpenBLAS 0.2.20 kills
all other multithreaded libraries.

USAGE
-----
Presently template code has been written for all matrix-matrix multiplication transposition permutations using the
following function (with argument types and defaults shown):

	void clas::mmdot_product_double(double* Out, double* In0, double* In1, uint64_t m, uint64_t k, uint64_t n,
					bool OutT = false, bool In0T = false, bool In1T = false, bool ColM = false, 
					double* In2 = 0, uint64_t NT = 0, 
					uint64_t U0 = 0, uint64_t U1 = 0, uint64_t UD= 0, uint64_t Arch = 0);

... where the first 6 arguments are compulsory:

	Out: is the pointer for the product matrix (where Out = In0 x In1).

	In0: is the pointer for the multiplicand matrix.

	In1: is the pointer for the multiple matrix.

	m: is the number of rows in Out and In0.
	
	k: is the number of columns in In0 and rows in In1.

	n: is the number of columns in Out and In1.

... and the next 6 arguments are optional:

	OutT (default false): is a boolean flag that is true for a transposed product.

	In0T (default false): is a boolean flag that is true for a transposed multiplicand.
	
	In1T (default false): is a boolean flag that is true for a transposed multiple.

	ColM (default false): is a boolean flag that is true to denote column-major ordering for all 3 matrices.

	In2 (default 0): is a pointer for an m-length vector added to respective rows of Out (0 denotes no 
	addition, or if In2 = Out, this adds the matrix product to the existing data content of Out).

	NT (default 0): is the maximum number of threads used (0 denotes a maximum of all C++11-detectable 
	threads).

... while the remaining 4 arguments are _not_ for general use and should be omitted since they are subject to change and
intended only for purely diagnostic purposes:

	U0 (default 0): is the unroll outer radix, which can be 1, 2, 4, or 8 (0 denotes cache-optimised dynamic 
	choice).

	U1 (default 0): is the unroll inner radix, which can be 1, 2, 4, 8, 16, or 32 (0 denotes automated 
	choice).

	UD (default 0): represents the unroll direction, which can be 2 (rows X matrix) or 3 (matrix X columns) 
	(0 denotes automated choice)

	Arch (default 0): represents which compiled architecture code to use, which can be 1 (C++) or 2 (SSE4) 
	(0 denotes automated choice)

MOTIVATION
-----------

The motivation behind CLAS is to execute floating point operations in a way that is optimised for machine learning using
biologically-inspired concepts. Generally, deep-learning libraries are dependent on calls to vendor-optimised BLAS
libraries to perform the heavy lifting for fast multiplication of weight matrices with data. However the BLAS
specification was originally devised in the 1970s for FORTRAN programmers to standardise low-level kernel operations
then Level 3 (matrix-matrix) BLAS operations were introduced in the 1980s well before the rise of deep-learning. While
the venerable BLAS standard is still universally used its double-precision matrix multiplication routine (dgemm) is
disadvantaged by its BLAS heritage, especially in the context of deep learning, in the following ways:

- its specification, by necessity, in C and FORTRAN differ (the C version has an additional first parameter).

- its FORTRAN specification provides no intuitive way to transpose output matrices without swapping inputs.

- it includes largely redundant coefficient scalars (alpha and beta).

- it includes nowadays largely redundant leading dimension parameters (lda, ldb, ldc).

- it does not include intuitive default values.

- itself it provides no facility to specify the maximum number of threads used by specific calls at runtime.

- it provides no option to offset the output matrix by a vector containing bias values added to the matrix product.

CLAS is an experiment that aims to overcome these limitations. However rather than simply devising another reference
specification, CLAS is intended to implement design strategies inspired by biology that should improve its performance
for deep learning applications:

- distribute thread loads evenly so each thread corresponds to a node or group of nodes with minimal write
  inter-dependence.

- minimal data copying but optimising read/write caching by using dynamic sizes for outer and inner loop-unrolls.

- minimal memory footprint inside and outside each thread (i.e. no 'malloc', 'new' etc... to allocate floating point
  arrays).

In practice, these motivations might conflict with the aim of extremely efficient L1 and L2 (and L3) caching performed
by the fastest BLAS implementations, but with the availability of many threads I suspect cache handling isn't everything
in deep learning and the best solution is likely to be somewhere in between.

IMPROVEMENTS
------------
My day-job is as a biologist so CLAS writing is slow. Intended improvements for the near future are:

- assembler-coded instructions for Intel architectures for double precision matrix-matrix multiplication for all 8 matrix transposition combinations.

- in addition to matrix multiplication (mmdot_product), code routines for simpler products i.e. ewise_product, inner_product, and outer_product.

- create a proper installer and provide better documentation.

