# ifndef _dot_product_mkc_txx
# define _dot_product_mkc_txx

//------------------------------------------------------------------------------
# include "clas.txx"

//------------------------------------------------------------------------------
template <class T, class U>
static NOINLINE void dot_product_mkc_1x1x1 (T* _Out, 
																						T* _In0, 
																						T* _In1, 
																						volatile const U m, 
																						volatile const U k,
																						volatile const U n,
																						volatile U OutS = 0, 
																						volatile U In0S = 0, 
																						volatile U In0s = 0, 
																						volatile U In1S = 0) { 

	register T o0; 
	register T i0;
	register T in1_0_0; 

	T in0_0_0;

	T *Out, *In0, *In1;
	T *Out_0; 
	T *out_0; 
	T *in0_0;
	T *in1_0;

	U h, M, K, N;
	register U i;
	register U j;

	if (!OutS) {OutS = n;}
	if (!In0S) {In0S = k;}
	if (!In0s) {In0s = (U)1;}
	if (!In1S) {In1S = k;}
	M = m;
	K = k;
	N = n;

	Out = _Out;
	In0 = _In0;

	for (h = M; h; h--) {
		Out_0 = Out + OutS * 0;
		Out += OutS * 1;
		in0_0 = In0 + In0S * 0;
		In0 += In0S * 1;
		In1 = _In1;
		for (i = K; i; i--) {
			out_0 = Out_0;
			in0_0_0 = *(in0_0 + In0s * 0);
			in0_0 += In0s * 1;
			in1_0 = In1 + 0 * In1S;
			In1 += 1;
			for (j = N; j; j--) {
				in1_0_0 = *(in1_0 + 0);
				in1_0 += In1S;
				i0 = in0_0_0;
				o0  = i0 * in1_0_0;
				*(out_0 + 0) += o0;
				out_0 += 1;
			}
		}
	}
}

//------------------------------------------------------------------------------
template <class T, class U>
static NOINLINE void dot_product_mkc_1x2x1 (T* _Out, 
																						T* _In0, 
																						T* _In1, 
																						volatile const U m, 
																						volatile const U k,
																						volatile const U n,
																						volatile U OutS = 0, 
																						volatile U In0S = 0, 
																						volatile U In0s = 0, 
																						volatile U In1S = 0) { 

	register T o0; 
	register T i0, i1;
	register T in1_0_0, in1_0_1; 

	T in0_0_0, in0_0_1;

	T *Out, *In0, *In1;
	T *Out_0; 
	T *out_0; 
	T *in0_0;
	T *in1_0;

	U h, M, K, N;
	register U i;
	register U j;

	if (!OutS) {OutS = n;}
	if (!In0S) {In0S = k;}
	if (!In0s) {In0s = (U)1;}
	if (!In1S) {In1S = k;}
	M = m;
	K = k >> 1;
	N = n;

	Out = _Out;
	In0 = _In0;

	for (h = M; h; h--) {
		Out_0 = Out + OutS * 0;
		Out += OutS * 1;
		in0_0 = In0 + In0S * 0;
		In0 += In0S * 1;
		In1 = _In1;
		for (i = K; i; i--) {
			out_0 = Out_0;
			in0_0_0 = *(in0_0 + In0s * 0);
			in0_0_1 = *(in0_0 + In0s * 1);
			in0_0 += In0s * 2;
			in1_0 = In1 + 0 * In1S;
			In1 += 2;
			for (j = N; j; j--) {
				in1_0_0 = *(in1_0 + 0);
				in1_0_1 = *(in1_0 + 1);
				in1_0 += In1S;
				i0 = in0_0_0;
				i1 = in0_0_1;
				o0  = i0 * in1_0_0;
				o0 += i1 * in1_0_1;
				*(out_0 + 0) += o0;
				out_0 += 1;
			}
		}
	}
	Out = _Out;
	In0 = _In0;
	In1 = _In1;
	K <<= 1;
	i = k;
	if (K < i) {
		K = i & 1;
		i -= K;
		In0 += In0s * i;
		In1 += i;
		dot_product_mkc_1x1x1(Out, In0, In1, m, K, n, OutS, In0S, In0s, In1S);
		In0 = _In0;
		In1 = _In1;
	}
}

