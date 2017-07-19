# ifndef _products_ut_txx
# define _products_ut_txx
//------------------------------------------------------------------------------
# include <math.h>
# include <functional>
# include <algorithm>

//------------------------------------------------------------------------------
# include <iostream>
using namespace std;

# include "clas_unroll.txx"
//------------------------------------------------------------------------------
# include "_ewise_product.txx"
# include "_outer_product.txx"
# include "_inner_product.txx"
# include "_rmdot_product.txx"
# include "_cmdot_product.txx"
# include "_mrdot_product.txx"
# include "_mcdot_product.txx"

//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
/* ewise:
   C = A .* B
*/
template <class T, class U>
static void ewise_product_ut (T* Out, 
															T* In0, 
															T* In1, 
															volatile const U m, 
															volatile const U k, 
															volatile const U Outs = 0,
															volatile const U In0s = 0,
															volatile const U In1s = 0,
															volatile U U1 = 0) { 

	register U u1 = set_unroll((U)sqrt(k), U1);

	switch (u1) {
		case 1: {
			return ewise_product_1(Out, In0, In1, m, k, Outs, In0s, In1s); 
		}
		case 2: {
			return ewise_product_2(Out, In0, In1, m, k, Outs, In0s, In1s); 
		}
		case 4: {
			return ewise_product_4(Out, In0, In1, m, k, Outs, In0s, In1s); 
		}
		case 8: {
			return ewise_product_8(Out, In0, In1, m, k, Outs, In0s, In1s); 
		}
		default: {
			return ewise_product_16(Out, In0, In1, m, k, Outs, In0s, In1s); 
		}
	}
}

//------------------------------------------------------------------------------
/* outer:
   C   = a * b.T
	 C.T = a * b.T
*/
template <class T, class U>
static inline void outer_product_ut(T* Out, 
																		T* In0, 
																		T* In1, 
																		volatile const U m, 
																		volatile const U n,
																		volatile const U Outs = 0,
																		volatile const U In0s = 0,
																		volatile const U In1s = 0,
																		volatile U U1 = 0) { 

	register U u1 = set_unroll((U)sqrt(n), U1);

	// Note for single-threads, U1=2 seems to outperform all others
	
	switch (u1) {
		case 1: {
			return outer_product_1(Out, In0, In1, m, n, Outs, In0s, In1s); 
		}
		case 2: {
			return outer_product_2(Out, In0, In1, m, n, Outs, In0s, In1s); 
		}                                             
		case 4: {                                     
			return outer_product_4(Out, In0, In1, m, n, Outs, In0s, In1s); 
		}                                             
		case 8: {                                     
			return outer_product_8(Out, In0, In1, m, n, Outs, In0s, In1s); 
		}
		case 16: {
			return outer_product_16(Out, In0, In1, m, n, Outs, In0s, In1s); 
		}
		case 32: {
			return outer_product_32(Out, In0, In1, m, n, Outs, In0s, In1s); 
		}
		default: {
			return outer_product_64(Out, In0, In1, m, n, Outs, In0s, In1s); 
		}
	}
}

//------------------------------------------------------------------------------
/* inner:
  c   = a.T * b
	c.T = a.T * b
*/
template <class T, class U>
static inline void inner_product_ut(T* Out, 
																		T* In0, 
																		T* In1, 
																		volatile const U m, 
																		volatile const U k, 
																		volatile const U Outs = 1, 
																		volatile U In0s = 1, 
																		volatile U In1s = 1, 
																		T* In2 = 0,
																		volatile U U1 = 0) {
	register U u1 = set_unroll((U)sqrt(k), U1);
	register U h;

  if (k > 1) {
		if (In0s == 1) {In0s = k;}
		if (In1s == 1) {In1s = k;}
	}

	switch (u1) {
		case 1: {
			replicate_1x1 (Out, m, In2, Outs, (U)1);
			inner_product_1 (Out, In0, In1, m, k, Outs, In0s, In1s); 
			return;
		}
		case 2: {
			replicate_1x2 (Out, m, In2, Outs, (U)1);
			inner_product_2 (Out, In0, In1, m, k, Outs, In0s, In1s); 
			return;
		}
		case 4: {
			replicate_1x4 (Out, m, In2, Outs, (U)1);
			inner_product_4 (Out, In0, In1, m, k, Outs, In0s, In1s); 
			return;
		}
		case 8: {
			replicate_1x8 (Out, m, In2, Outs, (U)1);
			inner_product_8 (Out, In0, In1, m, k, Outs, In0s, In1s); 
			return;
		}
		case 16: {
			replicate_1x16(Out, m, In2, Outs, (U)1);
			inner_product_16(Out, In0, In1, m, k, Outs, In0s, In1s); 
			return;
		}
		default: {
			replicate_1x32(Out, m, In2, Outs, (U)1);
			inner_product_32(Out, In0, In1, m, k, Outs, In0s, In1s); 
			return;
		}
	}
}

