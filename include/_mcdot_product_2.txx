# ifndef _mcdot_product_2_txx
# define _mcdot_product_2_txx

//------------------------------------------------------------------------------
template <class T, class U>
static inline void mcdot_product_2x1 (T* Out, 
																			T* _In0, 
																			T* In1, 
																			volatile const U m, 
																			volatile const U k,
																			volatile const U Outs0,
																			volatile const U Outs1 = 1,
																			volatile const U In0s = 1,
																			volatile const U In1s = 1) { 
	register T out0, out1;
	register T in0_0;
	register T in1_0, in1_1;
	register T *in0, *in1;
	T *Out0, *Out1; 
	T *In0;
	T* In1_0, *In1_1; 
	register U i, j;

	Out0 = Out;
	Out1 = Out + Outs0;
	In0 = _In0;

	for (i = m; i; i--) {
		in0 = In0;
		In0 += In0s;
		in1 = In1;
		out0 = 0.;
		out1 = 0.;
		for (j = k; j; j--) {
			in0_0 = *(in0 + 0);
			in0 ++;
			in1_0 = *(in1 + 0);
			in1_1 = *(in1 + 1);
			in1 += In1s;
			out0 += in0_0 * in1_0; 
			out1 += in0_0 * in1_1; 
		}
		*Out0 += out0;
		*Out1 += out1;
		Out0 += Outs1;
		Out1 += Outs1;
	}
}

//------------------------------------------------------------------------------
template <class T, class U>
static inline void mcdot_product_2x2 (T* Out, 
																			T* _In0, 
																			T* In1, 
																			volatile const U m, 
																			volatile const U k,
																			volatile const U Outs0,
																			volatile const U Outs1 = 1,
																			volatile const U In0s = 1,
																			volatile const U In1s = 1) { 
	register T out0, out1;
	register T in0_0, in0_1;
	register T in1_0, in1_1;
	register T *in0, *in1;
	T *Out0, *Out1; 
	T *In0;
	T* In1_0, *In1_1; 
	volatile U div, mod;
	register U i, j;

	div = k >> 1;
	mod = k & 1;

	Out0 = Out;
	Out1 = Out + Outs0;
	In0 = _In0;

	for (i = m; i; i--) {
		in0 = In0;
		In0 += In0s;
		in1 = In1;
		out0 = 0.;
		out1 = 0.;
		for (j = div; j; j--) {
			in0_0 = *(in0 + 0);
			in0_1 = *(in0 + 1);
			in0 += 2;
			in1_0 = *(in1 + 0);
			in1_1 = *(in1 + 1);
			in1 += In1s;
			out0 += in0_0 * in1_0; 
			out1 += in0_0 * in1_1; 
			in1_0 = *(in1 + 0);
			in1_1 = *(in1 + 1);
			in1 += In1s;
			out0 += in0_1 * in1_0; 
			out1 += in0_1 * in1_1; 
		}
		*Out0 += out0;
		*Out1 += out1;
		Out0 += Outs1;
		Out1 += Outs1;
	}

	if (mod) {
		div = k - mod;
		mcdot_product_2x1 (Out, _In0 + div, In1 + div*In1s, m, mod, Outs0, Outs1, In0s, In1s);
	}
}

