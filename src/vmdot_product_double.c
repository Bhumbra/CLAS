//------------------------------------------------------------------------------
# include "vmdot_product_double.h"

//------------------------------------------------------------------------------
static void vmdot_product_double_1 (double* Out, double* In0, 
																		double* In1, 
																		volatile const uint64_t m,
																		volatile const uint64_t k,
																		volatile const uint64_t n, 
																		volatile uint64_t OutS, 
																		volatile uint64_t In0S, 
																		volatile uint64_t In0s, 
																		volatile uint64_t In1s, 
																		volatile uint64_t U1) { 
	uint64_t h = m;
	switch (U1) {
		case 1: {
			for (; h; h--) {
				vmdot_product_double_1x1 (Out, In0, In1, k, n, In0s, In1s); 
				Out += OutS;
				In0 += In0S;
			}
			return;
		}
		case 2: {
			for (; h; h--) {
				vmdot_product_double_1x2 (Out, In0, In1, k, n, In0s, In1s); 
				Out += OutS;
				In0 += In0S;
			}
			return;
		}
		case 4: {
			for (; h; h--) {
				vmdot_product_double_1x4 (Out, In0, In1, k, n, In0s, In1s); 
				Out += OutS;
				In0 += In0S;
			}
			return;
		}
		case 8: {
			for (; h; h--) {
				vmdot_product_double_1x8 (Out, In0, In1, k, n, In0s, In1s); 
				Out += OutS;
				In0 += In0S;
			}
			return;
		}
		case 16: {
			for (; h; h--) {
				vmdot_product_double_1x16(Out, In0, In1, k, n, In0s, In1s); 
				Out += OutS;
				In0 += In0S;
			}
			return;
		}
		default: { for (; h; h--) {
				vmdot_product_double_1x32(Out, In0, In1, k, n, In0s, In1s); 
				Out += OutS;
				In0 += In0S;
			}
			return;
		}
	}
}

