#ifndef _vmdot_product_4_txx
#define _vmdot_product_4_txx

//------------------------------------------------------------------------------
// Note In1s is also the output stride
//------------------------------------------------------------------------------
template <class T, class U>
static inline void vmdot_product_4x1 (T* Out, 
																			T* In0, 
																			T* _In1, 
																			volatile const U k, 
																			volatile const U n = 1,
																			volatile const U In0S = 0,
																			volatile const U In0s = 0,
																			volatile const U In1s = 0) { 

	register T in0_0, in0_1, in0_2, in0_3;
	T in1_0;
	T *In1;
	T *Out0, *Out1, *Out2, *Out3;
	register T *out0, *out1, *out2, *out3;
	register T *in0, *in1;
	register U i, j;

	in0 = In0;
	In1 = _In1;
	Out0 = Out + In1s * 0;
	Out1 = Out + In1s * 1;
	Out2 = Out + In1s * 2;
	Out3 = Out + In1s * 3;

	for (i = k; i; i--) {
		out0 = Out0;
		out1 = Out1;
		out2 = Out2;
		out3 = Out3;
		in0_0 = *(in0 + 0);
		j  = In0S;
		in0_1 = *(in0 + j);
		j += In0S;
		in0_2 = *(in0 + j);
		j += In0S;
		in0_3 = *(in0 + j);
		in0 += In0s;
		in1 = In1;
		In1 += In1s;
		for (j = n; j; j--) {
			in1_0 = *(in1 +  0);
			*(out0 +  0) += in0_0 * in1_0; 
			*(out1 +  0) += in0_1 * in1_0; 
			*(out2 +  0) += in0_2 * in1_0; 
			*(out3 +  0) += in0_3 * in1_0; 
			in1 ++;
			out0 ++;
			out1 ++;
			out2 ++;
			out3 ++;
		}
	}
}

//------------------------------------------------------------------------------
template <class T, class U>
static inline void vmdot_product_4x2 (T* Out, 
																			T* In0, 
																			T* _In1, 
																			volatile const U k, 
																			volatile const U n = 1,
																			volatile const U In0S = 0,
																			volatile const U In0s = 0,
																			volatile const U In1s = 0) { 

	register T in0_0, in0_1, in0_2, in0_3;
	T in1_0, in1_1;
	T *In1;
	T *Out0, *Out1, *Out2, *Out3;
	register T *out0, *out1, *out2, *out3;
	register T *in0, *in1;
	register U i, j;
	volatile U div, mod;

	in0 = In0;
	In1 = _In1;
  Out0 = Out + In1s * 0;
	Out1 = Out + In1s * 1;
	Out2 = Out + In1s * 2;
	Out3 = Out + In1s * 3;

	div = n >> 1;
	mod = n & 1;

	for (i = k; i; i--) {
		out0 = Out0;
		out1 = Out1;
		out2 = Out2;
		out3 = Out3;
		in0_0 = *(in0 + 0);
		j  = In0S;
		in0_1 = *(in0 + j);
		j += In0S;
		in0_2 = *(in0 + j);
		j += In0S;
		in0_3 = *(in0 + j);
		in0 += In0s;
		in1 = In1;
		In1 += In1s;
		for (j = div; j; j--) {
			in1_0 = *(in1 + 0);
			in1_1 = *(in1 + 1);
			in1 += 2;
			*(out0 +  0) += in0_0 * in1_0; 
			*(out0 +  1) += in0_0 * in1_1; 
			*(out1 +  0) += in0_1 * in1_0; 
			*(out1 +  1) += in0_1 * in1_1; 
			*(out2 +  0) += in0_2 * in1_0; 
			*(out2 +  1) += in0_2 * in1_1; 
			*(out3 +  0) += in0_3 * in1_0; 
			*(out3 +  1) += in0_3 * in1_1; 
			out0 += 2;
			out1 += 2;
			out2 += 2;
			out3 += 2;
		}
	}

	if (mod) {
		div = n - mod;
		vmdot_product_4x1(Out + div, In0, _In1 + div, k, mod, In0S, In0s, In1s);
	}
}

