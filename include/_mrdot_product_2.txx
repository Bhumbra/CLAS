# ifndef _mrdot_product_2_txx
# define _mrdot_product_2_txx

//------------------------------------------------------------------------------
template <class T, class U>
static inline void mrdot_product_2x1 (T* Out, 
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
	register T *in0;
	T *in1_0, *in1_1;
	T *Out0, *Out1; 
	T *In0;
	register U i, j;

	Out0 = Out;
	Out1 = Out + Outs0;
	In0 = _In0;

	for (i = m; i; i--) {
		in0 = In0;
		In0 += In0s;
		in1_0 = In1 + In1s * 0;
		in1_1 = In1 + In1s * 1;
		out0 = 0.;
		out1 = 0.;
		for (j = k; j; j--) {
			in0_0 = *(in0 + 0);
			in0 ++;
			out0 += in0_0 * *(in1_0 + 0); 
			out1 += in0_0 * *(in1_1 + 0); 
			in1_0 ++;
			in1_1 ++;
		}
		*Out0 += out0;
		*Out1 += out1;
		Out0 += Outs1;
		Out1 += Outs1;
	}
}

//------------------------------------------------------------------------------
template <class T, class U>
static inline void mrdot_product_2x2 (T* Out, 
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
	register T *in0;
	T *Out0, *Out1; 
	T *In0;
	T *in1_0, *in1_1; 
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
		in1_0 = In1 + In1s * 0;
		in1_1 = In1 + In1s * 1;
		out0 = 0.;
		out1 = 0.;
		for (j = div; j; j--) {
			in0_0 = *(in0 + 0);
			in0_1 = *(in0 + 1);
			in0 += 2;
			out0 += in0_0 * *(in1_0 + 0); 
			out1 += in0_0 * *(in1_1 + 0); 
			out0 += in0_1 * *(in1_0 + 1); 
			out1 += in0_1 * *(in1_1 + 1); 
			in1_0 += 2;
			in1_1 += 2;
		}
		*Out0 += out0;
		*Out1 += out1;
		Out0 += Outs1;
		Out1 += Outs1;
	}

	if (mod) {
		div = k - mod;
		mrdot_product_2x1 (Out, _In0 + div, In1 + div, m, mod, Outs0, Outs1, In0s, In1s);
	}
}

//------------------------------------------------------------------------------
template <class T, class U>
static inline void mrdot_product_2x4 (T* Out, 
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
	register T *in0;
	T *Out0, *Out1; 
	T *In0;
	T *in1_0, *in1_1; 
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
		in1_0 = In1 + In1s * 0;
		in1_1 = In1 + In1s * 1;
		out0 = 0.;
		out1 = 0.;
		for (j = div; j; j--) {
			in0_0 = *(in0 + 0);
			in0_1 = *(in0 + 1);
			in0_2 = *(in0 + 2);
			in0_3 = *(in0 + 3);
			in0 += 4;
			out0 += in0_0 * *(in1_0 + 0); 
			out1 += in0_0 * *(in1_1 + 0); 
			out0 += in0_1 * *(in1_0 + 1); 
			out1 += in0_1 * *(in1_1 + 1); 
			out0 += in0_2 * *(in1_0 + 2); 
			out1 += in0_2 * *(in1_1 + 2); 
			out0 += in0_3 * *(in1_0 + 3); 
			out1 += in0_3 * *(in1_1 + 3); 
			in1_0 += 4;
			in1_1 += 4;
		}
		*Out0 += out0;
		*Out1 += out1;
		Out0 += Outs1;
		Out1 += Outs1;
	}

	if (mod) {
		div = k - mod;
		mrdot_product_2x2 (Out, _In0 + div, In1 + div, m, mod, Outs0, Outs1, In0s, In1s);
	}
}

