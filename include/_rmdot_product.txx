# ifndef _rmdot_product_txx
# define _rmdot_product_txx
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
# include <iostream>
using namespace std;

# include "clas_unroll.txx"
//------------------------------------------------------------------------------
# include "_replicate.txx"
# include "_rmdot_product_1.txx"
# include "_rmdot_product_2.txx"
# include "_rmdot_product_4.txx"

//------------------------------------------------------------------------------
template <class T, class U>
static inline void rmdot_product_1 (T* Out, 
																		T* In0, 
																		T* In1, 
																		volatile const U m,
																		volatile const U k,
																		volatile const U n, 
																		T* In2 = 0,
																		volatile const bool _In2Tr = false,
																		volatile U UR = 0) { 

	register U ur = set_unroll(k >> 2, UR);
	register U h;
	volatile const U In2s = In2 ? (U)1 : (U)0;
	volatile const bool In2Tr = In2s ? false : _In2Tr;

	if (!In2Tr) {
		switch (ur) {
			case 1: {
				for (h = 0; h<m; h++) {
					replicate_1x1(Out+h*n, n, In2+h*In2s, (U)1, (U)0);
					rmdot_product_1x1(Out+h*n, In0+h*k, In1, k, n, n); 
				}
				return;
			}
			case 2: {
				for (h = 0; h<m; h++) {
					replicate_1x2(Out+h*n, n, In2+h*In2s, (U)1, (U)0);
					rmdot_product_1x2(Out+h*n, In0+h*k, In1, k, n, n); 
				}
				return;
			}
			case 4: {
				for (h = 0; h<m; h++) {
					replicate_1x4(Out+h*n, n, In2+h*In2s, (U)1, (U)0);
					rmdot_product_1x4(Out+h*n, In0+h*k, In1, k, n, n); 
				}
				return;
			}
			case 8: {
				for (h = 0; h<m; h++) {
					replicate_1x8(Out+h*n, n, In2+h*In2s, (U)1, (U)0);
					rmdot_product_1x8(Out+h*n, In0+h*k, In1, k, n, n); 
				}
				return;
			}
			case 16: {
				for (h = 0; h<m; h++) {
					replicate_1x16(Out+h*n, n, In2+h*In2s, (U)1, (U)0);
					rmdot_product_1x16(Out+h*n, In0+h*k, In1, k, n, n); 
				}
				return;
			}
			default: {
				for (h = 0; h<m; h++) {
					replicate_1x32(Out+h*n, n, In2+h*In2s, (U)1, (U)0);
					rmdot_product_1x32(Out+h*n, In0+h*k, In1, k, n, n); 
				}
				return;
			}
		}
	}
	else {
		switch (ur) {
			case 1: {
				for (h = 0; h<m; h++) {
					replicate_1x1(Out+h*n, n, In2, (U)1, (U)1);
					rmdot_product_1x1(Out+h*n, In0+h*k, In1, k, n, n); 
				}
				return;
			}
			case 2: {
				for (h = 0; h<m; h++) {
					replicate_1x2(Out+h*n, n, In2, (U)1, (U)1);
					rmdot_product_1x2(Out+h*n, In0+h*k, In1, k, n, n); 
				}
				return;
			}
			case 4: {
				for (h = 0; h<m; h++) {
					replicate_1x4(Out+h*n, n, In2, (U)1, (U)1);
					rmdot_product_1x4(Out+h*n, In0+h*k, In1, k, n, n); 
				}
				return;
			}
			case 8: {
				for (h = 0; h<m; h++) {
					replicate_1x8(Out+h*n, n, In2, (U)1, (U)1);
					rmdot_product_1x8(Out+h*n, In0+h*k, In1, k, n, n); 
				}
				return;
			}
			case 16: {
				for (h = 0; h<m; h++) {
					replicate_1x16(Out+h*n, n, In2, (U)1, (U)1);
					rmdot_product_1x16(Out+h*n, In0+h*k, In1, k, n, n); 
				}
				return;
			}
			default: {
				for (h = 0; h<m; h++) {
					replicate_1x32(Out+h*n, n, In2, (U)1, (U)1);
					rmdot_product_1x32(Out+h*n, In0+h*k, In1, k, n, n); 
				}
				return;
			}
		}
	}
}

