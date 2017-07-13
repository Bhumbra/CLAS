# ifndef _mrdot_product_txx
# define _mrdot_product_txx
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
# include <iostream>
using namespace std;

# include "clas_unroll.txx"
//------------------------------------------------------------------------------
# include "_replicate.txx"
# include "_mrdot_product_1.txx"
# include "_mrdot_product_2.txx"
# include "_mrdot_product_4.txx"

//------------------------------------------------------------------------------
template <class T, class U>
static inline void mrdot_product_1 (T* Out, 
																		T* In0, 
																		T* In1, 
																		volatile const U m,
																		volatile const U k,
																		volatile const U n, 
																		volatile const U OutS,
																		volatile const U Outs,
																		T* In2 = 0,
																		volatile const U In2S = 0,
																		volatile const U In2s = 0,
																		volatile U UR = 0) { 
	register U ur = set_unroll(k >> 2, UR);
	register U h;
	U g, mod;
	switch (ur) {
		case 1: {
			for (h = 0; h<n; h++) {
				replicate_1x1 (Out, m, In2, Outs, In2s);
				mrdot_product_1x1 (Out, In0, In1+h*k, m, k, Outs, k); 
				Out += OutS;
				In2 += In2S;
			}
			return;
		}
		case 2: {
			for (h = 0; h<n; h++) {
				replicate_1x2 (Out, m, In2, Outs, In2s);
				mrdot_product_1x2 (Out, In0, In1+h*k, m, k, Outs, k); 
				Out += OutS;
				In2 += In2S;
			}
			return;
		}
		case 4: {
			for (h = 0; h<n; h++) {
				replicate_1x4 (Out, m, In2, Outs, In2s);
				mrdot_product_1x4 (Out, In0, In1+h*k, m, k, Outs, k); 
				Out += OutS;
				In2 += In2S;
			}
			return;
		}
		case 8: {
			for (h = 0; h<n; h++) {
				replicate_1x8 (Out, m, In2, Outs, In2s);
				mrdot_product_1x8 (Out, In0, In1+h*k, m, k, Outs, k); 
				Out += OutS;
				In2 += In2S;
			}
			return;
		}
		case 16: {
			for (h = 0; h<n; h++) {
				replicate_1x16(Out, m, In2, Outs, In2s);
				mrdot_product_1x16(Out, In0, In1+h*k, m, k, Outs, k); 
				Out += OutS;
				In2 += In2S;
			}
			return;
		}
		default: {
			for (h = 0; h<n; h++) {
				replicate_1x32(Out, m, In2, Outs, In2s);
				mrdot_product_1x32(Out, In0, In1+h*k, m, k, Outs, k); 
				Out += OutS;
				In2 += In2S;
			}
			return;
		}
	}
}

