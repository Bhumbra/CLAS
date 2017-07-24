# ifndef _mrdot_product_txx
# define _mrdot_product_txx
//------------------------------------------------------------------------------
# include "clas_unroll.txx"
# include "clas_cache.txx"

//------------------------------------------------------------------------------
# include "_replicate.txx"
# include "_mrdot_product_1.txx"
# include "_mrdot_product_2.txx"
# include "_mrdot_product_4.txx"
# include "_mrdot_product_8.txx"

//------------------------------------------------------------------------------
# define DEF_MRDOT_OUTER_UNROLL_MAX DEF_OUTER_UNROLL_MAX
# define DEF_MRDOT_INNER_UNROLL_MAX DEF_INNER_UNROLL_MAX
# define DEF_MRDOT_OUTER_UNROLL DEF_OUTER_UNROLL
# define DEF_MRDOT_INNER_UNROLL DEF_INNER_UNROLL 

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
																		volatile U In0s = 0, 
																		volatile U In1s = 0, 
																		volatile U U1 = 0) { 

	U h = n;
	switch (U1) {
		case 1: {
			for (; h; h--) {
				mrdot_product_1x1 (Out, In0, In1, m, k, Outs, In0s); 
				Out += OutS;
				In1 += In1s;
			}
			return;
		}
		case 2: {
			for (; h; h--) {
				mrdot_product_1x2 (Out, In0, In1, m, k, Outs, In0s); 
				Out += OutS;
				In1 += In1s;
			}
			return;
		}
		case 4: {
			for (; h; h--) {
				mrdot_product_1x4 (Out, In0, In1, m, k, Outs, In0s); 
				Out += OutS;
				In1 += In1s;
			}
			return;
		}
		case 8: {
			for (; h; h--) {
				mrdot_product_1x8 (Out, In0, In1, m, k, Outs, In0s); 
				Out += OutS;
				In1 += In1s;
			}
			return;
		}
		case 16: {
			for (; h; h--) {
				mrdot_product_1x16(Out, In0, In1, m, k, Outs, In0s); 
				Out += OutS;
				In1 += In1s;
			}
			return;
		}
		default: {
			for (; h; h--) {
				mrdot_product_1x32(Out, In0, In1, m, k, Outs, In0s); 
				Out += OutS;
				In1 += In1s;
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
																		volatile U In0s = 0, 
																		volatile U In1s = 0, 
																		volatile U U1 = 0) { 

	U h = n >> 1;
	U mod = n & 1;
	switch (U1) {
		case 1: { 
			for (; h; h--) {
				mrdot_product_2x1 (Out, In0, In1, m, k, OutS, Outs, In0s, In1s);
				Out += OutS * 2;
				In1 += In1s * 2;
			}
			if (mod) {
				mrdot_product_1x1 (Out, In0, In1, m, k, Outs, In0s);
				Out += OutS;
				In1 += In1s;
			}
			return;
		}
		case 2: {
			for (; h; h--) {
				mrdot_product_2x2 (Out, In0, In1, m, k, OutS, Outs, In0s, In1s);
				Out += OutS * 2;
				In1 += In1s * 2;
			}
			if (mod) {
				mrdot_product_1x2 (Out, In0, In1, m, k, Outs, In0s);
				Out += OutS;
				In1 += In1s;
			}
			return;
		}
		case 4: {
			for (; h; h--) {
				mrdot_product_2x4 (Out, In0, In1, m, k, OutS, Outs, In0s, In1s);
				Out += OutS * 2;
				In1 += In1s * 2;
			}
			if (mod) {
				mrdot_product_1x4 (Out, In0, In1, m, k, Outs, In0s);
				Out += OutS;
				In1 += In1s;
			}
			return;
		}
		case 8: {
			for (; h; h--) {
				mrdot_product_2x8 (Out, In0, In1, m, k, OutS, Outs, In0s, In1s);
				Out += OutS * 2;
				In1 += In1s * 2;
			}
			if (mod) {
				mrdot_product_1x8 (Out, In0, In1, m, k, Outs, In0s);
				Out += OutS;
				In1 += In1s;
			}
			return;
		}
		case 16: {
			for (; h; h--) {
				mrdot_product_2x16(Out, In0, In1, m, k, OutS, Outs, In0s, In1s);
				Out += OutS * 2;
				In1 += In1s * 2;
			}
			if (mod) {
				mrdot_product_1x16(Out, In0, In1, m, k, Outs, In0s);
				Out += OutS;
				In1 += In1s;
			}
			return;
		}
		default: {
			for (; h; h--) {
				mrdot_product_2x32(Out, In0, In1, m, k, OutS, Outs, In0s, In1s);
				Out += OutS * 2;
				In1 += In1s * 2;
			}
			if (mod) {
				mrdot_product_1x32(Out, In0, In1, m, k, Outs, In0s);
				Out += OutS;
				In1 += In1s;
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
																		volatile U In0s = 0, 
																		volatile U In1s = 0, 
																		volatile U U1 = 0) { 

	U h = n >> 2;
	U mod = n & 3;
	switch (U1) {
		case 1: { 
			for (; h; h--) {
				mrdot_product_4x1 (Out, In0, In1, m, k, OutS, Outs, In0s, In1s);
				Out += OutS * 4;
				In1 += In1s * 4;
			}
			if (mod > 1) {
				mrdot_product_2x1 (Out, In0, In1, m, k, OutS, Outs, In0s, In1s);
				Out += OutS * 2;
				In1 += In1s * 2;
				mod &= 1;
			}
			if (mod) {
				mrdot_product_1x1 (Out, In0, In1, m, k, Outs, In0s);
				Out += OutS;
				In1 += In1s;
			}
			return;
		}
		case 2: {
			for (; h; h--) {
				mrdot_product_4x2 (Out, In0, In1, m, k, OutS, Outs, In0s, In1s);
				Out += OutS * 4;
				In1 += In1s * 4;
			}
			if (mod > 1) {
				mrdot_product_2x2 (Out, In0, In1, m, k, OutS, Outs, In0s, In1s);
				Out += OutS * 2;
				In1 += In1s * 2;
				mod &= 1;
			}
			if (mod) {
				mrdot_product_1x2 (Out, In0, In1, m, k, Outs, In0s);
				Out += OutS;
				In1 += In1s;
			}
			return;
		}
		case 4: {
			for (; h; h--) {
				mrdot_product_4x4 (Out, In0, In1, m, k, OutS, Outs, In0s, In1s);
				Out += OutS * 4;
				In1 += In1s;
			}
			if (mod > 1) {
				mrdot_product_2x4 (Out, In0, In1, m, k, OutS, Outs, In0s, In1s);
				Out += OutS * 2;
				In1 += In1s * 2;
				mod &= 1;
			}
			if (mod) {
				mrdot_product_1x4 (Out, In0, In1, m, k, Outs, In0s);
				Out += OutS;
				In1 += In1s;
			}
			return;
		}
		case 8: {
			for (; h; h--) {
				mrdot_product_4x8 (Out, In0, In1, m, k, OutS, Outs, In0s, In1s);
				Out += OutS * 4;
				In1 += In1s * 4;
			}
			if (mod > 1) {
				mrdot_product_2x8 (Out, In0, In1, m, k, OutS, Outs, In0s, In1s);
				Out += OutS * 2;
				In1 += In1s * 2;
				mod &= 1;
			}
			if (mod) {
				mrdot_product_1x8 (Out, In0, In1, m, k, Outs, In0s);
				Out += OutS;
				In1 += In1s;
			}
			return;
		}
		case 16: {
			for (; h; h--) {
				mrdot_product_4x16(Out, In0, In1, m, k, OutS, Outs, In0s, In1s);
				Out += OutS * 4;
				In1 += In1s * 4;
			}
			if (mod > 1) {
				mrdot_product_2x16(Out, In0, In1, m, k, OutS, Outs, In0s, In1s);
				Out += OutS * 2;
				In1 += In1s * 2;
				mod &= 1;
			}
			if (mod) {
				mrdot_product_1x16(Out, In0, In1, m, k, Outs, In0s);
				Out += OutS;
				In1 += In1s;
			}
			return;
		}
		default: {
			for (; h; h--) {
				mrdot_product_4x32(Out, In0, In1, m, k, OutS, Outs, In0s, In1s);
				Out += OutS * 4;
				In1 += In1s * 4;
			}
			if (mod > 1) {
				mrdot_product_2x32(Out, In0, In1, m, k, OutS, Outs, In0s, In1s);
				Out += OutS * 2;
				In1 += In1s * 2;
				mod &= 1;
			}
			if (mod) {
				mrdot_product_1x32(Out, In0, In1, m, k, Outs, In0s);
				Out += OutS;
				In1 += In1s;
			}
			return;
		}
	}
}

//------------------------------------------------------------------------------
template <class T, class U>
static inline void mrdot_product_8 (T* Out, 
																		T* In0, 
																		T* In1, 
																		volatile const U m,
																		volatile const U k,
																		volatile const U n, 
																		volatile const U OutS,
																		volatile const U Outs,
																		volatile U In0s = 0, 
																		volatile U In1s = 0, 
																		volatile U U1 = 0) { 

	U h = n >> 3;
	U mod = n & 7;
	switch (U1) {
		case 1: { 
			for (; h; h--) {
				mrdot_product_8x1 (Out, In0, In1, m, k, OutS, Outs, In0s, In1s);
				Out += OutS * 8;
				In1 += In1s * 8;
			}
			if (mod > 3) {
				mrdot_product_4x1 (Out, In0, In1, m, k, OutS, Outs, In0s, In1s);
				Out += OutS * 4;
				In1 += In1s * 4;
				mod &= 3;
			}
			if (mod > 1) {
				mrdot_product_2x1 (Out, In0, In1, m, k, OutS, Outs, In0s, In1s);
				Out += OutS * 2;
				In1 += In1s * 2;
				mod &= 1;
			}
			if (mod) {
				mrdot_product_1x1 (Out, In0, In1, m, k, Outs, In0s);
				Out += OutS;
				In1 += In1s;
			}
			return;
		}
		case 2: {
			for (; h; h--) {
				mrdot_product_8x2 (Out, In0, In1, m, k, OutS, Outs, In0s, In1s);
				Out += OutS * 8;
				In1 += In1s * 8;
			}
			if (mod > 3) {
				mrdot_product_4x2 (Out, In0, In1, m, k, OutS, Outs, In0s, In1s);
				Out += OutS * 4;
				In1 += In1s * 4;
				mod &= 3;
			}
			if (mod > 1) {
				mrdot_product_2x2 (Out, In0, In1, m, k, OutS, Outs, In0s, In1s);
				Out += OutS * 2;
				In1 += In1s * 2;
				mod &= 1;
			}
			if (mod) {
				mrdot_product_1x2 (Out, In0, In1, m, k, Outs, In0s);
				Out += OutS;
				In1 += In1s;
			}
			return;
		}
		case 4: {
			for (; h; h--) {
				mrdot_product_8x4 (Out, In0, In1, m, k, OutS, Outs, In0s, In1s);
				Out += OutS * 8;
				In1 += In1s * 8;
			}
			if (mod > 3) {
				mrdot_product_4x4 (Out, In0, In1, m, k, OutS, Outs, In0s, In1s);
				Out += OutS * 4;
				In1 += In1s * 4;
				mod &= 3;
			}
			if (mod > 1) {
				mrdot_product_2x4 (Out, In0, In1, m, k, OutS, Outs, In0s, In1s);
				Out += OutS * 2;
				In1 += In1s * 2;
				mod &= 1;
			}
			if (mod) {
				mrdot_product_1x4 (Out, In0, In1, m, k, Outs, In0s);
				Out += OutS;
				In1 += In1s;
			}
			return;
		}
		case 8: {
			for (; h; h--) {
				mrdot_product_8x8 (Out, In0, In1, m, k, OutS, Outs, In0s, In1s);
				Out += OutS * 8;
				In1 += In1s * 8;
			}
			if (mod > 3) {
				mrdot_product_4x8 (Out, In0, In1, m, k, OutS, Outs, In0s, In1s);
				Out += OutS * 4;
				In1 += In1s * 4;
				mod &= 3;
			}
			if (mod > 1) {
				mrdot_product_2x8 (Out, In0, In1, m, k, OutS, Outs, In0s, In1s);
				Out += OutS * 2;
				In1 += In1s * 2;
				mod &= 1;
			}
			if (mod) {
				mrdot_product_1x8 (Out, In0, In1, m, k, Outs, In0s);
				Out += OutS;
				In1 += In1s;
			}
			return;
		}
		case 16: {
			for (; h; h--) {
				mrdot_product_8x16(Out, In0, In1, m, k, OutS, Outs, In0s, In1s);
				Out += OutS * 8;
				In1 += In1s * 8;
			}
			if (mod > 3) {
				mrdot_product_4x16(Out, In0, In1, m, k, OutS, Outs, In0s, In1s);
				Out += OutS * 4;
				In1 += In1s * 4;
				mod &= 3;
			}
			if (mod > 1) {
				mrdot_product_2x16(Out, In0, In1, m, k, OutS, Outs, In0s, In1s);
				Out += OutS * 2;
				In1 += In1s * 2;
				mod &= 1;
			}
			if (mod) {
				mrdot_product_1x16(Out, In0, In1, m, k, Outs, In0s);
				Out += OutS;
				In1 += In1s;
			}
			return;
		}
		default: {
			for (; h; h--) {
				mrdot_product_8x32(Out, In0, In1, m, k, OutS, Outs, In0s, In1s);
				Out += OutS * 8;
				In1 += In1s * 8;
			}
			if (mod > 3) {
				mrdot_product_4x32(Out, In0, In1, m, k, OutS, Outs, In0s, In1s);
				Out += OutS * 4;
				In1 += In1s * 4;
				mod &= 3;
			}
			if (mod > 1) {
				mrdot_product_2x32(Out, In0, In1, m, k, OutS, Outs, In0s, In1s);
				Out += OutS * 2;
				In1 += In1s * 2;
				mod &= 1;
			}
			if (mod) {
				mrdot_product_1x32(Out, In0, In1, m, k, Outs, In0s);
				Out += OutS;
				In1 += In1s;
			}
			return;
		}
	}
}

//------------------------------------------------------------------------------
template <class T, class U>
static inline void mrdot_product_0 (T* Out, 
																		T* In0, 
																		T* In1, 
																		volatile const U m,
																		volatile const U k,
																		volatile const U n, 
																		volatile const U OutS,
																		volatile const U Outs,
																		volatile U In0s = 0, 
																		volatile U In1s = 0, 
																		T* In2 = 0,
																		volatile U In2S = 0,
																		volatile U In2s = 0,
																		volatile U U0 = 0,
																		volatile U U1 = 0) { 

	if (In2 != Out) {
		replicate_0(Out, n, m, In2, OutS, In2S, Outs, In2s, U0, U1);
	}
	switch (U0) {
		case 1: {
			return mrdot_product_1(Out, In0, In1, m, k, n, OutS, Outs, In0s, In1s, U1);
		}
		case 2: {
			return mrdot_product_2(Out, In0, In1, m, k, n, OutS, Outs, In0s, In1s, U1);
		}
		case 4: {
			return mrdot_product_4(Out, In0, In1, m, k, n, OutS, Outs, In0s, In1s, U1);
		}
		default: {
			return mrdot_product_8(Out, In0, In1, m, k, n, OutS, Outs, In0s, In1s, U1);
		}
	}
}

//------------------------------------------------------------------------------
template <class T, class U>
static inline void mrdot_product (T* _Out, 
																	T* _In0, 
																	T* _In1, 
																	volatile const U m,
																	volatile const U k,
																	volatile const U n, 
																	volatile const U OutS,
																	volatile const U Outs,
																	volatile U In0s, 
																	volatile U In1s, 
																	T* _In2 = 0,
																	volatile const U In2S = 0,
																	volatile const U In2s = 0,
																	volatile U _U0 = 0,
																	volatile U _U1 = 0) { 

	if (_U0 && _U1) {
		return mrdot_product_0(_Out, _In0, _In1, m, k, n, OutS, Outs, In0s, In1s, _In2, In2S, In2s, _U0, _U1);
	}

	U L = (U)DEF_CACHE_LINE_SIZE/sizeof(T);
	U N = next_aligned_index(_In1, L, n);
	U K = next_aligned_index(_In0, L, k);

	if (!N && !K) {
		return mrdot_product_0(_Out, _In0, _In1, m, k, n, OutS, Outs, In0s, In1s, _In2, In2S, In2s, _U0, _U1);
	}

	U U0 = _U0;
	U U1 = _U1;
	T* Out = _Out;
	T* In0 = _In0;
	T* In1 = _In1;
	T* In2 = _In2;

	if (_U0) {
		U0 = _U0;
	}
	else {
		U0 = n % DEF_MRDOT_OUTER_UNROLL  ? (U)(DEF_MCDOT_OUTER_UNROLL/2) : (U)(DEF_MCDOT_OUTER_UNROLL);
		while (U0 > n) {
			U0 >>= 1;
		}
	}
	if (U0 > DEF_MRDOT_OUTER_UNROLL_MAX) {U0 = DEF_MCDOT_OUTER_UNROLL_MAX;}
	if (_U1) {
		U1 = _U1;
	}
	else {
		U1 = k % DEF_MRDOT_INNER_UNROLL  ? (U)(DEF_MCDOT_INNER_UNROLL/2) : (U)(DEF_MCDOT_INNER_UNROLL);
		while (U1 > k) {
			U1 >>= 1;
		}
	}
	if (U1 > DEF_MRDOT_OUTER_UNROLL_MAX) {U1 = DEF_MCDOT_OUTER_UNROLL_MAX;}
	if (_U0 || !N) {
		if (!K) {
			mrdot_product_0(_Out, _In0, _In1, m, k, n, OutS, Outs, In0s, In1s, In2, In2S, In2s, U0, U1);
			return;
		}
		else {
			mrdot_product_0(Out, In0, In1, m, K, n, OutS, Outs, In0s, In1s, In2, In2S, In2s, U0, U1);
			In0 += K;
			In1 += K;
			mrdot_product_0(Out, In0, In1, m, k-K, n, OutS, Outs, In0s, In1s, Out, In2S, In2s, U0, U1);
			return;
		}
	}
	if (_U1 || !K) {
		if (!N) {
			mrdot_product_0(_Out, _In0, _In1, m, k, n, OutS, Outs, In0s, In1s, In2, In2S, In2s, U0, U1);
			return;
		}
		else {
			mrdot_product_0(Out, In0, In1, m, k, N, OutS, Outs, In0s, In1s, In2, In2S, In2s, U0, U1);
			Out += N * OutS;
			In1 += N * In1s;
			In2 += N * In2S;
			mrdot_product_0(Out, In0, In1, m, k, n-N, OutS, Outs, In0s, In1s, In2, In2S, In2s, U0, U1);
			return;
		}
	}

	if (N) {
		if (K) {
			mrdot_product_0(Out, In0, In1, m, K, N, OutS, Outs, In0s, In1s, In2, In2S, In2s, U0, U1);
			In0 += K;
			In1 += K;
			mrdot_product_0(Out, In0, In1, m, k-K, N, OutS, Outs, In0s, In1s, Out, In2S, In2s, U0, U1);
		}
		else {
			mrdot_product_0(Out, In0, In1, m, k, N, OutS, Outs, In0s, In1s, In2, In2S, In2s, U0, U1);
		}
		Out = _Out + N * OutS;
		In0 = _In0;
		In1 = _In1 + N * In1s;
		In2 = _In2 + N * In2S;
	}
	if (K) {
		mrdot_product_0(Out, In0, In1, m, K, n-N, OutS, Outs, In0s, In1s, In2, In2S, In2s, U0, U1);
		In0 += K;
		In1 += K;
		mrdot_product_0(Out, In0, In1, m, k-K, n-N, OutS, Outs, In0s, In1s, Out, In2S, In2s, U0, U1);
	}
	else {
		mrdot_product_0(Out, In0, In1, m, k-K, n-N, OutS, Outs, In0s, In1s, In2, In2S, In2s, U0, U1);
	}
}

//------------------------------------------------------------------------------
#endif

