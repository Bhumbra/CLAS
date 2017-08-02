# ifndef _vmdot_product_txx
# define _vmdot_product_txx
//------------------------------------------------------------------------------
# include "clas_defs.h"
# include "clas_cache.txx"
# include "clas_unroll.txx"
 
//------------------------------------------------------------------------------
# ifdef HAVE_ARCHITECTURE
extern "C" {
	# include "vmdot_product_double.c"
}
# else
extern "C" {
	# include "vmdot_product_double.h"
}
# endif

//------------------------------------------------------------------------------
# include "_replicate.txx"
# include "_vmdot_product_1.txx"
# include "_vmdot_product_2.txx"
# include "_vmdot_product_4.txx"
# include "_vmdot_product_8.txx"
# include "_vmdot_product_m.txx"

//------------------------------------------------------------------------------
# define DEF_VMDOT_OUTER_UNROLL_MAX DEF_OUTER_UNROLL_MAX
# define DEF_VMDOT_INNER_UNROLL_MAX DEF_INNER_UNROLL_MAX
# define DEF_VMDOT_OUTER_UNROLL 4 // DEF_OUTER_UNROLL - 8 SSE4 hasn't been coded
# define DEF_VMDOT_INNER_UNROLL DEF_INNER_UNROLL 

//------------------------------------------------------------------------------
template <class T, class U>
static inline void vmdot_product_1 (T* Out, 
																		T* In0, 
																		T* In1, 
																		volatile const U m,
																		volatile const U k,
																		volatile const U n, 
																		volatile U OutS = 0, 
																		volatile U In0S = 0, 
																		volatile U In0s = 0, 
																		volatile U In1s = 0, 
																		volatile U U1 = 0) { 
	U h = m;
	switch (U1) {
		case 1: {
			for (; h; h--) {
				vmdot_product_1x1 (Out, In0, In1, k, n, In0s, In1s); 
				Out += OutS;
				In0 += In0S;
			}
			return;
		}
		case 2: {
			for (; h; h--) {
				vmdot_product_1x2 (Out, In0, In1, k, n, In0s, In1s); 
				Out += OutS;
				In0 += In0S;
			}
			return;
		}
		case 4: {
			for (; h; h--) {
				vmdot_product_1x4 (Out, In0, In1, k, n, In0s, In1s); 
				Out += OutS;
				In0 += In0S;
			}
			return;
		}
		case 8: {
			for (; h; h--) {
				vmdot_product_1x8 (Out, In0, In1, k, n, In0s, In1s); 
				Out += OutS;
				In0 += In0S;
			}
			return;
		}
		case 16: {
			for (; h; h--) {
				vmdot_product_1x16(Out, In0, In1, k, n, In0s, In1s); 
				Out += OutS;
				In0 += In0S;
			}
			return;
		}
		case 32: {
			for (; h; h--) {
				vmdot_product_1x32(Out, In0, In1, k, n, In0s, In1s); 
				Out += OutS;
				In0 += In0S;
			}
			return;
		}
		default: {
			vmdot_product_1x1x1(Out, In0, In1, m, k, n, OutS, In0S, In0s, In1s);
			return;
		}
	}
}

