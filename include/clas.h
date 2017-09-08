# ifndef clas_h
# define clas_h
//------------------------------------------------------------------------------
// Header included when linking to clas-dependent external source code

//------------------------------------------------------------------------------
# define CLAS_HEADERS_ONLY 1

//------------------------------------------------------------------------------
# include "products.hxx"

//------------------------------------------------------------------------------
namespace clas {
# define inner_product_double clas_inner_product_double
# define mmdot_product_double clas_mmdot_product_double
}
//------------------------------------------------------------------------------
#endif

