# ifndef _mcdot_product_4_txx
# define _mcdot_product_4_txx

//------------------------------------------------------------------------------
template <class T, class U>
static inline void mcdot_product_4x1 (T* Out, 
																			T* _In0, 
																			T* In1, 
																			volatile const U m, 
																			volatile const U k,
																			volatile const U Outs0,
																			volatile const U Outs1 = 1,
																			volatile const U In0s = 1,
																			volatile const U In1s = 1) { 
	register T out0, out1, out2, out3; 
	register T in0_0;
	T in1_0, in1_1, in1_2, in1_3;
	register T *in0, *in1;
	register T *Out0, *Out1, *Out2, *Out3; 
	T *In0;
	register U i, j;

	Out0 = Out + Outs0 * 0;
	Out1 = Out + Outs0 * 1;
	Out2 = Out + Outs0 * 2;
	Out3 = Out + Outs0 * 3;
	In0 = _In0;

	for (i = m; i; i--) {
		in0 = In0;
		In0 += In0s;
		in1 = In1;
		out0 = 0.;
		out1 = 0.;
		out2 = 0.;
		out3 = 0.;
		for (j = k; j; j--) {
			in0_0 = *(in0 + 0);
			in0 ++;
			in1_0 = *(in1 + 0);
			in1_1 = *(in1 + 1);
			in1_2 = *(in1 + 2);
			in1_3 = *(in1 + 3);
			in1 += In1s;
			out0 += in0_0 * in1_0; 
			out1 += in0_0 * in1_1; 
			out2 += in0_0 * in1_2; 
			out3 += in0_0 * in1_3; 
		}
		* Out0 += out0;
		* Out1 += out1;
		* Out2 += out2;
		* Out3 += out3;
		Out0 += Outs1;
		Out1 += Outs1;
		Out2 += Outs1;
		Out3 += Outs1;
	}
}

//------------------------------------------------------------------------------
template <class T, class U>
static inline void mcdot_product_4x2 (T* Out, 
																			T* _In0, 
																			T* In1, 
																			volatile const U m, 
																			volatile const U k,
																			volatile const U Outs0,
																			volatile const U Outs1 = 1,
																			volatile const U In0s = 1,
																			volatile const U In1s = 1) { 

	register T out0, out1, out2, out3; 
	register T in0_0, in0_1;
	T in1_0, in1_1, in1_2, in1_3;
	register T *in0, *in1;
	register T *Out0, *Out1, *Out2, *Out3; 
	T *In0;
	volatile U div, mod;
	register U i, j;

	div = k >> 1;
	mod = k & 1;

	Out0 = Out + Outs0 * 0;
	Out1 = Out + Outs0 * 1;
	Out2 = Out + Outs0 * 2;
	Out3 = Out + Outs0 * 3;
	In0 = _In0;

	for (i = m; i; i--) {
		in0 = In0;
		In0 += In0s;
		in1 = In1;
		out0 = 0.;
		out1 = 0.;
		out2 = 0.;
		out3 = 0.;
		for (j = div; j; j--) {
			in0_0 = *(in0 + 0);
			in0_1 = *(in0 + 1);
			in0 += 2;
			in1_0 = *(in1 + 0);
			in1_1 = *(in1 + 1);
			in1_2 = *(in1 + 2);
			in1_3 = *(in1 + 3);
			in1 += In1s;
			out0 += in0_0 * in1_0; 
			out1 += in0_0 * in1_1; 
			out2 += in0_0 * in1_2; 
			out3 += in0_0 * in1_3; 
			in1_0 = *(in1 + 0);
			in1_1 = *(in1 + 1);
			in1_2 = *(in1 + 2);
			in1_3 = *(in1 + 3);
			in1 += In1s;
			out0 += in0_1 * in1_0; 
			out1 += in0_1 * in1_1; 
			out2 += in0_1 * in1_2; 
			out3 += in0_1 * in1_3; 
		}
		* Out0 += out0;
		* Out1 += out1;
		* Out2 += out2;
		* Out3 += out3;
		Out0 += Outs1;
		Out1 += Outs1;
		Out2 += Outs1;
		Out3 += Outs1;
	}

	if (mod) {
		div = k - mod;
		mcdot_product_4x1(Out, _In0 + div, In1 + div*In1s, m, mod, Outs0, Outs1, In0s, In1s);
	}
}

