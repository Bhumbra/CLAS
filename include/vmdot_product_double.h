# ifndef _vmdot_product_double_h
# define _vmdot_product_double_h

# include "stdint.h"

//------------------------------------------------------------------------------
# ifdef __cpluscplus
extern "C" void vmdot_product_double_1x1 (double* Out, double* In0, double* _In1, uint64_t k, uint64_t n, uint64_t In0s, uint64_t In1s);
extern "C" void vmdot_product_double_1x2 (double* Out, double* In0, double* _In1, uint64_t k, uint64_t n, uint64_t In0s, uint64_t In1s);
extern "C" void vmdot_product_double_1x4 (double* Out, double* In0, double* _In1, uint64_t k, uint64_t n, uint64_t In0s, uint64_t In1s);
extern "C" void vmdot_product_double_1x8 (double* Out, double* In0, double* _In1, uint64_t k, uint64_t n, uint64_t In0s, uint64_t In1s);
extern "C" void vmdot_product_double_1x16(double* Out, double* In0, double* _In1, uint64_t k, uint64_t n, uint64_t In0s, uint64_t In1s);
extern "C" void vmdot_product_double_1x32(double* Out, double* In0, double* _In1, uint64_t k, uint64_t n, uint64_t In0s, uint64_t In1s);
extern "C" void vmdot_product_double_2x1 (double* Out, double* In0, double* _In1, uint64_t k, uint64_t n, uint64_t In0S, uint64_t In0s, uint64_t In1s);
extern "C" void vmdot_product_double_2x2 (double* Out, double* In0, double* _In1, uint64_t k, uint64_t n, uint64_t In0S, uint64_t In0s, uint64_t In1s);
extern "C" void vmdot_product_double_2x4 (double* Out, double* In0, double* _In1, uint64_t k, uint64_t n, uint64_t In0S, uint64_t In0s, uint64_t In1s);
extern "C" void vmdot_product_double_2x8 (double* Out, double* In0, double* _In1, uint64_t k, uint64_t n, uint64_t In0S, uint64_t In0s, uint64_t In1s);
extern "C" void vmdot_product_double_2x16(double* Out, double* In0, double* _In1, uint64_t k, uint64_t n, uint64_t In0S, uint64_t In0s, uint64_t In1s);
extern "C" void vmdot_product_double_2x32(double* Out, double* In0, double* _In1, uint64_t k, uint64_t n, uint64_t In0S, uint64_t In0s, uint64_t In1s);
# else
void vmdot_product_double_1x1 (double* Out, double* In0, double* _In1, uint64_t k, uint64_t n, uint64_t In0s, uint64_t In1s);
void vmdot_product_double_1x2 (double* Out, double* In0, double* _In1, uint64_t k, uint64_t n, uint64_t In0s, uint64_t In1s);
void vmdot_product_double_1x4 (double* Out, double* In0, double* _In1, uint64_t k, uint64_t n, uint64_t In0s, uint64_t In1s);
void vmdot_product_double_1x8 (double* Out, double* In0, double* _In1, uint64_t k, uint64_t n, uint64_t In0s, uint64_t In1s);
void vmdot_product_double_1x16(double* Out, double* In0, double* _In1, uint64_t k, uint64_t n, uint64_t In0s, uint64_t In1s);
void vmdot_product_double_1x32(double* Out, double* In0, double* _In1, uint64_t k, uint64_t n, uint64_t In0s, uint64_t In1s);
void vmdot_product_double_2x1 (double* Out, double* In0, double* _In1, uint64_t k, uint64_t n, uint64_t In0S, uint64_t In0s, uint64_t In1s);
void vmdot_product_double_2x2 (double* Out, double* In0, double* _In1, uint64_t k, uint64_t n, uint64_t In0S, uint64_t In0s, uint64_t In1s);
void vmdot_product_double_2x4 (double* Out, double* In0, double* _In1, uint64_t k, uint64_t n, uint64_t In0S, uint64_t In0s, uint64_t In1s);
void vmdot_product_double_2x8 (double* Out, double* In0, double* _In1, uint64_t k, uint64_t n, uint64_t In0S, uint64_t In0s, uint64_t In1s);
void vmdot_product_double_2x16(double* Out, double* In0, double* _In1, uint64_t k, uint64_t n, uint64_t In0S, uint64_t In0s, uint64_t In1s);
void vmdot_product_double_2x32(double* Out, double* In0, double* _In1, uint64_t k, uint64_t n, uint64_t In0S, uint64_t In0s, uint64_t In1s);
void vmdot_product_double_4x1 (double* Out, double* In0, double* _In1, uint64_t k, uint64_t n, uint64_t In0S, uint64_t In0s, uint64_t In1s);
void vmdot_product_double_4x2 (double* Out, double* In0, double* _In1, uint64_t k, uint64_t n, uint64_t In0S, uint64_t In0s, uint64_t In1s);
void vmdot_product_double_4x4 (double* Out, double* In0, double* _In1, uint64_t k, uint64_t n, uint64_t In0S, uint64_t In0s, uint64_t In1s);
void vmdot_product_double_4x8 (double* Out, double* In0, double* _In1, uint64_t k, uint64_t n, uint64_t In0S, uint64_t In0s, uint64_t In1s);
void vmdot_product_double_4x16(double* Out, double* In0, double* _In1, uint64_t k, uint64_t n, uint64_t In0S, uint64_t In0s, uint64_t In1s);
void vmdot_product_double_4x32(double* Out, double* In0, double* _In1, uint64_t k, uint64_t n, uint64_t In0S, uint64_t In0s, uint64_t In1s);
# endif

//------------------------------------------------------------------------------
static void vmdot_product_double_1 (double* Out, 
																		double* In0, 
																		double* In1, 
																		volatile const uint64_t m,
																		volatile const uint64_t k,
																		volatile const uint64_t n, 
																		volatile uint64_t OutS, 
																		volatile uint64_t In0S, 
																		volatile uint64_t In0s, 
																		volatile uint64_t In1s, 
																		volatile uint64_t U1); 

//------------------------------------------------------------------------------
static void vmdot_product_double_2 (double* Out, 
																		double* In0, 
																		double* In1, 
																		volatile const uint64_t m, 
																		volatile const uint64_t k,
																		volatile const uint64_t n,
																		volatile uint64_t OutS, 
																		volatile uint64_t In0S, 
																		volatile uint64_t In0s, 
																		volatile uint64_t In1s, 
																		volatile uint64_t U1);

//------------------------------------------------------------------------------
static void vmdot_product_double_4 (double* Out, 
																		double* In0, 
																		double* In1, 
																		volatile const uint64_t m, 
																		volatile const uint64_t k,
																		volatile const uint64_t n,
																		volatile uint64_t OutS, 
																		volatile uint64_t In0S, 
																		volatile uint64_t In0s, 
																		volatile uint64_t In1s, 
																		volatile uint64_t U1);

//------------------------------------------------------------------------------
static void vmdot_product_double_8 (double* Out, 
																		double* In0, 
																		double* In1, 
																		volatile const uint64_t m, 
																		volatile const uint64_t k,
																		volatile const uint64_t n,
																		volatile uint64_t OutS, 
																		volatile uint64_t In0S, 
																		volatile uint64_t In0s, 
																		volatile uint64_t In1s, 
																		volatile uint64_t U1);

//------------------------------------------------------------------------------
#endif