//------------------------------------------------------------------------------
template <class T, class U>
static inline void mrdot_product_2 (T* Out, 
																		T* In0, 
																		T* In1, 
																		volatile const U m,
																		volatile const U k,
																		volatile const U n, 
																		volatile const U OutS,
																		volatile const U Outs,
																		T* In2 = 0,
																		volatile const U In2S = 0,
																		volatile const U In2s = 0,
																		volatile U UR = 0) { 

	register U ur = set_unroll(k >> 2, UR);
	register U h;
	U g, mod;
	switch (ur) {
		case 1: { 
			h = 0;
			mod = n & 1;
			for (g = n >> 1; g; g--, h += 2) {
				replicate_2x1 (Out, m, In2, OutS, In2S, Outs, In2s);
				mrdot_product_2x1 (Out, In0, In1+h*k, m, k, OutS, Outs, k, k);
				Out += OutS * 2;
				In2 += In2S * 2;
			}
			if (mod) {
				replicate_1x1 (Out, m, In2, Outs, In2s);
				mrdot_product_1x1 (Out, In0, In1+h*k, m, k, Outs, k);
				Out += OutS;
				In2 += In2S;
			}
			return;
		}
		case 2: {
			h = 0;
			mod = n & 1;
			for (g = n >> 1; g; g--, h += 2) {
				replicate_2x2 (Out, m, In2, OutS, In2S, Outs, In2s);
				mrdot_product_2x2 (Out, In0, In1+h*k, m, k, OutS, Outs, k, k);
				Out += OutS * 2;
				In2 += In2S * 2;
			}
			if (mod) {
				replicate_1x2 (Out, m, In2, Outs, In2s);
				mrdot_product_1x2 (Out, In0, In1+h*k, m, k, Outs, k);
				Out += OutS;
				In2 += In2S;
			}
			return;
		}
		case 4: {
			h = 0;
			mod = n & 1;
			for (g = n >> 1; g; g--, h += 2) {
				replicate_2x4 (Out, m, In2, OutS, In2S, Outs, In2s);
				mrdot_product_2x4 (Out, In0, In1+h*k, m, k, OutS, Outs, k, k);
				Out += OutS * 2;
				In2 += In2S * 2;
			}
			if (mod) {
				replicate_1x4 (Out, m, In2, Outs, In2s);
				mrdot_product_1x4 (Out, In0, In1+h*k, m, k, Outs, k);
				Out += OutS;
				In2 += In2S;
			}
			return;
		}
		case 8: {
			h = 0;
			mod = n & 1;
			for (g = n >> 1; g; g--, h += 2) {
				replicate_2x8 (Out, m, In2, OutS, In2S, Outs, In2s);
				mrdot_product_2x8 (Out, In0, In1+h*k, m, k, OutS, Outs, k, k);
				Out += OutS * 2;
				In2 += In2S * 2;
			}
			if (mod) {
				replicate_1x8 (Out, m, In2, Outs, In2s);
				mrdot_product_1x8 (Out, In0, In1+h*k, m, k, Outs, k);
				Out += OutS;
				In2 += In2S;
			}
			return;
		}
		case 16: {
			h = 0;
			mod = n & 1;
			for (g = n >> 1; g; g--, h += 2) {
				replicate_2x16(Out, m, In2, OutS, In2S, Outs, In2s);
				mrdot_product_2x16(Out, In0, In1+h*k, m, k, OutS, Outs, k, k);
				Out += OutS * 2;
				In2 += In2S * 2;
			}
			if (mod) {
				replicate_1x16(Out, m, In2, Outs, In2s);
				mrdot_product_1x16(Out, In0, In1+h*k, m, k, Outs, k);
				Out += OutS;
				In2 += In2S;
			}
			return;
		}
		default: {
			h = 0;
			mod = n & 1;
			for (g = n >> 1; g; g--, h += 2) {
				replicate_2x32(Out, m, In2, OutS, In2S, Outs, In2s);
				mrdot_product_2x32(Out, In0, In1+h*k, m, k, OutS, Outs, k, k);
				Out += OutS * 2;
				In2 += In2S * 2;
			}
			if (mod) {
				replicate_1x32(Out, m, In2, Outs, In2s);
				mrdot_product_1x32(Out, In0, In1+h*k, m, k, Outs, k);
				Out += OutS;
				In2 += In2S;
			}
			return;
		}
	}
}

