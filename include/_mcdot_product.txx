# ifndef _mcdot_product_txx
# define _mcdot_product_txx
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
# include <iostream>
using namespace std;

# include "clas_unroll.txx"
//------------------------------------------------------------------------------
# include "_replicate.txx"
# include "_mcdot_product_1.txx"
# include "_mcdot_product_2.txx"
# include "_mcdot_product_4.txx"

//------------------------------------------------------------------------------
template <class T, class U>
static inline void mcdot_product_1 (T* Out, 
																		T* In0, 
																		T* In1, 
																		volatile const U m,
																		volatile const U k,
																		volatile const U n, 
																		volatile const U OutS,
																		volatile const U Outs,
																		volatile U In1s = 0, 
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
				mcdot_product_1x1 (Out, In0, In1+h, m, k, Outs, k, In1s); 
				Out += OutS;
				In2 += In2S;
			}
			return;
		}
		case 2: {
			for (h = 0; h<n; h++) {
				replicate_1x2 (Out, m, In2, Outs, In2s);
				mcdot_product_1x2 (Out, In0, In1+h, m, k, Outs, k, In1s); 
				Out += OutS;
				In2 += In2S;
			}
			return;
		}
		case 4: {
			for (h = 0; h<n; h++) {
				replicate_1x4 (Out, m, In2, Outs, In2s);
				mcdot_product_1x4 (Out, In0, In1+h, m, k, Outs, k, In1s); 
				Out += OutS;
				In2 += In2S;
			}
			return;
		}
		case 8: {
			for (h = 0; h<n; h++) {
				replicate_1x8 (Out, m, In2, Outs, In2s);
				mcdot_product_1x8 (Out, In0, In1+h, m, k, Outs, k, In1s); 
				Out += OutS;
				In2 += In2S;
			}
			return;
		}
		case 16: {
			for (h = 0; h<n; h++) {
				replicate_1x16(Out, m, In2, Outs, In2s);
				mcdot_product_1x16(Out, In0, In1+h, m, k, Outs, k, In1s); 
				Out += OutS;
				In2 += In2S;
			}
			return;
		}
		default: {
			for (h = 0; h<n; h++) {
				replicate_1x32(Out, m, In2, Outs, In2s);
				mcdot_product_1x32(Out, In0, In1+h, m, k, Outs, k, In1s); 
				Out += OutS;
				In2 += In2S;
			}
			return;
		}
	}
}
//------------------------------------------------------------------------------
template <class T, class U>
static inline void mcdot_product_2 (T* Out, 
																		T* In0, 
																		T* In1, 
																		volatile const U m,
																		volatile const U k,
																		volatile const U n, 
																		volatile const U OutS,
																		volatile const U Outs,
																		volatile U In1s = 0, 
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
				mcdot_product_2x1 (Out, In0, In1+h, m, k, OutS, Outs, k, In1s);
				Out += OutS * 2;
				In2 += In2S * 2;
			}
			if (mod) {
				replicate_1x1 (Out, m, In2, Outs, In2s);
				mcdot_product_1x1 (Out, In0, In1+h, m, k, Outs, k, In1s);
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
				mcdot_product_2x2 (Out, In0, In1+h, m, k, OutS, Outs, k, In1s);
				Out += OutS * 2;
				In2 += In2S * 2;
			}
			if (mod) {
				replicate_1x2 (Out, m, In2, Outs, In2s);
				mcdot_product_1x2 (Out, In0, In1+h, m, k, Outs, k, In1s);
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
				mcdot_product_2x4 (Out, In0, In1+h, m, k, OutS, Outs, k, In1s);
				Out += OutS * 2;
				In2 += In2S * 2;
			}
			if (mod) {
				replicate_1x4 (Out, m, In2, Outs, In2s);
				mcdot_product_1x4 (Out, In0, In1+h, m, k, Outs, k, In1s);
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
				mcdot_product_2x8 (Out, In0, In1+h, m, k, OutS, Outs, k, In1s);
				Out += OutS * 2;
				In2 += In2S * 2;
			}
			if (mod) {
				replicate_1x8 (Out, m, In2, Outs, In2s);
				mcdot_product_1x8 (Out, In0, In1+h, m, k, Outs, k, In1s);
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
				mcdot_product_2x16(Out, In0, In1+h, m, k, OutS, Outs, k, In1s);
				Out += OutS * 2;
				In2 += In2S * 2;
			}
			if (mod) {
				replicate_1x16(Out, m, In2, Outs, In2s);
				mcdot_product_1x16(Out, In0, In1+h, m, k, Outs, k, In1s);
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
				mcdot_product_2x32(Out, In0, In1+h, m, k, OutS, Outs, k, In1s);
				Out += OutS * 2;
				In2 += In2S * 2;
			}
			if (mod) {
				replicate_1x32(Out, m, In2, Outs, In2s);
				mcdot_product_1x32(Out, In0, In1+h, m, k, Outs, k, In1s);
				Out += OutS;
				In2 += In2S;
			}
			return;
		}
	}

}