//------------------------------------------------------------------------------
template <class T, class U>
static inline void rmdot_product_2 (T* Out, 
																		T* In0, 
																		T* In1, 
																		volatile const U m, 
																		volatile const U k,
																		volatile const U n,
																		T* In2 = 0,
																		volatile const bool _In2Tr = false,
																		volatile U UR = 0) { 

	register U ur = set_unroll(k >> 2, UR);
	register U h;
	volatile const U In2s = In2 ? (U)1 : (U)0;
	volatile const bool In2Tr = In2s ? false : _In2Tr;

	U mod, g;

	if (!In2Tr) {
		switch (ur) {
			case 1: {
				h = 0;
				mod = m & 1;
				for (g = m >> 1; g; g--, h += 2) {
					replicate_2x1(Out+h*n, n, In2+h*In2s, n, In2s, (U)1, (U)0);
					rmdot_product_2x1(Out+h*n, In0+h*k, In1, k, n, n); 
				}
				if (mod) {
					replicate_1x1(Out+h*n, n, In2+h*In2s, (U)1, (U)0);
					rmdot_product_1x1(Out+h*n, In0+h*k, In1, k, n, n); 
				}
				return;
			}
			case 2: {
				h = 0;
				mod = m & 1;
				for (g = m >> 1; g; g--, h += 2) {
					replicate_2x2(Out+h*n, n, In2+h*In2s, n, In2s, (U)1, (U)0);
					rmdot_product_2x2(Out+h*n, In0+h*k, In1, k, n, n); 
				}
				if (mod) {
					replicate_1x2(Out+h*n, n, In2+h*In2s, (U)1, (U)0);
					rmdot_product_1x2(Out+h*n, In0+h*k, In1, k, n, n); 
				}
				return;
			}
			case 4: {
				h = 0;
				mod = m & 1;
				for (g = m >> 1; g; g--, h += 2) {
					replicate_2x4(Out+h*n, n, In2+h*In2s, n, In2s, (U)1, (U)0);
					rmdot_product_2x4(Out+h*n, In0+h*k, In1, k, n, n); 
				}
				if (mod) {
					replicate_1x4(Out+h*n, n, In2+h*In2s, (U)1, (U)0);
					rmdot_product_1x4(Out+h*n, In0+h*k, In1, k, n, n); 
				}
				return;
			}
			case 8: {
				h = 0;
				mod = m & 1;
				for (g = m >> 1; g; g--, h += 2) {
					replicate_2x8(Out+h*n, n, In2+h*In2s, n, In2s, (U)1, (U)0);
					rmdot_product_2x8(Out+h*n, In0+h*k, In1, k, n, n); 
				}
				if (mod) {
					replicate_1x8(Out+h*n, n, In2+h*In2s, (U)1, (U)0);
					rmdot_product_1x8(Out+h*n, In0+h*k, In1, k, n, n); 
				}
				return;
			}
			case 16: {
				h = 0;
				mod = m & 1;
				for (g = m >> 1; g; g--, h += 2) {
					replicate_2x16(Out+h*n, n, In2+h*In2s, n, In2s, (U)1, (U)0);
					rmdot_product_2x16(Out+h*n, In0+h*k, In1, k, n, n); 
				}
				if (mod) {
					replicate_1x16(Out+h*n, n, In2+h*In2s, (U)1, (U)0);
					rmdot_product_1x16(Out+h*n, In0+h*k, In1, k, n, n); 
				}
				return;
			}
			default: {
				h = 0;
				mod = m & 1;
				for (g = m >> 1; g; g--, h += 2) {
					replicate_2x32(Out+h*n, n, In2+h*In2s, n, In2s, (U)1, (U)0);
					rmdot_product_2x32(Out+h*n, In0+h*k, In1, k, n, n); 
				}
				if (mod) {
					replicate_1x32(Out+h*n, n, In2+h*In2s, (U)1, (U)0);
					rmdot_product_1x32(Out+h*n, In0+h*k, In1, k, n, n); 
				}
				return;
			}
		}
	}
	else {
	}
}

