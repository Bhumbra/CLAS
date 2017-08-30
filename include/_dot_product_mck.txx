# ifndef _dot_product_mck_txx
# define _dot_product_mck_txx
//------------------------------------------------------------------------------
# include <iostream>
using namespace std;

//------------------------------------------------------------------------------
# include "clas.txx"

//------------------------------------------------------------------------------
template <class T, class U>
static NOINLINE void dot_product_mck_1x1x1 (T* _Out, 
																						T* _In0, 
																						T* _In1, 
																						volatile const U m, 
																						volatile const U k,
																						volatile const U n,
																						volatile U OutS = 0, 
																						volatile U In0S = 0, 
																						volatile U In1S = 0) { 

	register T o0; 
	register T in0_0_0;
	register T in1_0_0; 

	T *Out, *In0, *In1;
	T *Out_0; 
	T *out_0; 
	T* In0_0;
	T *in0_0;
	T *in1_0;

	U h, M, K, N;
	register U i;
	register U j;

	if (!OutS) {OutS = n;}
	if (!In0S) {In0S = k;}
	if (!In1S) {In1S = k;}
	M = m;
	K = k;
	N = n;
	Out = _Out;
	In0 = _In0;

	for (h = M; h; h--) {
		Out_0 = Out + OutS * 0;
		Out += OutS * 1;
		In0_0 = In0 + In0S * 0;
		In0 += In0S * 1;
		In1 = _In1;
		for (i = N; i; i--) {
			out_0 = Out_0 + 0;
			Out_0 += 1;
			o0 = *(out_0);
			in0_0 = In0_0;
			in1_0 = In1 + In1S * 0;
			In1 += In1S * 1;
			for (j = K; j; j--) {
				in0_0_0 = *(in0_0 + 0);
			  in0_0 += 1;
				in1_0_0 = *(in1_0 + 0);
				in1_0 += 1;
				o0 += in0_0_0 * in1_0_0;
			}
			*(out_0) = o0;
		}
	}
}

//------------------------------------------------------------------------------
template <class T, class U>
static NOINLINE void dot_product_mck_1x2x1 (T* _Out, 
																						T* _In0, 
																						T* _In1, 
																						volatile const U m, 
																						volatile const U k,
																						volatile const U n,
																						volatile U OutS = 0, 
																						volatile U In0S = 0, 
																						volatile U In1S = 0) { 

	register T o0; 
	register T in0_0_0, in0_0_1;
	register T in1_0_0, in1_0_1; 

	T *Out, *In0, *In1;
	T *Out_0; 
	T *out_0; 
	T* In0_0;
	T *in0_0;
	T *in1_0;

	U h, M, K, N;
	register U i;
	register U j;

	if (!OutS) {OutS = n;}
	if (!In0S) {In0S = k;}
	if (!In1S) {In1S = k;}
	M = m;
	K = k >> 1;
	N = n;
	Out = _Out;
	In0 = _In0;

	for (h = M; h; h--) {
		Out_0 = Out + OutS * 0;
		Out += OutS * 1;
		In0_0 = In0 + In0S * 0;
		In0 += In0S * 1;
		In1 = _In1;
		for (i = N; i; i--) {
			out_0 = Out_0 + 0;
			Out_0 += 1;
			o0 = *(out_0);
			in0_0 = In0_0;
			in1_0 = In1 + In1S * 0;
			In1 += In1S * 1;
			for (j = K; j; j--) {
				in0_0_0 = *(in0_0 + 0);
				in0_0_1 = *(in0_0 + 1);
			  in0_0 += 2;
				in1_0_0 = *(in1_0 + 0);
				in1_0_1 = *(in1_0 + 1);
				in1_0 += 2;
				o0 += in0_0_0 * in1_0_0;
				o0 += in0_0_1 * in1_0_1;
			}
			*(out_0) = o0;
		}
	}
	Out = _Out;
	In0 = _In0;
	In1 = _In1;
	K = k & 1;
	i = k;
	if (K) {
		i -= K;
		In0 += i;
		In1 += i;
		dot_product_mck_1x1x1(Out, In0, In1, m, K, n, OutS, In0S, In1S);
	}
}