/*
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
																		volatile uint64_t U1) { 
	uint64_t h = m >> 1;
	uint64_t mod = m & 1;
	switch (U1) {
		case 1: {
			for (; h; h--) {
				vmdot_product_double_2x1 (Out, In0, In1, k, n, In0S, In0s, In1s); 
				Out += OutS * 2;
				In0 += In0S * 2;
			}
			if (mod) {
				vmdot_product_double_1x1 (Out, In0, In1, k, n, In0s, In1s); 
				Out += OutS;
				In0 += In0S;
			}
			return;
		}
		case 2: {
			for (; h; h--) {
				vmdot_product_double_2x2 (Out, In0, In1, k, n, In0S, In0s, In1s); 
				Out += OutS * 2;
				In0 += In0S * 2;
			}
			if (mod) {
				vmdot_product_double_1x2 (Out, In0, In1, k, n, In0s, In1s); 
				Out += OutS;
				In0 += In0S;
			}
			return;
		}
		case 4: {
			for (; h; h--) {
				vmdot_product_double_2x4 (Out, In0, In1, k, n, In0S, In0s, In1s); 
				Out += OutS * 2;
				In0 += In0S * 2;
			}
			if (mod) {
				vmdot_product_double_1x4 (Out, In0, In1, k, n, In0s, In1s); 
				Out += OutS;
				In0 += In0S;
			}
			return;
		}
		case 8: {
			for (; h; h--) {
				vmdot_product_double_2x8 (Out, In0, In1, k, n, In0S, In0s, In1s); 
				Out += OutS * 2;
				In0 += In0S * 2;
			}
			if (mod) {
				vmdot_product_double_1x8 (Out, In0, In1, k, n, In0s, In1s); 
				Out += OutS;
				In0 += In0S;
			}
			return;
		}
		case 16: {
			for (; h; h--) {
				vmdot_product_double_2x16(Out, In0, In1, k, n, In0S, In0s, In1s); 
				Out += OutS * 2;
				In0 += In0S * 2;
			}
			if (mod) {
				vmdot_product_double_1x16(Out, In0, In1, k, n, In0s, In1s); 
				Out += OutS;
				In0 += In0S;
			}
			return;
		}
		default: {
			for (; h; h--) {
				vmdot_product_double_2x32(Out, In0, In1, k, n, In0S, In0s, In1s); 
				Out += OutS * 2;
				In0 += In0S * 2;
			}
			if (mod) {
				vmdot_product_double_1x32(Out, In0, In1, k, n, In0s, In1s); 
				Out += OutS;
				In0 += In0S;
			}
			return;
		}
	}
}

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
																		volatile uint64_t U1) { 
	uint64_t h = m >> 2;
	uint64_t mod = m & 3;
	switch (U1) {
		case 1: {
			for (; h; h--) {
				vmdot_product_double_4x1 (Out, In0, In1, k, n, In0S, In0s, In1s); 
				Out += OutS * 4;
				In0 += In0S * 4;
			}
			if (mod > 1) {
				vmdot_product_double_2x1 (Out, In0, In1, k, n, In0S, In0s, In1s); 
				Out += OutS * 2;
				In0 += In0S * 2;
				mod &= 1;
			}
			if (mod) {
				vmdot_product_double_1x1 (Out, In0, In1, k, n, In0s, In1s); 
				Out += OutS;
				In0 += In0S;
			}
			return;
		}
		case 2: {
			for (; h; h--) {
				vmdot_product_double_4x2 (Out, In0, In1, k, n, In0S, In0s, In1s); 
				Out += OutS * 4;
				In0 += In0S * 4;
			}
			if (mod > 1) {
				vmdot_product_double_2x2 (Out, In0, In1, k, n, In0S, In0s, In1s); 
				Out += OutS * 2;
				In0 += In0S * 2;
				mod &= 1;
			}
			if (mod) {
				vmdot_product_double_1x2 (Out, In0, In1, k, n, In0s, In1s); 
				Out += OutS;
				In0 += In0S;
			}
			return;
		}
		case 4: {
			for (; h; h--) {
				vmdot_product_double_4x4 (Out, In0, In1, k, n, In0S, In0s, In1s); 
				Out += OutS * 4;
				In0 += In0S * 4;
			}
			if (mod > 1) {
				vmdot_product_double_2x4 (Out, In0, In1, k, n, In0S, In0s, In1s); 
				Out += OutS * 2;
				In0 += In0S * 2;
				mod &= 1;
			}
			if (mod) {
				vmdot_product_double_1x4 (Out, In0, In1, k, n, In0s, In1s); 
				Out += OutS;
				In0 += In0S;
			}
			return;
		}
		case 8: {
			for (; h; h--) {
				vmdot_product_double_4x8 (Out, In0, In1, k, n, In0S, In0s, In1s); 
				Out += OutS * 4;
				In0 += In0S * 4;
			}
			if (mod > 1) {
				vmdot_product_double_2x8 (Out, In0, In1, k, n, In0S, In0s, In1s); 
				Out += OutS * 2;
				In0 += In0S * 2;
				mod &= 1;
			}
			if (mod) {
				vmdot_product_double_1x8 (Out, In0, In1, k, n, In0s, In1s); 
				Out += OutS;
				In0 += In0S;
			}
			return;
		}
		case 16: {
			for (; h; h--) {
				vmdot_product_double_4x16(Out, In0, In1, k, n, In0S, In0s, In1s); 
				Out += OutS * 4;
				In0 += In0S * 4;
			}
			if (mod > 1) {
				vmdot_product_double_2x16(Out, In0, In1, k, n, In0S, In0s, In1s); 
				Out += OutS * 2;
				In0 += In0S * 2;
				mod &= 1;
			}
			if (mod) {
				vmdot_product_double_1x16(Out, In0, In1, k, n, In0s, In1s); 
				Out += OutS;
				In0 += In0S;
			}
			return;
		}
		default: {
			for (; h; h--) {
				vmdot_product_double_4x32(Out, In0, In1, k, n, In0S, In0s, In1s); 
				Out += OutS * 4;
				In0 += In0S * 4;
			}
			if (mod > 1) {
				vmdot_product_double_2x32(Out, In0, In1, k, n, In0S, In0s, In1s); 
				Out += OutS * 2;
				In0 += In0S * 2;
				mod &= 1;
			}
			if (mod) {
				vmdot_product_double_1x32(Out, In0, In1, k, n, In0s, In1s); 
				Out += OutS;
				In0 += In0S;
			}
			return;
		}
	}
}

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
																		volatile uint64_t U1) { 
	uint64_t h = m >> 3;
	uint64_t mod = m & 7;
	switch (U1) {
		case 1: {
			for (; h; h--) {
				vmdot_product_double_8x1 (Out, In0, In1, k, n, In0S, In0s, In1s); 
				Out += OutS * 8;
				In0 += In0S * 8;
			}
			if (mod > 3) {
				vmdot_product_double_4x1 (Out, In0, In1, k, n, In0S, In0s, In1s); 
				Out += OutS * 4;
				In0 += In0S * 4;
				mod &= 3;
			}
			if (mod > 1) {
				vmdot_product_double_2x1 (Out, In0, In1, k, n, In0S, In0s, In1s); 
				Out += OutS * 2;
				In0 += In0S * 2;
				mod &= 1;
			}
			if (mod) {
				vmdot_product_double_1x1 (Out, In0, In1, k, n, In0s, In1s); 
				Out += OutS;
				In0 += In0S;
			}
			return;
		}
		case 2: {
			for (; h; h--) {
				vmdot_product_double_8x2 (Out, In0, In1, k, n, In0S, In0s, In1s); 
				Out += OutS * 8;
				In0 += In0S * 8;
			}
			if (mod > 3) {
				vmdot_product_double_4x2 (Out, In0, In1, k, n, In0S, In0s, In1s); 
				Out += OutS * 4;
				In0 += In0S * 4;
				mod &= 3;
			}
			if (mod > 1) {
				vmdot_product_double_2x2 (Out, In0, In1, k, n, In0S, In0s, In1s); 
				Out += OutS * 2;
				In0 += In0S * 2;
				mod &= 1;
			}
			if (mod) {
				vmdot_product_double_1x2 (Out, In0, In1, k, n, In0s, In1s); 
				Out += OutS;
				In0 += In0S;
			}
			return;
		}
		case 4: {
			for (; h; h--) {
				vmdot_product_double_8x4 (Out, In0, In1, k, n, In0S, In0s, In1s); 
				Out += OutS * 8;
				In0 += In0S * 8;
			}
			if (mod > 3) {
				vmdot_product_double_4x4 (Out, In0, In1, k, n, In0S, In0s, In1s); 
				Out += OutS * 4;
				In0 += In0S * 4;
				mod &= 3;
			}
			if (mod > 1) {
				vmdot_product_double_2x4 (Out, In0, In1, k, n, In0S, In0s, In1s); 
				Out += OutS * 2;
				In0 += In0S * 2;
				mod &= 1;
			}
			if (mod) {
				vmdot_product_double_1x4 (Out, In0, In1, k, n, In0s, In1s); 
				Out += OutS;
				In0 += In0S;
			}
			return;
		}
		case 8: {
			for (; h; h--) {
				vmdot_product_double_8x8 (Out, In0, In1, k, n, In0S, In0s, In1s); 
				Out += OutS * 8;
				In0 += In0S * 8;
			}
			if (mod > 3) {
				vmdot_product_double_4x8 (Out, In0, In1, k, n, In0S, In0s, In1s); 
				Out += OutS * 4;
				In0 += In0S * 4;
				mod &= 3;
			}
			if (mod > 1) {
				vmdot_product_double_2x8 (Out, In0, In1, k, n, In0S, In0s, In1s); 
				Out += OutS * 2;
				In0 += In0S * 2;
				mod &= 1;
			}
			if (mod) {
				vmdot_product_double_1x8 (Out, In0, In1, k, n, In0s, In1s); 
				Out += OutS;
				In0 += In0S;
			}
			return;
		}
		case 16: {
			for (; h; h--) {
				vmdot_product_double_8x16(Out, In0, In1, k, n, In0S, In0s, In1s); 
				Out += OutS * 8;
				In0 += In0S * 8;
			}
			if (mod > 3) {
				vmdot_product_double_4x16(Out, In0, In1, k, n, In0S, In0s, In1s); 
				Out += OutS * 4;
				In0 += In0S * 4;
				mod &= 3;
			}
			if (mod > 1) {
				vmdot_product_double_2x16(Out, In0, In1, k, n, In0S, In0s, In1s); 
				Out += OutS * 2;
				In0 += In0S * 2;
				mod &= 1;
			}
			if (mod) {
				vmdot_product_double_1x16(Out, In0, In1, k, n, In0s, In1s); 
				Out += OutS;
				In0 += In0S;
			}
			return;
		}
		default: {
			for (; h; h--) {
				vmdot_product_double_8x32(Out, In0, In1, k, n, In0S, In0s, In1s); 
				Out += OutS * 8;
				In0 += In0S * 8;
			}
			if (mod > 3) {
				vmdot_product_double_4x32(Out, In0, In1, k, n, In0S, In0s, In1s); 
				Out += OutS * 4;
				In0 += In0S * 4;
				mod &= 3;
			}
			if (mod > 1) {
				vmdot_product_double_2x32(Out, In0, In1, k, n, In0S, In0s, In1s); 
				Out += OutS * 2;
				In0 += In0S * 2;
				mod &= 1;
			}
			if (mod) {
				vmdot_product_double_1x32(Out, In0, In1, k, n, In0s, In1s); 
				Out += OutS;
				In0 += In0S;
			}
			return;
		}
	}
}

//------------------------------------------------------------------------------
*/