//------------------------------------------------------------------------------
template <class T, class U>
static inline void mcdot_product_4x4 (T* Out, 
																			T* _In0, 
																			T* In1, 
																			volatile const U m, 
																			volatile const U k,
																			volatile const U Outs0,
																			volatile const U Outs1 = 1,
																			volatile const U In0s = 1,
																			volatile const U In1s = 1) { 

	register T out0, out1, out2, out3; 
	register T in0_0, in0_1, in0_2, in0_3;
	T in1_0, in1_1, in1_2, in1_3;
	register T *in0, *in1;
	register T *Out0, *Out1, *Out2, *Out3;
	T *In0;
	volatile U div, mod;
	register U i, j;

	div = k >> 2;
	mod = k & 3;

	Out0 = Out + Outs0 * 0;
	Out1 = Out + Outs0 * 1;
	Out2 = Out + Outs0 * 2;
	Out3 = Out + Outs0 * 3;
	In0 = _In0;

	for (i = m; i; i--) {
		in0 = In0;
		In0 += In0s;
		in1 = In1;
		out0 = 0.;
		out1 = 0.;
		out2 = 0.;
		out3 = 0.;
		for (j = div; j; j--) {
			in0_0 = *(in0 + 0);
			in0_1 = *(in0 + 1);
			in0_2 = *(in0 + 2);
			in0_3 = *(in0 + 3);
			in0 += 4;
			in1_0 = *(in1 + 0);
			in1_1 = *(in1 + 1);
			in1_2 = *(in1 + 2);
			in1_3 = *(in1 + 3);
			in1 += In1s;
			out0 += in0_0 * in1_0; 
			out1 += in0_0 * in1_1; 
			out2 += in0_0 * in1_2; 
			out3 += in0_0 * in1_3; 
			in1_0 = *(in1 + 0);
			in1_1 = *(in1 + 1);
			in1_2 = *(in1 + 2);
			in1_3 = *(in1 + 3);
			in1 += In1s;
			out0 += in0_1 * in1_0; 
			out1 += in0_1 * in1_1; 
			out2 += in0_1 * in1_2; 
			out3 += in0_1 * in1_3; 
			in1_0 = *(in1 + 0);
			in1_1 = *(in1 + 1);
			in1_2 = *(in1 + 2);
			in1_3 = *(in1 + 3);
			in1 += In1s;
			out0 += in0_2 * in1_0; 
			out1 += in0_2 * in1_1; 
			out2 += in0_2 * in1_2; 
			out3 += in0_2 * in1_3; 
			in1_0 = *(in1 + 0);
			in1_1 = *(in1 + 1);
			in1_2 = *(in1 + 2);
			in1_3 = *(in1 + 3);
			in1 += In1s;
			out0 += in0_3 * in1_0; 
			out1 += in0_3 * in1_1; 
			out2 += in0_3 * in1_2; 
			out3 += in0_3 * in1_3; 
		}
		* Out0 += out0;
		* Out1 += out1;
		* Out2 += out2;
		* Out3 += out3;
		Out0 += Outs1;
		Out1 += Outs1;
		Out2 += Outs1;
		Out3 += Outs1;
	}

	if (mod) {
		div = k - mod;
		mcdot_product_4x2 (Out, _In0 + div, In1 + div*In1s, m, mod, Outs0, Outs1, In0s, In1s);
	}
}