//------------------------------------------------------------------------------
template <class T, class U>
static inline void mcdot_product_4 (T* Out, 
																		T* In0, 
																		T* In1, 
																		volatile const U m,
																		volatile const U k,
																		volatile const U n, 
																		volatile const U OutS,
																		volatile const U Outs,
																		volatile U In1s = 0, 
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
				mcdot_product_4x1 (Out, In0, In1+h, m, k, OutS, Outs, k, In1s);
				Out += OutS * 4;
				In2 += In2S * 4;
			}
			if (mod > 1) {
				replicate_2x1 (Out, m, In2, OutS, In2S, Outs, In2s);
				mcdot_product_2x1 (Out, In0, In1+h, m, k, OutS, Outs, k, In1s);
				Out += OutS * 2;
				In2 += In2S * 2;
				h += 2;
				mod &= 1;
			}
			if (mod) {
				replicate_1x1 (Out, m, In2, Outs, In2s);
				mcdot_product_1x1 (Out, In0, In1+h, m, k, Outs, k, In1s);
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
				mcdot_product_4x2 (Out, In0, In1+h, m, k, OutS, Outs, k, In1s);
				Out += OutS * 4;
				In2 += In2S * 4;
			}
			if (mod > 1) {
				replicate_2x2 (Out, m, In2, OutS, In2S, Outs, In2s);
				mcdot_product_2x2 (Out, In0, In1+h, m, k, OutS, Outs, k, In1s);
				Out += OutS * 2;
				In2 += In2S * 2;
				h += 2;
				mod &= 1;
			}
			if (mod) {
				replicate_1x2 (Out, m, In2, Outs, In2s);
				mcdot_product_1x2 (Out, In0, In1+h, m, k, Outs, k, In1s);
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
				mcdot_product_4x4 (Out, In0, In1+h, m, k, OutS, Outs, k, In1s);
				Out += OutS * 4;
				In2 += In2S * 4;
			}
			if (mod > 1) {
				replicate_2x4 (Out, m, In2, OutS, In2S, Outs, In2s);
				mcdot_product_2x4 (Out, In0, In1+h, m, k, OutS, Outs, k, In1s);
				Out += OutS * 2;
				In2 += In2S * 2;
				h += 2;
				mod &= 1;
			}
			if (mod) {
				replicate_1x4 (Out, m, In2, Outs, In2s);
				mcdot_product_1x4 (Out, In0, In1+h, m, k, Outs, k, In1s);
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
				mcdot_product_4x8 (Out, In0, In1+h, m, k, OutS, Outs, k, In1s);
				Out += OutS * 4;
				In2 += In2S * 4;
			}
			if (mod > 1) {
				replicate_2x8 (Out, m, In2, OutS, In2S, Outs, In2s);
				mcdot_product_2x8 (Out, In0, In1+h, m, k, OutS, Outs, k, In1s);
				Out += OutS * 2;
				In2 += In2S * 2;
				h += 2;
				mod &= 1;
			}
			if (mod) {
				replicate_1x8 (Out, m, In2, Outs, In2s);
				mcdot_product_1x8 (Out, In0, In1+h, m, k, Outs, k, In1s);
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
				mcdot_product_4x16(Out, In0, In1+h, m, k, OutS, Outs, k, In1s);
				Out += OutS * 4;
				In2 += In2S * 4;
			}
			if (mod > 1) {
				replicate_2x16(Out, m, In2, OutS, In2S, Outs, In2s);
				mcdot_product_2x16(Out, In0, In1+h, m, k, OutS, Outs, k, In1s);
				Out += OutS * 2;
				In2 += In2S * 2;
				h += 2;
				mod &= 1;
			}
			if (mod) {
				replicate_1x16(Out, m, In2, Outs, In2s);
				mcdot_product_1x16(Out, In0, In1+h, m, k, Outs, k, In1s);
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
				mcdot_product_4x32(Out, In0, In1+h, m, k, OutS, Outs, k, In1s);
				Out += OutS * 4;
				In2 += In2S * 4;
			}
			if (mod > 1) {
				replicate_2x32(Out, m, In2, OutS, In2S, Outs, In2s);
				mcdot_product_2x32(Out, In0, In1+h, m, k, OutS, Outs, k, In1s);
				Out += OutS * 2;
				In2 += In2S * 2;
				h += 2;
				mod &= 1;
			}
			if (mod) {
				replicate_1x32(Out, m, In2, Outs, In2s);
				mcdot_product_1x32(Out, In0, In1+h, m, k, Outs, k, In1s);
				Out += OutS;
				In2 += In2S;
			}
			return;
		}
	}
}