//------------------------------------------------------------------------------
template <class T, class U>
static NOINLINE void dot_product_mkc_1x4x1 (T* _Out, 
																						T* _In0, 
																						T* _In1, 
																						volatile const U m, 
																						volatile const U k,
																						volatile const U n,
																						volatile U OutS = 0, 
																						volatile U In0S = 0, 
																						volatile U In0s = 0, 
																						volatile U In1S = 0) { 

	register T o0; 
	register T i0, i1, i2, i3;
	register T in1_0_0, in1_0_1, in1_0_2, in1_0_3; 

	T in0_0_0, in0_0_1, in0_0_2, in0_0_3;

	T *Out, *In0, *In1;
	T *Out_0; 
	T *out_0; 
	T *in0_0;
	T *in1_0;

	U h, M, K, N;
	register U i;
	register U j;

	if (!OutS) {OutS = n;}
	if (!In0S) {In0S = k;}
	if (!In0s) {In0s = (U)1;}
	if (!In1S) {In1S = k;}
	M = m;
	K = k >> 2;
	N = n;

	Out = _Out;
	In0 = _In0;

	for (h = M; h; h--) {
		Out_0 = Out + OutS * 0;
		Out += OutS * 1;
		in0_0 = In0 + In0S * 0;
		In0 += In0S * 1;
		In1 = _In1;
		for (i = K; i; i--) {
			out_0 = Out_0;
			in0_0_0 = *(in0_0 + In0s * 0);
			in0_0_1 = *(in0_0 + In0s * 1);
			in0_0_2 = *(in0_0 + In0s * 2);
			in0_0_3 = *(in0_0 + In0s * 3);
			in0_0 += In0s * 4;
			in1_0 = In1 + 0 * In1S;
			In1 += 4;
			for (j = N; j; j--) {
				in1_0_0 = *(in1_0 + 0);
				in1_0_1 = *(in1_0 + 1);
				in1_0_2 = *(in1_0 + 2);
				in1_0_3 = *(in1_0 + 3);
				in1_0 += In1S;
				i0 = in0_0_0;
				i1 = in0_0_1;
				i2 = in0_0_2;
				i3 = in0_0_3;
				o0  = i0 * in1_0_0;
				o0 += i1 * in1_0_1;
				o0 += i2 * in1_0_2;
				o0 += i3 * in1_0_3;
				*(out_0 + 0) += o0;
				out_0 += 1;
			}
		}
	}
	Out = _Out;
	In0 = _In0;
	In1 = _In1;
	K <<= 2;
	i = k;
	if (K < i) {
		K = i & 3;
		i -= K;
		In0 += In0s * i;
		In1 += i;
		dot_product_mkc_1x2x1(Out, In0, In1, m, K, n, OutS, In0S, In0s, In1S);
		In0 = _In0;
		In1 = _In1;
	}
}