//------------------------------------------------------------------------------
template <class T, class U>
static NOINLINE void dot_product_mck_1x4x1 (T* _Out, 
																						T* _In0, 
																						T* _In1, 
																						volatile const U m, 
																						volatile const U k,
																						volatile const U n,
																						volatile U OutS = 0, 
																						volatile U In0S = 0, 
																						volatile U In1S = 0) { 

	register T o0; 
	register T in0_0_0, in0_0_1, in0_0_2, in0_0_3;
	register T in1_0_0, in1_0_1, in1_0_2, in1_0_3; 

	T *Out, *In0, *In1;
	T *Out_0; 
	T *out_0; 
	T* In0_0;
	T *in0_0;
	T *in1_0;

	U h, M, K, N;
	register U i;
	register U j;

	if (!OutS) {OutS = n;}
	if (!In0S) {In0S = k;}
	if (!In1S) {In1S = k;}
	M = m;
	K = k >> 2;
	N = n;
	Out = _Out;
	In0 = _In0;

	for (h = M; h; h--) {
		Out_0 = Out + OutS * 0;
		Out += OutS * 1;
		In0_0 = In0 + In0S * 0;
		In0 += In0S * 1;
		In1 = _In1;
		for (i = N; i; i--) {
			out_0 = Out_0 + 0;
			Out_0 += 1;
			o0 = *(out_0);
			in0_0 = In0_0;
			in1_0 = In1 + In1S * 0;
			In1 += In1S * 1;
			for (j = K; j; j--) {
				in0_0_0 = *(in0_0 + 0);
				in0_0_1 = *(in0_0 + 1);
				in0_0_2 = *(in0_0 + 2);
				in0_0_3 = *(in0_0 + 3);
			  in0_0 += 4;
				in1_0_0 = *(in1_0 + 0);
				in1_0_1 = *(in1_0 + 1);
				in1_0_2 = *(in1_0 + 2);
				in1_0_3 = *(in1_0 + 3);
				in1_0 += 4;
				o0 += in0_0_0 * in1_0_0;
				o0 += in0_0_1 * in1_0_1;
				o0 += in0_0_2 * in1_0_2;
				o0 += in0_0_3 * in1_0_3;
			}
			*(out_0) = o0;
		}
	}
	Out = _Out;
	In0 = _In0;
	In1 = _In1;
	K = k & 3;
	i = k;
	if (K) {
		i -= K;
		In0 += i;
		In1 += i;
		dot_product_mck_1x2x1(Out, In0, In1, m, K, n, OutS, In0S, In1S);
	}
}

//------------------------------------------------------------------------------
template <class T, class U>
static NOINLINE void dot_product_mck_1x8x1 (T* _Out, 
																						T* _In0, 
																						T* _In1, 
																						volatile const U m, 
																						volatile const U k,
																						volatile const U n,
																						volatile U OutS = 0, 
																						volatile U In0S = 0, 
																						volatile U In1S = 0) { 

	register T o0; 
	register T in0_0_0, in0_0_1, in0_0_2, in0_0_3, in0_0_4, in0_0_5, in0_0_6, in0_0_7;
	register T in1_0_0, in1_0_1, in1_0_2, in1_0_3, in1_0_4, in1_0_5, in1_0_6, in1_0_7; 

	T *Out, *In0, *In1;
	T *Out_0; 
	T *out_0; 
	T* In0_0;
	T *in0_0;
	T *in1_0;

	U h, M, K, N;
	register U i;
	register U j;

	if (!OutS) {OutS = n;}
	if (!In0S) {In0S = k;}
	if (!In1S) {In1S = k;}
	M = m;
	K = k >> 3;
	N = n;
	Out = _Out;
	In0 = _In0;

	for (h = M; h; h--) {
		Out_0 = Out + OutS * 0;
		Out += OutS * 1;
		In0_0 = In0 + In0S * 0;
		In0 += In0S * 1;
		In1 = _In1;
		for (i = N; i; i--) {
			out_0 = Out_0 + 0;
			Out_0 += 1;
			o0 = *(out_0);
			in0_0 = In0_0;
			in1_0 = In1 + In1S * 0;
			In1 += In1S * 1;
			for (j = K; j; j--) {
				in0_0_0 = *(in0_0 + 0);
				in0_0_1 = *(in0_0 + 1);
				in0_0_2 = *(in0_0 + 2);
				in0_0_3 = *(in0_0 + 3);
				in0_0_4 = *(in0_0 + 4);
				in0_0_5 = *(in0_0 + 5);
				in0_0_6 = *(in0_0 + 6);
				in0_0_7 = *(in0_0 + 7);
			  in0_0 += 8;
				in1_0_0 = *(in1_0 + 0);
				in1_0_1 = *(in1_0 + 1);
				in1_0_2 = *(in1_0 + 2);
				in1_0_3 = *(in1_0 + 3);
				in1_0_4 = *(in1_0 + 4);
				in1_0_5 = *(in1_0 + 5);
				in1_0_6 = *(in1_0 + 6);
				in1_0_7 = *(in1_0 + 7);
				in1_0 += 8;
				o0 += in0_0_0 * in1_0_0;
				o0 += in0_0_1 * in1_0_1;
				o0 += in0_0_2 * in1_0_2;
				o0 += in0_0_3 * in1_0_3;
				o0 += in0_0_4 * in1_0_4;
				o0 += in0_0_5 * in1_0_5;
				o0 += in0_0_6 * in1_0_6;
				o0 += in0_0_7 * in1_0_7;
			}
			*(out_0) = o0;
		}
	}
	Out = _Out;
	In0 = _In0;
	In1 = _In1;
	K = k & 7;
	i = k;
	if (K) {
		i -= K;
		In0 += i;
		In1 += i;
		dot_product_mck_1x4x1(Out, In0, In1, m, K, n, OutS, In0S, In1S);
	}
}