//------------------------------------------------------------------------------
template <class T, class U>
static inline void mrdot_product_2x8 (T* Out, 
																			T* _In0, 
																			T* In1, 
																			volatile const U m, 
																			volatile const U k,
																			volatile const U Outs0,
																			volatile const U Outs1 = 1,
																			volatile const U In0s = 1,
																			volatile const U In1s = 1) { 
	register T out0, out1;
	register T in0_0, in0_1, in0_2, in0_3, in0_4, in0_5, in0_6, in0_7;
	register T *in0;
	T *Out0, *Out1; 
	T *In0;
	T *in1_0, *in1_1; 
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
		in1_0 = In1 + In1s * 0;
		in1_1 = In1 + In1s * 1;
		out0 = 0.;
		out1 = 0.;
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
			out0 += in0_0 * *(in1_0 + 0); 
			out1 += in0_0 * *(in1_1 + 0); 
			out0 += in0_1 * *(in1_0 + 1); 
			out1 += in0_1 * *(in1_1 + 1); 
			out0 += in0_2 * *(in1_0 + 2); 
			out1 += in0_2 * *(in1_1 + 2); 
			out0 += in0_3 * *(in1_0 + 3); 
			out1 += in0_3 * *(in1_1 + 3); 
			out0 += in0_4 * *(in1_0 + 4); 
			out1 += in0_4 * *(in1_1 + 4); 
			out0 += in0_5 * *(in1_0 + 5); 
			out1 += in0_5 * *(in1_1 + 5); 
			out0 += in0_6 * *(in1_0 + 6); 
			out1 += in0_6 * *(in1_1 + 6); 
			out0 += in0_7 * *(in1_0 + 7); 
			out1 += in0_7 * *(in1_1 + 7); 
			in1_0 += 8;
			in1_1 += 8;
		}
		*Out0 += out0;
		*Out1 += out1;
		Out0 += Outs1;
		Out1 += Outs1;
	}

	if (mod) {
		div = k - mod;
		mrdot_product_2x4 (Out, _In0 + div, In1 + div, m, mod, Outs0, Outs1, In0s, In1s);
	}
}

//------------------------------------------------------------------------------
template <class T, class U>
static inline void mrdot_product_2x16(T* Out, 
																			T* _In0, 
																			T* In1, 
																			volatile const U m, 
																			volatile const U k,
																			volatile const U Outs0,
																			volatile const U Outs1 = 1,
																			volatile const U In0s = 1,
																			volatile const U In1s = 1) { 
	register T out0, out1;
	register T in0_0, in0_1, in0_2, in0_3, in0_4, in0_5, in0_6, in0_7;
	register T *in0;
	T *Out0, *Out1; 
	T *In0;
	T *in1_0, *in1_1; 
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
		in1_0 = In1 + In1s * 0;
		in1_1 = In1 + In1s * 1;
		out0 = 0.;
		out1 = 0.;
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
			out0 += in0_0 * *(in1_0 + 0); 
			out1 += in0_0 * *(in1_1 + 0); 
			out0 += in0_1 * *(in1_0 + 1); 
			out1 += in0_1 * *(in1_1 + 1); 
			out0 += in0_2 * *(in1_0 + 2); 
			out1 += in0_2 * *(in1_1 + 2); 
			out0 += in0_3 * *(in1_0 + 3); 
			out1 += in0_3 * *(in1_1 + 3); 
			out0 += in0_4 * *(in1_0 + 4); 
			out1 += in0_4 * *(in1_1 + 4); 
			out0 += in0_5 * *(in1_0 + 5); 
			out1 += in0_5 * *(in1_1 + 5); 
			out0 += in0_6 * *(in1_0 + 6); 
			out1 += in0_6 * *(in1_1 + 6); 
			out0 += in0_7 * *(in1_0 + 7); 
			out1 += in0_7 * *(in1_1 + 7); 
			in1_0 += 8;
			in1_1 += 8;
			in0_0 = *(in0 + 0);
			in0_1 = *(in0 + 1);
			in0_2 = *(in0 + 2);
			in0_3 = *(in0 + 3);
			in0_4 = *(in0 + 4);
			in0_5 = *(in0 + 5);
			in0_6 = *(in0 + 6);
			in0_7 = *(in0 + 7);
			in0 += 8;
			out0 += in0_0 * *(in1_0 + 0); 
			out1 += in0_0 * *(in1_1 + 0); 
			out0 += in0_1 * *(in1_0 + 1); 
			out1 += in0_1 * *(in1_1 + 1); 
			out0 += in0_2 * *(in1_0 + 2); 
			out1 += in0_2 * *(in1_1 + 2); 
			out0 += in0_3 * *(in1_0 + 3); 
			out1 += in0_3 * *(in1_1 + 3); 
			out0 += in0_4 * *(in1_0 + 4); 
			out1 += in0_4 * *(in1_1 + 4); 
			out0 += in0_5 * *(in1_0 + 5); 
			out1 += in0_5 * *(in1_1 + 5); 
			out0 += in0_6 * *(in1_0 + 6); 
			out1 += in0_6 * *(in1_1 + 6); 
			out0 += in0_7 * *(in1_0 + 7); 
			out1 += in0_7 * *(in1_1 + 7); 
			in1_0 += 8;
			in1_1 += 8;
		}
		*Out0 += out0;
		*Out1 += out1;
		Out0 += Outs1;
		Out1 += Outs1;
	}

	if (mod) {
		div = k - mod;
		mrdot_product_2x8 (Out, _In0 + div, In1 + div, m, mod, Outs0, Outs1, In0s, In1s);
	}
}

