# ifndef clas_h
# define clas_h
//------------------------------------------------------------------------------
// Header included when linking to clas-dependent external source code

//------------------------------------------------------------------------------
# define EXCLUDE_C_SOURCE_FILES 1

//------------------------------------------------------------------------------
# include "products.hxx"

//------------------------------------------------------------------------------
namespace clas {
# define mmdot_product_double mmdot_product_double_mt
}
//------------------------------------------------------------------------------
#endif

