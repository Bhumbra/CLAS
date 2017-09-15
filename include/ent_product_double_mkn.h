# ifndef ent_product_double_mkn_h
# define ent_product_double_mkn_h
//------------------------------------------------------------------------------
# define ENT_PRODUCT_DOUBLE_MKN_1X8X1_0 ent_product_double_mkn_1x8x1_sse4
# define ENT_PRODUCT_DOUBLE_MKN_1X8X1_1 ent_product_double_mkn_1x8x1_sse4
# define ENT_PRODUCT_DOUBLE_MKN_1X8X1_2 ent_product_double_mkn_1x8x1_sse4
//------------------------------------------------------------------------------
# include "stdint.h"

//------------------------------------------------------------------------------
# ifdef __cplusplus
extern "C" void ent_product_double_mkn_1x8x1_sse4(double* Out, 
	double* In0, double* In1, uint64_t m, uint64_t k, uint64_t n,
	uint64_t OutS, uint64_t In0S,	uint64_t In0s, uint64_t In1S);
# else
void ent_product_double_mkn_1x8x1_sse4(double* Out, 
	double* In0, double* In1, uint64_t m, uint64_t k, uint64_t n,
	uint64_t OutS, uint64_t In0S,	uint64_t In0s, uint64_t In1S);
# endif

//------------------------------------------------------------------------------
void ent_product_double_mkn_1x8x1(double* _Out, 
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
