# ifndef _ent_product_mkn_txx
# define _ent_product_mkn_txx

//------------------------------------------------------------------------------
# include "clas.txx"

//------------------------------------------------------------------------------
template <class T, class U>
static NOINLINE void ent_product_mkn_1x1x1 (T* _Out, 
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

	if (!OutS) {OutS = n*k;}
	if (!In0S) {In0S = k;}
	if (!In0s) {In0s = (U)1;}
	if (!In1S) {In1S = k;}
	M = m;
	K = k;
	N = n;

	Out = _Out;
	In0 = _In0;

	for (h = M; h; h--) {
		Out_0 = Out + 0 * OutS;
		Out += OutS * 1;
		in0_0 = In0 + 0 * In0S;
		In0 += In0S * 1;
		In1 = _In1;
		for (i = K; i; i--) {
			out_0 = Out_0;
			Out_0 += 1;
			in0_0_0 = *(in0_0 + 0 * In0s);
			in0_0 += In0s * 1;
			in1_0 = In1 + 0 * In1S;
			In1 += 1;
			for (j = N; j; j--) {
				in1_0_0 = *(in1_0 + 0);
				in1_0 += In1S;
				i0 = in0_0_0;
				o0 = i0 * in1_0_0;
				*(out_0 + 0) += o0;
				out_0 += In1S;
			}
		}
	}
}