//------------------------------------------------------------------------------
template <class T, class U>
static inline void mcdot_product_4x8 (T* Out, 
																			T* _In0, 
																			T* In1, 
																			volatile const U m, 
																			volatile const U k,
																			volatile const U Outs0,
																			volatile const U Outs1 = 1,
																			volatile const U In0s = 1,
																			volatile const U In1s = 1) { 

	register T out0, out1, out2, out3; 
	register T in0_0, in0_1, in0_2, in0_3, in0_4, in0_5, in0_6, in0_7;
	T in1_0, in1_1, in1_2, in1_3;
	register T *in0, *in1;
	register T *Out0, *Out1, *Out2, *Out3;
	T *In0;
	volatile U div, mod;
	register U i, j;

	div = k >> 3;
	mod = k & 7;

	Out0 = Out + Outs0 * 0;
	Out1 = Out + Outs0 * 1;
	Out2 = Out + Outs0 * 2;
	Out3 = Out + Outs0 * 3;
	In0 = _In0;

	for (i = m; i; i--) {
		in0 = In0;
		In0 += In0s;
		in1 = In1;
		out0 = 0.;
		out1 = 0.;
		out2 = 0.;
		out3 = 0.;
		for (j = div; j; j--) {
			in0_0 = *(in0 + 0);
			in0_1 = *(in0 + 1);
			in0_2 = *(in0 + 2);
			in0_3 = *(in0 + 3);
			in0_4 = *(in0 + 4);
			in0_5 = *(in0 + 5);
			in0_6 = *(in0 + 6);
			in0_7 = *(in0 + 7);
			in0 += 8;
			in1_0 = *(in1 + 0);
			in1_1 = *(in1 + 1);
			in1_2 = *(in1 + 2);
			in1_3 = *(in1 + 3);
			in1 += In1s;
			out0 += in0_0 * in1_0; 
			out1 += in0_0 * in1_1; 
			out2 += in0_0 * in1_2; 
			out3 += in0_0 * in1_3; 
			in1_0 = *(in1 + 0);
			in1_1 = *(in1 + 1);
			in1_2 = *(in1 + 2);
			in1_3 = *(in1 + 3);
			in1 += In1s;
			out0 += in0_1 * in1_0; 
			out1 += in0_1 * in1_1; 
			out2 += in0_1 * in1_2; 
			out3 += in0_1 * in1_3; 
			in1_0 = *(in1 + 0);
			in1_1 = *(in1 + 1);
			in1_2 = *(in1 + 2);
			in1_3 = *(in1 + 3);
			in1 += In1s;
			out0 += in0_2 * in1_0; 
			out1 += in0_2 * in1_1; 
			out2 += in0_2 * in1_2; 
			out3 += in0_2 * in1_3; 
			in1_0 = *(in1 + 0);
			in1_1 = *(in1 + 1);
			in1_2 = *(in1 + 2);
			in1_3 = *(in1 + 3);
			in1 += In1s;
			out0 += in0_3 * in1_0; 
			out1 += in0_3 * in1_1; 
			out2 += in0_3 * in1_2; 
			out3 += in0_3 * in1_3; 
			in1_0 = *(in1 + 0);
			in1_1 = *(in1 + 1);
			in1_2 = *(in1 + 2);
			in1_3 = *(in1 + 3);
			in1 += In1s;
			out0 += in0_4 * in1_0; 
			out1 += in0_4 * in1_1; 
			out2 += in0_4 * in1_2; 
			out3 += in0_4 * in1_3; 
			in1_0 = *(in1 + 0);
			in1_1 = *(in1 + 1);
			in1_2 = *(in1 + 2);
			in1_3 = *(in1 + 3);
			in1 += In1s;
			out0 += in0_5 * in1_0; 
			out1 += in0_5 * in1_1; 
			out2 += in0_5 * in1_2; 
			out3 += in0_5 * in1_3; 
			in1_0 = *(in1 + 0);
			in1_1 = *(in1 + 1);
			in1_2 = *(in1 + 2);
			in1_3 = *(in1 + 3);
			in1 += In1s;
			out0 += in0_6 * in1_0; 
			out1 += in0_6 * in1_1; 
			out2 += in0_6 * in1_2; 
			out3 += in0_6 * in1_3; 
			in1_0 = *(in1 + 0);
			in1_1 = *(in1 + 1);
			in1_2 = *(in1 + 2);
			in1_3 = *(in1 + 3);
			in1 += In1s;
			out0 += in0_7 * in1_0; 
			out1 += in0_7 * in1_1; 
			out2 += in0_7 * in1_2; 
			out3 += in0_7 * in1_3; 
		}
		* Out0 += out0;
		* Out1 += out1;
		* Out2 += out2;
		* Out3 += out3;
		Out0 += Outs1;
		Out1 += Outs1;
		Out2 += Outs1;
		Out3 += Outs1;
	}

	if (mod) {
		div = k - mod;
		mcdot_product_4x4 (Out, _In0 + div, In1 + div*In1s, m, mod, Outs0, Outs1, In0s, In1s);
	}
}