//------------------------------------------------------------------------------
template <class T, class U>
static inline void vmdot_product_2 (T* Out, 
																		T* In0, 
																		T* In1, 
																		volatile const U m, 
																		volatile const U k,
																		volatile const U n,
																		volatile U OutS = 0, 
																		volatile U In0S = 0, 
																		volatile U In0s = 0, 
																		volatile U In1s = 0, 
																		volatile U U1 = 0) { 
	U h = m >> 1; U mod = m & 1;
	switch (U1) {
		case 1: {
			for (; h; h--) {
				vmdot_product_2x1 (Out, In0, In1, k, n, In0S, In0s, In1s); 
				Out += OutS * 2;
				In0 += In0S * 2;
			}
			if (mod) {
				vmdot_product_1x1 (Out, In0, In1, k, n, In0s, In1s); 
				Out += OutS;
				In0 += In0S;
			}
			return;
		}
		case 2: {
			for (; h; h--) {
				vmdot_product_2x2 (Out, In0, In1, k, n, In0S, In0s, In1s); 
				Out += OutS * 2;
				In0 += In0S * 2;
			}
			if (mod) {
				vmdot_product_1x2 (Out, In0, In1, k, n, In0s, In1s); 
				Out += OutS;
				In0 += In0S;
			}
			return;
		}
		case 4: {
			for (; h; h--) {
				vmdot_product_2x4 (Out, In0, In1, k, n, In0S, In0s, In1s); 
				Out += OutS * 2;
				In0 += In0S * 2;
			}
			if (mod) {
				vmdot_product_1x4 (Out, In0, In1, k, n, In0s, In1s); 
				Out += OutS;
				In0 += In0S;
			}
			return;
		}
		case 8: {
			for (; h; h--) {
				vmdot_product_2x8 (Out, In0, In1, k, n, In0S, In0s, In1s); 
				Out += OutS * 2;
				In0 += In0S * 2;
			}
			if (mod) {
				vmdot_product_1x8 (Out, In0, In1, k, n, In0s, In1s); 
				Out += OutS;
				In0 += In0S;
			}
			return;
		}
		case 16: {
			for (; h; h--) {
				vmdot_product_2x16(Out, In0, In1, k, n, In0S, In0s, In1s); 
				Out += OutS * 2;
				In0 += In0S * 2;
			}
			if (mod) {
				vmdot_product_1x16(Out, In0, In1, k, n, In0s, In1s); 
				Out += OutS;
				In0 += In0S;
			}
			return;
		}
		case 32: {
			for (; h; h--) {
				vmdot_product_2x32(Out, In0, In1, k, n, In0S, In0s, In1s); 
				Out += OutS * 2;
				In0 += In0S * 2;
			}
			if (mod) {
				vmdot_product_1x32(Out, In0, In1, k, n, In0s, In1s); 
				Out += OutS;
				In0 += In0S;
			}
			return;
		}
		default: {
			vmdot_product_2x2x2(Out, In0, In1, m, k, n, OutS, In0S, In0s, In1s);
			return;
		}
	}
}

