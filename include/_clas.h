# ifndef _clas_h
# define _clas_h
//------------------------------------------------------------------------------
// Diagnostic C++ header to compile architecture-blind template code directly.
// Cannot be mixed with clas.h, and does not use C-code or assembler.

//------------------------------------------------------------------------------
# define CLAS_HEADERS_ONLY 1

//------------------------------------------------------------------------------
namespace clas {
# include "clas.txx"
}

//------------------------------------------------------------------------------
namespace clas {
# define mmdot_product_double clas::mmdot_product_mt
}

//------------------------------------------------------------------------------
# endif