//------------------------------------------------------------------------------
template <class T, class U>
static inline void mcdot_product_2x4 (T* Out, 
																			T* _In0, 
																			T* In1, 
																			volatile const U m, 
																			volatile const U k,
																			volatile const U Outs0,
																			volatile const U Outs1 = 1,
																			volatile const U In0s = 1,
																			volatile const U In1s = 1) { 
	register T out0, out1;
	register T in0_0, in0_1, in0_2, in0_3;
	register T in1_0, in1_1;
	register T *in0, *in1;
	T *Out0, *Out1; 
	T *In0;
	volatile U div, mod;
	register U i, j;

	div = k >> 2;
	mod = k & 3;

	Out0 = Out;
	Out1 = Out + Outs0;
	In0 = _In0;

	for (i = m; i; i--) {
		in0 = In0;
		In0 += In0s;
		in1 = In1;
		out0 = 0.;
		out1 = 0.;
		for (j = div; j; j--) {
			in0_0 = *(in0 + 0);
			in0_1 = *(in0 + 1);
			in0_2 = *(in0 + 2);
			in0_3 = *(in0 + 3);
			in0 += 4;
			in1_0 = *(in1 + 0);
			in1_1 = *(in1 + 1);
			in1 += In1s;
			out0 += in0_0 * in1_0; 
			out1 += in0_0 * in1_1; 
			in1_0 = *(in1 + 0);
			in1_1 = *(in1 + 1);
			in1 += In1s;
			out0 += in0_1 * in1_0; 
			out1 += in0_1 * in1_1; 
			in1_0 = *(in1 + 0);
			in1_1 = *(in1 + 1);
			in1 += In1s;
			out0 += in0_2 * in1_0; 
			out1 += in0_2 * in1_1; 
			in1_0 = *(in1 + 0);
			in1_1 = *(in1 + 1);
			in1 += In1s;
			out0 += in0_3 * in1_0; 
			out1 += in0_3 * in1_1; 
		}
		*Out0 += out0;
		*Out1 += out1;
		Out0 += Outs1;
		Out1 += Outs1;
	}

	if (mod) {
		div = k - mod;
		mcdot_product_2x2 (Out, _In0 + div, In1 + div*In1s, m, mod, Outs0, Outs1, In0s, In1s);
	}
}

//------------------------------------------------------------------------------
template <class T, class U>
static inline void mcdot_product_2x8 (T* Out, 
																			T* _In0, 
																			T* In1, 
																			volatile const U m, 
																			volatile const U k,
																			volatile const U Outs0,
																			volatile const U Outs1 = 1,
																			volatile const U In0s = 1,
																			volatile const U In1s = 1) { 
	register T out0, out1;
	register T in0_0, in0_1, in0_2, in0_3;
	register T in1_0, in1_1;
	register T *in0, *in1;
	T *Out0, *Out1; 
	T *In0;
	volatile U div, mod;
	register U i, j;

	div = k >> 3;
	mod = k & 7;

	Out0 = Out;
	Out1 = Out + Outs0;
	In0 = _In0;

	for (i = m; i; i--) {
		in0 = In0;
		In0 += In0s;
		in1 = In1;
		out0 = 0.;
		out1 = 0.;
		for (j = div; j; j--) {
			in0_0 = *(in0 + 0);
			in0_1 = *(in0 + 1);
			in0_2 = *(in0 + 2);
			in0_3 = *(in0 + 3);
			in0 += 4;
			in1_0 = *(in1 + 0);
			in1_1 = *(in1 + 1);
			in1 += In1s;
			out0 += in0_0 * in1_0; 
			out1 += in0_0 * in1_1; 
			in1_0 = *(in1 + 0);
			in1_1 = *(in1 + 1);
			in1 += In1s;
			out0 += in0_1 * in1_0; 
			out1 += in0_1 * in1_1; 
			in1_0 = *(in1 + 0);
			in1_1 = *(in1 + 1);
			in1 += In1s;
			out0 += in0_2 * in1_0; 
			out1 += in0_2 * in1_1; 
			in1_0 = *(in1 + 0);
			in1_1 = *(in1 + 1);
			in1 += In1s;
			out0 += in0_3 * in1_0; 
			out1 += in0_3 * in1_1; 
			in0_0 = *(in0 + 0);
			in0_1 = *(in0 + 1);
			in0_2 = *(in0 + 2);
			in0_3 = *(in0 + 3);
			in0 += 4;
			in1_0 = *(in1 + 0);
			in1_1 = *(in1 + 1);
			in1 += In1s;
			out0 += in0_0 * in1_0; 
			out1 += in0_0 * in1_1; 
			in1_0 = *(in1 + 0);
			in1_1 = *(in1 + 1);
			in1 += In1s;
			out0 += in0_1 * in1_0; 
			out1 += in0_1 * in1_1; 
			in1_0 = *(in1 + 0);
			in1_1 = *(in1 + 1);
			in1 += In1s;
			out0 += in0_2 * in1_0; 
			out1 += in0_2 * in1_1; 
			in1_0 = *(in1 + 0);
			in1_1 = *(in1 + 1);
			in1 += In1s;
			out0 += in0_3 * in1_0; 
			out1 += in0_3 * in1_1; 
		}
		*Out0 += out0;
		*Out1 += out1;
		Out0 += Outs1;
		Out1 += Outs1;
	}

	if (mod) {
		div = k - mod;
		mcdot_product_2x4 (Out, _In0 + div, In1 + div*In1s, m, mod, Outs0, Outs1, In0s, In1s);
	}
}