//------------------------------------------------------------------------------
template <class T, class U>
static inline void vmdot_product_3 (T* Out, 
																		T* In0, 
																		T* In1, 
																		volatile const U m, 
																		volatile const U k,
																		volatile const U n,
																		volatile U OutS = 0, 
																		volatile U In0S = 0, 
																		volatile U In0s = 0, 
																		volatile U In1s = 0, 
																		volatile U U1 = 0) { 
	U g, h; 

	switch (U1) {
		case 1: {
			for (h = m; h; h--) {
				vmdot_product_1x1x1(Out, In0, In1, k, n, In0s, In1s); 
				Out += OutS;
				In0 += In0S;
			}
			return;
		}
		case 2: {
			g = m & 1;
			for (h = m >> 1; h; h--) {
				vmdot_product_2x2x2(Out, In0, In1, k, n, In0S, In0s, In1s); 
				Out += OutS * 2;
				In0 += In0S * 2;
			}
			if (g) {
				vmdot_product_1x1x1(Out, In0, In1, k, n, In0s, In1s); 
				Out += OutS;
				In0 += In0S;
			}
			return;
		}
		default: {
			g = m & 3;
			for (h == m >> 2; h; h--) {
				vmdot_product_4x4x4(Out, In0, In1, k, n, In0S, In0s, In1s); 
				Out += OutS * 4;
				In0 += In0S * 4;
			}
			if (g > 1) {
				vmdot_product_2x2x2(Out, In0, In1, k, n, In0S, In0s, In1s); 
				Out += OutS * 2;
				In0 += In0S * 2;
				g &= 1;
			}
			if (g) {
				vmdot_product_1x1x1(Out, In0, In1, k, n, In0S, In1s); 
				Out += OutS;
				In0 += In0S;
			}
			return;
		}
	}
}
//------------------------------------------------------------------------------
template <class T, class U>
static inline void vmdot_product_4 (T* Out, 
																		T* In0, 
																		T* In1, 
																		volatile const U m, 
																		volatile const U k,
																		volatile const U n,
																		volatile U OutS = 0, 
																		volatile U In0S = 0, 
																		volatile U In0s = 0, 
																		volatile U In1s = 0, 
																		volatile U U1 = 0) { 
	U h = m >> 2;
	U mod = m & 3;
	switch (U1) {
		case 1: {
			for (; h; h--) {
				vmdot_product_4x1 (Out, In0, In1, k, n, In0S, In0s, In1s); 
				Out += OutS * 4;
				In0 += In0S * 4;
			}
			if (mod > 1) {
				vmdot_product_2x1 (Out, In0, In1, k, n, In0S, In0s, In1s); 
				Out += OutS * 2;
				In0 += In0S * 2;
				mod &= 1;
			}
			if (mod) {
				vmdot_product_1x1 (Out, In0, In1, k, n, In0s, In1s); 
				Out += OutS;
				In0 += In0S;
			}
			return;
		}
		case 2: {
			for (; h; h--) {
				vmdot_product_4x2 (Out, In0, In1, k, n, In0S, In0s, In1s); 
				Out += OutS * 4;
				In0 += In0S * 4;
			}
			if (mod > 1) {
				vmdot_product_2x2 (Out, In0, In1, k, n, In0S, In0s, In1s); 
				Out += OutS * 2;
				In0 += In0S * 2;
				mod &= 1;
			}
			if (mod) {
				vmdot_product_1x2 (Out, In0, In1, k, n, In0s, In1s); 
				Out += OutS;
				In0 += In0S;
			}
			return;
		}
		case 4: {
			for (; h; h--) {
				vmdot_product_4x4 (Out, In0, In1, k, n, In0S, In0s, In1s); 
				Out += OutS * 4;
				In0 += In0S * 4;
			}
			if (mod > 1) {
				vmdot_product_2x4 (Out, In0, In1, k, n, In0S, In0s, In1s); 
				Out += OutS * 2;
				In0 += In0S * 2;
				mod &= 1;
			}
			if (mod) {
				vmdot_product_1x4 (Out, In0, In1, k, n, In0s, In1s); 
				Out += OutS;
				In0 += In0S;
			}
			return;
		}
		case 8: {
			for (; h; h--) {
				vmdot_product_4x8 (Out, In0, In1, k, n, In0S, In0s, In1s); 
				Out += OutS * 4;
				In0 += In0S * 4;
			}
			if (mod > 1) {
				vmdot_product_2x8 (Out, In0, In1, k, n, In0S, In0s, In1s); 
				Out += OutS * 2;
				In0 += In0S * 2;
				mod &= 1;
			}
			if (mod) {
				vmdot_product_1x8 (Out, In0, In1, k, n, In0s, In1s); 
				Out += OutS;
				In0 += In0S;
			}
			return;
		}
		case 16: {
			for (; h; h--) {
				vmdot_product_4x16(Out, In0, In1, k, n, In0S, In0s, In1s); 
				Out += OutS * 4;
				In0 += In0S * 4;
			}
			if (mod > 1) {
				vmdot_product_2x16(Out, In0, In1, k, n, In0S, In0s, In1s); 
				Out += OutS * 2;
				In0 += In0S * 2;
				mod &= 1;
			}
			if (mod) {
				vmdot_product_1x16(Out, In0, In1, k, n, In0s, In1s); 
				Out += OutS;
				In0 += In0S;
			}
			return;
		}
		case 32: {
			for (; h; h--) {
				vmdot_product_4x32(Out, In0, In1, k, n, In0S, In0s, In1s); 
				Out += OutS * 4;
				In0 += In0S * 4;
			}
			if (mod > 1) {
				vmdot_product_2x32(Out, In0, In1, k, n, In0S, In0s, In1s); 
				Out += OutS * 2;
				In0 += In0S * 2;
				mod &= 1;
			}
			if (mod) {
				vmdot_product_1x32(Out, In0, In1, k, n, In0s, In1s); 
				Out += OutS;
				In0 += In0S;
			}
			return;
		}
		default: {
			vmdot_product_4x4x4(Out, In0, In1, m, k, n, OutS, In0S, In0s, In1s);
			return;
		}
	}
}

