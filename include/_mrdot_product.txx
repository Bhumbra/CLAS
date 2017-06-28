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
																		volatile const bool OutCm = false,
																		T* In2 = 0,
																		volatile U UR = 0) { 

	register U ur = set_unroll(k >> 2, UR);
	register U h;
	volatile const U In2s = In2 ? (U)1 : (U)0;

  if (!OutCm) {
		switch (ur) {
			case 1: {
				for (h = 0; h<n; h++) {
					replicate_1x1 (Out+h, m, In2, n, (U)1);
					mrdot_product_1x1 (Out+h, In0, In1+h*k, m, k, n, k); 
				}
				return;
			}
			case 2: {
				for (h = 0; h<n; h++) {
					replicate_1x2 (Out+h, m, In2, n, (U)1);
					mrdot_product_1x2 (Out+h, In0, In1+h*k, m, k, n, k); 
				}
				return;
			}
			case 4: {
				for (h = 0; h<n; h++) {
					replicate_1x4 (Out+h, m, In2, n, (U)1);
					mrdot_product_1x4 (Out+h, In0, In1+h*k, m, k, n, k); 
				}
				return;
			}
			case 8: {
				for (h = 0; h<n; h++) {
					replicate_1x8 (Out+h, m, In2, n, (U)1);
					mrdot_product_1x8 (Out+h, In0, In1+h*k, m, k, n, k); 
				}
				return;
			}
			case 16: {
				for (h = 0; h<n; h++) {
					replicate_1x16(Out+h, m, In2, n, (U)1);
					mrdot_product_1x16(Out+h, In0, In1+h*k, m, k, n, k); 
				}
				return;
			}
			default: {
				for (h = 0; h<n; h++) {
				  replicate_1x32(Out+h, m, In2, n, (U)1);
					mrdot_product_1x32(Out+h, In0, In1+h*k, m, k, n, k); 
				}
				return;
			}
		}
	}
	else {
		switch (ur) {
			case 1: {
				for (h = 0; h<n; h++) {
				  replicate_1x1 (Out+h*m, m, In2, (U)1, (U)1);
					mrdot_product_1x1 (Out+h*m, In0, In1+h*k, m, k, (U)1, k); 
				}
				return;
			}
			case 2: {
				for (h = 0; h<n; h++) {
				  replicate_1x2 (Out+h*m, m, In2, (U)1, (U)1);
					mrdot_product_1x2 (Out+h*m, In0, In1+h*k, m, k, (U)1, k); 
				}
				return;
			}
			case 4: {
				for (h = 0; h<n; h++) {
				  replicate_1x4 (Out+h*m, m, In2, (U)1, (U)1);
					mrdot_product_1x4 (Out+h*m, In0, In1+h*k, m, k, (U)1, k); 
				}
				return;
			}
			case 8: {
				for (h = 0; h<n; h++) {
				  replicate_1x8 (Out+h*m, m, In2, (U)1, (U)1);
					mrdot_product_1x8 (Out+h*m, In0, In1+h*k, m, k, (U)1, k); 
				}
				return;
			}
			case 16: {
				for (h = 0; h<n; h++) {
				  replicate_1x16(Out+h*m, m, In2, (U)1, (U)1);
					mrdot_product_1x16(Out+h*m, In0, In1+h*k, m, k, (U)1, k); 
				}
				return;
			}
			default: {
				for (h = 0; h<n; h++) {
				  replicate_1x32(Out+h*m, m, In2, (U)1, (U)1);
					mrdot_product_1x32(Out+h*m, In0, In1+h*k, m, k, (U)1, k); 
				}
				return;
			}
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
																		volatile const bool OutCm = false,
																		T* In2 = 0,
																		volatile U UR = 0) { 

	register U ur = set_unroll(k >> 2, UR);
	register U h;
	volatile const U In2s = In2 ? (U)1 : (U)0;
	U mod, g;

  if (!OutCm) {
		switch (ur) {
			case 1: {
				h = 0;
				mod = n & 1;
				for (g = n >> 1; g; g--, h += 2) {
					replicate_2x1 (Out+h, m, In2, (U)1, (U)0, n, (U)1);
					mrdot_product_2x1 (Out+h, In0, In1+h*k, m, k, (U)1, n, k, k);
				}
				if (mod) {
					replicate_1x1 (Out+h, m, In2, n, (U)1);
					mrdot_product_1x1 (Out+h, In0, In1+h*k, m, k, n, k);
				}
				return;
			}
			case 2: {
				h = 0;
				mod = n & 1;
				for (g = n >> 1; g; g--, h += 2) {
					replicate_2x2 (Out+h, m, In2, (U)1, (U)0, n, (U)1);
					mrdot_product_2x2 (Out+h, In0, In1+h*k, m, k, (U)1, n, k, k);
				}
				if (mod) {
					replicate_1x2 (Out+h, m, In2, n, (U)1);
					mrdot_product_1x2 (Out+h, In0, In1+h*k, m, k, n, k);
				}
				return;
			}
			case 4: {
				h = 0;
				mod = n & 1;
				for (g = n >> 1; g; g--, h += 2) {
					replicate_2x4 (Out+h, m, In2, (U)1, (U)0, n, (U)1);
					mrdot_product_2x4 (Out+h, In0, In1+h*k, m, k, (U)1, n, k, k);
				}
				if (mod) {
					replicate_1x4 (Out+h, m, In2, n, (U)1);
					mrdot_product_1x4 (Out+h, In0, In1+h*k, m, k, n, k);
				}
				return;
			}
			case 8: {
				h = 0;
				mod = n & 1;
				for (g = n >> 1; g; g--, h += 2) {
					replicate_2x8 (Out+h, m, In2, (U)1, (U)0, n, (U)1);
					mrdot_product_2x8 (Out+h, In0, In1+h*k, m, k, (U)1, n, k, k);
				}
				if (mod) {
					replicate_1x8 (Out+h, m, In2, n, (U)1);
					mrdot_product_1x8 (Out+h, In0, In1+h*k, m, k, n, k);
				}
				return;
			}
			case 16: {
				h = 0;
				mod = n & 1;
				for (g = n >> 1; g; g--, h += 2) {
					replicate_2x16(Out+h, m, In2, (U)1, (U)0, n, (U)1);
					mrdot_product_2x16(Out+h, In0, In1+h*k, m, k, (U)1, n, k, k);
				}
				if (mod) {
					replicate_1x16(Out+h, m, In2, n, (U)1);
					mrdot_product_1x16(Out+h, In0, In1+h*k, m, k, n, k);
				}
				return;
			}
			default: {
				h = 0;
				mod = n & 1;
				for (g = n >> 1; g; g--, h += 2) {
					replicate_2x32(Out+h, m, In2, (U)1, (U)0, n, (U)1);
					mrdot_product_2x32(Out+h, In0, In1+h*k, m, k, (U)1, n, k, k);
				}
				if (mod) {
					replicate_1x32(Out+h, m, In2, n, (U)1);
					mrdot_product_1x32(Out+h, In0, In1+h*k, m, k, n, k);
				}
				return;
			}
		}
	}
	else {
		switch (ur) {
			case 1: {
				h = 0;
				mod = n & 1;
				for (g = n >> 1; g; g--, h += 2) {
					replicate_2x1 (Out+h*m, m, In2, m, (U)0, (U)1, (U)1);
					mrdot_product_2x1 (Out+h*m, In0, In1+h*k, m, k, m, (U)1, k, k);
				}
				if (mod) {
					replicate_1x1 (Out+h*m, m, In2, (U)1, (U)1);
					mrdot_product_1x1 (Out+h*m, In0, In1+h*k, m, k, (U)1, k); 
				}
				return;
			}
			case 2: {
				h = 0;
				mod = n & 1;
				for (g = n >> 1; g; g--, h += 2) {
					replicate_2x2 (Out+h*m, m, In2, m, (U)0, (U)1, (U)1);
					mrdot_product_2x2 (Out+h*m, In0, In1+h*k, m, k, m, (U)1, k, k);
				}
				if (mod) {
					replicate_1x2 (Out+h*m, m, In2, (U)1, (U)1);
					mrdot_product_1x2 (Out+h*m, In0, In1+h*k, m, k, (U)1, k); 
				}
				return;
			}
			case 4: {
				h = 0;
				mod = n & 1;
				for (g = n >> 1; g; g--, h += 2) {
					replicate_2x4 (Out+h*m, m, In2, m, (U)0, (U)1, (U)1);
					mrdot_product_2x4 (Out+h*m, In0, In1+h*k, m, k, m, (U)1, k, k);
				}
				if (mod) {
					replicate_1x4 (Out+h*m, m, In2, (U)1, (U)1);
					mrdot_product_1x4 (Out+h*m, In0, In1+h*k, m, k, (U)1, k); 
				}
				return;
			}
			case 8: {
				h = 0;
				mod = n & 1;
				for (g = n >> 1; g; g--, h += 2) {
					replicate_2x8 (Out+h*m, m, In2, m, (U)0, (U)1, (U)1);
					mrdot_product_2x8 (Out+h*m, In0, In1+h*k, m, k, m, (U)1, k, k);
				}
				if (mod) {
					replicate_1x8 (Out+h*m, m, In2, (U)1, (U)1);
					mrdot_product_1x8 (Out+h*m, In0, In1+h*k, m, k, (U)1, k); 
				}
				return;
			}
			case 16: {
				h = 0;
				mod = n & 1;
				for (g = n >> 1; g; g--, h += 2) {
					replicate_2x16(Out+h*m, m, In2, m, (U)0, (U)1, (U)1);
					mrdot_product_2x16(Out+h*m, In0, In1+h*k, m, k, m, (U)1, k, k);
				}
				if (mod) {
					replicate_1x16(Out+h*m, m, In2, (U)1, (U)1);
					mrdot_product_1x16(Out+h*m, In0, In1+h*k, m, k, (U)1, k); 
				}
				return;
			}
			default: {
				h = 0;
				mod = n & 1;
				for (g = n >> 1; g; g--, h += 2) {
					replicate_2x32(Out+h*m, m, In2, m, (U)0, (U)1, (U)1);
					mrdot_product_2x32(Out+h*m, In0, In1+h*k, m, k, m, (U)1, k, k);
				}
				if (mod) {
					replicate_1x32(Out+h*m, m, In2, (U)1, (U)1);
					mrdot_product_1x32(Out+h*m, In0, In1+h*k, m, k, (U)1, k); 
				}
				return;
			}
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
																		volatile const bool OutCm = false,
																		T* In2 = 0,
																		volatile U UR = 0) { 

	register U ur = set_unroll(k >> 2, UR);
	register U h;
	volatile const U In2s = In2 ? (U)1 : (U)0;
	U mod, g;

  if (!OutCm) {
		switch (ur) {
			case 1: {
				h = 0;
				mod = n & 3;
				for (g = n >> 2; g; g--, h += 4) {
					replicate_4x1 (Out+h, m, In2, (U)1, (U)0, n, (U)1);
					mrdot_product_4x1 (Out+h, In0, In1+h*k, m, k, (U)1, n, k, k);
				}
				if (mod > 1) {
					replicate_2x1 (Out+h, m, In2, (U)1, (U)0, n, (U)1);
					mrdot_product_2x1 (Out+h, In0, In1+h*k, m, k, (U)1, n, k, k);
					h += 2;
					mod &= 1;
				}
				if (mod) {
					replicate_1x1 (Out+h, m, In2, n, (U)1);
					mrdot_product_1x1 (Out+h, In0, In1+h*k, m, k, n, k);
				}
				return;
			}
			case 2: {
				h = 0;
				mod = n & 3;
				for (g = n >> 2; g; g--, h += 4) {
					replicate_4x2 (Out+h, m, In2, (U)1, (U)0, n, (U)1);
					mrdot_product_4x2 (Out+h, In0, In1+h*k, m, k, (U)1, n, k, k);
				}
				if (mod > 1) {
					replicate_2x2 (Out+h, m, In2, (U)1, (U)0, n, (U)1);
					mrdot_product_2x2 (Out+h, In0, In1+h*k, m, k, (U)1, n, k, k);
					h += 2;
					mod &= 1;
				}
				if (mod) {
					replicate_1x2 (Out+h, m, In2, n, (U)1);
					mrdot_product_1x2 (Out+h, In0, In1+h*k, m, k, n, k);
				}
				return;
			}
			case 4: {
				h = 0;
				mod = n & 3;
				for (g = n >> 2; g; g--, h += 4) {
					replicate_4x4 (Out+h, m, In2, (U)1, (U)0, n, (U)1);
					mrdot_product_4x4 (Out+h, In0, In1+h*k, m, k, (U)1, n, k, k);
				}
				if (mod > 1) {
					replicate_2x4 (Out+h, m, In2, (U)1, (U)0, n, (U)1);
					mrdot_product_2x4 (Out+h, In0, In1+h*k, m, k, (U)1, n, k, k);
					h += 2;
					mod &= 1;
				}
				if (mod) {
					replicate_1x4 (Out+h, m, In2, n, (U)1);
					mrdot_product_1x4 (Out+h, In0, In1+h*k, m, k, n, k);
				}
				return;
			}
			case 8: {
				h = 0;
				mod = n & 3;
				for (g = n >> 2; g; g--, h += 4) {
					replicate_4x8 (Out+h, m, In2, (U)1, (U)0, n, (U)1);
					mrdot_product_4x8 (Out+h, In0, In1+h*k, m, k, (U)1, n, k, k);
				}
				if (mod > 1) {
					replicate_2x8 (Out+h, m, In2, (U)1, (U)0, n, (U)1);
					mrdot_product_2x8 (Out+h, In0, In1+h*k, m, k, (U)1, n, k, k);
					h += 2;
					mod &= 1;
				}
				if (mod) {
					replicate_1x8 (Out+h, m, In2, n, (U)1);
					mrdot_product_1x8 (Out+h, In0, In1+h*k, m, k, n, k);
				}
				return;
			}
			case 16: {
				h = 0;
				mod = n & 3;
				for (g = n >> 2; g; g--, h += 4) {
					replicate_4x16(Out+h, m, In2, (U)1, (U)0, n, (U)1);
					mrdot_product_4x16(Out+h, In0, In1+h*k, m, k, (U)1, n, k, k);
				}
				if (mod > 1) {
					replicate_2x16(Out+h, m, In2, (U)1, (U)0, n, (U)1);
					mrdot_product_2x16(Out+h, In0, In1+h*k, m, k, (U)1, n, k, k);
					h += 2;
					mod &= 1;
				}
				if (mod) {
					replicate_1x16(Out+h, m, In2, n, (U)1);
					mrdot_product_1x16(Out+h, In0, In1+h*k, m, k, n, k);
				}
				return;
			}
			default: {
				h = 0;
				mod = n & 3;
				for (g = n >> 2; g; g--, h += 4) {
					replicate_4x32(Out+h, m, In2, (U)1, (U)0, n, (U)1);
					mrdot_product_4x32(Out+h, In0, In1+h*k, m, k, (U)1, n, k, k);
				}
				if (mod > 1) {
					replicate_2x32(Out+h, m, In2, (U)1, (U)0, n, (U)1);
					mrdot_product_2x32(Out+h, In0, In1+h*k, m, k, (U)1, n, k, k);
					h += 2;
					mod &= 1;
				}
				if (mod) {
					replicate_1x32(Out+h, m, In2, n, (U)1);
					mrdot_product_1x32(Out+h, In0, In1+h*k, m, k, n, k);
				}
				return;
			}
		}
	}
	else {
		switch (ur) {
			case 1: {
				h = 0;
				mod = n & 3;
				for (g = n >> 2; g; g--, h += 4) {
					replicate_4x1 (Out+h*m, m, In2, m, (U)0, (U)1, (U)1);
					mrdot_product_4x1 (Out+h*m, In0, In1+h*k, m, k, m, (U)1, k, k);
				}
				if (mod > 1) {
					replicate_2x1 (Out+h*m, m, In2, m, (U)0, (U)1, (U)1);
					mrdot_product_2x1 (Out+h*m, In0, In1+h*k, m, k, m, (U)1, k, k);
					h += 2;
					mod &= 1;
				}
				if (mod) {
					replicate_1x1 (Out+h*m, m, In2, (U)1, (U)1);
					mrdot_product_1x1 (Out+h*m, In0, In1+h*k, m, k, (U)1, k); 
				}
				return;
			}
			case 2: {
				h = 0;
				mod = n & 3;
				for (g = n >> 2; g; g--, h += 4) {
					replicate_4x2 (Out+h*m, m, In2, m, (U)0, (U)1, (U)1);
					mrdot_product_4x2 (Out+h*m, In0, In1+h*k, m, k, m, (U)1, k, k);
				}
				if (mod > 1) {
					replicate_2x2 (Out+h*m, m, In2, m, (U)0, (U)1, (U)1);
					mrdot_product_2x2 (Out+h*m, In0, In1+h*k, m, k, m, (U)1, k, k);
					h += 2;
					mod &= 1;
				}
				if (mod) {
					replicate_1x2 (Out+h*m, m, In2, (U)1, (U)1);
					mrdot_product_1x2 (Out+h*m, In0, In1+h*k, m, k, (U)1, k); 
				}
				return;
			}
			case 4: {
				h = 0;
				mod = n & 3;
				for (g = n >> 2; g; g--, h += 4) {
					replicate_4x4 (Out+h*m, m, In2, m, (U)0, (U)1, (U)1);
					mrdot_product_4x4 (Out+h*m, In0, In1+h*k, m, k, m, (U)1, k, k);
				}
				if (mod > 1) {
					replicate_2x4 (Out+h*m, m, In2, m, (U)0, (U)1, (U)1);
					mrdot_product_2x4 (Out+h*m, In0, In1+h*k, m, k, m, (U)1, k, k);
					h += 2;
					mod &= 1;
				}
				if (mod) {
					replicate_1x4 (Out+h*m, m, In2, (U)1, (U)1);
					mrdot_product_1x4 (Out+h*m, In0, In1+h*k, m, k, (U)1, k); 
				}
				return;
			}
			case 8: {
				h = 0;
				mod = n & 3;
				for (g = n >> 2; g; g--, h += 4) {
					replicate_4x8 (Out+h*m, m, In2, m, (U)0, (U)1, (U)1);
					mrdot_product_4x8 (Out+h*m, In0, In1+h*k, m, k, m, (U)1, k, k);
				}
				if (mod > 1) {
					replicate_2x8 (Out+h*m, m, In2, m, (U)0, (U)1, (U)1);
					mrdot_product_2x8 (Out+h*m, In0, In1+h*k, m, k, m, (U)1, k, k);
					h += 2;
					mod &= 1;
				}
				if (mod) {
					replicate_1x8 (Out+h*m, m, In2, (U)1, (U)1);
					mrdot_product_1x8 (Out+h*m, In0, In1+h*k, m, k, (U)1, k); 
				}
				return;
			}
			case 16: {
				h = 0;
				mod = n & 3;
				for (g = n >> 2; g; g--, h += 4) {
					replicate_4x16(Out+h*m, m, In2, m, (U)0, (U)1, (U)1);
					mrdot_product_4x16(Out+h*m, In0, In1+h*k, m, k, m, (U)1, k, k);
				}
				if (mod > 1) {
					replicate_2x16(Out+h*m, m, In2, m, (U)0, (U)1, (U)1);
					mrdot_product_2x16(Out+h*m, In0, In1+h*k, m, k, m, (U)1, k, k);
					h += 2;
					mod &= 1;
				}
				if (mod) {
					replicate_1x16(Out+h*m, m, In2, (U)1, (U)1);
					mrdot_product_1x16(Out+h*m, In0, In1+h*k, m, k, (U)1, k); 
				}
				return;
			}
			default: {
				h = 0;
				mod = n & 3;
				for (g = n >> 2; g; g--, h += 4) {
					replicate_4x32(Out+h*m, m, In2, m, (U)0, (U)1, (U)1);
					mrdot_product_4x32(Out+h*m, In0, In1+h*k, m, k, m, (U)1, k, k);
				}
				if (mod > 1) {
					replicate_2x32(Out+h*m, m, In2, m, (U)0, (U)1, (U)1);
					mrdot_product_2x32(Out+h*m, In0, In1+h*k, m, k, m, (U)1, k, k);
					h += 2;
					mod &= 1;
				}
				if (mod) {
					replicate_1x32(Out+h*m, m, In2, (U)1, (U)1);
					mrdot_product_1x32(Out+h*m, In0, In1+h*k, m, k, (U)1, k); 
				}
				return;
			}
		}
	}
}

//------------------------------------------------------------------------------
#endif