//------------------------------------------------------------------------------
template <class T, class U>
static inline void mcdot_product_2x16(T* Out, 
																			T* _In0, 
																			T* In1, 
																			volatile const U m, 
																			volatile const U k,
																			volatile const U Outs0,
																			volatile const U Outs1 = 1,
																			volatile const U In0s = 1,
																			volatile const U In1s = 1) { 
	register T out0, out1;
	register T in0_0, in0_1, in0_2, in0_3;
	register T in1_0, in1_1;
	register T *in0, *in1;
	T *Out0, *Out1; 
	T *In0;
	volatile U div, mod;
	register U i, j;

	div = k >> 4;
	mod = k & 15;

	Out0 = Out;
	Out1 = Out + Outs0;
	In0 = _In0;

	for (i = m; i; i--) {
		in0 = In0;
		In0 += In0s;
		in1 = In1;
		out0 = 0.;
		out1 = 0.;
		for (j = div; j; j--) {
			in0_0 = *(in0 + 0);
			in0_1 = *(in0 + 1);
			in0_2 = *(in0 + 2);
			in0_3 = *(in0 + 3);
			in0 += 4;
			in1_0 = *(in1 + 0);
			in1_1 = *(in1 + 1);
			in1 += In1s;
			out0 += in0_0 * in1_0; 
			out1 += in0_0 * in1_1; 
			in1_0 = *(in1 + 0);
			in1_1 = *(in1 + 1);
			in1 += In1s;
			out0 += in0_1 * in1_0; 
			out1 += in0_1 * in1_1; 
			in1_0 = *(in1 + 0);
			in1_1 = *(in1 + 1);
			in1 += In1s;
			out0 += in0_2 * in1_0; 
			out1 += in0_2 * in1_1; 
			in1_0 = *(in1 + 0);
			in1_1 = *(in1 + 1);
			in1 += In1s;
			out0 += in0_3 * in1_0; 
			out1 += in0_3 * in1_1; 
			in0_0 = *(in0 + 0);
			in0_1 = *(in0 + 1);
			in0_2 = *(in0 + 2);
			in0_3 = *(in0 + 3);
			in0 += 4;
			in1_0 = *(in1 + 0);
			in1_1 = *(in1 + 1);
			in1 += In1s;
			out0 += in0_0 * in1_0; 
			out1 += in0_0 * in1_1; 
			in1_0 = *(in1 + 0);
			in1_1 = *(in1 + 1);
			in1 += In1s;
			out0 += in0_1 * in1_0; 
			out1 += in0_1 * in1_1; 
			in1_0 = *(in1 + 0);
			in1_1 = *(in1 + 1);
			in1 += In1s;
			out0 += in0_2 * in1_0; 
			out1 += in0_2 * in1_1; 
			in1_0 = *(in1 + 0);
			in1_1 = *(in1 + 1);
			in1 += In1s;
			out0 += in0_3 * in1_0; 
			out1 += in0_3 * in1_1; 
			in0_0 = *(in0 + 0);
			in0_1 = *(in0 + 1);
			in0_2 = *(in0 + 2);
			in0_3 = *(in0 + 3);
			in0 += 4;
			in1_0 = *(in1 + 0);
			in1_1 = *(in1 + 1);
			in1 += In1s;
			out0 += in0_0 * in1_0; 
			out1 += in0_0 * in1_1; 
			in1_0 = *(in1 + 0);
			in1_1 = *(in1 + 1);
			in1 += In1s;
			out0 += in0_1 * in1_0; 
			out1 += in0_1 * in1_1; 
			in1_0 = *(in1 + 0);
			in1_1 = *(in1 + 1);
			in1 += In1s;
			out0 += in0_2 * in1_0; 
			out1 += in0_2 * in1_1; 
			in1_0 = *(in1 + 0);
			in1_1 = *(in1 + 1);
			in1 += In1s;
			out0 += in0_3 * in1_0; 
			out1 += in0_3 * in1_1; 
			in0_0 = *(in0 + 0);
			in0_1 = *(in0 + 1);
			in0_2 = *(in0 + 2);
			in0_3 = *(in0 + 3);
			in0 += 4;
			in1_0 = *(in1 + 0);
			in1_1 = *(in1 + 1);
			in1 += In1s;
			out0 += in0_0 * in1_0; 
			out1 += in0_0 * in1_1; 
			in1_0 = *(in1 + 0);
			in1_1 = *(in1 + 1);
			in1 += In1s;
			out0 += in0_1 * in1_0; 
			out1 += in0_1 * in1_1; 
			in1_0 = *(in1 + 0);
			in1_1 = *(in1 + 1);
			in1 += In1s;
			out0 += in0_2 * in1_0; 
			out1 += in0_2 * in1_1; 
			in1_0 = *(in1 + 0);
			in1_1 = *(in1 + 1);
			in1 += In1s;
			out0 += in0_3 * in1_0; 
			out1 += in0_3 * in1_1; 
		}
		*Out0 += out0;
		*Out1 += out1;
		Out0 += Outs1;
		Out1 += Outs1;
	}

	if (mod) {
		div = k - mod;
		mcdot_product_2x8 (Out, _In0 + div, In1 + div*In1s, m, mod, Outs0, Outs1, In0s, In1s);
	}
}