//------------------------------------------------------------------------------
/* rmdot:
  c   = a   * B
*/
template <class T, class U>
static inline void rmdot_product_ut(T* Out, 
																		T* In0, 
																		T* In1, 
																		volatile const U m,
																		volatile const U k,
																		volatile const U n, 
																		T* In2 = 0,
																		volatile const bool In2Tr = false,
																		volatile U U0 = 0,
																		volatile U U1 = 0) { 
	switch (U0) {
		case 1: {
			return rmdot_product_1(Out, In0, In1, m, k, n, In2, In2Tr, U1);
		}
		case 2: {
			return rmdot_product_2(Out, In0, In1, m, k, n, In2, In2Tr, U1);
		}
		default: {
			return rmdot_product_4(Out, In0, In1, m, k, n, In2, In2Tr, U1);
		}
	}
}
//------------------------------------------------------------------------------
/* cmdot:
  c   = a.T   * B
*/
template <class T, class U>
static inline void cmdot_product_ut(T* Out, 
																		T* In0, 
																		T* In1, 
																		volatile const U m,
																		volatile const U k,
																		volatile const U n, 
																		T* In2 = 0,
																		volatile const bool In2Tr = false,
																		volatile U In0s = 0,
																		volatile U U0 = 0,
																		volatile U U1 = 0) { 
	switch (U0) {
		case 1: {
			return cmdot_product_1(Out, In0, In1, m, k, n, In2, In2Tr, In0s, U1);
		}
		case 2: {
			return cmdot_product_2(Out, In0, In1, m, k, n, In2, In2Tr, In0s, U1);
		}
		default: {
			return cmdot_product_4(Out, In0, In1, m, k, n, In2, In2Tr, In0s, U1);
		}
	}
}
//------------------------------------------------------------------------------
/* mrdot:
  c or c.t  = A   * b.T
*/
template <class T, class U>
static inline void _mrdot_product_ut (T* Out, 
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
																			volatile U U0 = 0,
																			volatile U U1 = 0) { 
	switch (U0) {
		case 1: {
			return mrdot_product_1(Out, In0, In1, m, k, n, OutS, Outs, In2, In2S, In2s, U1);
		}
		case 2: {
			return mrdot_product_2(Out, In0, In1, m, k, n, OutS, Outs, In2, In2S, In2s, U1);
		}
		default: {
			return mrdot_product_4(Out, In0, In1, m, k, n, OutS, Outs, In2, In2S, In2s, U1);
		}
	}
}
//------------------------------------------------------------------------------
// Convenience function to accommodate tranposed output and swapped inputs
template <class T, class U>
static inline void mrdot_product_ut(T* Out, 
																		T* _In0, 
																		T* _In1, 
																		volatile const U _m,
																		volatile const U k,
																		volatile const U _n, 
																		volatile const bool OutCm = false,
																		volatile const bool InpSw = false,
																		T* In2 = 0,
																		volatile U U0 = 0,
																		volatile U U1 = 0) { 
	T *In0, *In1;
	U m, n;
	volatile U OutS, Outs;
	volatile U In2S, In2s;

	In2S = (U)0;
	In2s = (U)0;

	if (!InpSw) {
		In0 = _In0;
		In1 = _In1;
		m = _m;
		n = _n;
		if (In2) {In2s = (U)1;}
	}
	else {
		In0 = _In1;
		In1 = _In0;
		m = _n;
		n = _m;
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
	return _mrdot_product_ut(Out, In0, In1, m, k, n, OutS, Outs, In2, In2S, In2s, U0, U1);
}

//------------------------------------------------------------------------------
/* mcdot:
  c or c.t = A   * b
*/
template <class T, class U>
static inline void _mcdot_product_ut (T* _Out, 
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
		return mcdot_product_0(_Out, _In0, _In1, m, k, n, OutS, Outs, In0s, In1s, _In2, In2S, In2s, _U0, _U1);
	}

	U N = next_aligned_index(_In1, (U)DEF_OUTER_UNROLL_MAX, n);
	U K = next_aligned_index(_In0, (U)DEF_INNER_UNROLL_MAX, k);

	if (!N && !K) {
		return mcdot_product_0(_Out, _In0, _In1, m, k, n, OutS, Outs, In0s, In1s, _In2, In2S, In2s, _U0, _U1);
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
		U0 = n % DEF_OUTER_UNROLL_MAX  ? (U)(DEF_OUTER_UNROLL_MAX/2) : (U)(DEF_OUTER_UNROLL_MAX);
	}
	if (_U1) {
		U1 = _U1;
	}
	else {
		U1 = k % DEF_INNER_UNROLL_MAX  ? (U)(DEF_INNER_UNROLL_MAX/2) : (U)(DEF_INNER_UNROLL_MAX);
	}
	if (_U0 || !N) {
		if (!K) {
			mcdot_product_0(_Out, _In0, _In1, m, k, n, OutS, Outs, In0s, In1s, In2, In2S, In2s, U0, U1);
			return;
		}
		else {
			mcdot_product_0(Out, In0, In1, m, K, n, OutS, Outs, In0s, In1s, In2, In2S, In2s, U0, U1);
			In0 += K;
			In1 += K * In1s;
			mcdot_product_0(Out, In0, In1, m, k-K, n, OutS, Outs, In0s, In1s, Out, In2S, In2s, U0, U1);
			return;
		}
	}
	if (_U1 || !K) {
		if (!N) {
			mcdot_product_0(_Out, _In0, _In1, m, k, n, OutS, Outs, In0s, In1s, In2, In2S, In2s, U0, U1);
			return;
		}
		else {
			mcdot_product_0(Out, In0, In1, m, k, N, OutS, Outs, In0s, In1s, In2, In2S, In2s, U0, U1);
			Out += N * OutS;
			In1 += N;
			In2 += N * In2S;
			mcdot_product_0(Out, In0, In1, m, k, n-N, OutS, Outs, In0s, In1s, In2, In2S, In2s, U0, U1);
			return;
		}
	}

	if (N) {
		if (K) {
			mcdot_product_0(Out, In0, In1, m, K, N, OutS, Outs, In0s, In1s, In2, In2S, In2s, U0, U1);
			In0 += K;
			In1 += K * In1s;
			mcdot_product_0(Out, In0, In1, m, k-K, N, OutS, Outs, In0s, In1s, Out, In2S, In2s, U0, U1);
		}
		else {
			mcdot_product_0(Out, In0, In1, m, k, N, OutS, Outs, In0s, In1s, In2, In2S, In2s, U0, U1);
		}
		Out = _Out + N * OutS;
		In0 = _In0;
		In1 = _In1 + N;
		In2 = _In2 + N * In2S;
	}
	if (K) {
		mcdot_product_0(Out, In0, In1, m, K, n-N, OutS, Outs, In0s, In1s, In2, In2S, In2s, U0, U1);
		In0 += K;
		In1 += K * In1s;
		mcdot_product_0(Out, In0, In1, m, k-K, n-N, OutS, Outs, In0s, In1s, Out, In2S, In2s, U0, U1);
	}
	else {
		mcdot_product_0(Out, In0, In1, m, k-K, n-N, OutS, Outs, In0s, In1s, In2, In2S, In2s, U0, U1);
	}
}