//------------------------------------------------------------------------------
template <class T, class U>
static inline void mrdot_product_2x32(T* Out, 
																			T* _In0, 
																			T* In1, 
																			volatile const U m, 
																			volatile const U k,
																			volatile const U Outs0,
																			volatile const U Outs1 = 1,
																			volatile const U In0s = 1,
																			volatile const U In1s = 1) { 
	register T out0, out1;
	register T in0_0, in0_1, in0_2, in0_3, in0_4, in0_5, in0_6, in0_7;
	register T *in0;
	T *Out0, *Out1; 
	T *In0;
	T *in1_0, *in1_1; 
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
		in1_0 = In1 + In1s * 0;
		in1_1 = In1 + In1s * 1;
		out0 = 0.;
		out1 = 0.;
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
			out0 += in0_0 * *(in1_0 + 0); 
			out1 += in0_0 * *(in1_1 + 0); 
			out0 += in0_1 * *(in1_0 + 1); 
			out1 += in0_1 * *(in1_1 + 1); 
			out0 += in0_2 * *(in1_0 + 2); 
			out1 += in0_2 * *(in1_1 + 2); 
			out0 += in0_3 * *(in1_0 + 3); 
			out1 += in0_3 * *(in1_1 + 3); 
			out0 += in0_4 * *(in1_0 + 4); 
			out1 += in0_4 * *(in1_1 + 4); 
			out0 += in0_5 * *(in1_0 + 5); 
			out1 += in0_5 * *(in1_1 + 5); 
			out0 += in0_6 * *(in1_0 + 6); 
			out1 += in0_6 * *(in1_1 + 6); 
			out0 += in0_7 * *(in1_0 + 7); 
			out1 += in0_7 * *(in1_1 + 7); 
			in1_0 += 8;
			in1_1 += 8;
			in0_0 = *(in0 + 0);
			in0_1 = *(in0 + 1);
			in0_2 = *(in0 + 2);
			in0_3 = *(in0 + 3);
			in0_4 = *(in0 + 4);
			in0_5 = *(in0 + 5);
			in0_6 = *(in0 + 6);
			in0_7 = *(in0 + 7);
			in0 += 8;
			out0 += in0_0 * *(in1_0 + 0); 
			out1 += in0_0 * *(in1_1 + 0); 
			out0 += in0_1 * *(in1_0 + 1); 
			out1 += in0_1 * *(in1_1 + 1); 
			out0 += in0_2 * *(in1_0 + 2); 
			out1 += in0_2 * *(in1_1 + 2); 
			out0 += in0_3 * *(in1_0 + 3); 
			out1 += in0_3 * *(in1_1 + 3); 
			out0 += in0_4 * *(in1_0 + 4); 
			out1 += in0_4 * *(in1_1 + 4); 
			out0 += in0_5 * *(in1_0 + 5); 
			out1 += in0_5 * *(in1_1 + 5); 
			out0 += in0_6 * *(in1_0 + 6); 
			out1 += in0_6 * *(in1_1 + 6); 
			out0 += in0_7 * *(in1_0 + 7); 
			out1 += in0_7 * *(in1_1 + 7); 
			in1_0 += 8;
			in1_1 += 8;
			in0_0 = *(in0 + 0);
			in0_1 = *(in0 + 1);
			in0_2 = *(in0 + 2);
			in0_3 = *(in0 + 3);
			in0_4 = *(in0 + 4);
			in0_5 = *(in0 + 5);
			in0_6 = *(in0 + 6);
			in0_7 = *(in0 + 7);
			in0 += 8;
			out0 += in0_0 * *(in1_0 + 0); 
			out1 += in0_0 * *(in1_1 + 0); 
			out0 += in0_1 * *(in1_0 + 1); 
			out1 += in0_1 * *(in1_1 + 1); 
			out0 += in0_2 * *(in1_0 + 2); 
			out1 += in0_2 * *(in1_1 + 2); 
			out0 += in0_3 * *(in1_0 + 3); 
			out1 += in0_3 * *(in1_1 + 3); 
			out0 += in0_4 * *(in1_0 + 4); 
			out1 += in0_4 * *(in1_1 + 4); 
			out0 += in0_5 * *(in1_0 + 5); 
			out1 += in0_5 * *(in1_1 + 5); 
			out0 += in0_6 * *(in1_0 + 6); 
			out1 += in0_6 * *(in1_1 + 6); 
			out0 += in0_7 * *(in1_0 + 7); 
			out1 += in0_7 * *(in1_1 + 7); 
			in1_0 += 8;
			in1_1 += 8;
			in0_0 = *(in0 + 0);
			in0_1 = *(in0 + 1);
			in0_2 = *(in0 + 2);
			in0_3 = *(in0 + 3);
			in0_4 = *(in0 + 4);
			in0_5 = *(in0 + 5);
			in0_6 = *(in0 + 6);
			in0_7 = *(in0 + 7);
			in0 += 8;
			out0 += in0_0 * *(in1_0 + 0); 
			out1 += in0_0 * *(in1_1 + 0); 
			out0 += in0_1 * *(in1_0 + 1); 
			out1 += in0_1 * *(in1_1 + 1); 
			out0 += in0_2 * *(in1_0 + 2); 
			out1 += in0_2 * *(in1_1 + 2); 
			out0 += in0_3 * *(in1_0 + 3); 
			out1 += in0_3 * *(in1_1 + 3); 
			out0 += in0_4 * *(in1_0 + 4); 
			out1 += in0_4 * *(in1_1 + 4); 
			out0 += in0_5 * *(in1_0 + 5); 
			out1 += in0_5 * *(in1_1 + 5); 
			out0 += in0_6 * *(in1_0 + 6); 
			out1 += in0_6 * *(in1_1 + 6); 
			out0 += in0_7 * *(in1_0 + 7); 
			out1 += in0_7 * *(in1_1 + 7); 
			in1_0 += 8;
			in1_1 += 8;
		}
		*Out0 += out0;
		*Out1 += out1;
		Out0 += Outs1;
		Out1 += Outs1;
	}

	if (mod) {
		div = k - mod;
		mrdot_product_2x16(Out, _In0 + div, In1 + div, m, mod, Outs0, Outs1, In0s, In1s);
	}
}

//------------------------------------------------------------------------------
#endif