//------------------------------------------------------------------------------
template <class T, class U>
static NOINLINE void dot_product_mck_2x2x2 (T* _Out, 
																						T* _In0, 
																						T* _In1, 
																						volatile const U m, 
																						volatile const U k,
																						volatile const U n,
																						volatile U OutS = 0, 
																						volatile U In0S = 0, 
																						volatile U In1S = 0) { 

	register T o0_0, o0_1; 
	register T o1_0, o1_1; 
	T i0, i1;
	T in0_0_0, in0_0_1; 
	T in0_1_0, in0_1_1;
	register T in1_0_0, in1_0_1; 
	register T in1_1_0, in1_1_1;

	T *Out, *In0, *In1;
	T *Out_0, *Out_1; 
	T *out_0, *out_1; 
	T* In0_0, *In0_1;
	T *in0_0, *in0_1;
	T *in1_0, *in1_1;

	U h, M, K, N;
	register U i;
	register U j;

	if (!OutS) {OutS = n;}
	if (!In0S) {In0S = k;}
	if (!In1S) {In1S = k;}
	M = m >> 1;
	K = k >> 1;
	N = n >> 1;
	Out = _Out;
	In0 = _In0;

	for (h = M; h; h--) {
		Out_0 = Out + OutS * 0;
		Out_1 = Out + OutS * 1;
		Out += OutS * 2;
		In0_0 = In0 + In0S * 0;
		In0_1 = In0 + In0S * 1;
		In0 += In0S * 2;
		In1 = _In1;
		for (i = N; i; i--) {
			out_0 = Out_0;
			out_1 = Out_1;
			Out_0 += 2;
			Out_1 += 2;
			o0_0 = *(out_0 + 0);
			o0_1 = *(out_0 + 1);
			o1_0 = *(out_1 + 0);
			o1_1 = *(out_1 + 1);
			in0_0 = In0_0;
			in0_1 = In0_1;
			in1_0 = In1 + In1S * 0;
			in1_1 = In1 + In1S * 1;
			In1 += In1S * 2;
			for (j = K; j; j--) {
				in0_0_0 = *(in0_0 + 0);
				in0_0_1 = *(in0_0 + 1);
			  in0_0 += 2;
				in0_1_0 = *(in0_1 + 0);
				in0_1_1 = *(in0_1 + 1);
			  in0_1 += 2;
				in1_0_0 = *(in1_0 + 0);
				in1_0_1 = *(in1_0 + 1);
				in1_0 += 2;
				in1_1_0 = *(in1_1 + 0);
				in1_1_1 = *(in1_1 + 1);
				in1_1 += 2;
				i0 = in0_0_0;
				i1 = in0_0_1;
				o0_0 += i0 * in1_0_0;
				o0_0 += i1 * in1_0_1;
				o0_1 += i0 * in1_1_0;
				o0_1 += i1 * in1_1_1;
				i0 = in0_1_0;
				i1 = in0_1_1;
				o1_0 += i0 * in1_0_0;
				o1_0 += i1 * in1_0_1;
				o1_1 += i0 * in1_1_0;
				o1_1 += i1 * in1_1_1;
			}
			*(out_0 + 0) = o0_0;
			*(out_0 + 1) = o0_1;
			*(out_1 + 0) = o1_0;
			*(out_1 + 1) = o1_1;
		}
	}
	Out = _Out;
	In0 = _In0;
	In1 = _In1;
	h = m;
	i = k;
	j = n;
	M <<= 1;
	K <<= 1;
	N <<= 1;
	if (K < k) {
		K = k & 1;
		i -= K;
		In0 += i;
		In1 += i;
		dot_product_mck_1x1x1(Out, In0, In1, M, K, N, OutS, In0S, In1S);
		In0 = _In0;
		In1 = _In1;
	}

	if (N < n) {
		N = n & 1;
		j -= N;
		Out += j;
		In1 += j * In1S;
		dot_product_mck_1x8x1(Out, In0, In1, M, k, N, OutS, In0S, In1S);
		Out = _Out;
		In1 = _In1;
	}

	if (M < m) {
		M = m & 1;
		h -= M;
		Out += OutS * h;
		In0 += In0S * h;
		dot_product_mck_1x8x1(Out, In0, In1, M, k, n, OutS, In0S, In1S);
		Out = _Out;
		In0 = _In0;
	}
}

