# CLAS
------
C++ Linear Algebra Subroutines - a biologically-inspired library of linear algebra operations optimised for machine
learning.

This library has only recently been started and following a successful proof-of-concept stage is under active
development. At this initial stage, documentation is scant. Although CLAS is mostly written in C++,
architecture-optimised routines are coded in C and assembler.

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
No formal installer has yet been written. However the combination of C++, C, and assembler means that CLAS should not be
compiled manually but through the makefile. Check (using `gcc -v') that your default g++ version is 5.2 or later.  If so
the CLAS library can be compiled using:

sh-4.3$ make 

Normally I code CLAS on a Gentoo GNU/Linux build, whose latest Portage snapshots are more than sufficiently up-to-date
to compile CLAS this way. A number of DEB-based and RPM-based GNU/Linux distributions however default to gcc 4.8.X but
accommodate gcc 5.x installations that can be invoked using /usr/bin/gcc-5. Without having to change any environment
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

If it is desired to compare CLAS with BLAS, it is necessary to include the inclusions and linkage options specific to
the tested BLAS implementation. A rough set of test examples of a few BLAS vs CLAS benchmarks (using OpenBLAS) is
included in tests/ and can be compiled thus:

sh-4.3$ make -f maketest

or

sh-4.3$ make -f maketest.gcc-5

outputting to 4 executables in bin/, namely bvc_ewise, bvc_outer, bvc_inner, and bvc_mmdot each of which can be run
specifying input arguments to test different array dimensions. An example script running all four executables is
provided in bin/blasvsclas.sh which can be run from console thus:

sh-4.3$ bin/blasvsclas.sh

It may be necessary to modify maketest or maketest.gcc5 to include the relevant paths to OpenBLAS for a given system.
For a fair test, please use the most recent stable release (OpenBLAS 0.2.19), because it appears OpenBLAS 0.2.20 kills
all other multithreaded libraries running from the same executable although hopefully the authors will correct this
soon. Please also note that I've so far only coded SSE4 assembler and therefore for now CLAS will inherently be
disadvantaged in comparison to BLAS implementations adopting AVX2 instructions for Intel architectures that support them
(e.g. Haswell, Broadwell, Skylake, Kaby Lake, etc...).

USAGE OF PRODUCT FUNCTION FOR MATRICES
--------------------------------------

Presently template code and SSE4 assembler has been written for all matrix-matrix multiplication transposition
permutations using the following function (with argument types and defaults shown):

	void clas::mmdot_product_double(double* Out, double* In0, double* In1, 
					uint64_t m, uint64_t k, uint64_t n,
					bool OutT = false, bool In0T = false, bool In1T = false, 
					bool ColM = false, double* In2 = 0, 
					uint64_t NT = 0, double FT = 1.);

... where the first 6 arguments are compulsory:

	Out: is the pointer for the product matrix (where Out = In0 x In1).

	In0: is the pointer for the multiplicand matrix.

	In1: is the pointer for the multiple matrix.

	m: is the number of rows in Out and In0.
	
	k: is the number of columns in In0 and rows in In1.

	n: is the number of columns in Out and In1.

... and the next 7 arguments are optional:

	OutT (default false): is a boolean flag that is true for a transposed product.

	In0T (default false): is a boolean flag that is true for a transposed multiplicand.
	
	In1T (default false): is a boolean flag that is true for a transposed multiple.

	ColM (default false): is a boolean flag that is true to denote column-major ordering for all 3 matrices.

	In2 (default 0): is a pointer for an m-length vector added to respective rows of Out (0 denotes no 
	addition, or if In2 = Out, this adds the matrix product to the existing data content of Out).

	NT (default 0): is the maximum number of threads used (0 denotes a maximum of all C++11-detectable 
	threads at runtime), multiplied by FT (see below).

	FT (default 1.): is the coefficient multiplied by NT to specify the maximum number of threads used. 
	For example, if NT = 0, and FT = 0.25, then this means CLAS will use a maximum of 25% of all threads 
	detectable at runtime.

USAGE OF PRODUCT FUNCTIONS FOR VECTOR ARRAYS
--------------------------------------------

Presently, template code and SSE4 assembler has been written for three types of multiplications using the following
three functions:

	void clas::ewise_product_double(double* Out, double* In0, double* In1, 
					uint64_t m, uint64_t k, uint64_t p, uint64_t q,
					bool In0Cm = false, bool In1Br = false, In2 = 0, 
					uint64_t NT = 0, double FT = 1.);

	void clas::inner_product_double(double* Out, double* In0, double* In1, 
					uint64_t m, uint64_t k, uint64_t p, uint64_t q,
					bool In0Cm = false, bool In1Br = false, In2 = 0, 
					uint64_t NT = 0, double FT = 1.);

	void clas::outer_product_double(double* Out, double* In0, double* In1, 
					uint64_t m, uint64_t k, uint64_t p, uint64_t q,
					bool In0Cm = false, bool In1Br = false, In2 = 0, 
					uint64_t NT = 0, double FT = 1.);

... where the first 7 arguments are compulsory:

	Out: is the pointer for a multidimensional product array of row-major vectors.

	In0: is the pointer for a two-dimensional multiplicand array.

	In1: is the pointer for a multidimensional multiple array of row-major vectors.

	m: is the number of vectors in In0 and (if In1Br is false) the second dimension of In1.
	
	k: is the vector length in In0 (and of In1 for ewise and inner).

	p: is the first (outer-most) dimension of In1.

	q: is the third (innermost for outer or second-from-innermost for ewise and inner) dimension of In2.

... and the next 5 arguments are optional:

	In0Cm (default false): is a boolean flag that is true to denote column-major ordering for In0.

	In1Br (default false): is a boolean flag that is true to denote a singleton second dimension in In1
	and broadcast the vectors of In1 to use the same elements within In1 to multiply with each of the m 
	vectors in In0. If In1Br is false, the functions adopt a second dimension for In1 of m rather than 1.

	In2 (default 0): is a pointer for an m-length vector added to the vectors of Out, where the _i_th 
	element of In2 corresponds to the _i_th vector in In0 (0 denotes no addition, or if In2 = Out, this 
	adds the product to the existing data content of Out).

	NT (default 0): is the maximum number of threads used (0 denotes a maximum of all C++11-detectable 
	threads at runtime), multiplied by FT (see below).

	FT (default 1.): is the coefficient multiplied by NT to specify the maximum number of threads used. 
	For example, if NT = 0, and FT = 0.25, then this means CLAS will use a maximum of 25% of all threads 
	detectable at runtime.

Despite similarities in their specifications, the three functions perform very different calculations:

- ewise_product_double calculates the entrywise (or elementwise) product of the vectors of the two dimensional array In0
  (mxk) with the vectors of the four-dimensional array In1 (pxmxqxk) and writes the result to the four-dimensional array
  Out (pxmxqxk). If however In1Br is true, then this denotes a singleton second dimension in In1 (px1xqxk) and
  broadcasts the same (1xqxk) data in In1 when multiplying with the m vectors of In0. Note that if In1Br is false, p =
  1, and q = 1, then In0 and In1 are effectively two-dimensional with identical sizes with each other (1xmx1xk) and with
  the size of Out.

- outer_product_double calculates the outer (or tensor) product of the vectors of the two dimensional array In0 (mxk)
  with the vectors of the three-dimensional array In1 (pxmxq) and writes the result to the four-dimensional array Out
  (pxmxkxq).  If however In1Br is true, then this denotes a singleton second dimension in In1 (px1xq) and broadcasts the
  same (1xq) data in In1 when multiplying with the m vectors of In0. Note that if In1Br is true _or_ false, m = 1, and p
  = 1, then In0 and In1 are of effectively single vectors of independent lengths (i.e. k and q) and Out is effectively
  two dimensional since its outer-most two dimensions are singleton (i.e. having dimensions 1x1xkxq).
	
- inner_product_double calculates the inner (or dot) product of the vectors of the two dimensional array In0 (mxk) with
  the vectors of the four-dimensional array In1 (pxmxqxk) and writes the result to the three-dimensional array Out
  (pxmxq).  If however In1Br is true, then this denotes a singleton second dimension in In1 (px1xqxk) and broadcasts the
  same (1xqxk) data in In1 when multiplying with the m vectors of In0. Note that if In1Br is false, p = 1, and q = 1,
  then In0 and In1 are of identical sizes with each other (1xmxkx1) and Out is effectively one dimensional since its
  outer two dimensions are singleton (i.e. having dimensions 1x1xm). 

Perhaps this will require more explanation with some useful examples beyond the few lines here within the README text.
More detailed documention is to follow in the future!

	
MOTIVATION 
-----------

The motivation behind CLAS is to execute floating point operations in a way that is optimised for machine learning using
biologically-inspired concepts. Generally, deep-learning libraries are dependent on calls to vendor-optimised BLAS
libraries to perform the heavy lifting for fast multiplication of weight matrices with data. However the BLAS
specification was originally devised in the 1970s for FORTRAN programmers to standardise low-level kernel operations
then Level 3 (matrix-matrix) BLAS operations were introduced in the 1980s well before the rise of deep-learning. 

While the venerable BLAS standard is still universally used, deep-learning is likely to benefit strongly from a more
tailored specification. For example, the double-precision matrix multiplication routine (dgemm) is disadvantaged by its
BLAS heritage, particularly in the context of deep learning, in the following ways:

- its specification, by necessity, in C and FORTRAN differ (the C version has an additional first parameter).

- its FORTRAN specification provides no intuitive way to transpose output matrices without swapping inputs.

- it includes largely redundant coefficient scalars (alpha and beta).

- it includes nowadays largely redundant leading dimension parameters (lda, ldb, ldc).

- it does not include intuitive default values.

- itself it provides no facility to specify the maximum number of threads used by specific calls at runtime.

- it provides no option to offset the output matrix by a vector containing bias values added to the matrix product.

CLAS is an experiment that aims to overcome these limitations. However rather than simply devising another reference
specification, CLAS is intended to implement design strategies inspired by biology to improve its performance
particularly for deep learning applications:

- distribute thread loads evenly so that the operation of each thread corresponds to a node or group of nodes with
  minimal write inter-dependence.

- recruit threads only as required for optimum performance up to a user-specifiable maximum that may be expressed an
  absolute number or fraction of total number threads available at runtime.

- minimal memory footprint inside and outside each thread (i.e. no 'malloc', 'new' etc... to allocate floating point
  arrays).

In practice, these motivations must dovetail with efficient cache usage but recent progress that has been extremely
promising as a result of combining three strategies:

- copies of read data restricted to sizes optimal for L1 and L2 caching within individual thread loads.
- architecture-dependent assembler coded for inner-most three loops with inner-most two using SIMD instructions.
- outer-most loop multithreaded in a way that guarantees each thread writes to mutually exclusive regions of memory.

At the moment, most of the functions that perform the simpler products (i.e. ewise, inner, and outer) simply borrow
code written for the matrix operations and or not yet optimised for vector operations. Despite this, they are already
very competitive in comparison to their CBLAS equivalents (i.e. cblas_dgemv and cblas_dger; there is no entrywise
product equivalent in CBLAS).

IMPROVEMENTS
------------
My day-job is as a biologist so CLAS writing is slow. Intended improvements for the near future are:

- write single- and multi-threaded stride code intended for very fast convolution operations.
- assembler-coded instructions for Intel architectures beyond SSE4 instructions such as the newer AVX2 extensions.
- create a proper installer.
- provide better documentation.