//------------------------------------------------------------------------------
template <class T, class U>
static inline void mcdot_product_2x32(T* Out, 
																			T* _In0, 
																			T* In1, 
																			volatile const U m, 
																			volatile const U k,
																			volatile const U Outs0,
																			volatile const U Outs1 = 1,
																			volatile const U In0s = 1,
																			volatile const U In1s = 1) { 
	register T out0, out1;
	register T in0_0, in0_1, in0_2, in0_3;
	register T in1_0, in1_1;
	register T *in0, *in1;
	T *Out0, *Out1; 
	T *In0;
	volatile U div, mod;
	register U i, j;

	div = k >> 5;
	mod = k & 31;

	Out0 = Out;
	Out1 = Out + Outs0;
	In0 = _In0;

	for (i = m; i; i--) {
		in0 = In0;
		In0 += In0s;
		in1 = In1;
		out0 = 0.;
		out1 = 0.;
		for (j = div; j; j--) {
			in0_0 = *(in0 + 0);
			in0_1 = *(in0 + 1);
			in0_2 = *(in0 + 2);
			in0_3 = *(in0 + 3);
			in0 += 4;
			in1_0 = *(in1 + 0);
			in1_1 = *(in1 + 1);
			in1 += In1s;
			out0 += in0_0 * in1_0; 
			out1 += in0_0 * in1_1; 
			in1_0 = *(in1 + 0);
			in1_1 = *(in1 + 1);
			in1 += In1s;
			out0 += in0_1 * in1_0; 
			out1 += in0_1 * in1_1; 
			in1_0 = *(in1 + 0);
			in1_1 = *(in1 + 1);
			in1 += In1s;
			out0 += in0_2 * in1_0; 
			out1 += in0_2 * in1_1; 
			in1_0 = *(in1 + 0);
			in1_1 = *(in1 + 1);
			in1 += In1s;
			out0 += in0_3 * in1_0; 
			out1 += in0_3 * in1_1; 
			in0_0 = *(in0 + 0);
			in0_1 = *(in0 + 1);
			in0_2 = *(in0 + 2);
			in0_3 = *(in0 + 3);
			in0 += 4;
			in1_0 = *(in1 + 0);
			in1_1 = *(in1 + 1);
			in1 += In1s;
			out0 += in0_0 * in1_0; 
			out1 += in0_0 * in1_1; 
			in1_0 = *(in1 + 0);
			in1_1 = *(in1 + 1);
			in1 += In1s;
			out0 += in0_1 * in1_0; 
			out1 += in0_1 * in1_1; 
			in1_0 = *(in1 + 0);
			in1_1 = *(in1 + 1);
			in1 += In1s;
			out0 += in0_2 * in1_0; 
			out1 += in0_2 * in1_1; 
			in1_0 = *(in1 + 0);
			in1_1 = *(in1 + 1);
			in1 += In1s;
			out0 += in0_3 * in1_0; 
			out1 += in0_3 * in1_1; 
			in0_0 = *(in0 + 0);
			in0_1 = *(in0 + 1);
			in0_2 = *(in0 + 2);
			in0_3 = *(in0 + 3);
			in0 += 4;
			in1_0 = *(in1 + 0);
			in1_1 = *(in1 + 1);
			in1 += In1s;
			out0 += in0_0 * in1_0; 
			out1 += in0_0 * in1_1; 
			in1_0 = *(in1 + 0);
			in1_1 = *(in1 + 1);
			in1 += In1s;
			out0 += in0_1 * in1_0; 
			out1 += in0_1 * in1_1; 
			in1_0 = *(in1 + 0);
			in1_1 = *(in1 + 1);
			in1 += In1s;
			out0 += in0_2 * in1_0; 
			out1 += in0_2 * in1_1; 
			in1_0 = *(in1 + 0);
			in1_1 = *(in1 + 1);
			in1 += In1s;
			out0 += in0_3 * in1_0; 
			out1 += in0_3 * in1_1; 
			in0_0 = *(in0 + 0);
			in0_1 = *(in0 + 1);
			in0_2 = *(in0 + 2);
			in0_3 = *(in0 + 3);
			in0 += 4;
			in1_0 = *(in1 + 0);
			in1_1 = *(in1 + 1);
			in1 += In1s;
			out0 += in0_0 * in1_0; 
			out1 += in0_0 * in1_1; 
			in1_0 = *(in1 + 0);
			in1_1 = *(in1 + 1);
			in1 += In1s;
			out0 += in0_1 * in1_0; 
			out1 += in0_1 * in1_1; 
			in1_0 = *(in1 + 0);
			in1_1 = *(in1 + 1);
			in1 += In1s;
			out0 += in0_2 * in1_0; 
			out1 += in0_2 * in1_1; 
			in1_0 = *(in1 + 0);
			in1_1 = *(in1 + 1);
			in1 += In1s;
			out0 += in0_3 * in1_0; 
			out1 += in0_3 * in1_1; 
			in0_0 = *(in0 + 0);
			in0_1 = *(in0 + 1);
			in0_2 = *(in0 + 2);
			in0_3 = *(in0 + 3);
			in0 += 4;
			in1_0 = *(in1 + 0);
			in1_1 = *(in1 + 1);
			in1 += In1s;
			out0 += in0_0 * in1_0; 
			out1 += in0_0 * in1_1; 
			in1_0 = *(in1 + 0);
			in1_1 = *(in1 + 1);
			in1 += In1s;
			out0 += in0_1 * in1_0; 
			out1 += in0_1 * in1_1; 
			in1_0 = *(in1 + 0);
			in1_1 = *(in1 + 1);
			in1 += In1s;
			out0 += in0_2 * in1_0; 
			out1 += in0_2 * in1_1; 
			in1_0 = *(in1 + 0);
			in1_1 = *(in1 + 1);
			in1 += In1s;
			out0 += in0_3 * in1_0; 
			out1 += in0_3 * in1_1; 
			in0_0 = *(in0 + 0);
			in0_1 = *(in0 + 1);
			in0_2 = *(in0 + 2);
			in0_3 = *(in0 + 3);
			in0 += 4;
			in1_0 = *(in1 + 0);
			in1_1 = *(in1 + 1);
			in1 += In1s;
			out0 += in0_0 * in1_0; 
			out1 += in0_0 * in1_1; 
			in1_0 = *(in1 + 0);
			in1_1 = *(in1 + 1);
			in1 += In1s;
			out0 += in0_1 * in1_0; 
			out1 += in0_1 * in1_1; 
			in1_0 = *(in1 + 0);
			in1_1 = *(in1 + 1);
			in1 += In1s;
			out0 += in0_2 * in1_0; 
			out1 += in0_2 * in1_1; 
			in1_0 = *(in1 + 0);
			in1_1 = *(in1 + 1);
			in1 += In1s;
			out0 += in0_3 * in1_0; 
			out1 += in0_3 * in1_1; 
			in0_0 = *(in0 + 0);
			in0_1 = *(in0 + 1);
			in0_2 = *(in0 + 2);
			in0_3 = *(in0 + 3);
			in0 += 4;
			in1_0 = *(in1 + 0);
			in1_1 = *(in1 + 1);
			in1 += In1s;
			out0 += in0_0 * in1_0; 
			out1 += in0_0 * in1_1; 
			in1_0 = *(in1 + 0);
			in1_1 = *(in1 + 1);
			in1 += In1s;
			out0 += in0_1 * in1_0; 
			out1 += in0_1 * in1_1; 
			in1_0 = *(in1 + 0);
			in1_1 = *(in1 + 1);
			in1 += In1s;
			out0 += in0_2 * in1_0; 
			out1 += in0_2 * in1_1; 
			in1_0 = *(in1 + 0);
			in1_1 = *(in1 + 1);
			in1 += In1s;
			out0 += in0_3 * in1_0; 
			out1 += in0_3 * in1_1; 
			in0_0 = *(in0 + 0);
			in0_1 = *(in0 + 1);
			in0_2 = *(in0 + 2);
			in0_3 = *(in0 + 3);
			in0 += 4;
			in1_0 = *(in1 + 0);
			in1_1 = *(in1 + 1);
			in1 += In1s;
			out0 += in0_0 * in1_0; 
			out1 += in0_0 * in1_1; 
			in1_0 = *(in1 + 0);
			in1_1 = *(in1 + 1);
			in1 += In1s;
			out0 += in0_1 * in1_0; 
			out1 += in0_1 * in1_1; 
			in1_0 = *(in1 + 0);
			in1_1 = *(in1 + 1);
			in1 += In1s;
			out0 += in0_2 * in1_0; 
			out1 += in0_2 * in1_1; 
			in1_0 = *(in1 + 0);
			in1_1 = *(in1 + 1);
			in1 += In1s;
			out0 += in0_3 * in1_0; 
			out1 += in0_3 * in1_1; 
		}
		*Out0 += out0;
		*Out1 += out1;
		Out0 += Outs1;
		Out1 += Outs1;
	}

	if (mod) {
		div = k - mod;
		mcdot_product_2x16(Out, _In0 + div, In1 + div*In1s, m, mod, Outs0, Outs1, In0s, In1s);
	}
}

//------------------------------------------------------------------------------
#endif
