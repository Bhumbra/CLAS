# include "products.hxx"

namespace clas {

//------------------------------------------------------------------------------
void ewise_product_double_ut (double* Out, 
															double* In0, 
															double* In1, 
															volatile const uint64_t m, 
															volatile const uint64_t n, 
															volatile const uint64_t Outs,
															volatile const uint64_t In0s,
															volatile const uint64_t In1s,
															volatile uint64_t UR) {
  ewise_product_ut(Out, In0, In1, m, n, Outs, In0s, In1s, UR);
}
//------------------------------------------------------------------------------
void outer_product_double_ut (double* Out, 
															double* In0, 
															double* In1, 
															volatile const uint64_t m, 
															volatile const uint64_t n,
															volatile const uint64_t Outs,
															volatile const uint64_t In0s,
															volatile const uint64_t In1s,
															volatile uint64_t UR) {
  outer_product_ut(Out, In0, In1, m, n, Outs, In0s, In1s, UR);
}
//------------------------------------------------------------------------------
void inner_product_double_ut (double* Out, 
															double* In0, 
															double* In1, 
															volatile const uint64_t m, 
															volatile const uint64_t k, 
															volatile const uint64_t Outs,
															volatile uint64_t In0s,
															volatile uint64_t In1s,
															double* In2,
															volatile uint64_t UR) {
	inner_product_ut(Out, In0, In1, m, k, Outs, In0s, In1s, In2, UR);
}
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
void ewise_product_double_mt (double* Out, 
															double* In0, 
															double* In1, 
															volatile const uint64_t m, 
															volatile const uint64_t n, 
															volatile const uint64_t Outs,
															volatile const uint64_t In0s,
															volatile const uint64_t In1s,
															volatile uint64_t UR) {
	ewise_product_mt(Out, In0, In1, m, n, Outs, In0s, In1s, UR);
}
//------------------------------------------------------------------------------
void outer_product_double_mt (double* Out, 
															double* In0, 
															double* In1, 
															volatile const uint64_t m, 
															volatile const uint64_t n,
															volatile const uint64_t Outs,
															volatile const uint64_t In0s,
															volatile const uint64_t In1s,
															volatile uint64_t UR) {
	outer_product_mt(Out, In0, In1, m, n, Outs, In0s, In1s, UR);
}
//------------------------------------------------------------------------------
void inner_product_double_mt (double* Out, 
															double* In0, 
															double* In1, 
															volatile const uint64_t m, 
															volatile const uint64_t k, 
															volatile const uint64_t Outs,
															volatile uint64_t In0s,
															volatile uint64_t In1s,
															double* In2,
															volatile uint64_t UR) {
	inner_product_mt(Out, In0, In1, m, k, Outs, In0s, In1s, In2, UR);
}

//------------------------------------------------------------------------------
void clas_inner_product_double (double* Out, 
																double* In0, 
																double* In1, 
																volatile const uint64_t m, 
																volatile const uint64_t k,
																volatile const uint64_t p,
																volatile const uint64_t q,
																double* In2,
																volatile uint64_t NT,
																volatile double FT,
																volatile uint64_t D,
																volatile uint64_t R,
																volatile uint64_t A) { 
  INNER_DOUBLE_UINT64_T.init (Out, In0, In1, m, k, p, q,
															In2, NT, FT, D, R, A);
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