//------------------------------------------------------------------------------
template <class T, class U>
static inline void mcdot_product_4x16(T* Out, 
																			T* _In0, 
																			T* In1, 
																			volatile const U m, 
																			volatile const U k,
																			volatile const U Outs0,
																			volatile const U Outs1 = 1,
																			volatile const U In0s = 1,
																			volatile const U In1s = 1) { 

	register T out0, out1, out2, out3; 
	register T in0_0, in0_1, in0_2, in0_3, in0_4, in0_5, in0_6, in0_7;
	T in1_0, in1_1, in1_2, in1_3;
	register T *in0, *in1;
	register T *Out0, *Out1, *Out2, *Out3;
	T *In0;
	volatile U div, mod;
	register U i, j;

	div = k >> 4;
	mod = k & 15;

	Out0 = Out + Outs0 * 0;
	Out1 = Out + Outs0 * 1;
	Out2 = Out + Outs0 * 2;
	Out3 = Out + Outs0 * 3;
	In0 = _In0;

	for (i = m; i; i--) {
		in0 = In0;
		In0 += In0s;
		in1 = In1;
		out0 = 0.;
		out1 = 0.;
		out2 = 0.;
		out3 = 0.;
		for (j = div; j; j--) {
			in0_0 = *(in0 + 0);
			in0_1 = *(in0 + 1);
			in0_2 = *(in0 + 2);
			in0_3 = *(in0 + 3);
			in0_4 = *(in0 + 4);
			in0_5 = *(in0 + 5);
			in0_6 = *(in0 + 6);
			in0_7 = *(in0 + 7);
			in0 += 8;
			in1_0 = *(in1 + 0);
			in1_1 = *(in1 + 1);
			in1_2 = *(in1 + 2);
			in1_3 = *(in1 + 3);
			in1 += In1s;
			out0 += in0_0 * in1_0; 
			out1 += in0_0 * in1_1; 
			out2 += in0_0 * in1_2; 
			out3 += in0_0 * in1_3; 
			in1_0 = *(in1 + 0);
			in1_1 = *(in1 + 1);
			in1_2 = *(in1 + 2);
			in1_3 = *(in1 + 3);
			in1 += In1s;
			out0 += in0_1 * in1_0; 
			out1 += in0_1 * in1_1; 
			out2 += in0_1 * in1_2; 
			out3 += in0_1 * in1_3; 
			in1_0 = *(in1 + 0);
			in1_1 = *(in1 + 1);
			in1_2 = *(in1 + 2);
			in1_3 = *(in1 + 3);
			in1 += In1s;
			out0 += in0_2 * in1_0; 
			out1 += in0_2 * in1_1; 
			out2 += in0_2 * in1_2; 
			out3 += in0_2 * in1_3; 
			in1_0 = *(in1 + 0);
			in1_1 = *(in1 + 1);
			in1_2 = *(in1 + 2);
			in1_3 = *(in1 + 3);
			in1 += In1s;
			out0 += in0_3 * in1_0; 
			out1 += in0_3 * in1_1; 
			out2 += in0_3 * in1_2; 
			out3 += in0_3 * in1_3; 
			in1_0 = *(in1 + 0);
			in1_1 = *(in1 + 1);
			in1_2 = *(in1 + 2);
			in1_3 = *(in1 + 3);
			in1 += In1s;
			out0 += in0_4 * in1_0; 
			out1 += in0_4 * in1_1; 
			out2 += in0_4 * in1_2; 
			out3 += in0_4 * in1_3; 
			in1_0 = *(in1 + 0);
			in1_1 = *(in1 + 1);
			in1_2 = *(in1 + 2);
			in1_3 = *(in1 + 3);
			in1 += In1s;
			out0 += in0_5 * in1_0; 
			out1 += in0_5 * in1_1; 
			out2 += in0_5 * in1_2; 
			out3 += in0_5 * in1_3; 
			in1_0 = *(in1 + 0);
			in1_1 = *(in1 + 1);
			in1_2 = *(in1 + 2);
			in1_3 = *(in1 + 3);
			in1 += In1s;
			out0 += in0_6 * in1_0; 
			out1 += in0_6 * in1_1; 
			out2 += in0_6 * in1_2; 
			out3 += in0_6 * in1_3; 
			in1_0 = *(in1 + 0);
			in1_1 = *(in1 + 1);
			in1_2 = *(in1 + 2);
			in1_3 = *(in1 + 3);
			in1 += In1s;
			out0 += in0_7 * in1_0; 
			out1 += in0_7 * in1_1; 
			out2 += in0_7 * in1_2; 
			out3 += in0_7 * in1_3; 
			in0_0 = *(in0 + 0);
			in0_1 = *(in0 + 1);
			in0_2 = *(in0 + 2);
			in0_3 = *(in0 + 3);
			in0_4 = *(in0 + 4);
			in0_5 = *(in0 + 5);
			in0_6 = *(in0 + 6);
			in0_7 = *(in0 + 7);
			in0 += 8;
			in1_0 = *(in1 + 0);
			in1_1 = *(in1 + 1);
			in1_2 = *(in1 + 2);
			in1_3 = *(in1 + 3);
			in1 += In1s;
			out0 += in0_0 * in1_0; 
			out1 += in0_0 * in1_1; 
			out2 += in0_0 * in1_2; 
			out3 += in0_0 * in1_3; 
			in1_0 = *(in1 + 0);
			in1_1 = *(in1 + 1);
			in1_2 = *(in1 + 2);
			in1_3 = *(in1 + 3);
			in1 += In1s;
			out0 += in0_1 * in1_0; 
			out1 += in0_1 * in1_1; 
			out2 += in0_1 * in1_2; 
			out3 += in0_1 * in1_3; 
			in1_0 = *(in1 + 0);
			in1_1 = *(in1 + 1);
			in1_2 = *(in1 + 2);
			in1_3 = *(in1 + 3);
			in1 += In1s;
			out0 += in0_2 * in1_0; 
			out1 += in0_2 * in1_1; 
			out2 += in0_2 * in1_2; 
			out3 += in0_2 * in1_3; 
			in1_0 = *(in1 + 0);
			in1_1 = *(in1 + 1);
			in1_2 = *(in1 + 2);
			in1_3 = *(in1 + 3);
			in1 += In1s;
			out0 += in0_3 * in1_0; 
			out1 += in0_3 * in1_1; 
			out2 += in0_3 * in1_2; 
			out3 += in0_3 * in1_3; 
			in1_0 = *(in1 + 0);
			in1_1 = *(in1 + 1);
			in1_2 = *(in1 + 2);
			in1_3 = *(in1 + 3);
			in1 += In1s;
			out0 += in0_4 * in1_0; 
			out1 += in0_4 * in1_1; 
			out2 += in0_4 * in1_2; 
			out3 += in0_4 * in1_3; 
			in1_0 = *(in1 + 0);
			in1_1 = *(in1 + 1);
			in1_2 = *(in1 + 2);
			in1_3 = *(in1 + 3);
			in1 += In1s;
			out0 += in0_5 * in1_0; 
			out1 += in0_5 * in1_1; 
			out2 += in0_5 * in1_2; 
			out3 += in0_5 * in1_3; 
			in1_0 = *(in1 + 0);
			in1_1 = *(in1 + 1);
			in1_2 = *(in1 + 2);
			in1_3 = *(in1 + 3);
			in1 += In1s;
			out0 += in0_6 * in1_0; 
			out1 += in0_6 * in1_1; 
			out2 += in0_6 * in1_2; 
			out3 += in0_6 * in1_3; 
			in1_0 = *(in1 + 0);
			in1_1 = *(in1 + 1);
			in1_2 = *(in1 + 2);
			in1_3 = *(in1 + 3);
			in1 += In1s;
			out0 += in0_7 * in1_0; 
			out1 += in0_7 * in1_1; 
			out2 += in0_7 * in1_2; 
			out3 += in0_7 * in1_3; 
		}
		* Out0 += out0;
		* Out1 += out1;
		* Out2 += out2;
		* Out3 += out3;
		Out0 += Outs1;
		Out1 += Outs1;
		Out2 += Outs1;
		Out3 += Outs1;
	}

	if (mod) {
		div = k - mod;
		mcdot_product_4x8 (Out, _In0 + div, In1 + div*In1s, m, mod, Outs0, Outs1, In0s, In1s);
	}
}