//------------------------------------------------------------------------------
template <class T, class U>
static NOINLINE void ent_product_mkn_1x2x1 (T* _Out, 
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

	T in0_0_0, in0_0_1;

	T *Out, *In0, *In1;
	T *Out_0; 
	T *out_0; 
	T *in0_0;
	T *in1_0;

	U h, M, K, N;
	register U i;
	register U j;

	if (!OutS) {OutS = n*k;}
	if (!In0S) {In0S = k;}
	if (!In0s) {In0s = (U)1;}
	if (!In1S) {In1S = k;}
	M = m;
	K = k >> 1;
	N = n;

	Out = _Out;
	In0 = _In0;

	for (h = M; h; h--) {
		Out_0 = Out + 0 * OutS;
		Out += OutS * 1;
		in0_0 = In0 + 0 * In0S;
		In0 += In0S * 1;
		In1 = _In1;
		for (i = K; i; i--) {
			out_0 = Out_0;
			Out_0 += 2;
			in0_0_0 = *(in0_0 + 0 * In0s);
			in0_0_1 = *(in0_0 + 1 * In0s);
			in0_0 += In0s * 2;
			in1_0 = In1 + 0 * In1S;
			In1 += 2;
			for (j = N; j; j--) {
				in1_0_0 = *(in1_0 + 0);
				in1_0_1 = *(in1_0 + 1);
				in1_0 += In1S;
				i0 = in0_0_0;
				i1 = in0_0_1;
				o0 = i0 * in1_0_0;
				o1 = i1 * in1_0_1;
				*(out_0 + 0) += o0;
				*(out_0 + 1) += o1;
				out_0 += In1S;
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
		Out += i;
		In0 += In0s * i;
		In1 += i;
		ent_product_mkn_1x1x1(Out, In0, In1, m, K, n, OutS, In0S, In0s, In1S);
		Out = _Out;
		In0 = _In0;
		In1 = _In1;
	}
}

//------------------------------------------------------------------------------
template <class T, class U>
static NOINLINE void ent_product_mkn_1x4x1 (T* _Out, 
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

	T in0_0_0, in0_0_1, in0_0_2, in0_0_3;

	T *Out, *In0, *In1;
	T *Out_0; 
	T *out_0; 
	T *in0_0;
	T *in1_0;

	U h, M, K, N;
	register U i;
	register U j;

	if (!OutS) {OutS = n*k;}
	if (!In0S) {In0S = k;}
	if (!In0s) {In0s = (U)1;}
	if (!In1S) {In1S = k;}
	M = m;
	K = k >> 2;
	N = n;

	Out = _Out;
	In0 = _In0;

	for (h = M; h; h--) {
		Out_0 = Out + 0 * OutS;
		Out += OutS * 1;
		in0_0 = In0 + 0 * In0S;
		In0 += In0S * 1;
		In1 = _In1;
		for (i = K; i; i--) {
			out_0 = Out_0;
			Out_0 += 4;
			in0_0_0 = *(in0_0 + 0 * In0s);
			in0_0_1 = *(in0_0 + 1 * In0s);
			in0_0_2 = *(in0_0 + 2 * In0s);
			in0_0_3 = *(in0_0 + 3 * In0s);
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
				o0 = i0 * in1_0_0;
				o1 = i1 * in1_0_1;
				o2 = i2 * in1_0_2;
				o3 = i3 * in1_0_3;
				*(out_0 + 0) += o0;
				*(out_0 + 1) += o1;
				*(out_0 + 2) += o2;
				*(out_0 + 3) += o3;
				out_0 += In1S;
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
		Out += i;
		In0 += In0s * i;
		In1 += i;
		ent_product_mkn_1x2x1(Out, In0, In1, m, K, n, OutS, In0S, In0s, In1S);
		Out = _Out;
		In0 = _In0;
		In1 = _In1;
	}
}

//------------------------------------------------------------------------------
template <class T, class U>
static NOINLINE void ent_product_mkn_1x8x1 (T* _Out, 
																						T* _In0, 
																						T* _In1, 
																						volatile const U m, 
																						volatile const U k,
																						volatile const U n,
																						volatile U OutS = 0, 
																						volatile U In0S = 0, 
																						volatile U In0s = 0, 
																						volatile U In1S = 0) { 

	register T o0, o1, o2, o3, o4, o5, o6, o7; 
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

	if (!OutS) {OutS = n*k;}
	if (!In0S) {In0S = k;}
	if (!In0s) {In0s = (U)1;}
	if (!In1S) {In1S = k;}
	M = m;
	K = k >> 3;
	N = n;

	Out = _Out;
	In0 = _In0;

	for (h = M; h; h--) {
		Out_0 = Out + 0 * OutS;
		Out += OutS * 1;
		in0_0 = In0 + 0 * In0S;
		In0 += In0S * 1;
		In1 = _In1;
		for (i = K; i; i--) {
			out_0 = Out_0;
			Out_0 += 8;
			in0_0_0 = *(in0_0 + 0 * In0s);
			in0_0_1 = *(in0_0 + 1 * In0s);
			in0_0_2 = *(in0_0 + 2 * In0s);
			in0_0_3 = *(in0_0 + 3 * In0s);
			in0_0_4 = *(in0_0 + 4 * In0s);
			in0_0_5 = *(in0_0 + 5 * In0s);
			in0_0_6 = *(in0_0 + 6 * In0s);
			in0_0_7 = *(in0_0 + 7 * In0s);
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
				o0 = i0 * in1_0_0;
				o1 = i1 * in1_0_1;
				o2 = i2 * in1_0_2;
				o3 = i3 * in1_0_3;
				o4 = i4 * in1_0_4;
				o5 = i5 * in1_0_5;
				o6 = i6 * in1_0_6;
				o7 = i7 * in1_0_7;
				*(out_0 + 0) += o0;
				*(out_0 + 1) += o1;
				*(out_0 + 2) += o2;
				*(out_0 + 3) += o3;
				*(out_0 + 4) += o4;
				*(out_0 + 5) += o5;
				*(out_0 + 6) += o6;
				*(out_0 + 7) += o7;
				out_0 += In1S;
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
		Out += i;
		In0 += In0s * i;
		In1 += i;
		ent_product_mkn_1x4x1(Out, In0, In1, m, K, n, OutS, In0S, In0s, In1S);
		Out = _Out;
		In0 = _In0;
		In1 = _In1;
	}
}

//------------------------------------------------------------------------------
#endif

