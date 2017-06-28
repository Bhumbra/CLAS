#ifndef products_hxx
#define products_hxx

#include "products.txx"

# define ASM_PROLOGUE (ASM_INTEL ASM_MOV(RX8, RBX)
# define ASM_EPILOGUE ASM_ATT : : "a" (Out), "b" (Rx8) : );

namespace clas {
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
void rmdot_product_double_ut(double* Out, 
														 double* In0, 
														 double* In1, 
														 volatile const uint64_t m, 
														 volatile const uint64_t k, 
														 volatile const uint64_t n,
														 double* In2 = 0,
														 volatile uint64_t U0 = 0,
														 volatile uint64_t U1 = 0);
//------------------------------------------------------------------------------
void cmdot_product_double_ut(double* Out, 
														 double* In0, 
														 double* In1, 
														 volatile const uint64_t m, 
														 volatile const uint64_t k, 
														 volatile const uint64_t n,
														 double* In2 = 0,
														 volatile uint64_t U0 = 0,
														 volatile uint64_t U1 = 0);
//------------------------------------------------------------------------------
void mrdot_product_double_ut(double* Out, 
														 double* In0, 
														 double* In1, 
														 volatile const uint64_t m, 
														 volatile const uint64_t k, 
														 volatile const uint64_t n,
														 volatile const bool OutCm = false,
														 double* In2 = 0,
														 volatile uint64_t U0 = 0,
														 volatile uint64_t U1 = 0);
//------------------------------------------------------------------------------
void mcdot_product_double_ut(double* Out, 
														 double* In0, 
														 double* In1, 
														 volatile const uint64_t m, 
														 volatile const uint64_t k, 
														 volatile const uint64_t n,
														 volatile const bool OutCm = false,
														 double* In2 = 0,
														 volatile uint64_t U0 = 0,
														 volatile uint64_t U1 = 0);

//------------------------------------------------------------------------------
void mmdot_product_double_ut (double* Out, 
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
											volatile uint64_t U0 = 0,
											volatile uint64_t U1 = 0);

//------------------------------------------------------------------------------
void ewise_product_double_mt(double* Out, 
			   	            double* In0, 
							   		  double* In1, 
		                  volatile const uint64_t m, 
		                  volatile const uint64_t n, 
											volatile const uint64_t Outs = 0,
											volatile const uint64_t In0s = 0,
										  volatile const uint64_t In1s = 0,
											volatile uint64_t UR = 0);
//------------------------------------------------------------------------------
void outer_product_double_mt(double* Out, 
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
void rmdot_product_double_mt(double* Out, 
														 double* In0, 
														 double* In1, 
														 volatile const uint64_t m, 
														 volatile const uint64_t k, 
														 volatile const uint64_t n,
														 double* In2 = 0,
														 volatile uint64_t U0 = 0,
														 volatile uint64_t U1 = 0,
														 volatile uint64_t NT = 0);
//------------------------------------------------------------------------------
void cmdot_product_double_mt(double* Out, 
														 double* In0, 
														 double* In1, 
														 volatile const uint64_t m, 
														 volatile const uint64_t k, 
														 volatile const uint64_t n,
														 double* In2 = 0,
														 volatile uint64_t U0 = 0,
														 volatile uint64_t U1 = 0,
														 volatile uint64_t NT = 0);
//------------------------------------------------------------------------------
void mrdot_product_double_mt(double* Out, 
														 double* In0, 
														 double* In1, 
														 volatile const uint64_t m, 
														 volatile const uint64_t k, 
														 volatile const uint64_t n,
														 volatile const bool OutCm = false,
														 double* in2 = 0,
														 volatile uint64_t U0 = 0,
														 volatile uint64_t U1 = 0,
														 volatile uint64_t NT = 0);

//------------------------------------------------------------------------------
void mcdot_product_double_mt(double* Out, 
														 double* In0, 
														 double* In1, 
														 volatile const uint64_t m, 
														 volatile const uint64_t k, 
														 volatile const uint64_t n,
														 volatile const bool OutCm = false,
														 double* in2 = 0,
														 volatile uint64_t U0 = 0,
														 volatile uint64_t U1 = 0,
														 volatile uint64_t NT = 0);

//------------------------------------------------------------------------------
void mmdot_product_double_mt (double* Out, 
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
											volatile uint64_t U0 = 0,
											volatile uint64_t U1 = 0);

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
void ewise_product_double_asm_sse4_2(double* Out,
		                        double* In0, 
													  double* In1,
		                        const uint64_t In0d0,
													  const uint64_t In0d1,
													  const uint64_t In1s0 = 0);
//------------------------------------------------------------------------------
void ewise_product_double_asm_sse4_4(double* Out,
		                        double* In0, 
													  double* In1,
		                        const uint64_t In0d0,
														const uint64_t In0d1,
														const uint64_t In1s0 = 0);
//------------------------------------------------------------------------------
void ewise_product_double_asm_sse4_8(double* Out,
		                        double* In0, 
													  double* In1,
		                        const uint64_t In0d0,
														const uint64_t In0d1,
														const uint64_t In1s0 = 0);
//------------------------------------------------------------------------------
void ewise_product_double_asm_sse4_16(double* Out,
		                        double* In0, 
													  double* In1,
		                        const uint64_t In0d0,
														const uint64_t In0d1,
														const uint64_t In1s0 = 0);
//------------------------------------------------------------------------------
void outer_product_double_asm_sse4_2(double* Out,
		                                 double* In0, 
																		 double* In1,
										   		           const uint64_t In0d, 
																		 const uint64_t In1d,
																		 const uint64_t In1s = 1); 
//------------------------------------------------------------------------------
void outer_product_double_asm_sse4_4(double* Out,
		                                 double* In0, 
																		 double* In1,
										   		           const uint64_t In0d, 
																		 const uint64_t In1d,
																		 const uint64_t In1s = 1); 
//------------------------------------------------------------------------------
void outer_product_double_asm_sse4_8(double* Out,
		                                 double* In0, 
																		 double* In1,
										   		           const uint64_t In0d, 
																		 const uint64_t In1d,
																		 const uint64_t In1s = 1); 
//------------------------------------------------------------------------------
void outer_product_double_asm_sse4_16(double* Out,
		                                  double* In0, 
																		  double* In1,
										   		            const uint64_t In0d, 
																		  const uint64_t In1d,
																		  const uint64_t In1s = 1); 
}
#endif