//------------------------------------------------------------------------------
template <class T, class U>
static inline void vmdot_product_8 (T* Out, 
																		T* In0, 
																		T* In1, 
																		volatile const U m, 
																		volatile const U k,
																		volatile const U n,
																		volatile U OutS = 0, 
																		volatile U In0S = 0, 
																		volatile U In0s = 0, 
																		volatile U In1s = 0, 
																		volatile U U1 = 0) { 
	U h = m >> 3;
	U mod = m & 7;
	switch (U1) {
		case 1: {
			for (; h; h--) {
				vmdot_product_8x1 (Out, In0, In1, k, n, In0S, In0s, In1s); 
				Out += OutS * 8;
				In0 += In0S * 8;
			}
			if (mod > 3) {
				vmdot_product_4x1 (Out, In0, In1, k, n, In0S, In0s, In1s); 
				Out += OutS * 4;
				In0 += In0S * 4;
				mod &= 3;
			}
			if (mod > 1) {
				vmdot_product_2x1 (Out, In0, In1, k, n, In0S, In0s, In1s); 
				Out += OutS * 2;
				In0 += In0S * 2;
				mod &= 1;
			}
			if (mod) {
				vmdot_product_1x1 (Out, In0, In1, k, n, In0s, In1s); 
				Out += OutS;
				In0 += In0S;
			}
			return;
		}
		case 2: {
			for (; h; h--) {
				vmdot_product_8x2 (Out, In0, In1, k, n, In0S, In0s, In1s); 
				Out += OutS * 8;
				In0 += In0S * 8;
			}
			if (mod > 3) {
				vmdot_product_4x2 (Out, In0, In1, k, n, In0S, In0s, In1s); 
				Out += OutS * 4;
				In0 += In0S * 4;
				mod &= 3;
			}
			if (mod > 1) {
				vmdot_product_2x2 (Out, In0, In1, k, n, In0S, In0s, In1s); 
				Out += OutS * 2;
				In0 += In0S * 2;
				mod &= 1;
			}
			if (mod) {
				vmdot_product_1x2 (Out, In0, In1, k, n, In0s, In1s); 
				Out += OutS;
				In0 += In0S;
			}
			return;
		}
		case 4: {
			for (; h; h--) {
				vmdot_product_8x4 (Out, In0, In1, k, n, In0S, In0s, In1s); 
				Out += OutS * 8;
				In0 += In0S * 8;
			}
			if (mod > 3) {
				vmdot_product_4x4 (Out, In0, In1, k, n, In0S, In0s, In1s); 
				Out += OutS * 4;
				In0 += In0S * 4;
				mod &= 3;
			}
			if (mod > 1) {
				vmdot_product_2x4 (Out, In0, In1, k, n, In0S, In0s, In1s); 
				Out += OutS * 2;
				In0 += In0S * 2;
				mod &= 1;
			}
			if (mod) {
				vmdot_product_1x4 (Out, In0, In1, k, n, In0s, In1s); 
				Out += OutS;
				In0 += In0S;
			}
			return;
		}
		case 8: {
			for (; h; h--) {
				vmdot_product_8x8 (Out, In0, In1, k, n, In0S, In0s, In1s); 
				Out += OutS * 8;
				In0 += In0S * 8;
			}
			if (mod > 3) {
				vmdot_product_4x8 (Out, In0, In1, k, n, In0S, In0s, In1s); 
				Out += OutS * 4;
				In0 += In0S * 4;
				mod &= 3;
			}
			if (mod > 1) {
				vmdot_product_2x8 (Out, In0, In1, k, n, In0S, In0s, In1s); 
				Out += OutS * 2;
				In0 += In0S * 2;
				mod &= 1;
			}
			if (mod) {
				vmdot_product_1x8 (Out, In0, In1, k, n, In0s, In1s); 
				Out += OutS;
				In0 += In0S;
			}
			return;
		}
		case 16: {
			for (; h; h--) {
				vmdot_product_8x16(Out, In0, In1, k, n, In0S, In0s, In1s); 
				Out += OutS * 8;
				In0 += In0S * 8;
			}
			if (mod > 3) {
				vmdot_product_4x16(Out, In0, In1, k, n, In0S, In0s, In1s); 
				Out += OutS * 4;
				In0 += In0S * 4;
				mod &= 3;
			}
			if (mod > 1) {
				vmdot_product_2x16(Out, In0, In1, k, n, In0S, In0s, In1s); 
				Out += OutS * 2;
				In0 += In0S * 2;
				mod &= 1;
			}
			if (mod) {
				vmdot_product_1x16(Out, In0, In1, k, n, In0s, In1s); 
				Out += OutS;
				In0 += In0S;
			}
			return;
		}
		default: {
			for (; h; h--) {
				vmdot_product_8x32(Out, In0, In1, k, n, In0S, In0s, In1s); 
				Out += OutS * 8;
				In0 += In0S * 8;
			}
			if (mod > 3) {
				vmdot_product_4x32(Out, In0, In1, k, n, In0S, In0s, In1s); 
				Out += OutS * 4;
				In0 += In0S * 4;
				mod &= 3;
			}
			if (mod > 1) {
				vmdot_product_2x32(Out, In0, In1, k, n, In0S, In0s, In1s); 
				Out += OutS * 2;
				In0 += In0S * 2;
				mod &= 1;
			}
			if (mod) {
				vmdot_product_1x32(Out, In0, In1, k, n, In0s, In1s); 
				Out += OutS;
				In0 += In0S;
			}
			return;
		}
	}
}

