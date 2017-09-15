# ifndef products_hxx
# define products_hxx

# include "clas.hxx"
# include "_products_mt.txx"
# include "ewise.txx"
# include "outer.txx"
# include "inner.txx"
# include "mmdot.txx"

namespace clas {
# ifndef CLAS_HEADERS_ONLY
ewise<double, uint64_t> EWISE_DOUBLE_UINT64_T;
outer<double, uint64_t> OUTER_DOUBLE_UINT64_T;
inner<double, uint64_t> INNER_DOUBLE_UINT64_T;
mmdot<double, uint64_t> MMDOT_DOUBLE_UINT64_T;
# endif
//------------------------------------------------------------------------------
void ewise_product_double_ut (double* Out, 
															double* In0, 
															double* In1, 
															volatile const uint64_t m, 
															volatile const uint64_t n, 
															volatile const uint64_t Outs = 0,
															volatile const uint64_t In0s = 0,
															volatile const uint64_t In1s = 0,
															volatile uint64_t UR = 0);
//------------------------------------------------------------------------------
void outer_product_double_ut (double* Out, 
															double* In0, 
															double* In1, 
															volatile const uint64_t m, 
															volatile const uint64_t n,
															volatile const uint64_t Outs = 0,
															volatile const uint64_t In0s = 0,
															volatile const uint64_t In1s = 0,
															volatile uint64_t UR = 0);
//------------------------------------------------------------------------------
void inner_product_double_ut (double* Out, 
															double* In0, 
															double* In1, 
															volatile const uint64_t m, 
															volatile const uint64_t k, 
															volatile const uint64_t Outs = 1,
															volatile uint64_t In0s = 1,
															volatile uint64_t In1s = 1,
															double* In2 = 0,
															volatile uint64_t UR = 0);
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
void ewise_product_double_mt (double* Out, 
															double* In0, 
															double* In1, 
															volatile const uint64_t m, 
															volatile const uint64_t n, 
															volatile const uint64_t Outs = 0,
															volatile const uint64_t In0s = 0,
															volatile const uint64_t In1s = 0,
															volatile uint64_t UR = 0);
//------------------------------------------------------------------------------
void outer_product_double_mt (double* Out, 
															double* In0, 
															double* In1, 
															volatile const uint64_t m, 
															volatile const uint64_t n,
															volatile const uint64_t Outs = 0,
															volatile const uint64_t In0s = 0,
															volatile const uint64_t In1s = 0,
															volatile uint64_t UR = 0);
//------------------------------------------------------------------------------
void inner_product_double_mt (double* Out, 
															double* In0, 
															double* In1, 
															volatile const uint64_t m, 
															volatile const uint64_t k, 
															volatile const uint64_t Outs = 1,
															volatile uint64_t In0s = 1,
															volatile uint64_t In1s = 1,
															double* In2 = 0,
															volatile uint64_t UR = 0);

//------------------------------------------------------------------------------
void clas_ewise_product_double (double* Out, 
																double* In0, 
																double* In1, 
																volatile const uint64_t m, 
																volatile const uint64_t k,
																volatile const uint64_t p,
																volatile const uint64_t q,
																bool i0c,
																bool i1b,
																double* In2 = 0,
																volatile uint64_t NT = 0,
																volatile double FT = 1.,
																volatile uint64_t D = 0,
																volatile uint64_t R = 0,
																volatile uint64_t A = 0);
//------------------------------------------------------------------------------
void clas_outer_product_double (double* Out, 
																double* In0, 
																double* In1, 
																volatile const uint64_t m, 
																volatile const uint64_t k,
																volatile const uint64_t p,
																volatile const uint64_t q,
																bool i0c,
																bool i1b,
																double* In2 = 0,
																volatile uint64_t NT = 0,
																volatile double FT = 1.,
																volatile uint64_t D = 0,
																volatile uint64_t R = 0,
																volatile uint64_t A = 0);
//------------------------------------------------------------------------------
void clas_inner_product_double (double* Out, 
																double* In0, 
																double* In1, 
																volatile const uint64_t m, 
																volatile const uint64_t k,
																volatile const uint64_t p,
																volatile const uint64_t q,
																bool i0c,
																bool i1b,
																double* In2 = 0,
																volatile uint64_t NT = 0,
																volatile double FT = 1.,
																volatile uint64_t D = 0,
																volatile uint64_t R = 0,
																volatile uint64_t A = 0);
//------------------------------------------------------------------------------
void clas_mmdot_product_double (double* Out, 
																double* In0, 
																double* In1, 
																volatile const uint64_t m, 
																volatile const uint64_t k,
																volatile const uint64_t n,
																volatile bool OutT = false,
																volatile bool In0T = false,
																volatile bool In1T = false,
																volatile bool ColM = false,
																double* In2 = 0,
																volatile uint64_t NT = 0,
																volatile double FT = 1.,
																volatile uint64_t D = 0,
																volatile uint64_t R = 0,
																volatile uint64_t A = 0);
//------------------------------------------------------------------------------
} // namespace
//------------------------------------------------------------------------------
#endif