//------------------------------------------------------------------------------
template <class T, class U>
static NOINLINE void dot_product_mkc_1x8x1 (T* _Out, 
																						T* _In0, 
																						T* _In1, 
																						volatile const U m, 
																						volatile const U k,
																						volatile const U n,
																						volatile U OutS = 0, 
																						volatile U In0S = 0, 
																						volatile U In0s = 0, 
																						volatile U In1S = 0) { 

	register T o0; 
	register T i0, i1, i2, i3, i4, i5, i6, i7;
	register T in1_0_0, in1_0_1, in1_0_2, in1_0_3, in1_0_4, in1_0_5, in1_0_6, in1_0_7; 

	T in0_0_0, in0_0_1, in0_0_2, in0_0_3, in0_0_4, in0_0_5, in0_0_6, in0_0_7;

	T *Out, *In0, *In1;
	T *Out_0; 
	T *out_0; 
	T *in0_0;
	T *in1_0;

	U h, M, K, N;
	register U i;
	register U j;

	if (!OutS) {OutS = n;}
	if (!In0S) {In0S = k;}
	if (!In0s) {In0s = (U)1;}
	if (!In1S) {In1S = k;}
	M = m;
	K = k >> 3;
	N = n;

	Out = _Out;
	In0 = _In0;

	for (h = M; h; h--) {
		Out_0 = Out + OutS * 0;
		Out += OutS * 1;
		in0_0 = In0 + In0S * 0;
		In0 += In0S * 1;
		In1 = _In1;
		for (i = K; i; i--) {
			out_0 = Out_0;
			in0_0_0 = *(in0_0 + In0s * 0);
			in0_0_1 = *(in0_0 + In0s * 1);
			in0_0_2 = *(in0_0 + In0s * 2);
			in0_0_3 = *(in0_0 + In0s * 3);
			in0_0_4 = *(in0_0 + In0s * 4);
			in0_0_5 = *(in0_0 + In0s * 5);
			in0_0_6 = *(in0_0 + In0s * 6);
			in0_0_7 = *(in0_0 + In0s * 7);
			in0_0 += In0s * 8;
			in1_0 = In1 + 0 * In1S;
			In1 += 8;
			for (j = N; j; j--) {
				in1_0_0 = *(in1_0 + 0);
				in1_0_1 = *(in1_0 + 1);
				in1_0_2 = *(in1_0 + 2);
				in1_0_3 = *(in1_0 + 3);
				in1_0_4 = *(in1_0 + 4);
				in1_0_5 = *(in1_0 + 5);
				in1_0_6 = *(in1_0 + 6);
				in1_0_7 = *(in1_0 + 7);
				in1_0 += In1S;
				i0 = in0_0_0;
				i1 = in0_0_1;
				i2 = in0_0_2;
				i3 = in0_0_3;
				i4 = in0_0_4;
				i5 = in0_0_5;
				i6 = in0_0_6;
				i7 = in0_0_7;
				o0  = i0 * in1_0_0;
				o0 += i1 * in1_0_1;
				o0 += i2 * in1_0_2;
				o0 += i3 * in1_0_3;
				o0 += i4 * in1_0_4;
				o0 += i5 * in1_0_5;
				o0 += i6 * in1_0_6;
				o0 += i7 * in1_0_7;
				*(out_0 + 0) += o0;
				out_0 += 1;
			}
		}
	}
	Out = _Out;
	In0 = _In0;
	In1 = _In1;
	K <<= 3;
	i = k;
	if (K < i) {
		K = i & 7;
		i -= K;
		In0 += In0s * i;
		In1 += i;
		dot_product_mkc_1x4x1(Out, In0, In1, m, K, n, OutS, In0S, In0s, In1S);
		In0 = _In0;
		In1 = _In1;
	}
}