//------------------------------------------------------------------------------
template <class T, class U>
static inline void vmdot_product_0 (T* Out, 
																		T* In0, 
																		T* In1, 
																		volatile const U m,
																		volatile const U k,
																		volatile const U n, 
																		volatile U OutS = 0, 
																		volatile U In0S = 0, 
																		volatile U In0s = 0, 
																		volatile U In1s = 0, 
																		T* In2 = 0,
																		volatile U In2S = 0, 
																		volatile U In2s = 0, 
																		volatile U U0 = 0,
																		volatile U U1 = 0,
																		volatile U Arch = 0) { 
	if (In2 != Out) {
		replicate_0(Out, m, n, In2, OutS, In2S, (U)1, In2s, U0, U1);
	}

	U s = Arch != 1 ? sizeof(T) : (U)0;
	switch (s) {
		case 8: {
			switch (U0) {
				case 1: {
					return VMDOT_PRODUCT_DOUBLE_1(Out, In0, In1, (uint64_t)m, (uint64_t)k, (uint64_t)n, (uint64_t)OutS, 
																				(uint64_t)In0S, (uint64_t)In0s, (uint64_t)In1s, (uint64_t)U1);
					//return vmdot_product_1(Out, In0, In1, m, k, n, OutS, In0S, In0s, In1s, U1);
				}
				case 2: {
					return VMDOT_PRODUCT_DOUBLE_2(Out, In0, In1, (uint64_t)m, (uint64_t)k, (uint64_t)n, (uint64_t)OutS, 
																				(uint64_t)In0S, (uint64_t)In0s, (uint64_t)In1s, (uint64_t)U1);
					//return vmdot_product_2(Out, In0, In1, m, k, n, OutS, In0S, In0s, In1s, U1);
				}
				case 4: {
					return VMDOT_PRODUCT_DOUBLE_4(Out, In0, In1, (uint64_t)m, (uint64_t)k, (uint64_t)n, (uint64_t)OutS, 
																				(uint64_t)In0S, (uint64_t)In0s, (uint64_t)In1s, (uint64_t)U1);
					//return vmdot_product_4(Out, In0, In1, m, k, n, OutS, In0S, In0s, In1s, U1);
				}
				case 8: {
					return VMDOT_PRODUCT_DOUBLE_8(Out, In0, In1, (uint64_t)m, (uint64_t)k, (uint64_t)n, (uint64_t)OutS, 
																				(uint64_t)In0S, (uint64_t)In0s, (uint64_t)In1s, (uint64_t)U1);
					//return vmdot_product_8(Out, In0, In1, m, k, n, OutS, In0S, In0s, In1s, U1);
				}
				default: { // default to 4
					return VMDOT_PRODUCT_DOUBLE_4(Out, In0, In1, (uint64_t)m, (uint64_t)k, (uint64_t)n, (uint64_t)OutS, 
																				(uint64_t)In0S, (uint64_t)In0s, (uint64_t)In1s, (uint64_t)U1);
					//return vmdot_product_4(Out, In0, In1, m, k, n, OutS, In0S, In0s, In1s, U1);
				}
			}
		}
		default: { 
			switch (U0) {
				case 1: {
					return vmdot_product_1(Out, In0, In1, m, k, n, OutS, In0S, In0s, In1s, U1);
				}
				case 2: {
					return vmdot_product_2(Out, In0, In1, m, k, n, OutS, In0S, In0s, In1s, U1);
				}
				case 4: {
					return vmdot_product_4(Out, In0, In1, m, k, n, OutS, In0S, In0s, In1s, U1);
				}
				case 8: {
					return vmdot_product_8(Out, In0, In1, m, k, n, OutS, In0S, In0s, In1s, U1);
				}
				default: { // default to 4
					return vmdot_product_4(Out, In0, In1, m, k, n, OutS, In0S, In0s, In1s, U1);
				}
			}
		}
	}
}