//------------------------------------------------------------------------------
template <class T, class U>
static inline void vmdot_product_4x4 (T* Out, 
																			T* In0, 
																			T* _In1, 
																			volatile const U k, 
																			volatile const U n = 1,
																			volatile const U In0S = 0,
																			volatile const U In0s = 0,
																			volatile const U In1s = 0) { 

	T in1_0, in1_1, in1_2, in1_3;
	register T in0_0, in0_1, in0_2, in0_3;
	T *In1;
	T *Out0, *Out1, *Out2, *Out3;
	register T *out0, *out1, *out2, *out3;
	register T *in0, *in1;
	register U i, j;
	volatile U div, mod;

	in0 = In0;
	In1 = _In1;
	Out0 = Out + In1s * 0;
	Out1 = Out + In1s * 1;
	Out2 = Out + In1s * 2;
	Out3 = Out + In1s * 3;

	div = n >> 2;
	mod = n & 3;

	for (i = k; i; i--) {
		out0 = Out0;
		out1 = Out1;
		out2 = Out2;
		out3 = Out3;
		in0_0 = *(in0 + 0);
		j  = In0S;
		in0_1 = *(in0 + j);
		j += In0S;
		in0_2 = *(in0 + j);
		j += In0S;
		in0_3 = *(in0 + j);
		in0 += In0s;
		in1 = In1;
		In1 += In1s;
		for (j = div; j; j--) {
			in1_0 = *(in1 + 0);
			in1_1 = *(in1 + 1);
			in1_2 = *(in1 + 2);
			in1_3 = *(in1 + 3);
			*(out0 +  0) += in0_0 * in1_0; 
			*(out0 +  1) += in0_0 * in1_1; 
			*(out0 +  2) += in0_0 * in1_2; 
			*(out0 +  3) += in0_0 * in1_3; 
			*(out1 +  0) += in0_1 * in1_0; 
			*(out1 +  1) += in0_1 * in1_1; 
			*(out1 +  2) += in0_1 * in1_2; 
			*(out1 +  3) += in0_1 * in1_3; 
			*(out2 +  0) += in0_2 * in1_0; 
			*(out2 +  1) += in0_2 * in1_1; 
			*(out2 +  2) += in0_2 * in1_2; 
			*(out2 +  3) += in0_2 * in1_3; 
			*(out3 +  0) += in0_3 * in1_0; 
			*(out3 +  1) += in0_3 * in1_1; 
			*(out3 +  2) += in0_3 * in1_2; 
			*(out3 +  3) += in0_3 * in1_3; 
			in1 += 4;
			out0 += 4;
			out1 += 4;
			out2 += 4;
			out3 += 4;
		}
	}

	if (mod) {
		div = n - mod;
		vmdot_product_4x2(Out + div, In0, _In1 + div, k, mod, In0S, In0s, In1s);
	}
}

