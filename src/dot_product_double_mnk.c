//------------------------------------------------------------------------------
# include "dot_product_double_mnk.h"

//------------------------------------------------------------------------------
void dot_product_double_MNK_8x8x8(double* _Out, 
																	double* _In0, 
																	double* _In1, 
																	volatile const uint64_t m, 
																	volatile const uint64_t k,
																	volatile const uint64_t n,
																	volatile uint64_t OutS,
																	volatile uint64_t Arch) { 
	switch (Arch) {
		case 1: {
			return DOT_PRODUCT_DOUBLE_MNK_8X8X8_1 (_Out, _In0, _In1, m, k, n, OutS);
		}
		case 2: {
			return DOT_PRODUCT_DOUBLE_MNK_8X8X8_2 (_Out, _In0, _In1, m, k, n, OutS);
		}
		default: {
			return DOT_PRODUCT_DOUBLE_MNK_8X8X8_0 (_Out, _In0, _In1, m, k, n, OutS);
		}
	}
}

//------------------------------------------------------------------------------