//------------------------------------------------------------------------------
template <class T, class U>
static inline void vmdot_product (T* Out, 
																	T* In0, 
																	T* In1, 
																	volatile const U m,
																	volatile const U k,
																	volatile const U n, 
																	volatile U OutS = 0, 
																	volatile U In0S = 0, 
																	volatile U In0s = 0, 
																	volatile U In1s = 0, 
																	T* In2 = 0,
																	volatile U In2S = 0, 
																	volatile U In2s = 0, 
																	volatile U _U0 = 0,
																	volatile U _U1 = 0,
																	volatile U Arch = 0) { 
	U U0 = _U0;
	U U1 = _U1;
	U L = (U)DEF_CACHE_LINE_SIZE/sizeof(T);

	if (U0 && U1) {
		return vmdot_product_0(Out, In0, In1, m, k, n, OutS, In0S, In0s, In1s, In2, In2S, In2s, U0, U1, Arch);
	}

	if (!U0) {
		U0 = set_outer_unroll(m, (U)DEF_VMDOT_OUTER_UNROLL);
		if (U0 > DEF_VMDOT_OUTER_UNROLL_MAX) {U0 = DEF_VMDOT_OUTER_UNROLL_MAX;}
	}
	if (!U1) { 
		if (!_U0 && m < 2) {U1 = set_inner_unroll(n, (U)DEF_VMDOT_INNER_UNROLL);}
		if (U1 > DEF_VMDOT_INNER_UNROLL_MAX) {U1 = DEF_VMDOT_INNER_UNROLL_MAX;}
	}

	// Attempt alignment of Out to cache line-size alignment if U1 not entered

	U N = next_aligned_index(Out, L, n);
	if (!N || _U1) {
		return vmdot_product_0(Out, In0, In1, m, k, n, OutS, In0S, In0s, In1s, In2, In2S, In2s, U0, U1, Arch);
	}
	vmdot_product_0(Out, In0, In1, m, k, N, OutS, In0S, In0s, In1s, In2, In2S, In2s, U0, U1, Arch);
	vmdot_product_0(Out+N, In0, In1+N, m, k, n-N, OutS, In0S, In0s, In1s, In2+In2s*N, In2S, In2s, U0, U1, Arch);
}

//------------------------------------------------------------------------------
#endif