//------------------------------------------------------------------------------
template <class T, class U>
static inline void vmdot_product_4x8 (T* Out, 
																			T* In0, 
																			T* _In1, 
																			volatile const U k, 
																			volatile const U n = 1,
																			volatile const U In0S = 0,
																			volatile const U In0s = 0,
																			volatile const U In1s = 0) { 

	T in1_0, in1_1, in1_2, in1_3, in1_4, in1_5, in1_6, in1_7;
	register T in0_0, in0_1, in0_2, in0_3;
	T *In1;
	T *Out0, *Out1, *Out2, *Out3;
	register T *out0, *out1, *out2, *out3;
	register T *in0, *in1;
	register U i, j;
	volatile U div, mod;

	in0 = In0;
	In1 = _In1;
	Out0 = Out + In1s * 0;
	Out1 = Out + In1s * 1;
	Out2 = Out + In1s * 2;
	Out3 = Out + In1s * 3;

	div = n >> 3;
	mod = n & 7;

	for (i = k; i; i--) {
		out0 = Out0;
		out1 = Out1;
		out2 = Out2;
		out3 = Out3;
		in0_0 = *(in0 + 0);
		j  = In0S;
		in0_1 = *(in0 + j);
		j += In0S;
		in0_2 = *(in0 + j);
		j += In0S;
		in0_3 = *(in0 + j);
		in0 += In0s;
		in1 = In1;
		In1 += In1s;
		for (j = div; j; j--) {
			in1_0 = *(in1 + 0);
			in1_1 = *(in1 + 1);
			in1_2 = *(in1 + 2);
			in1_3 = *(in1 + 3);
			in1_4 = *(in1 + 4);
			in1_5 = *(in1 + 5);
			in1_6 = *(in1 + 6);
			in1_7 = *(in1 + 7);
			in1 += 8;
			*(out0 +  0) += in0_0 * in1_0; 
			*(out0 +  1) += in0_0 * in1_1; 
			*(out0 +  2) += in0_0 * in1_2; 
			*(out0 +  3) += in0_0 * in1_3; 
			*(out0 +  4) += in0_0 * in1_4; 
			*(out0 +  5) += in0_0 * in1_5; 
			*(out0 +  6) += in0_0 * in1_6; 
			*(out0 +  7) += in0_0 * in1_7; 
			*(out1 +  0) += in0_1 * in1_0; 
			*(out1 +  1) += in0_1 * in1_1; 
			*(out1 +  2) += in0_1 * in1_2; 
			*(out1 +  3) += in0_1 * in1_3; 
			*(out1 +  4) += in0_1 * in1_4; 
			*(out1 +  5) += in0_1 * in1_5; 
			*(out1 +  6) += in0_1 * in1_6; 
			*(out1 +  7) += in0_1 * in1_7; 
			*(out2 +  0) += in0_2 * in1_0; 
			*(out2 +  1) += in0_2 * in1_1; 
			*(out2 +  2) += in0_2 * in1_2; 
			*(out2 +  3) += in0_2 * in1_3; 
			*(out2 +  4) += in0_2 * in1_4; 
			*(out2 +  5) += in0_2 * in1_5; 
			*(out2 +  6) += in0_2 * in1_6; 
			*(out2 +  7) += in0_2 * in1_7; 
			*(out3 +  0) += in0_3 * in1_0; 
			*(out3 +  1) += in0_3 * in1_1; 
			*(out3 +  2) += in0_3 * in1_2; 
			*(out3 +  3) += in0_3 * in1_3; 
			*(out3 +  4) += in0_3 * in1_4; 
			*(out3 +  5) += in0_3 * in1_5; 
			*(out3 +  6) += in0_3 * in1_6; 
			*(out3 +  7) += in0_3 * in1_7; 
			out0 += 8;
			out1 += 8;
			out2 += 8;
			out3 += 8;
		}
	}

	if (mod) {
		div = n - mod;
		vmdot_product_4x4 (Out + div, In0, _In1 + div, k, mod, In0S, In0s, In1s);
	}
}

