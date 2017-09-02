//------------------------------------------------------------------------------
# include "dot_product_double_mkc.h"

//------------------------------------------------------------------------------
void dot_product_double_mkc_4x4x4(double* _Out, 
																	double* _In0, 
																	double* _In1, 
																	volatile const uint64_t m, 
																	volatile const uint64_t k,
																	volatile const uint64_t n,
																	volatile uint64_t OutS,
																	volatile uint64_t In0S, 
																	volatile uint64_t In0s, 
																	volatile uint64_t In1S,
																	volatile uint64_t Arch) { 
	switch (Arch) {
		case 1: {
			DOT_PRODUCT_DOUBLE_MKC_4X4X4_1 (_Out, _In0, _In1, m, k, n,
																			OutS, In0S, In0s, In1S);
			return;
		}
		case 2: {
			DOT_PRODUCT_DOUBLE_MKC_4X4X4_2 (_Out, _In0, _In1, m, k, n,
																			OutS, In0S, In0s, In1S);
			return;
		}
		default: {
			DOT_PRODUCT_DOUBLE_MKC_4X4X4_0 (_Out, _In0, _In1, m, k, n,
																			OutS, In0S, In0s, In1S);
			return;
		}
	}
}

//------------------------------------------------------------------------------
void dot_product_double_mkc_1x8x1(double* _Out, 
																	double* _In0, 
																	double* _In1, 
																	volatile const uint64_t m, 
																	volatile const uint64_t k,
																	volatile const uint64_t n,
																	volatile uint64_t OutS,
																	volatile uint64_t In0S, 
																	volatile uint64_t In0s, 
																	volatile uint64_t In1S,
																	volatile uint64_t Arch) { 
	switch (Arch) {
		case 1: {
			DOT_PRODUCT_DOUBLE_MKC_1X8X1_1 (_Out, _In0, _In1, m, k, n,
																			OutS, In0S, In0s, In1S);
			return;
		}
		case 2: {
			DOT_PRODUCT_DOUBLE_MKC_1X8X1_2 (_Out, _In0, _In1, m, k, n,
																			OutS, In0S, In0s, In1S);
			return;
		}
		default: {
			DOT_PRODUCT_DOUBLE_MKC_1X8X1_0 (_Out, _In0, _In1, m, k, n,
																			OutS, In0S, In0s, In1S);
			return;
		}
	}
}

//------------------------------------------------------------------------------