//------------------------------------------------------------------------------
template <class T, class U>
static NOINLINE void dot_product_mkc_2x2x2 (T* _Out, 
																						T* _In0, 
																						T* _In1, 
																						volatile const U m, 
																						volatile const U k,
																						volatile const U n,
																						volatile U OutS = 0, 
																						volatile U In0S = 0, 
																						volatile U In0s = 0, 
																						volatile U In1S = 0) { 

	register T o0, o1; 
	register T i0, i1;
	register T in1_0_0, in1_0_1;
	register T in1_1_0, in1_1_1; 

	T in0_0_0, in0_0_1;
	T in0_1_0, in0_1_1;

	T *Out, *In0, *In1;
	T *Out_0, *Out_1; 
	T *out_0, *out_1; 
	T *in0_0, *in0_1;
	T *in1_0, *in1_1;

	U h, M, K, N;
	register U i;
	register U j;

	if (!OutS) {OutS = n;}
	if (!In0S) {In0S = k;}
	if (!In0s) {In0s = (U)1;}
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
		in0_0 = In0 + In0S * 0;
		in0_1 = In0 + In0S * 1;
		In0 += In0S * 2;
		In1 = _In1;
		for (i = K; i; i--) {
			out_0 = Out_0;
			out_1 = Out_1;
			in0_0_0 = *(in0_0 + In0s * 0);
			in0_0_1 = *(in0_0 + In0s * 1);
			in0_0 += In0s * 2;
			in0_1_0 = *(in0_1 + In0s * 0);
			in0_1_1 = *(in0_1 + In0s * 1);
			in0_1 += In0s * 2;
			in1_0 = In1 + 0 * In1S;
			in1_1 = In1 + 1 * In1S;
			In1 += 2;
			for (j = N; j; j--) {
				in1_0_0 = *(in1_0 + 0);
				in1_0_1 = *(in1_0 + 1);
				in1_0 += In1S * 2;
				in1_1_0 = *(in1_1 + 0);
				in1_1_1 = *(in1_1 + 1);
				in1_1 += In1S * 2;
				i0 = in0_0_0;
				i1 = in0_0_1;
				o0  = i0 * in1_0_0;
				o0 += i1 * in1_0_1;
				o1  = i0 * in1_1_0;
				o1 += i1 * in1_1_1;
				*(out_0 + 0) += o0;
				*(out_0 + 1) += o1;
				out_0 += 2;
				i0 = in0_1_0;
				i1 = in0_1_1;
				o0  = i0 * in1_0_0;
				o0 += i1 * in1_0_1;
				o1  = i0 * in1_1_0;
				o1 += i1 * in1_1_1;
				*(out_1 + 0) += o0;
				*(out_1 + 1) += o1;
				out_1 += 2;
			}
		}
	}

	Out = _Out;
	In0 = _In0;
	In1 = _In1;
	M <<= 1;
	K <<= 1;
	N <<= 1;
	j = n;
	if (N < j) {
		N = j & 1;
		j -= N;
		Out += j;
		In1 += j * In1S;
		dot_product_mkc_1x8x1(Out, In0, In1, M, K, N, OutS, In0S, In0s, In1S);
		Out = _Out;
		In1 = _In1;
	}
	i = k;
	if (K < i) {
		K = i & 1;
		i -= K;
		In0 += In0s * i;
		In1 += i;
		dot_product_mkc_1x1x1(Out, In0, In1, M, K, n, OutS, In0S, In0s, In1S);
		In0 = _In0;
		In1 = _In1;
	}
	h = m;
	if (M < h) {
		M = h & 1;
		h -= M;
		Out += OutS * h;
		In0 += In0S * h;
		dot_product_mkc_1x8x1(Out, In0, In1, M, k, n, OutS, In0S, In0s, In1S);
		Out = _Out;
		In0 = _In0;
	}
}