//------------------------------------------------------------------------------
template <class T, class U>
static inline void vmdot_product_4x16(T* Out, 
																			T* In0, 
																			T* _In1, 
																			volatile const U k, 
																			volatile const U n = 1,
																			volatile const U In0S = 0,
																			volatile const U In0s = 0,
																			volatile const U In1s = 0) { 

	T in1_0, in1_1, in1_2, in1_3, in1_4, in1_5, in1_6, in1_7;
	register T in0_0, in0_1, in0_2, in0_3;
	T *In1;
	T *Out0, *Out1, *Out2, *Out3;
	register T *out0, *out1, *out2, *out3;
	register T *in0, *in1;
	register U i, j;
	volatile U div, mod;

	in0 = In0;
	In1 = _In1;
	Out0 = Out + In1s * 0;
	Out1 = Out + In1s * 1;
	Out2 = Out + In1s * 2;
	Out3 = Out + In1s * 3;

	div = n >> 4;
	mod = n & 15;

	for (i = k; i; i--) {
		out0 = Out0;
		out1 = Out1;
		out2 = Out2;
		out3 = Out3;
		in0_0 = *(in0 + 0);
		j  = In0S;
		in0_1 = *(in0 + j);
		j += In0S;
		in0_2 = *(in0 + j);
		j += In0S;
		in0_3 = *(in0 + j);
		in0 += In0s;
		in1 = In1;
		In1 += In1s;
		for (j = div; j; j--) {
			in1_0 = *(in1 + 0);
			in1_1 = *(in1 + 1);
			in1_2 = *(in1 + 2);
			in1_3 = *(in1 + 3);
			in1_4 = *(in1 + 4);
			in1_5 = *(in1 + 5);
			in1_6 = *(in1 + 6);
			in1_7 = *(in1 + 7);
			in1 += 8;
			*(out0 +  0) += in0_0 * in1_0; 
			*(out0 +  1) += in0_0 * in1_1; 
			*(out0 +  2) += in0_0 * in1_2; 
			*(out0 +  3) += in0_0 * in1_3; 
			*(out0 +  4) += in0_0 * in1_4; 
			*(out0 +  5) += in0_0 * in1_5; 
			*(out0 +  6) += in0_0 * in1_6; 
			*(out0 +  7) += in0_0 * in1_7; 
			*(out1 +  0) += in0_1 * in1_0; 
			*(out1 +  1) += in0_1 * in1_1; 
			*(out1 +  2) += in0_1 * in1_2; 
			*(out1 +  3) += in0_1 * in1_3; 
			*(out1 +  4) += in0_1 * in1_4; 
			*(out1 +  5) += in0_1 * in1_5; 
			*(out1 +  6) += in0_1 * in1_6; 
			*(out1 +  7) += in0_1 * in1_7; 
			*(out2 +  0) += in0_2 * in1_0; 
			*(out2 +  1) += in0_2 * in1_1; 
			*(out2 +  2) += in0_2 * in1_2; 
			*(out2 +  3) += in0_2 * in1_3; 
			*(out2 +  4) += in0_2 * in1_4; 
			*(out2 +  5) += in0_2 * in1_5; 
			*(out2 +  6) += in0_2 * in1_6; 
			*(out2 +  7) += in0_2 * in1_7; 
			*(out3 +  0) += in0_3 * in1_0; 
			*(out3 +  1) += in0_3 * in1_1; 
			*(out3 +  2) += in0_3 * in1_2; 
			*(out3 +  3) += in0_3 * in1_3; 
			*(out3 +  4) += in0_3 * in1_4; 
			*(out3 +  5) += in0_3 * in1_5; 
			*(out3 +  6) += in0_3 * in1_6; 
			*(out3 +  7) += in0_3 * in1_7; 
			out0 += 8;
			out1 += 8;
			out2 += 8;
			out3 += 8;
			in1_0 = *(in1 + 0);
			in1_1 = *(in1 + 1);
			in1_2 = *(in1 + 2);
			in1_3 = *(in1 + 3);
			in1_4 = *(in1 + 4);
			in1_5 = *(in1 + 5);
			in1_6 = *(in1 + 6);
			in1_7 = *(in1 + 7);
			in1 += 8;
			*(out0 +  0) += in0_0 * in1_0; 
			*(out0 +  1) += in0_0 * in1_1; 
			*(out0 +  2) += in0_0 * in1_2; 
			*(out0 +  3) += in0_0 * in1_3; 
			*(out0 +  4) += in0_0 * in1_4; 
			*(out0 +  5) += in0_0 * in1_5; 
			*(out0 +  6) += in0_0 * in1_6; 
			*(out0 +  7) += in0_0 * in1_7; 
			*(out1 +  0) += in0_1 * in1_0; 
			*(out1 +  1) += in0_1 * in1_1; 
			*(out1 +  2) += in0_1 * in1_2; 
			*(out1 +  3) += in0_1 * in1_3; 
			*(out1 +  4) += in0_1 * in1_4; 
			*(out1 +  5) += in0_1 * in1_5; 
			*(out1 +  6) += in0_1 * in1_6; 
			*(out1 +  7) += in0_1 * in1_7; 
			*(out2 +  0) += in0_2 * in1_0; 
			*(out2 +  1) += in0_2 * in1_1; 
			*(out2 +  2) += in0_2 * in1_2; 
			*(out2 +  3) += in0_2 * in1_3; 
			*(out2 +  4) += in0_2 * in1_4; 
			*(out2 +  5) += in0_2 * in1_5; 
			*(out2 +  6) += in0_2 * in1_6; 
			*(out2 +  7) += in0_2 * in1_7; 
			*(out3 +  0) += in0_3 * in1_0; 
			*(out3 +  1) += in0_3 * in1_1; 
			*(out3 +  2) += in0_3 * in1_2; 
			*(out3 +  3) += in0_3 * in1_3; 
			*(out3 +  4) += in0_3 * in1_4; 
			*(out3 +  5) += in0_3 * in1_5; 
			*(out3 +  6) += in0_3 * in1_6; 
			*(out3 +  7) += in0_3 * in1_7; 
			out0 += 8;
			out1 += 8;
			out2 += 8;
			out3 += 8;
		}
	}

	if (mod) {
		div = n - mod;
		vmdot_product_4x8 (Out + div, In0, _In1 + div, k, mod, In0S, In0s, In1s);
	}
}

