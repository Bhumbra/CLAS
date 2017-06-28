# include "products.hxx"

// to debug assembler
// g++ -g -save-temps a.cpp
// gdb a.out
// break class::function
// r
// disp/i $pc
// si

namespace clas {

//------------------------------------------------------------------------------
void ewise_product_double_ut(double* Out, 
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
void outer_product_double_ut(double* Out, 
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
void rmdot_product_double_ut(double* Out, 
														 double* In0, 
														 double* In1, 
														 volatile const uint64_t m, 
														 volatile const uint64_t k, 
														 volatile const uint64_t n,
														 double* In2,
														 volatile uint64_t U0,
														 volatile uint64_t U1) {
	rmdot_product_ut(Out, In0, In1, m, k, n, In2, U0, U1);
}
//------------------------------------------------------------------------------
void cmdot_product_double_ut(double* Out, 
														 double* In0, 
														 double* In1, 
														 volatile const uint64_t m, 
														 volatile const uint64_t k, 
														 volatile const uint64_t n,
														 double* In2,
														 volatile uint64_t U0,
														 volatile uint64_t U1) {
	cmdot_product_ut(Out, In0, In1, m, k, n, In2, U0, U1);
}
//------------------------------------------------------------------------------
void mrdot_product_double_ut(double* Out, 
														 double* In0, 
														 double* In1, 
														 volatile const uint64_t m, 
														 volatile const uint64_t k, 
														 volatile const uint64_t n,
														 volatile const bool OutCm,
														 double* In2,
														 volatile uint64_t U0,
														 volatile uint64_t U1) {
	mrdot_product_ut(Out, In0, In1, m, k, n, OutCm, In2, U0, U1);
}
//------------------------------------------------------------------------------
void mcdot_product_double_ut(double* Out, 
														 double* In0, 
														 double* In1, 
														 volatile const uint64_t m, 
														 volatile const uint64_t k, 
														 volatile const uint64_t n,
														 volatile const bool OutCm,
														 double* In2,
														 volatile uint64_t U0,
														 volatile uint64_t U1) {
	mcdot_product_ut(Out, In0, In1, m, k, n, OutCm, In2, U0, U1);
}
//------------------------------------------------------------------------------
void mmdot_product_double_ut (double* Out, 
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
											volatile uint64_t U0,
											volatile uint64_t U1) { 
	mmdot_product_ut(Out, In0, In1, m, k, n, OutT, In0T, In1T, ColM, In2, U0, U1); 
}

//------------------------------------------------------------------------------
void ewise_product_double_mt(double* Out, 
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
void outer_product_double_mt(double* Out, 
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
void rmdot_product_double_mt(double* Out, 
														 double* In0, 
														 double* In1, 
														 volatile const uint64_t m, 
														 volatile const uint64_t k, 
														 volatile const uint64_t n,
														 double* In2,
														 volatile uint64_t U0,
														 volatile uint64_t U1,
														 volatile uint64_t NT) {
	rmdot_product_mt(Out, In0, In1, m, k, n, In2, U0, U1, NT);
}
//------------------------------------------------------------------------------
void cmdot_product_double_mt(double* Out, 
														 double* In0, 
														 double* In1, 
														 volatile const uint64_t m, 
														 volatile const uint64_t k, 
														 volatile const uint64_t n,
														 double* In2,
														 volatile uint64_t U0,
														 volatile uint64_t U1,
														 volatile uint64_t NT) {
	cmdot_product_mt(Out, In0, In1, m, k, n, In2, U0, U1, NT);
}
//------------------------------------------------------------------------------
void mrdot_product_double_mt(double* Out, 
														 double* In0, 
														 double* In1, 
														 volatile const uint64_t m, 
														 volatile const uint64_t k, 
														 volatile const uint64_t n,
														 volatile const bool OutCm,
														 double* In2,
														 volatile uint64_t U0,
														 volatile uint64_t U1,
														 volatile uint64_t NT) {
	mrdot_product_mt(Out, In0, In1, m, k, n, OutCm, In2, U0, U1, NT);
}
//------------------------------------------------------------------------------
void mcdot_product_double_mt(double* Out, 
														 double* In0, 
														 double* In1, 
														 volatile const uint64_t m, 
														 volatile const uint64_t k, 
														 volatile const uint64_t n,
														 volatile const bool OutCm,
														 double* In2,
														 volatile uint64_t U0,
														 volatile uint64_t U1,
														 volatile uint64_t NT) {
	mcdot_product_mt(Out, In0, In1, m, k, n, OutCm, In2, U0, U1, NT);
}
//------------------------------------------------------------------------------
void mmdot_product_double_mt (double* Out, 
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
											volatile uint64_t U0,
											volatile uint64_t U1) { 
	// NT at end in template 
	mmdot_product_mt(Out, In0, In1, m, k, n, OutT, In0T, In1T, ColM, In2, U0, U1, NT); 
}

//------------------------------------------------------------------------------

}
