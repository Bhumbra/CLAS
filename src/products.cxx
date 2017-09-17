# include "products.hxx"

namespace clas {

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
																double* In2,
																volatile uint64_t NT,
																volatile double FT,
																volatile uint64_t D,
																volatile uint64_t R,
																volatile uint64_t A) { 
  EWISE_DOUBLE_UINT64_T.init (Out, In0, In1, m, k, p, q,
															i0c, i1b, In2, NT, FT, D, R, A);
	EWISE_DOUBLE_UINT64_T.exec();
}

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
																double* In2,
																volatile uint64_t NT,
																volatile double FT,
																volatile uint64_t D,
																volatile uint64_t R,
																volatile uint64_t A) { 
  OUTER_DOUBLE_UINT64_T.init (Out, In0, In1, m, k, p, q,
															i0c, i1b, In2, NT, FT, D, R, A);
	OUTER_DOUBLE_UINT64_T.exec();
}

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
																double* In2,
																volatile uint64_t NT,
																volatile double FT,
																volatile uint64_t D,
																volatile uint64_t R,
																volatile uint64_t A) { 
  INNER_DOUBLE_UINT64_T.init (Out, In0, In1, m, k, p, q,
															i0c, i1b, In2, NT, FT, D, R, A);
	INNER_DOUBLE_UINT64_T.exec();
}

//------------------------------------------------------------------------------
void clas_mmdot_product_double (double* Out, 
																double* In0, 
																double* In1, 
																volatile const uint64_t m, 
																volatile const uint64_t k,
																volatile const uint64_t n,
																volatile bool OutT,
																volatile bool In0T,
																volatile bool In1T,
																volatile bool ColM,
																double* In2,
																volatile uint64_t NT,
																volatile double FT,
																volatile uint64_t D,
																volatile uint64_t R,
																volatile uint64_t A) { 
  MMDOT_DOUBLE_UINT64_T.init (Out, In0, In1, m, k, n, OutT, In0T, In1T, ColM, 
															In2, NT, FT, D, R, A); 
	MMDOT_DOUBLE_UINT64_T.exec();
}

//------------------------------------------------------------------------------
} // namespace