//------------------------------------------------------------------------------
template <class T, class U>
static inline void rmdot_product_4 (T* Out, 
																		T* In0, 
																		T* In1, 
																		volatile const U m, 
																		volatile const U k,
																		volatile const U n, 
																		T* In2 = 0,
																		volatile const bool In2Tr = false,
																		volatile U UR = 0) { 

	register U ur = set_unroll(k >> 2, UR);
	register U h;
	volatile const U In2s = In2 ? (U)1 : (U)0;
	U mod, g;

	switch (ur) {
		case 1: {
			h = 0;
			mod = m & 3;
			for (g = m >> 2; g; g--, h += 4) {
				replicate_4x1(Out+h*n, n, In2+h*In2s, n, In2s, (U)1, (U)0);
				rmdot_product_4x1(Out+h*n, In0+h*k, In1, k, n, n); 
			}
			if (mod > 1) {
				replicate_2x1(Out+h*n, n, In2+h*In2s, n, In2s, (U)1, (U)0);
				rmdot_product_2x1(Out+h*n, In0+h*k, In1, k, n, n); 
				mod &= 1;
				h += 2;
			}
			if (mod) {
				replicate_1x1(Out+h*n, n, In2+h*In2s, (U)1, (U)0);
				rmdot_product_1x1(Out+h*n, In0+h*k, In1, k, n, n); 
			}
			return;
		}
		case 2: {
			h = 0;
			mod = m & 3;
			for (g = m >> 2; g; g--, h += 4) {
				replicate_4x2(Out+h*n, n, In2+h*In2s, n, In2s, (U)1, (U)0);
				rmdot_product_4x2(Out+h*n, In0+h*k, In1, k, n, n); 
			}
			if (mod > 1) {
				replicate_2x2(Out+h*n, n, In2+h*In2s, n, In2s, (U)1, (U)0);
				rmdot_product_2x2(Out+h*n, In0+h*k, In1, k, n, n); 
				mod &= 1;
				h += 2;
			}
			if (mod) {
				replicate_1x2(Out+h*n, n, In2+h*In2s, (U)1, (U)0);
				rmdot_product_1x2(Out+h*n, In0+h*k, In1, k, n, n); 
			}
			return;
		}
		case 4: {
			h = 0;
			mod = m & 3;
			for (g = m >> 2; g; g--, h += 4) {
				replicate_4x4(Out+h*n, n, In2+h*In2s, n, In2s, (U)1, (U)0);
				rmdot_product_4x4(Out+h*n, In0+h*k, In1, k, n, n); 
			}
			if (mod > 1) {
				replicate_2x4(Out+h*n, n, In2+h*In2s, n, In2s, (U)1, (U)0);
				rmdot_product_2x4(Out+h*n, In0+h*k, In1, k, n, n); 
				mod &= 1;
				h += 2;
			}
			if (mod) {
				replicate_1x4(Out+h*n, n, In2+h*In2s, (U)1, (U)0);
				rmdot_product_1x4(Out+h*n, In0+h*k, In1, k, n, n); 
			}
			return;
		}
		case 8: {
			h = 0;
			mod = m & 3;
			for (g = m >> 2; g; g--, h += 4) {
				replicate_4x8(Out+h*n, n, In2+h*In2s, n, In2s, (U)1, (U)0);
				rmdot_product_4x8(Out+h*n, In0+h*k, In1, k, n, n); 
			}
			if (mod > 1) {
				replicate_2x8(Out+h*n, n, In2+h*In2s, n, In2s, (U)1, (U)0);
				rmdot_product_2x8(Out+h*n, In0+h*k, In1, k, n, n); 
				mod &= 1;
				h += 2;
			}
			if (mod) {
				replicate_1x8(Out+h*n, n, In2+h*In2s, (U)1, (U)0);
				rmdot_product_1x8(Out+h*n, In0+h*k, In1, k, n, n); 
			}
			return;
		}
		case 16: {
			h = 0;
			mod = m & 3;
			for (g = m >> 2; g; g--, h += 4) {
				replicate_4x16(Out+h*n, n, In2+h*In2s, n, In2s, (U)1, (U)0);
				rmdot_product_4x16(Out+h*n, In0+h*k, In1, k, n, n); 
			}
			if (mod > 1) {
				replicate_2x16(Out+h*n, n, In2+h*In2s, n, In2s, (U)1, (U)0);
				rmdot_product_2x16(Out+h*n, In0+h*k, In1, k, n, n); 
				mod &= 1;
				h += 2;
			}
			if (mod) {
				replicate_1x16(Out+h*n, n, In2+h*In2s, (U)1, (U)0);
				rmdot_product_1x16(Out+h*n, In0+h*k, In1, k, n, n); 
			}
			return;
		}
		case 32: {
			h = 0;
			mod = m & 3;
			for (g = m >> 2; g; g--, h += 4) {
				replicate_4x32(Out+h*n, n, In2+h*In2s, n, In2s, (U)1, (U)0);
				rmdot_product_4x32(Out+h*n, In0+h*k, In1, k, n, n); 
			}
			if (mod > 1) {
				replicate_2x32(Out+h*n, n, In2+h*In2s, n, In2s, (U)1, (U)0);
				rmdot_product_2x32(Out+h*n, In0+h*k, In1, k, n, n); 
				mod &= 1;
				h += 2;
			}
			if (mod) {
				replicate_1x32(Out+h*n, n, In2+h*In2s, (U)1, (U)0);
				rmdot_product_1x32(Out+h*n, In0+h*k, In1, k, n, n); 
			}
			return;
		}
		default: {
			h = 0;
			mod = m & 3;
			for (g = m >> 2; g; g--, h += 4) {
				replicate_4x64(Out+h*n, n, In2+h*In2s, n, In2s, (U)1, (U)0);
				rmdot_product_4x64(Out+h*n, In0+h*k, In1, k, n, n); 
			}
			if (mod > 1) {
				replicate_2x64(Out+h*n, n, In2+h*In2s, n, In2s, (U)1, (U)0);
				rmdot_product_2x64(Out+h*n, In0+h*k, In1, k, n, n); 
				mod &= 1;
				h += 2;
			}
			if (mod) {
				replicate_1x64(Out+h*n, n, In2+h*In2s, (U)1, (U)0);
				rmdot_product_1x64(Out+h*n, In0+h*k, In1, k, n, n); 
			}
			return;
		}
	}
}
//------------------------------------------------------------------------------
#endif
