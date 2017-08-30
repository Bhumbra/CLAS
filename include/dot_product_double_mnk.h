# ifndef dot_product_double_mnk_h
# define dot_product_double_mnk_h
//------------------------------------------------------------------------------
# define DOT_PRODUCT_DOUBLE_MNK_8X8X8_0 dot_product_double_MNK_2x1x8_sse4
# define DOT_PRODUCT_DOUBLE_MNK_8X8X8_1 dot_product_double_MNK_2x1x8_sse4
# define DOT_PRODUCT_DOUBLE_MNK_8X8X8_2 dot_product_double_MNK_2x1x8_sse4
//------------------------------------------------------------------------------
# include "stdint.h"

//------------------------------------------------------------------------------
# ifdef __cplusplus
extern "C" void dot_product_double_mnk_1x8x8_sse4(double* Out, double* In0, 
		double* In1, uint64_t m, uint64_t k, uint64_t n, 
		uint64_t OutS, uint64_t In0S, uint64_t In1S);
extern "C" void dot_product_double_MNK_1x8x8_sse4(double* Out, double* In0, 
		double* In1, uint64_t m, uint64_t k, uint64_t n, 
		uint64_t OutS);
extern "C" void dot_product_double_mnk_2x1x8_sse4(double* Out, double* In0, 
		double* In1, uint64_t m, uint64_t k, uint64_t n,
		uint64_t OutS, uint64_t In0S, uint64_t In1S);
extern "C" void dot_product_double_MNK_2x1x8_sse4(double* Out, double* In0, 
		double* In1, uint64_t m, uint64_t k, uint64_t n, 
		uint64_t OutS);
# else
void dot_product_double_mnk(double* Out, double* In0, double* In1, 
		uint64_t m, uint64_t k, uint64_t n,
		uint64_t OutS, uint64_t In0S, uint64_t In1S);
void dot_product_double_MNK_1x8x8_sse4(double* Out, double* In0, double* In1, 
		uint64_t m, uint64_t k, uint64_t n, 
		uint64_t OutS);
void dot_product_double_mnk_2x1x8_sse4(double* Out, double* In0, double* In1, 
		uint64_t m, uint64_t k, uint64_t n,
		uint64_t OutS, uint64_t In0S, uint64_t In1S);
void dot_product_double_MNK_2x1x8_sse4(double* Out, double* In0, double* In1, 
		uint64_t m, uint64_t k, uint64_t n, 
		uint64_t OutS);
# endif

//------------------------------------------------------------------------------
void dot_product_double_MNK_8x8x8(double* _Out, 
																	double* _In0, 
																	double* _In1, 
																	volatile const uint64_t m, 
																	volatile const uint64_t k,
																	volatile const uint64_t n,
																	volatile uint64_t OutS,
																	volatile uint64_t Arch);

//------------------------------------------------------------------------------

# endif