//------------------------------------------------------------------------------
// Convenience function to accommodate tranposed output and swapped inputs
template <class T, class U>
static inline void mcdot_product_ut(T* Out, 
																		T* _In0, 
																		T* _In1, 
																		volatile const U _m,
																		volatile const U k,
																		volatile const U _n, 
																		volatile const bool OutCm = false,
																		volatile const bool InpSw = false,
																		T* In2 = 0,
																		volatile U U0 = 0,
																		volatile U U1 = 0) { 
	T *In0, *In1;
	U m, n;
	volatile U OutS, Outs, In0s, In1s;
	volatile U In2S, In2s;

	In0s = k;
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
	return _mcdot_product_ut(Out, In0, In1, m, k, n, OutS, Outs, In0s, In1s, In2, In2S, In2s, U0, U1);
}

//------------------------------------------------------------------------------
template <class T, class U>
static inline void mmdot_product_ut(T* Out, 
																		T* In0, 
																		T* In1, 
																		volatile const U m, 
																		volatile const U k,
																		volatile const U n,
																		volatile bool OutCm = false,
																		volatile bool In0Cm = false,
																		volatile bool In1Cm = false,
																		volatile bool r2c = false,
																		T* In2 = 0,
																		volatile U U0 = 0,
																		volatile U U1 = 0) { 
	if (r2c) {
		OutCm = !OutCm;
		In0Cm = !In0Cm;
		In1Cm = !In1Cm;
	}

	// Scalar/vector outputs fast-track

	if (m == 1) {        // out can only be a scalar or vector
		if (n == 1) {      // out is a scalar
			return inner_product_ut(Out, In0, In1, m, k, (U)1, (U)0, (U)0, In2, U1);
		}                  // otherwise out is a vector
		else if (!In1Cm) { // untranposed multiple: vector = vector * matrix
			return rmdot_product_ut(Out, In0, In1, m, k, n, In2, false, U0, U1);
		}
		else {             // transposed multiple:  inner product
			return inner_product_ut(Out, In0, In1, n, k, (U)1, (U)0, k, In2, U1);
		}      
	}
	
	if (n == 1) {        // out can only be a vector
		if (!In0Cm) {      // untranposed multiplicand: 
			return inner_product_ut(Out, In0, In1, m, k, n, k, (U)0, In2, U1);
		}
		else {             // tranposed multiplicand - inner product of swapped inputs
			return cmdot_product_ut(Out, In0, In1, m, k, n, In2, false, m, U0, U1);
		}
	}

	// Outer products 
	if (k == 1) {     
		if (!In2) {        // No maxuend
			if (!OutCm) {    // untransposed product
				return outer_product_ut(Out, In0, In1, m, n, n, (U)1, (U)0, U1);
			}
			else {           // transposed product - outer product of swapped inputs
				return outer_product_ut(Out, In1, In0, n, m, m, (U)1, (U)0, U1);
			}
		}
		else {             // Have maxuend
			return mrdot_product_ut(Out, In0, In1, m, (U)1, n, OutCm, false, In2, U0, U1);
		}
	}

	//  matrix = matrix * matrix with 8 transposition permutations

	if (!OutCm) {        // Untransposed product
		if (!In0Cm) {      // Untransposed multiplicand
			if (!In1Cm) {    // Untransposed multiple
				return rmdot_product_ut(Out, In0, In1, m, k, n, In2, false, U0, U1);
				//return mcdot_product_ut(Out, In0, In1, m, k, n, OutCm, false, In2, U0, U1);
			}
			else {           // Transposed multiple
				return mrdot_product_ut(Out, In0, In1, m, k, n, OutCm, false, In2, U0, U1);
			}
		}
		else {             // Transposed multiplicand
			if (!In1Cm) {    // Untransposed multiple
				return cmdot_product_ut(Out, In0, In1, m, k, n, In2, false, m, U0, U1);
			}
			else {           // Tranposed multiple
				// C = A.T * B.T => C.T = B * A
				return mcdot_product_ut(Out, In0, In1, m, k, n, true, true, In2, U0, U1);
			}
		}
	}
	else {               // Transposed product
		if (!In0Cm) {      // Untransposed multiplicand
			if (!In1Cm) {    // Untransposed multiple
				return mcdot_product_ut(Out, In0, In1, m, k, n, OutCm, false, In2, U0, U1);
			}
			else {           // Transposed multiple
				return mrdot_product_ut(Out, In0, In1, m, k, n, OutCm, false, In2, U0, U1);
			}
		}
		else {             // Transposed multiplicand
			if (!In1Cm) {    // Untransposed multiple
				// C.T = A.T * B => C = B.T * A
				return cmdot_product_ut(Out, In1, In0, n, k, m, In2, true, n, U0, U1);
			}
			else {           // Transposed multiple
				// C.T = A.T * B.T => C = B * A
				return rmdot_product_ut(Out, In1, In0, n, k, m, In2, true, U0, U1);
				//return mcdot_product_ut(Out, In0, In1, m, k, n, false, true, In2, U0, U1);
			}
		}
	}
}
//------------------------------------------------------------------------------
#endif