//------------------------------------------------------------------------------
template <class T, class U>
static NOINLINE void dot_product_mck_4x4x4 (T* _Out, 
																						T* _In0, 
																						T* _In1, 
																						volatile const U m, 
																						volatile const U k,
																						volatile const U n,
																						volatile U OutS = 0, 
																						volatile U In0S = 0, 
																						volatile U In1S = 0) { 

	register T o0_0, o0_1, o0_2, o0_3; 
	register T o1_0, o1_1, o1_2, o1_3; 
	register T o2_0, o2_1, o2_2, o2_3; 
	register T o3_0, o3_1, o3_2, o3_3; 
	register T i0, i1, i2, i3;
	T in0_0_0, in0_0_1, in0_0_2, in0_0_3; 
	T in0_1_0, in0_1_1, in0_1_2, in0_1_3;
	T in0_2_0, in0_2_1, in0_2_2, in0_2_3; 
	T in0_3_0, in0_3_1, in0_3_2, in0_3_3;
	T in1_0_0, in1_0_1, in1_0_2, in1_0_3; 
	T in1_1_0, in1_1_1, in1_1_2, in1_1_3;
	T in1_2_0, in1_2_1, in1_2_2, in1_2_3; 
	T in1_3_0, in1_3_1, in1_3_2, in1_3_3;

	T *Out, *In0, *In1;
	T *Out_0, *Out_1, *Out_2, *Out_3; 
	T *out_0, *out_1, *out_2, *out_3; 
	T *In0_0, *In0_1, *In0_2, *In0_3;
	T *in0_0, *in0_1, *in0_2, *in0_3;
	T *in1_0, *in1_1, *in1_2, *in1_3;

	U h, M, K, N;
	register U i;
	register U j;

	if (!OutS) {OutS = n;}
	if (!In0S) {In0S = k;}
	if (!In1S) {In1S = k;}
	M = m >> 2;
	K = k >> 2;
	N = n >> 2;
	Out = _Out;
	In0 = _In0;

	for (h = M; h; h--) {
		Out_0 = Out + OutS * 0;
		Out_1 = Out + OutS * 1;
		Out_2 = Out + OutS * 2;
		Out_3 = Out + OutS * 3;
		Out += OutS * 4;
		In0_0 = In0 + In0S * 0;
		In0_1 = In0 + In0S * 1;
		In0_2 = In0 + In0S * 2;
		In0_3 = In0 + In0S * 3;
		In0 += In0S * 4;
		In1 = _In1;
		for (i = N; i; i--) {
			out_0 = Out_0;
			out_1 = Out_1;
			out_2 = Out_2;
			out_3 = Out_3;
			Out_0 += 4;
			Out_1 += 4;
			Out_2 += 4;
			Out_3 += 4;
			o0_0 = *(out_0 + 0);
			o0_1 = *(out_0 + 1);
			o0_2 = *(out_0 + 2);
			o0_3 = *(out_0 + 3);
			o1_0 = *(out_1 + 0);
			o1_1 = *(out_1 + 1);
			o1_2 = *(out_1 + 2);
			o1_3 = *(out_1 + 3);
			o2_0 = *(out_2 + 0);
			o2_1 = *(out_2 + 1);
			o2_2 = *(out_2 + 2);
			o2_3 = *(out_2 + 3);
			o3_0 = *(out_3 + 0);
			o3_1 = *(out_3 + 1);
			o3_2 = *(out_3 + 2);
			o3_3 = *(out_3 + 3);
			in0_0 = In0_0;
			in0_1 = In0_1;
			in0_2 = In0_2;
			in0_3 = In0_3;
			in1_0 = In1 + In1S * 0;
			in1_1 = In1 + In1S * 1;
			in1_2 = In1 + In1S * 2;
			in1_3 = In1 + In1S * 3;
			In1 += In1S * 4;
			for (j = K; j; j--) {
				in0_0_0 = *(in0_0 + 0);
				in0_0_1 = *(in0_0 + 1);
				in0_0_2 = *(in0_0 + 2);
				in0_0_3 = *(in0_0 + 3);
			  in0_0 += 4;
				in0_1_0 = *(in0_1 + 0);
				in0_1_1 = *(in0_1 + 1);
				in0_1_2 = *(in0_1 + 2);
				in0_1_3 = *(in0_1 + 3);
			  in0_1 += 4;
				in0_2_0 = *(in0_2 + 0);
				in0_2_1 = *(in0_2 + 1);
				in0_2_2 = *(in0_2 + 2);
				in0_2_3 = *(in0_2 + 3);
			  in0_2 += 4;
				in0_3_0 = *(in0_3 + 0);
				in0_3_1 = *(in0_3 + 1);
				in0_3_2 = *(in0_3 + 2);
				in0_3_3 = *(in0_3 + 3);
			  in0_3 += 4;
				in1_0_0 = *(in1_0 + 0);
				in1_0_1 = *(in1_0 + 1);
				in1_0_2 = *(in1_0 + 2);
				in1_0_3 = *(in1_0 + 3);
				in1_0 += 4;
				in1_1_0 = *(in1_1 + 0);
				in1_1_1 = *(in1_1 + 1);
				in1_1_2 = *(in1_1 + 2);
				in1_1_3 = *(in1_1 + 3);
				in1_1 += 4;
				in1_2_0 = *(in1_2 + 0);
				in1_2_1 = *(in1_2 + 1);
				in1_2_2 = *(in1_2 + 2);
				in1_2_3 = *(in1_2 + 3);
				in1_2 += 4;
				in1_3_0 = *(in1_3 + 0);
				in1_3_1 = *(in1_3 + 1);
				in1_3_2 = *(in1_3 + 2);
				in1_3_3 = *(in1_3 + 3);
				in1_3 += 4;

				i0 = in0_0_0;
				i1 = in0_0_1;
				i2 = in0_0_2;
				i3 = in0_0_3;
				o0_0 += i0 * in1_0_0;
				o0_0 += i1 * in1_0_1;
				o0_0 += i2 * in1_0_2;
				o0_0 += i3 * in1_0_3;
				o0_1 += i0 * in1_1_0;
				o0_1 += i1 * in1_1_1;
				o0_1 += i2 * in1_1_2;
				o0_1 += i3 * in1_1_3;

				o0_2 += i0 * in1_2_0;
				o0_2 += i1 * in1_2_1;
				o0_2 += i2 * in1_2_2;
				o0_2 += i3 * in1_2_3;
				o0_3 += i0 * in1_3_0;
				o0_3 += i1 * in1_3_1;
				o0_3 += i2 * in1_3_2;
				o0_3 += i3 * in1_3_3;

				i0 = in0_1_0;
				i1 = in0_1_1;
				i2 = in0_1_2;
				i3 = in0_1_3;
				o1_0 += i0 * in1_0_0;
				o1_0 += i1 * in1_0_1;
				o1_0 += i2 * in1_0_2;
				o1_0 += i3 * in1_0_3;
				o1_1 += i0 * in1_1_0;
				o1_1 += i1 * in1_1_1;
				o1_1 += i2 * in1_1_2;
				o1_1 += i3 * in1_1_3;
				o1_2 += i0 * in1_2_0;
				o1_2 += i1 * in1_2_1;
				o1_2 += i2 * in1_2_2;
				o1_2 += i3 * in1_2_3;
				o1_3 += i0 * in1_3_0;
				o1_3 += i1 * in1_3_1;
				o1_3 += i2 * in1_3_2;
				o1_3 += i3 * in1_3_3;

				i0 = in0_2_0;
				i1 = in0_2_1;
				i2 = in0_2_2;
				i3 = in0_2_3;
				o2_0 += i0 * in1_0_0;
				o2_0 += i1 * in1_0_1;
				o2_0 += i2 * in1_0_2;
				o2_0 += i3 * in1_0_3;
				o2_1 += i0 * in1_1_0;
				o2_1 += i1 * in1_1_1;
				o2_1 += i2 * in1_1_2;
				o2_1 += i3 * in1_1_3;
				o2_2 += i0 * in1_2_0;
				o2_2 += i1 * in1_2_1;
				o2_2 += i2 * in1_2_2;
				o2_2 += i3 * in1_2_3;
				o2_3 += i0 * in1_3_0;
				o2_3 += i1 * in1_3_1;
				o2_3 += i2 * in1_3_2;
				o2_3 += i3 * in1_3_3;

				i0 = in0_3_0;
				i1 = in0_3_1;
				i2 = in0_3_2;
				i3 = in0_3_3;
				o3_0 += i0 * in1_0_0;
				o3_0 += i1 * in1_0_1;
				o3_0 += i2 * in1_0_2;
				o3_0 += i3 * in1_0_3;
				o3_1 += i0 * in1_1_0;
				o3_1 += i1 * in1_1_1;
				o3_1 += i2 * in1_1_2;
				o3_1 += i3 * in1_1_3;
				o3_2 += i0 * in1_2_0;
				o3_2 += i1 * in1_2_1;
				o3_2 += i2 * in1_2_2;
				o3_2 += i3 * in1_2_3;
				o3_3 += i0 * in1_3_0;
				o3_3 += i1 * in1_3_1;
				o3_3 += i2 * in1_3_2;
				o3_3 += i3 * in1_3_3;
			}
			*(out_0 + 0) = o0_0;
			*(out_0 + 1) = o0_1;
			*(out_0 + 2) = o0_2;
			*(out_0 + 3) = o0_3;
			*(out_1 + 0) = o1_0;
			*(out_1 + 1) = o1_1;
			*(out_1 + 2) = o1_2;
			*(out_1 + 3) = o1_3;
			*(out_2 + 0) = o2_0;
			*(out_2 + 1) = o2_1;
			*(out_2 + 2) = o2_2;
			*(out_2 + 3) = o2_3;
			*(out_3 + 0) = o3_0;
			*(out_3 + 1) = o3_1;
			*(out_3 + 2) = o3_2;
			*(out_3 + 3) = o3_3;
		}
	}
	Out = _Out;
	In0 = _In0;
	In1 = _In1;
	h = m;
	i = k;
	j = n;
	M <<= 2;
	K <<= 2;
	N <<= 2;
	if (K < k) {
		K = k & 3;
		i -= K;
		In0 += i;
		In1 += i;
		dot_product_mck_2x2x2(Out, In0, In1, M, K, N, OutS, In0S, In1S);
		In0 = _In0;
		In1 = _In1;
	}

	if (N < n) {
		N = n & 3;
		j -= N;
		Out += j;
		In1 += j * In1S;
		dot_product_mck_2x2x2(Out, In0, In1, M, k, N, OutS, In0S, In1S);
		Out = _Out;
		In1 = _In1;
	}

	if (M < m) {
		M = m & 3;
		h -= M;
		Out += OutS * h;
		In0 += In0S * h;
		dot_product_mck_2x2x2(Out, In0, In1, M, k, n, OutS, In0S, In1S);
		Out = _Out;
		In0 = _In0;
	}
}

//------------------------------------------------------------------------------
#endif