//------------------------------------------------------------------------------
template <class T, class U>
static inline void mrdot_product_4 (T* Out, 
																		T* In0, 
																		T* In1, 
																		volatile const U m,
																		volatile const U k,
																		volatile const U n, 
																		volatile const U OutS,
																		volatile const U Outs,
																		T* In2 = 0,
																		volatile const U In2S = 0,
																		volatile const U In2s = 0,
																		volatile U UR = 0) { 

	register U ur = set_unroll(k >> 2, UR);
	register U h;
	U g, mod;
	switch (ur) {
		case 1: { 
			h = 0;
			mod = n & 3;
			for (g = n >> 2; g; g--, h += 4) {
				replicate_4x1 (Out, m, In2, OutS, In2S, Outs, In2s);
				mrdot_product_4x1 (Out, In0, In1+h*k, m, k, OutS, Outs, k, k);
				Out += OutS * 4;
				In2 += In2S * 4;
			}
			if (mod > 1) {
				replicate_2x1 (Out, m, In2, OutS, In2S, Outs, In2s);
				mrdot_product_2x1 (Out, In0, In1+h*k, m, k, OutS, Outs, k, k);
				Out += OutS * 2;
				In2 += In2S * 2;
				h += 2;
				mod &= 1;
			}
			if (mod) {
				replicate_1x1 (Out, m, In2, Outs, In2s);
				mrdot_product_1x1 (Out, In0, In1+h*k, m, k, Outs, k);
				Out += OutS;
				In2 += In2S;
			}
			return;
		}
		case 2: {
			h = 0;
			mod = n & 3;
			for (g = n >> 2; g; g--, h += 4) {
				replicate_4x2 (Out, m, In2, OutS, In2S, Outs, In2s);
				mrdot_product_4x2 (Out, In0, In1+h*k, m, k, OutS, Outs, k, k);
				Out += OutS * 4;
				In2 += In2S * 4;
			}
			if (mod > 1) {
				replicate_2x2 (Out, m, In2, OutS, In2S, Outs, In2s);
				mrdot_product_2x2 (Out, In0, In1+h*k, m, k, OutS, Outs, k, k);
				Out += OutS * 2;
				In2 += In2S * 2;
				h += 2;
				mod &= 1;
			}
			if (mod) {
				replicate_1x2 (Out, m, In2, Outs, In2s);
				mrdot_product_1x2 (Out, In0, In1+h*k, m, k, Outs, k);
				Out += OutS;
				In2 += In2S;
			}
			return;
		}
		case 4: {
			h = 0;
			mod = n & 3;
			for (g = n >> 2; g; g--, h += 4) {
				replicate_4x4 (Out, m, In2, OutS, In2S, Outs, In2s);
				mrdot_product_4x4 (Out, In0, In1+h*k, m, k, OutS, Outs, k, k);
				Out += OutS * 4;
				In2 += In2S * 4;
			}
			if (mod > 1) {
				replicate_2x4 (Out, m, In2, OutS, In2S, Outs, In2s);
				mrdot_product_2x4 (Out, In0, In1+h*k, m, k, OutS, Outs, k, k);
				Out += OutS * 2;
				In2 += In2S * 2;
				h += 2;
				mod &= 1;
			}
			if (mod) {
				replicate_1x4 (Out, m, In2, Outs, In2s);
				mrdot_product_1x4 (Out, In0, In1+h*k, m, k, Outs, k);
				Out += OutS;
				In2 += In2S;
			}
			return;
		}
		case 8: {
			h = 0;
			mod = n & 3;
			for (g = n >> 2; g; g--, h += 4) {
				replicate_4x8 (Out, m, In2, OutS, In2S, Outs, In2s);
				mrdot_product_4x8 (Out, In0, In1+h*k, m, k, OutS, Outs, k, k);
				Out += OutS * 4;
				In2 += In2S * 4;
			}
			if (mod > 1) {
				replicate_2x8 (Out, m, In2, OutS, In2S, Outs, In2s);
				mrdot_product_2x8 (Out, In0, In1+h*k, m, k, OutS, Outs, k, k);
				Out += OutS * 2;
				In2 += In2S * 2;
				h += 2;
				mod &= 1;
			}
			if (mod) {
				replicate_1x8 (Out, m, In2, Outs, In2s);
				mrdot_product_1x8 (Out, In0, In1+h*k, m, k, Outs, k);
				Out += OutS;
				In2 += In2S;
			}
			return;
		}
		case 16: {
			h = 0;
			mod = n & 3;
			for (g = n >> 2; g; g--, h += 4) {
				replicate_4x16 (Out, m, In2, OutS, In2S, Outs, In2s);
				mrdot_product_4x16(Out, In0, In1+h*k, m, k, OutS, Outs, k, k);
				Out += OutS * 4;
				In2 += In2S * 4;
			}
			if (mod > 1) {
				replicate_2x16(Out, m, In2, OutS, In2S, Outs, In2s);
				mrdot_product_2x16(Out, In0, In1+h*k, m, k, OutS, Outs, k, k);
				Out += OutS * 2;
				In2 += In2S * 2;
				h += 2;
				mod &= 1;
			}
			if (mod) {
				replicate_1x16(Out, m, In2, Outs, In2s);
				mrdot_product_1x16(Out, In0, In1+h*k, m, k, Outs, k);
				Out += OutS;
				In2 += In2S;
			}
			return;
		}
		default: {
			h = 0;
			mod = n & 3;
			for (g = n >> 2; g; g--, h += 4) {
				replicate_4x32(Out, m, In2, OutS, In2S, Outs, In2s);
				mrdot_product_4x32(Out, In0, In1+h*k, m, k, OutS, Outs, k, k);
				Out += OutS * 4;
				In2 += In2S * 4;
			}
			if (mod > 1) {
				replicate_2x32(Out, m, In2, OutS, In2S, Outs, In2s);
				mrdot_product_2x32(Out, In0, In1+h*k, m, k, OutS, Outs, k, k);
				Out += OutS * 2;
				In2 += In2S * 2;
				h += 2;
				mod &= 1;
			}
			if (mod) {
				replicate_1x32(Out, m, In2, Outs, In2s);
				mrdot_product_1x32(Out, In0, In1+h*k, m, k, Outs, k);
				Out += OutS;
				In2 += In2S;
			}
			return;
		}
	}
}

//------------------------------------------------------------------------------
#endif