//------------------------------------------------------------------------------
template <class T, class U>
static NOINLINE void dot_product_mkc_4x4x4 (T* _Out, 
																						T* _In0, 
																						T* _In1, 
																						volatile const U m, 
																						volatile const U k,
																						volatile const U n,
																						volatile U OutS = 0, 
																						volatile U In0S = 0, 
																						volatile U In0s = 0, 
																						volatile U In1S = 0) { 

	register T o0, o1, o2, o3; 
	register T i0, i1, i2, i3;
	register T in1_0_0, in1_0_1, in1_0_2, in1_0_3;
	register T in1_1_0, in1_1_1, in1_1_2, in1_1_3; 
	register T in1_2_0, in1_2_1, in1_2_2, in1_2_3;
	register T in1_3_0, in1_3_1, in1_3_2, in1_3_3; 

	T in0_0_0, in0_0_1, in0_0_2, in0_0_3;
	T in0_1_0, in0_1_1, in0_1_2, in0_1_3;
	T in0_2_0, in0_2_1, in0_2_2, in0_2_3;
	T in0_3_0, in0_3_1, in0_3_2, in0_3_3;

	T *Out, *In0, *In1;
	T *Out_0, *Out_1, *Out_2, *Out_3; 
	T *out_0, *out_1, *out_2, *out_3; 
	T *in0_0, *in0_1, *in0_2, *in0_3;
	T *in1_0, *in1_1, *in1_2, *in1_3;

	U h, M, K, N;
	register U i;
	register U j;

	if (!OutS) {OutS = n;}
	if (!In0S) {In0S = k;}
	if (!In0s) {In0s = (U)1;}
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
		in0_0 = In0 + In0S * 0;
		in0_1 = In0 + In0S * 1;
		in0_2 = In0 + In0S * 2;
		in0_3 = In0 + In0S * 3;
		In0 += In0S * 4;
		In1 = _In1;
		for (i = K; i; i--) {
			out_0 = Out_0;
			out_1 = Out_1;
			out_2 = Out_2;
			out_3 = Out_3;
			in0_0_0 = *(in0_0 + In0s * 0);
			in0_0_1 = *(in0_0 + In0s * 1);
			in0_0_2 = *(in0_0 + In0s * 2);
			in0_0_3 = *(in0_0 + In0s * 3);
			in0_0 += In0s * 4;
			in0_1_0 = *(in0_1 + In0s * 0);
			in0_1_1 = *(in0_1 + In0s * 1);
			in0_1_2 = *(in0_1 + In0s * 2);
			in0_1_3 = *(in0_1 + In0s * 3);
			in0_1 += In0s * 4;
			in0_2_0 = *(in0_2 + In0s * 0);
			in0_2_1 = *(in0_2 + In0s * 1);
			in0_2_2 = *(in0_2 + In0s * 2);
			in0_2_3 = *(in0_2 + In0s * 3);
			in0_2 += In0s * 4;
			in0_3_0 = *(in0_3 + In0s * 0);
			in0_3_1 = *(in0_3 + In0s * 1);
			in0_3_2 = *(in0_3 + In0s * 2);
			in0_3_3 = *(in0_3 + In0s * 3);
			in0_3 += In0s * 4;
			in1_0 = In1 + 0 * In1S;
			in1_1 = In1 + 1 * In1S;
			in1_2 = In1 + 2 * In1S;
			in1_3 = In1 + 3 * In1S;
			In1 += 4;
			for (j = N; j; j--) {
				in1_0_0 = *(in1_0 + 0);
				in1_0_1 = *(in1_0 + 1);
				in1_0_2 = *(in1_0 + 2);
				in1_0_3 = *(in1_0 + 3);
				in1_0 += In1S * 4;
				in1_1_0 = *(in1_1 + 0);
				in1_1_1 = *(in1_1 + 1);
				in1_1_2 = *(in1_1 + 2);
				in1_1_3 = *(in1_1 + 3);
				in1_1 += In1S * 4;
				in1_2_0 = *(in1_2 + 0);
				in1_2_1 = *(in1_2 + 1);
				in1_2_2 = *(in1_2 + 2);
				in1_2_3 = *(in1_2 + 3);
				in1_2 += In1S * 4;
				in1_3_0 = *(in1_3 + 0);
				in1_3_1 = *(in1_3 + 1);
				in1_3_2 = *(in1_3 + 2);
				in1_3_3 = *(in1_3 + 3);
				in1_3 += In1S * 4;
				i0 = in0_0_0;
				i1 = in0_0_1;
				i2 = in0_0_2;
				i3 = in0_0_3;
				o0  = i0 * in1_0_0;
				o0 += i1 * in1_0_1;
				o0 += i2 * in1_0_2;
				o0 += i3 * in1_0_3;
				o1  = i0 * in1_1_0;
				o1 += i1 * in1_1_1;
				o1 += i2 * in1_1_2;
				o1 += i3 * in1_1_3;
				o2  = i0 * in1_2_0;
				o2 += i1 * in1_2_1;
				o2 += i2 * in1_2_2;
				o2 += i3 * in1_2_3;
				o3  = i0 * in1_3_0;
				o3 += i1 * in1_3_1;
				o3 += i2 * in1_3_2;
				o3 += i3 * in1_3_3;
				*(out_0 + 0) += o0;
				*(out_0 + 1) += o1;
				*(out_0 + 2) += o2;
				*(out_0 + 3) += o3;
				out_0 += 4;
				i0 = in0_1_0;
				i1 = in0_1_1;
				i2 = in0_1_2;
				i3 = in0_1_3;
				o0  = i0 * in1_0_0;
				o0 += i1 * in1_0_1;
				o0 += i2 * in1_0_2;
				o0 += i3 * in1_0_3;
				o1  = i0 * in1_1_0;
				o1 += i1 * in1_1_1;
				o1 += i2 * in1_1_2;
				o1 += i3 * in1_1_3;
				o2  = i0 * in1_2_0;
				o2 += i1 * in1_2_1;
				o2 += i2 * in1_2_2;
				o2 += i3 * in1_2_3;
				o3  = i0 * in1_3_0;
				o3 += i1 * in1_3_1;
				o3 += i2 * in1_3_2;
				o3 += i3 * in1_3_3;
				*(out_1 + 0) += o0;
				*(out_1 + 1) += o1;
				*(out_1 + 2) += o2;
				*(out_1 + 3) += o3;
				out_1 += 4;
				i0 = in0_2_0;
				i1 = in0_2_1;
				i2 = in0_2_2;
				i3 = in0_2_3;
				o0  = i0 * in1_0_0;
				o0 += i1 * in1_0_1;
				o0 += i2 * in1_0_2;
				o0 += i3 * in1_0_3;
				o1  = i0 * in1_1_0;
				o1 += i1 * in1_1_1;
				o1 += i2 * in1_1_2;
				o1 += i3 * in1_1_3;
				o2  = i0 * in1_2_0;
				o2 += i1 * in1_2_1;
				o2 += i2 * in1_2_2;
				o2 += i3 * in1_2_3;
				o3  = i0 * in1_3_0;
				o3 += i1 * in1_3_1;
				o3 += i2 * in1_3_2;
				o3 += i3 * in1_3_3;
				*(out_2 + 0) += o0;
				*(out_2 + 1) += o1;
				*(out_2 + 2) += o2;
				*(out_2 + 3) += o3;
				out_2 += 4;
				i0 = in0_3_0;
				i1 = in0_3_1;
				i2 = in0_3_2;
				i3 = in0_3_3;
				o0  = i0 * in1_0_0;
				o0 += i1 * in1_0_1;
				o0 += i2 * in1_0_2;
				o0 += i3 * in1_0_3;
				o1  = i0 * in1_1_0;
				o1 += i1 * in1_1_1;
				o1 += i2 * in1_1_2;
				o1 += i3 * in1_1_3;
				o2  = i0 * in1_2_0;
				o2 += i1 * in1_2_1;
				o2 += i2 * in1_2_2;
				o2 += i3 * in1_2_3;
				o3  = i0 * in1_3_0;
				o3 += i1 * in1_3_1;
				o3 += i2 * in1_3_2;
				o3 += i3 * in1_3_3;
				*(out_3 + 0) += o0;
				*(out_3 + 1) += o1;
				*(out_3 + 2) += o2;
				*(out_3 + 3) += o3;
				out_3 += 4;
			}
		}
	}

	Out = _Out;
	In0 = _In0;
	In1 = _In1;
	M <<= 2;
	K <<= 2;
	N <<= 2;
	j = n;
	if (N < j) {
		N = j & 3;
		j -= N;
		Out += j;
		In1 += j * In1S;
		dot_product_mkc_2x2x2(Out, In0, In1, M, K, N, OutS, In0S, In0s, In1S);
		Out = _Out;
		In1 = _In1;
	}
	i = k;
	if (K < i) {
		K = i & 3;
		i -= K;
		In0 += In0s * i;
		In1 += i;
		dot_product_mkc_2x2x2(Out, In0, In1, M, K, n, OutS, In0S, In0s, In1S);
		In0 = _In0;
		In1 = _In1;
	}
	h = m;
	if (M < h) {
		M = h & 3;
		h -= M;
		Out += OutS * h;
		In0 += In0S * h;
		dot_product_mkc_2x2x2(Out, In0, In1, M, k, n, OutS, In0S, In0s, In1S);
		Out = _Out;
		In0 = _In0;
	}
}

//------------------------------------------------------------------------------
#endif