//------------------------------------------------------------------------------
// Following functions are convenience functions to allow swapping inputs
//------------------------------------------------------------------------------
template <class T, class U>
static inline void mcdot_product_1 (T* Out, 
																		T* _In0, 
																		T* _In1, 
																		volatile const U _m,
																		volatile const U k,
																		volatile const U _n, 
																		volatile const bool OutCm = false,
																		volatile const bool InpSw = false,
																		T* In2 = 0,
																		volatile U UR = 0) { 

	T *In0, *In1;
	U m, n;
	volatile U OutS, Outs, In1s;
	volatile U In2S, In2s;

	In2S = (U)0;
	In2s = (U)0;

	if (!InpSw) {
		In0 = _In0;
		In1 = _In1;
		m = _m;
		n = _n;
		In1s = _n;
		if (In2) {In2s = (U)1;}
	}
	else {
		In0 = _In1;
		In1 = _In0;
		m = _n;
		n = _m;
		In1s = _m;
		if (In2) {In2S = (U)1;}
	}
	if (!OutCm) {
		OutS = (U)1;
		Outs = _n;
	}
	else {
		OutS = m;
		Outs = (U)1;
	}
	return mcdot_product_1 (Out, In0, In1, m, k, n, OutS, Outs, In1s, In2, In2S, In2s, UR);
}
//------------------------------------------------------------------------------
template <class T, class U>
static inline void mcdot_product_2 (T* Out, 
																		T* _In0, 
																		T* _In1, 
																		volatile const U _m,
																		volatile const U k,
																		volatile const U _n, 
																		volatile const bool OutCm = false,
																		volatile const bool InpSw = false,
																		T* In2 = 0,
																		volatile U UR = 0) { 

	register U ur = set_unroll(k >> 2, UR);
	register U h;
	T *In0, *In1;
	U m, n;
	volatile U OutS, Outs, In1s;
	volatile U In2S, In2s;

	In2S = (U)0;
	In2s = (U)0;

	if (!InpSw) {
		In0 = _In0;
		In1 = _In1;
		m = _m;
		n = _n;
		In1s = _n;
		if (In2) {In2s = (U)1;}
	}
	else {
		In0 = _In1;
		In1 = _In0;
		m = _n;
		n = _m;
		In1s = _m;
		if (In2) {In2S = (U)1;}
	}
	if (!OutCm) {
		OutS = (U)1;
		Outs = _n;
	}
	else {
		OutS = m;
		Outs = (U)1;
	}

	return mcdot_product_2 (Out, In0, In1, m, k, n, OutS, Outs, In1s, In2, In2S, In2s, UR);
}
//------------------------------------------------------------------------------
template <class T, class U>
static inline void mcdot_product_4 (T* Out, 
																		T* _In0, 
																		T* _In1, 
																		volatile const U _m,
																		volatile const U k,
																		volatile const U _n, 
																		volatile const bool OutCm = false,
																		volatile const bool InpSw = false,
																		T* In2 = 0,
																		volatile U UR = 0) { 

	register U ur = set_unroll(k >> 2, UR);
	register U h;
	T *In0, *In1;
	U m, n;
	volatile U OutS, Outs, In1s;
	volatile U In2S, In2s;

	In2S = (U)0;
	In2s = (U)0;

	if (!InpSw) {
		In0 = _In0;
		In1 = _In1;
		m = _m;
		n = _n;
		In1s = _n;
		if (In2) {In2s = (U)1;}
	}
	else {
		In0 = _In1;
		In1 = _In0;
		m = _n;
		n = _m;
		In1s = _m;
		if (In2) {In2S = (U)1;}
	}
	if (!OutCm) {
		OutS = (U)1;
		Outs = _n;
	}
	else {
		OutS = m;
		Outs = (U)1;
	}

	return mcdot_product_4 (Out, In0, In1, m, k, n, OutS, Outs, In1s, In2, In2S, In2s, UR);
}

//------------------------------------------------------------------------------
#endif

