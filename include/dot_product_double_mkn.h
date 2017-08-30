# ifndef dot_product_double_mkn_h
# define dot_product_double_mkn_h
//------------------------------------------------------------------------------
# define DOT_PRODUCT_DOUBLE_MKN_4X4X4_0 dot_product_double_mkn_4x4x4_sse4
# define DOT_PRODUCT_DOUBLE_MKN_4X4X4_1 dot_product_double_mkn_4x4x4_sse4
# define DOT_PRODUCT_DOUBLE_MKN_4X4X4_2 dot_product_double_mkn_4x4x4_sse4
//------------------------------------------------------------------------------
# include "stdint.h"

//------------------------------------------------------------------------------
# ifdef __cplusplus
extern "C" void dot_product_double_mkn_4x4x4_sse4(double* Out, 
	double* In0, double* In1, uint64_t m, uint64_t k, uint64_t n,
	uint64_t OutS, uint64_t In0S,	uint64_t In0s, uint64_t In1S);
# else
void dot_product_double_mkn_4x4x4_sse4(double* Out, 
	double* In0, double* In1, uint64_t m, uint64_t k, uint64_t n,
	uint64_t OutS, uint64_t In0S,	uint64_t In0s, uint64_t In1S);
# endif

//------------------------------------------------------------------------------
void dot_product_double_mkn_4x4x4(double* _Out, 
																	double* _In0, 
																	double* _In1, 
																	volatile const uint64_t m, 
																	volatile const uint64_t k,
																	volatile const uint64_t n,
																	volatile uint64_t OutS,
																	volatile uint64_t In0S,
																	volatile uint64_t In0s, 
																	volatile uint64_t In1S,
																	volatile uint64_t Arch);

//------------------------------------------------------------------------------

# endif
