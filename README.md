# CLAS
------
C++ Linear Algebra Subroutines - a biologically-inspired library of linear algebra operations optimised for machine
learning.

This library has only recently been started and is at a proof-of-concept stage. Documentation is thus scant.

INSTALLATION
------------
No formal installer has yet been written. However the dependence of CLAS on C++11 standards means that CLAS should not
be compiled manually but only through the makefile. If your default g++ version is 5.x or later, the library can be
compiled using:

sh-4.3$ make 

Otherwise if compiling using g++-5, use:

sh-4.3$ make -f makefile.gcc5 

The library archive is outputted to path: lib/libclas.a

LINKING
-------
Using CLAS requires including the CLAS header and linking with the library archive. The clas.h header is included in the
source header:

# include <clas.h>

The source file must be linked to the libclas archive during compiling e.g.: 

sh-4.3$ g++ sourcefile.cc -o executable.run -L/CLAS_LIB_DIRECTORY/ -lclas

If it is desired to compare with BLAS, it is necessary to include the inclusions and linkage options specific to the
tested BLAS implementation. An example of a BLAS vs CLAS test (using openBLAS) is included in tests/blasvstest.cc and
can be compiled thus:

sh-4.3$ make -f maketest
or
sh-4.3$ make -f maketest.gcc5

outputting to an executable bin/blasvsclas.run.

It may be necessary to modify maketest or maketest.gcc5 to include the relevant paths to openBLAS for a given system.

USAGE
-----
Presently only untransposed row major matrix-matrix multiplication has been template-coded using the following function
(with argument types and defaults shown):

void clas::mmdot_product_double(double* Out, double* In0, double* In1, uint64_t m, uint64_t k, uint64_t n,
	bool OutT = false, bool In0T = false, bool In1T = false, bool ColM = false, 
	double* In2 = 0, uint64_t NT = 0, uint64_t U0 = 0, uint64_t U1 = 0);

where:
	Out: is the pointer for the product matrix (where Out = In0 x In1).
	In0: is the pointer for the multiplicand matrix.
	In1: is the pointer for the multiple matrix.
	m: is the number of rows in Out and In0.
	k: is the number of columns in In0 and rows in In1.
	n: is the number of columns in Out and In1.
	OutT (default false): is a boolean flag that is true for a transposed product.
	In0T (default false): is a boolean flag that is true for a transposed multiplicand.
	In1T (default false): is a boolean flag that is true for a transposed multiple.
	ColM (default false): is a boolean flag that is true to denote column-major ordering for all 3 matrices.
	In2 (default 0): is a pointer for an m-length vector added to respective rows of Out (0 denotes no addition).
	NT (default 0): is the maximum number of threads used (0 denotes a maximum of all C++11-detectable threads).
	U0 (default 0): is the unroll outer radix, which can be 1, 2, or 4 (0 denotes automated choice).
	U1 (default 0): is the unroll inner radix, which can be 1, 2, 4, 8, 16, or 32 (0 denotes automated choice).

The last two arguments are intended purely for diagnostic use and are subject to change.

