# ifndef _vmdot_product_mkn_txx
# define _vmdot_product_mkn_txx

//------------------------------------------------------------------------------
# include "clas_defs.h"

# include <iostream>
using namespace std;

//------------------------------------------------------------------------------
template <class T, class U>
static NOINLINE void vmdot_product_1x1x1 (T* _Out, 
																					T* _In0, 
																					T* _In1, 
																					volatile const U m, 
																					volatile const U k,
																					volatile const U n,
																					volatile U OutS = 0, 
																					volatile U In0S = 0, 
																					volatile U In0s = 0, 
																					volatile const U In1S = 0) { 

	register T o0, i0;
	register T in1_0_0; 

	T in0_0_0;

	T *Out, *In0, *In1;
	T *Out_0; 
	T *out_0; 
	T *in0_0;
	T *in1_0;

	U h;
	register U i;
	register U j;

	Out = _Out;
	In0 = _In0;
	for (h = m; h; h--) {
		Out_0 = Out + OutS * 0;
		Out += OutS;
		in0_0 = In0 + In0S * 0;
		In0 += In0S;
		In1 = _In1;
		for (i = k; i; i--) {
			out_0 = Out_0;
			in0_0_0 = *(in0_0 + In0s * 0);
			in0_0 += In0s * 1;
			in1_0 = In1 + In1S * 0;
			In1 += In1S * 1;
			for (j = n; j; j--) {
				in1_0_0 = *(in1_0 + 0);
				in1_0 += 1;
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
static NOINLINE void vmdot_product_2x2x2 (T* _Out, 
																					T* _In0, 
																					T* _In1, 
																					volatile const U m, 
																					volatile const U k,
																					volatile const U n,
																					volatile U OutS = 0, 
																					volatile U In0S = 0, 
																					volatile U In0s = 0, 
																					volatile const U In1S = 0) { 

	register T o0, o1, i0, i1;
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
			in1_0 = In1 + In1S * 0;
			in1_1 = In1 + In1S * 1;
			In1 += In1S * 2;
			for (j = N; j; j--) {
				in1_0_0 = *(in1_0 + 0);
				in1_0_1 = *(in1_0 + 1);
				in1_0 += 2;
				in1_1_0 = *(in1_1 + 0);
				in1_1_1 = *(in1_1 + 1);
				in1_1 += 2;

				i0 = in0_0_0;
				i1 = in0_0_1;
				o0  = i0 * in1_0_0;
				o1  = i0 * in1_0_1;
				o0 += i1 * in1_1_0;
				o1 += i1 * in1_1_1;
				*(out_0 + 0) += o0;
				*(out_0 + 1) += o1;
				out_0 += 2;

				i0 = in0_1_0;
				i1 = in0_1_1;
				o0  = i0 * in1_0_0;
				o1  = i0 * in1_0_1;
				o0 += i1 * in1_1_0;
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
	M = m & 1;
	K = k & 1;
	N = n & 1;
	h = m;
	i = k;
	j = n;
	if (M) {
		h -= M;
		Out += OutS * h;
		In0 += In0S * h;
		vmdot_product_1x1x1(Out, In0, In1, M, k, n, OutS, In0S, In0s, In1S);
		Out = _Out;
		In0 = _In0;
	}
	if (K) {
		i -= K;
		In0 += In0s * i;
		In1 += In1S * i;
		vmdot_product_1x1x1(Out, In0, In1, h, K, n, OutS, In0S, In0s, In1S);
		In0 = _In0;
		In1 = _In1;
	}
	if (N) {
		j -= N;
		Out += j;
		In1 += j;
		vmdot_product_1x1x1(Out, In0, In1, h, i, N, OutS, In0S, In0s, In1S);
	}
}

//------------------------------------------------------------------------------
template <class T, class U>
static NOINLINE void vmdot_product_4x4x4 (T* _Out, 
																					T* _In0, 
																					T* _In1, 
																					volatile const U m, 
																					volatile const U k,
																					volatile const U n,
																					volatile U OutS = 0, 
																					volatile U In0S = 0, 
																					volatile U In0s = 0, 
																					volatile U In1S = 0) { 
	if (!OutS) (OutS = n);																					
	if (!In0S) (In0S = k);																					
	if (!In0s) (In0s = 1);																					
	if (!In1S) (In1S = n);																					

	register T o0, o1, o2, o3, i0, i1, i2, i3;
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
			in1_0 = In1 + In1S * 0;
			in1_1 = In1 + In1S * 1;
			in1_2 = In1 + In1S * 2;
			in1_3 = In1 + In1S * 3;
			In1 += In1S * 4;
			for (j = N; j; j--) {
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
				o0  = i0 * in1_0_0;
				o1  = i0 * in1_0_1;
				o2  = i0 * in1_0_2;
				o3  = i0 * in1_0_3;
				o0 += i1 * in1_1_0;
				o1 += i1 * in1_1_1;
				o2 += i1 * in1_1_2;
				o3 += i1 * in1_1_3;
				o0 += i2 * in1_2_0;
				o1 += i2 * in1_2_1;
				o2 += i2 * in1_2_2;
				o3 += i2 * in1_2_3;
				o0 += i3 * in1_3_0;
				o1 += i3 * in1_3_1;
				o2 += i3 * in1_3_2;
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
				o1  = i0 * in1_0_1;
				o2  = i0 * in1_0_2;
				o3  = i0 * in1_0_3;
				o0 += i1 * in1_1_0;
				o1 += i1 * in1_1_1;
				o2 += i1 * in1_1_2;
				o3 += i1 * in1_1_3;
				o0 += i2 * in1_2_0;
				o1 += i2 * in1_2_1;
				o2 += i2 * in1_2_2;
				o3 += i2 * in1_2_3;
				o0 += i3 * in1_3_0;
				o1 += i3 * in1_3_1;
				o2 += i3 * in1_3_2;
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
				o1  = i0 * in1_0_1;
				o2  = i0 * in1_0_2;
				o3  = i0 * in1_0_3;
				o0 += i1 * in1_1_0;
				o1 += i1 * in1_1_1;
				o2 += i1 * in1_1_2;
				o3 += i1 * in1_1_3;
				o0 += i2 * in1_2_0;
				o1 += i2 * in1_2_1;
				o2 += i2 * in1_2_2;
				o3 += i2 * in1_2_3;
				o0 += i3 * in1_3_0;
				o1 += i3 * in1_3_1;
				o2 += i3 * in1_3_2;
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
				o1  = i0 * in1_0_1;
				o2  = i0 * in1_0_2;
				o3  = i0 * in1_0_3;
				o0 += i1 * in1_1_0;
				o1 += i1 * in1_1_1;
				o2 += i1 * in1_1_2;
				o3 += i1 * in1_1_3;
				o0 += i2 * in1_2_0;
				o1 += i2 * in1_2_1;
				o2 += i2 * in1_2_2;
				o3 += i2 * in1_2_3;
				o0 += i3 * in1_3_0;
				o1 += i3 * in1_3_1;
				o2 += i3 * in1_3_2;
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
	M = m & 3;
	K = k & 3;
	N = n & 3;
	h = m;
	i = k;
	j = n;
	if (M) {
		h -= M;
		Out += OutS * h;
		In0 += In0S * h;
		vmdot_product_2x2x2(Out, In0, In1, M, k, n, OutS, In0S, In0s, In1S);
		Out = _Out;
		In0 = _In0;
	}
	if (K) {
		i -= K;
		In0 += In0s * i;
		In1 += In1S * i;
		vmdot_product_2x2x2(Out, In0, In1, h, K, n, OutS, In0S, In0s, In1S);
		In0 = _In0;
		In1 = _In1;
	}
	if (N) {
		j -= N;
		Out += j;
		In1 += j;
		vmdot_product_2x2x2(Out, In0, In1, h, i, N, OutS, In0S, In0s, In1S);
	}
}

//------------------------------------------------------------------------------
#endif