//------------------------------------------------------------------------------
template <class T, class U>
static inline void vmdot_product_4x32(T* Out, 
																			T* In0, 
																			T* _In1, 
																			volatile const U k, 
																			volatile const U n = 1,
																			volatile const U In0S = 0,
																			volatile const U In0s = 0,
																			volatile const U In1s = 0) { 

	T in1_0, in1_1, in1_2, in1_3, in1_4, in1_5, in1_6, in1_7;
	register T in0_0, in0_1, in0_2, in0_3;
	T *In1;
	T *Out0, *Out1, *Out2, *Out3;
	register T *out0, *out1, *out2, *out3;
	register T *in0, *in1;
	register U i, j;
	volatile U div, mod;

	in0 = In0;
	In1 = _In1;
	Out0 = Out + In1s * 0;
	Out1 = Out + In1s * 1;
	Out2 = Out + In1s * 2;
	Out3 = Out + In1s * 3;

	div = n >> 5;
	mod = n & 31;

	for (i = k; i; i--) {
		out0 = Out0;
		out1 = Out1;
		out2 = Out2;
		out3 = Out3;
		in0_0 = *(in0 + 0);
		j  = In0S;
		in0_1 = *(in0 + j);
		j += In0S;
		in0_2 = *(in0 + j);
		j += In0S;
		in0_3 = *(in0 + j);
		in0 += In0s;
		in1 = In1;
		In1 += In1s;
		for (j = div; j; j--) {
			in1_0 = *(in1 + 0);
			in1_1 = *(in1 + 1);
			in1_2 = *(in1 + 2);
			in1_3 = *(in1 + 3);
			in1_4 = *(in1 + 4);
			in1_5 = *(in1 + 5);
			in1_6 = *(in1 + 6);
			in1_7 = *(in1 + 7);
			in1 += 8;
			*(out0 +  0) += in0_0 * in1_0; 
			*(out0 +  1) += in0_0 * in1_1; 
			*(out0 +  2) += in0_0 * in1_2; 
			*(out0 +  3) += in0_0 * in1_3; 
			*(out0 +  4) += in0_0 * in1_4; 
			*(out0 +  5) += in0_0 * in1_5; 
			*(out0 +  6) += in0_0 * in1_6; 
			*(out0 +  7) += in0_0 * in1_7; 
			*(out1 +  0) += in0_1 * in1_0; 
			*(out1 +  1) += in0_1 * in1_1; 
			*(out1 +  2) += in0_1 * in1_2; 
			*(out1 +  3) += in0_1 * in1_3; 
			*(out1 +  4) += in0_1 * in1_4; 
			*(out1 +  5) += in0_1 * in1_5; 
			*(out1 +  6) += in0_1 * in1_6; 
			*(out1 +  7) += in0_1 * in1_7; 
			*(out2 +  0) += in0_2 * in1_0; 
			*(out2 +  1) += in0_2 * in1_1; 
			*(out2 +  2) += in0_2 * in1_2; 
			*(out2 +  3) += in0_2 * in1_3; 
			*(out2 +  4) += in0_2 * in1_4; 
			*(out2 +  5) += in0_2 * in1_5; 
			*(out2 +  6) += in0_2 * in1_6; 
			*(out2 +  7) += in0_2 * in1_7; 
			*(out3 +  0) += in0_3 * in1_0; 
			*(out3 +  1) += in0_3 * in1_1; 
			*(out3 +  2) += in0_3 * in1_2; 
			*(out3 +  3) += in0_3 * in1_3; 
			*(out3 +  4) += in0_3 * in1_4; 
			*(out3 +  5) += in0_3 * in1_5; 
			*(out3 +  6) += in0_3 * in1_6; 
			*(out3 +  7) += in0_3 * in1_7; 
			out0 += 8;
			out1 += 8;
			out2 += 8;
			out3 += 8;
			in1_0 = *(in1 + 0);
			in1_1 = *(in1 + 1);
			in1_2 = *(in1 + 2);
			in1_3 = *(in1 + 3);
			in1_4 = *(in1 + 4);
			in1_5 = *(in1 + 5);
			in1_6 = *(in1 + 6);
			in1_7 = *(in1 + 7);
			in1 += 8;
			*(out0 +  0) += in0_0 * in1_0; 
			*(out0 +  1) += in0_0 * in1_1; 
			*(out0 +  2) += in0_0 * in1_2; 
			*(out0 +  3) += in0_0 * in1_3; 
			*(out0 +  4) += in0_0 * in1_4; 
			*(out0 +  5) += in0_0 * in1_5; 
			*(out0 +  6) += in0_0 * in1_6; 
			*(out0 +  7) += in0_0 * in1_7; 
			*(out1 +  0) += in0_1 * in1_0; 
			*(out1 +  1) += in0_1 * in1_1; 
			*(out1 +  2) += in0_1 * in1_2; 
			*(out1 +  3) += in0_1 * in1_3; 
			*(out1 +  4) += in0_1 * in1_4; 
			*(out1 +  5) += in0_1 * in1_5; 
			*(out1 +  6) += in0_1 * in1_6; 
			*(out1 +  7) += in0_1 * in1_7; 
			*(out2 +  0) += in0_2 * in1_0; 
			*(out2 +  1) += in0_2 * in1_1; 
			*(out2 +  2) += in0_2 * in1_2; 
			*(out2 +  3) += in0_2 * in1_3; 
			*(out2 +  4) += in0_2 * in1_4; 
			*(out2 +  5) += in0_2 * in1_5; 
			*(out2 +  6) += in0_2 * in1_6; 
			*(out2 +  7) += in0_2 * in1_7; 
			*(out3 +  0) += in0_3 * in1_0; 
			*(out3 +  1) += in0_3 * in1_1; 
			*(out3 +  2) += in0_3 * in1_2; 
			*(out3 +  3) += in0_3 * in1_3; 
			*(out3 +  4) += in0_3 * in1_4; 
			*(out3 +  5) += in0_3 * in1_5; 
			*(out3 +  6) += in0_3 * in1_6; 
			*(out3 +  7) += in0_3 * in1_7; 
			out0 += 8;
			out1 += 8;
			out2 += 8;
			out3 += 8;
			in1_0 = *(in1 + 0);
			in1_1 = *(in1 + 1);
			in1_2 = *(in1 + 2);
			in1_3 = *(in1 + 3);
			in1_4 = *(in1 + 4);
			in1_5 = *(in1 + 5);
			in1_6 = *(in1 + 6);
			in1_7 = *(in1 + 7);
			in1 += 8;
			*(out0 +  0) += in0_0 * in1_0; 
			*(out0 +  1) += in0_0 * in1_1; 
			*(out0 +  2) += in0_0 * in1_2; 
			*(out0 +  3) += in0_0 * in1_3; 
			*(out0 +  4) += in0_0 * in1_4; 
			*(out0 +  5) += in0_0 * in1_5; 
			*(out0 +  6) += in0_0 * in1_6; 
			*(out0 +  7) += in0_0 * in1_7; 
			*(out1 +  0) += in0_1 * in1_0; 
			*(out1 +  1) += in0_1 * in1_1; 
			*(out1 +  2) += in0_1 * in1_2; 
			*(out1 +  3) += in0_1 * in1_3; 
			*(out1 +  4) += in0_1 * in1_4; 
			*(out1 +  5) += in0_1 * in1_5; 
			*(out1 +  6) += in0_1 * in1_6; 
			*(out1 +  7) += in0_1 * in1_7; 
			*(out2 +  0) += in0_2 * in1_0; 
			*(out2 +  1) += in0_2 * in1_1; 
			*(out2 +  2) += in0_2 * in1_2; 
			*(out2 +  3) += in0_2 * in1_3; 
			*(out2 +  4) += in0_2 * in1_4; 
			*(out2 +  5) += in0_2 * in1_5; 
			*(out2 +  6) += in0_2 * in1_6; 
			*(out2 +  7) += in0_2 * in1_7; 
			*(out3 +  0) += in0_3 * in1_0; 
			*(out3 +  1) += in0_3 * in1_1; 
			*(out3 +  2) += in0_3 * in1_2; 
			*(out3 +  3) += in0_3 * in1_3; 
			*(out3 +  4) += in0_3 * in1_4; 
			*(out3 +  5) += in0_3 * in1_5; 
			*(out3 +  6) += in0_3 * in1_6; 
			*(out3 +  7) += in0_3 * in1_7; 
			out0 += 8;
			out1 += 8;
			out2 += 8;
			out3 += 8;
			in1_0 = *(in1 + 0);
			in1_1 = *(in1 + 1);
			in1_2 = *(in1 + 2);
			in1_3 = *(in1 + 3);
			in1_4 = *(in1 + 4);
			in1_5 = *(in1 + 5);
			in1_6 = *(in1 + 6);
			in1_7 = *(in1 + 7);
			in1 += 8;
			*(out0 +  0) += in0_0 * in1_0; 
			*(out0 +  1) += in0_0 * in1_1; 
			*(out0 +  2) += in0_0 * in1_2; 
			*(out0 +  3) += in0_0 * in1_3; 
			*(out0 +  4) += in0_0 * in1_4; 
			*(out0 +  5) += in0_0 * in1_5; 
			*(out0 +  6) += in0_0 * in1_6; 
			*(out0 +  7) += in0_0 * in1_7; 
			*(out1 +  0) += in0_1 * in1_0; 
			*(out1 +  1) += in0_1 * in1_1; 
			*(out1 +  2) += in0_1 * in1_2; 
			*(out1 +  3) += in0_1 * in1_3; 
			*(out1 +  4) += in0_1 * in1_4; 
			*(out1 +  5) += in0_1 * in1_5; 
			*(out1 +  6) += in0_1 * in1_6; 
			*(out1 +  7) += in0_1 * in1_7; 
			*(out2 +  0) += in0_2 * in1_0; 
			*(out2 +  1) += in0_2 * in1_1; 
			*(out2 +  2) += in0_2 * in1_2; 
			*(out2 +  3) += in0_2 * in1_3; 
			*(out2 +  4) += in0_2 * in1_4; 
			*(out2 +  5) += in0_2 * in1_5; 
			*(out2 +  6) += in0_2 * in1_6; 
			*(out2 +  7) += in0_2 * in1_7; 
			*(out3 +  0) += in0_3 * in1_0; 
			*(out3 +  1) += in0_3 * in1_1; 
			*(out3 +  2) += in0_3 * in1_2; 
			*(out3 +  3) += in0_3 * in1_3; 
			*(out3 +  4) += in0_3 * in1_4; 
			*(out3 +  5) += in0_3 * in1_5; 
			*(out3 +  6) += in0_3 * in1_6; 
			*(out3 +  7) += in0_3 * in1_7; 
			out0 += 8;
			out1 += 8;
			out2 += 8;
			out3 += 8;
		}
	}

	if (mod) {
		div = n - mod;
		vmdot_product_4x16(Out + div, In0, _In1 + div, k, mod, In0S, In0s, In1s);
	}
}

//------------------------------------------------------------------------------
#endif