//------------------------------------------------------------------------------
template <class T, class U>
static inline void mcdot_product_4x32(T* Out, 
																			T* _In0, 
																			T* In1, 
																			volatile const U m, 
																			volatile const U k,
																			volatile const U Outs0,
																			volatile const U Outs1 = 1,
																			volatile const U In0s = 1,
																			volatile const U In1s = 1) { 

	register T out0, out1, out2, out3; 
	register T in0_0, in0_1, in0_2, in0_3, in0_4, in0_5, in0_6, in0_7;
	T in1_0, in1_1, in1_2, in1_3;
	register T *in0, *in1;
	register T *Out0, *Out1, *Out2, *Out3;
	T *In0;
	volatile U div, mod;
	register U i, j;

	div = k >> 5;
	mod = k & 31;

	Out0 = Out + Outs0 * 0;
	Out1 = Out + Outs0 * 1;
	Out2 = Out + Outs0 * 2;
	Out3 = Out + Outs0 * 3;
	In0 = _In0;

	for (i = m; i; i--) {
		in0 = In0;
		In0 += In0s;
		in1 = In1;
		out0 = 0.;
		out1 = 0.;
		out2 = 0.;
		out3 = 0.;
		for (j = div; j; j--) {
			in0_0 = *(in0 + 0);
			in0_1 = *(in0 + 1);
			in0_2 = *(in0 + 2);
			in0_3 = *(in0 + 3);
			in0_4 = *(in0 + 4);
			in0_5 = *(in0 + 5);
			in0_6 = *(in0 + 6);
			in0_7 = *(in0 + 7);
			in0 += 8;
			in1_0 = *(in1 + 0);
			in1_1 = *(in1 + 1);
			in1_2 = *(in1 + 2);
			in1_3 = *(in1 + 3);
			in1 += In1s;
			out0 += in0_0 * in1_0; 
			out1 += in0_0 * in1_1; 
			out2 += in0_0 * in1_2; 
			out3 += in0_0 * in1_3; 
			in1_0 = *(in1 + 0);
			in1_1 = *(in1 + 1);
			in1_2 = *(in1 + 2);
			in1_3 = *(in1 + 3);
			in1 += In1s;
			out0 += in0_1 * in1_0; 
			out1 += in0_1 * in1_1; 
			out2 += in0_1 * in1_2; 
			out3 += in0_1 * in1_3; 
			in1_0 = *(in1 + 0);
			in1_1 = *(in1 + 1);
			in1_2 = *(in1 + 2);
			in1_3 = *(in1 + 3);
			in1 += In1s;
			out0 += in0_2 * in1_0; 
			out1 += in0_2 * in1_1; 
			out2 += in0_2 * in1_2; 
			out3 += in0_2 * in1_3; 
			in1_0 = *(in1 + 0);
			in1_1 = *(in1 + 1);
			in1_2 = *(in1 + 2);
			in1_3 = *(in1 + 3);
			in1 += In1s;
			out0 += in0_3 * in1_0; 
			out1 += in0_3 * in1_1; 
			out2 += in0_3 * in1_2; 
			out3 += in0_3 * in1_3; 
			in1_0 = *(in1 + 0);
			in1_1 = *(in1 + 1);
			in1_2 = *(in1 + 2);
			in1_3 = *(in1 + 3);
			in1 += In1s;
			out0 += in0_4 * in1_0; 
			out1 += in0_4 * in1_1; 
			out2 += in0_4 * in1_2; 
			out3 += in0_4 * in1_3; 
			in1_0 = *(in1 + 0);
			in1_1 = *(in1 + 1);
			in1_2 = *(in1 + 2);
			in1_3 = *(in1 + 3);
			in1 += In1s;
			out0 += in0_5 * in1_0; 
			out1 += in0_5 * in1_1; 
			out2 += in0_5 * in1_2; 
			out3 += in0_5 * in1_3; 
			in1_0 = *(in1 + 0);
			in1_1 = *(in1 + 1);
			in1_2 = *(in1 + 2);
			in1_3 = *(in1 + 3);
			in1 += In1s;
			out0 += in0_6 * in1_0; 
			out1 += in0_6 * in1_1; 
			out2 += in0_6 * in1_2; 
			out3 += in0_6 * in1_3; 
			in1_0 = *(in1 + 0);
			in1_1 = *(in1 + 1);
			in1_2 = *(in1 + 2);
			in1_3 = *(in1 + 3);
			in1 += In1s;
			out0 += in0_7 * in1_0; 
			out1 += in0_7 * in1_1; 
			out2 += in0_7 * in1_2; 
			out3 += in0_7 * in1_3; 
			in0_0 = *(in0 + 0);
			in0_1 = *(in0 + 1);
			in0_2 = *(in0 + 2);
			in0_3 = *(in0 + 3);
			in0_4 = *(in0 + 4);
			in0_5 = *(in0 + 5);
			in0_6 = *(in0 + 6);
			in0_7 = *(in0 + 7);
			in0 += 8;
			in1_0 = *(in1 + 0);
			in1_1 = *(in1 + 1);
			in1_2 = *(in1 + 2);
			in1_3 = *(in1 + 3);
			in1 += In1s;
			out0 += in0_0 * in1_0; 
			out1 += in0_0 * in1_1; 
			out2 += in0_0 * in1_2; 
			out3 += in0_0 * in1_3; 
			in1_0 = *(in1 + 0);
			in1_1 = *(in1 + 1);
			in1_2 = *(in1 + 2);
			in1_3 = *(in1 + 3);
			in1 += In1s;
			out0 += in0_1 * in1_0; 
			out1 += in0_1 * in1_1; 
			out2 += in0_1 * in1_2; 
			out3 += in0_1 * in1_3; 
			in1_0 = *(in1 + 0);
			in1_1 = *(in1 + 1);
			in1_2 = *(in1 + 2);
			in1_3 = *(in1 + 3);
			in1 += In1s;
			out0 += in0_2 * in1_0; 
			out1 += in0_2 * in1_1; 
			out2 += in0_2 * in1_2; 
			out3 += in0_2 * in1_3; 
			in1_0 = *(in1 + 0);
			in1_1 = *(in1 + 1);
			in1_2 = *(in1 + 2);
			in1_3 = *(in1 + 3);
			in1 += In1s;
			out0 += in0_3 * in1_0; 
			out1 += in0_3 * in1_1; 
			out2 += in0_3 * in1_2; 
			out3 += in0_3 * in1_3; 
			in1_0 = *(in1 + 0);
			in1_1 = *(in1 + 1);
			in1_2 = *(in1 + 2);
			in1_3 = *(in1 + 3);
			in1 += In1s;
			out0 += in0_4 * in1_0; 
			out1 += in0_4 * in1_1; 
			out2 += in0_4 * in1_2; 
			out3 += in0_4 * in1_3; 
			in1_0 = *(in1 + 0);
			in1_1 = *(in1 + 1);
			in1_2 = *(in1 + 2);
			in1_3 = *(in1 + 3);
			in1 += In1s;
			out0 += in0_5 * in1_0; 
			out1 += in0_5 * in1_1; 
			out2 += in0_5 * in1_2; 
			out3 += in0_5 * in1_3; 
			in1_0 = *(in1 + 0);
			in1_1 = *(in1 + 1);
			in1_2 = *(in1 + 2);
			in1_3 = *(in1 + 3);
			in1 += In1s;
			out0 += in0_6 * in1_0; 
			out1 += in0_6 * in1_1; 
			out2 += in0_6 * in1_2; 
			out3 += in0_6 * in1_3; 
			in1_0 = *(in1 + 0);
			in1_1 = *(in1 + 1);
			in1_2 = *(in1 + 2);
			in1_3 = *(in1 + 3);
			in1 += In1s;
			out0 += in0_7 * in1_0; 
			out1 += in0_7 * in1_1; 
			out2 += in0_7 * in1_2; 
			out3 += in0_7 * in1_3; 
			in0_0 = *(in0 + 0);
			in0_1 = *(in0 + 1);
			in0_2 = *(in0 + 2);
			in0_3 = *(in0 + 3);
			in0_4 = *(in0 + 4);
			in0_5 = *(in0 + 5);
			in0_6 = *(in0 + 6);
			in0_7 = *(in0 + 7);
			in0 += 8;
			in1_0 = *(in1 + 0);
			in1_1 = *(in1 + 1);
			in1_2 = *(in1 + 2);
			in1_3 = *(in1 + 3);
			in1 += In1s;
			out0 += in0_0 * in1_0; 
			out1 += in0_0 * in1_1; 
			out2 += in0_0 * in1_2; 
			out3 += in0_0 * in1_3; 
			in1_0 = *(in1 + 0);
			in1_1 = *(in1 + 1);
			in1_2 = *(in1 + 2);
			in1_3 = *(in1 + 3);
			in1 += In1s;
			out0 += in0_1 * in1_0; 
			out1 += in0_1 * in1_1; 
			out2 += in0_1 * in1_2; 
			out3 += in0_1 * in1_3; 
			in1_0 = *(in1 + 0);
			in1_1 = *(in1 + 1);
			in1_2 = *(in1 + 2);
			in1_3 = *(in1 + 3);
			in1 += In1s;
			out0 += in0_2 * in1_0; 
			out1 += in0_2 * in1_1; 
			out2 += in0_2 * in1_2; 
			out3 += in0_2 * in1_3; 
			in1_0 = *(in1 + 0);
			in1_1 = *(in1 + 1);
			in1_2 = *(in1 + 2);
			in1_3 = *(in1 + 3);
			in1 += In1s;
			out0 += in0_3 * in1_0; 
			out1 += in0_3 * in1_1; 
			out2 += in0_3 * in1_2; 
			out3 += in0_3 * in1_3; 
			in1_0 = *(in1 + 0);
			in1_1 = *(in1 + 1);
			in1_2 = *(in1 + 2);
			in1_3 = *(in1 + 3);
			in1 += In1s;
			out0 += in0_4 * in1_0; 
			out1 += in0_4 * in1_1; 
			out2 += in0_4 * in1_2; 
			out3 += in0_4 * in1_3; 
			in1_0 = *(in1 + 0);
			in1_1 = *(in1 + 1);
			in1_2 = *(in1 + 2);
			in1_3 = *(in1 + 3);
			in1 += In1s;
			out0 += in0_5 * in1_0; 
			out1 += in0_5 * in1_1; 
			out2 += in0_5 * in1_2; 
			out3 += in0_5 * in1_3; 
			in1_0 = *(in1 + 0);
			in1_1 = *(in1 + 1);
			in1_2 = *(in1 + 2);
			in1_3 = *(in1 + 3);
			in1 += In1s;
			out0 += in0_6 * in1_0; 
			out1 += in0_6 * in1_1; 
			out2 += in0_6 * in1_2; 
			out3 += in0_6 * in1_3; 
			in1_0 = *(in1 + 0);
			in1_1 = *(in1 + 1);
			in1_2 = *(in1 + 2);
			in1_3 = *(in1 + 3);
			in1 += In1s;
			out0 += in0_7 * in1_0; 
			out1 += in0_7 * in1_1; 
			out2 += in0_7 * in1_2; 
			out3 += in0_7 * in1_3; 
			in0_0 = *(in0 + 0);
			in0_1 = *(in0 + 1);
			in0_2 = *(in0 + 2);
			in0_3 = *(in0 + 3);
			in0_4 = *(in0 + 4);
			in0_5 = *(in0 + 5);
			in0_6 = *(in0 + 6);
			in0_7 = *(in0 + 7);
			in0 += 8;
			in1_0 = *(in1 + 0);
			in1_1 = *(in1 + 1);
			in1_2 = *(in1 + 2);
			in1_3 = *(in1 + 3);
			in1 += In1s;
			out0 += in0_0 * in1_0; 
			out1 += in0_0 * in1_1; 
			out2 += in0_0 * in1_2; 
			out3 += in0_0 * in1_3; 
			in1_0 = *(in1 + 0);
			in1_1 = *(in1 + 1);
			in1_2 = *(in1 + 2);
			in1_3 = *(in1 + 3);
			in1 += In1s;
			out0 += in0_1 * in1_0; 
			out1 += in0_1 * in1_1; 
			out2 += in0_1 * in1_2; 
			out3 += in0_1 * in1_3; 
			in1_0 = *(in1 + 0);
			in1_1 = *(in1 + 1);
			in1_2 = *(in1 + 2);
			in1_3 = *(in1 + 3);
			in1 += In1s;
			out0 += in0_2 * in1_0; 
			out1 += in0_2 * in1_1; 
			out2 += in0_2 * in1_2; 
			out3 += in0_2 * in1_3; 
			in1_0 = *(in1 + 0);
			in1_1 = *(in1 + 1);
			in1_2 = *(in1 + 2);
			in1_3 = *(in1 + 3);
			in1 += In1s;
			out0 += in0_3 * in1_0; 
			out1 += in0_3 * in1_1; 
			out2 += in0_3 * in1_2; 
			out3 += in0_3 * in1_3; 
			in1_0 = *(in1 + 0);
			in1_1 = *(in1 + 1);
			in1_2 = *(in1 + 2);
			in1_3 = *(in1 + 3);
			in1 += In1s;
			out0 += in0_4 * in1_0; 
			out1 += in0_4 * in1_1; 
			out2 += in0_4 * in1_2; 
			out3 += in0_4 * in1_3; 
			in1_0 = *(in1 + 0);
			in1_1 = *(in1 + 1);
			in1_2 = *(in1 + 2);
			in1_3 = *(in1 + 3);
			in1 += In1s;
			out0 += in0_5 * in1_0; 
			out1 += in0_5 * in1_1; 
			out2 += in0_5 * in1_2; 
			out3 += in0_5 * in1_3; 
			in1_0 = *(in1 + 0);
			in1_1 = *(in1 + 1);
			in1_2 = *(in1 + 2);
			in1_3 = *(in1 + 3);
			in1 += In1s;
			out0 += in0_6 * in1_0; 
			out1 += in0_6 * in1_1; 
			out2 += in0_6 * in1_2; 
			out3 += in0_6 * in1_3; 
			in1_0 = *(in1 + 0);
			in1_1 = *(in1 + 1);
			in1_2 = *(in1 + 2);
			in1_3 = *(in1 + 3);
			in1 += In1s;
			out0 += in0_7 * in1_0; 
			out1 += in0_7 * in1_1; 
			out2 += in0_7 * in1_2; 
			out3 += in0_7 * in1_3; 
		}
		* Out0 += out0;
		* Out1 += out1;
		* Out2 += out2;
		* Out3 += out3;
		Out0 += Outs1;
		Out1 += Outs1;
		Out2 += Outs1;
		Out3 += Outs1;
	}

	if (mod) {
		div = k - mod;
		mcdot_product_4x16(Out, _In0 + div, In1 + div*In1s, m, mod, Outs0, Outs1, In0s, In1s);
	}
}

//------------------------------------------------------------------------------
#endif
