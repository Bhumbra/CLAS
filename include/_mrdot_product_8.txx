# ifndef _mrdot_product_8_txx
# define _mrdot_product_8_txx

//------------------------------------------------------------------------------
template <class T, class U>
static inline void mrdot_product_8x1 (T* Out, 
																			T* _In0, 
																			T* In1, 
																			volatile const U m, 
																			volatile const U k,
																			volatile const U Outs0,
																			volatile const U Outs1 = 1,
																			volatile const U In0s = 1,
																			volatile const U In1s = 1) { 
	register T out0, out1, out2, out3, out4, out5, out6, out7;
	register T in0_0;
	register T *in0;
	T *Out0, *Out1, *Out2, *Out3, *Out4, *Out5, *Out6, *Out7; 
	T *In0;
	T *in1_0, *in1_1, *in1_2, *in1_3, *in1_4, *in1_5, *in1_6, *in1_7;
	register U i, j;

	Out0 = Out + Outs0 * 0;
	Out1 = Out + Outs0 * 1;
	Out2 = Out + Outs0 * 2;
	Out3 = Out + Outs0 * 3;
	Out4 = Out + Outs0 * 4;
	Out5 = Out + Outs0 * 5;
	Out6 = Out + Outs0 * 6;
	Out7 = Out + Outs0 * 7;
	In0 = _In0;

	for (i = m; i; i--) {
		in0 = In0;
		In0 += In0s;
		in1_0 = In1 + In1s * 0;
		in1_1 = In1 + In1s * 1;
		in1_2 = In1 + In1s * 2;
		in1_3 = In1 + In1s * 3;
		in1_4 = In1 + In1s * 4;
		in1_5 = In1 + In1s * 5;
		in1_6 = In1 + In1s * 6;
		in1_7 = In1 + In1s * 7;
		out0 = 0.;
		out1 = 0.;
		out2 = 0.;
		out3 = 0.;
		out4 = 0.;
		out5 = 0.;
		out6 = 0.;
		out7 = 0.;
		for (j = k; j; j--) {
			in0_0 = *(in0 + 0);
			in0 ++;
			out0 += in0_0 * *(in1_0 + 0); 
			out1 += in0_0 * *(in1_1 + 0); 
			out2 += in0_0 * *(in1_2 + 0); 
			out3 += in0_0 * *(in1_3 + 0); 
			out4 += in0_0 * *(in1_4 + 0); 
			out5 += in0_0 * *(in1_5 + 0); 
			out6 += in0_0 * *(in1_6 + 0); 
			out7 += in0_0 * *(in1_7 + 0); 
			in1_0 ++;
			in1_1 ++;
			in1_2 ++;
			in1_3 ++;
			in1_4 ++;
			in1_5 ++;
			in1_6 ++;
			in1_7 ++;
		}
		*Out0 += out0;
		*Out1 += out1;
		*Out2 += out2;
		*Out3 += out3;
		*Out4 += out4;
		*Out5 += out5;
		*Out6 += out6;
		*Out7 += out7;
		Out0 += Outs1;
		Out1 += Outs1;
		Out2 += Outs1;
		Out3 += Outs1;
		Out4 += Outs1;
		Out5 += Outs1;
		Out6 += Outs1;
		Out7 += Outs1;
	}
}

//------------------------------------------------------------------------------
template <class T, class U>
static inline void mrdot_product_8x2 (T* Out, 
																			T* _In0, 
																			T* In1, 
																			volatile const U m, 
																			volatile const U k,
																			volatile const U Outs0,
																			volatile const U Outs1 = 1,
																			volatile const U In0s = 1,
																			volatile const U In1s = 1) { 
	register T out0, out1, out2, out3, out4, out5, out6, out7;
	register T in0_0, in0_1;
	register T *in0;
	T *Out0, *Out1, *Out2, *Out3, *Out4, *Out5, *Out6, *Out7; 
	T *In0;
	T *in1_0, *in1_1, *in1_2, *in1_3, *in1_4, *in1_5, *in1_6, *in1_7;
	volatile U div, mod;
	register U i, j;

	div = k >> 1;
	mod = k & 1;

	Out0 = Out + Outs0 * 0;
	Out1 = Out + Outs0 * 1;
	Out2 = Out + Outs0 * 2;
	Out3 = Out + Outs0 * 3;
	Out4 = Out + Outs0 * 4;
	Out5 = Out + Outs0 * 5;
	Out6 = Out + Outs0 * 6;
	Out7 = Out + Outs0 * 7;
	In0 = _In0;

	for (i = m; i; i--) {
		in0 = In0;
		In0 += In0s;
		in1_0 = In1 + In1s * 0;
		in1_1 = In1 + In1s * 1;
		in1_2 = In1 + In1s * 2;
		in1_3 = In1 + In1s * 3;
		in1_4 = In1 + In1s * 4;
		in1_5 = In1 + In1s * 5;
		in1_6 = In1 + In1s * 6;
		in1_7 = In1 + In1s * 7;
		out0 = 0.;
		out1 = 0.;
		out2 = 0.;
		out3 = 0.;
		out4 = 0.;
		out5 = 0.;
		out6 = 0.;
		out7 = 0.;
		for (j = div; j; j--) {
			in0_0 = *(in0 + 0);
			in0_1 = *(in0 + 1);
			in0 += 2;
			out0 += in0_0 * *(in1_0 + 0); 
			out1 += in0_0 * *(in1_1 + 0); 
			out2 += in0_0 * *(in1_2 + 0); 
			out3 += in0_0 * *(in1_3 + 0); 
			out4 += in0_0 * *(in1_4 + 0); 
			out5 += in0_0 * *(in1_5 + 0); 
			out6 += in0_0 * *(in1_6 + 0); 
			out7 += in0_0 * *(in1_7 + 0); 
			out0 += in0_1 * *(in1_0 + 1); 
			out1 += in0_1 * *(in1_1 + 1); 
			out2 += in0_1 * *(in1_2 + 1); 
			out3 += in0_1 * *(in1_3 + 1); 
			out4 += in0_1 * *(in1_4 + 1); 
			out5 += in0_1 * *(in1_5 + 1); 
			out6 += in0_1 * *(in1_6 + 1); 
			out7 += in0_1 * *(in1_7 + 1); 
			in1_0 += 2;
			in1_1 += 2;
			in1_2 += 2;
			in1_3 += 2;
			in1_4 += 2;
			in1_5 += 2;
			in1_6 += 2;
			in1_7 += 2;
		}
		*Out0 += out0;
		*Out1 += out1;
		*Out2 += out2;
		*Out3 += out3;
		*Out4 += out4;
		*Out5 += out5;
		*Out6 += out6;
		*Out7 += out7;
		Out0 += Outs1;
		Out1 += Outs1;
		Out2 += Outs1;
		Out3 += Outs1;
		Out4 += Outs1;
		Out5 += Outs1;
		Out6 += Outs1;
		Out7 += Outs1;
	}

	if (mod) {
		div = k - mod;
		mrdot_product_8x1 (Out, _In0 + div, In1 + div, m, mod, Outs0, Outs1, In0s, In1s);
	}
}

//------------------------------------------------------------------------------
template <class T, class U>
static inline void mrdot_product_8x4 (T* Out, 
																			T* _In0, 
																			T* In1, 
																			volatile const U m, 
																			volatile const U k,
																			volatile const U Outs0,
																			volatile const U Outs1 = 1,
																			volatile const U In0s = 1,
																			volatile const U In1s = 1) { 
	register T out0, out1, out2, out3, out4, out5, out6, out7;
	register T in0_0, in0_1, in0_2, in0_3;
	register T *in0;
	T *Out0, *Out1, *Out2, *Out3, *Out4, *Out5, *Out6, *Out7; 
	T *In0;
	T *in1_0, *in1_1, *in1_2, *in1_3, *in1_4, *in1_5, *in1_6, *in1_7;
	volatile U div, mod;
	register U i, j;

	div = k >> 2;
	mod = k & 3;

	Out0 = Out + Outs0 * 0;
	Out1 = Out + Outs0 * 1;
	Out2 = Out + Outs0 * 2;
	Out3 = Out + Outs0 * 3;
	Out4 = Out + Outs0 * 4;
	Out5 = Out + Outs0 * 5;
	Out6 = Out + Outs0 * 6;
	Out7 = Out + Outs0 * 7;
	In0 = _In0;

	for (i = m; i; i--) {
		in0 = In0;
		In0 += In0s;
		in1_0 = In1 + In1s * 0;
		in1_1 = In1 + In1s * 1;
		in1_2 = In1 + In1s * 2;
		in1_3 = In1 + In1s * 3;
		in1_4 = In1 + In1s * 4;
		in1_5 = In1 + In1s * 5;
		in1_6 = In1 + In1s * 6;
		in1_7 = In1 + In1s * 7;
		out0 = 0.;
		out1 = 0.;
		out2 = 0.;
		out3 = 0.;
		out4 = 0.;
		out5 = 0.;
		out6 = 0.;
		out7 = 0.;
		for (j = div; j; j--) {
			in0_0 = *(in0 + 0);
			in0_1 = *(in0 + 1);
			in0_2 = *(in0 + 2);
			in0_3 = *(in0 + 3);
			in0 += 4;
			out0 += in0_0 * *(in1_0 + 0); 
			out1 += in0_0 * *(in1_1 + 0); 
			out2 += in0_0 * *(in1_2 + 0); 
			out3 += in0_0 * *(in1_3 + 0); 
			out4 += in0_0 * *(in1_4 + 0); 
			out5 += in0_0 * *(in1_5 + 0); 
			out6 += in0_0 * *(in1_6 + 0); 
			out7 += in0_0 * *(in1_7 + 0); 
			out0 += in0_1 * *(in1_0 + 1); 
			out1 += in0_1 * *(in1_1 + 1); 
			out2 += in0_1 * *(in1_2 + 1); 
			out3 += in0_1 * *(in1_3 + 1); 
			out4 += in0_1 * *(in1_4 + 1); 
			out5 += in0_1 * *(in1_5 + 1); 
			out6 += in0_1 * *(in1_6 + 1); 
			out7 += in0_1 * *(in1_7 + 1); 
			out0 += in0_2 * *(in1_0 + 2); 
			out1 += in0_2 * *(in1_1 + 2); 
			out2 += in0_2 * *(in1_2 + 2); 
			out3 += in0_2 * *(in1_3 + 2); 
			out4 += in0_2 * *(in1_4 + 2); 
			out5 += in0_2 * *(in1_5 + 2); 
			out6 += in0_2 * *(in1_6 + 2); 
			out7 += in0_2 * *(in1_7 + 2); 
			out0 += in0_3 * *(in1_0 + 3); 
			out1 += in0_3 * *(in1_1 + 3); 
			out2 += in0_3 * *(in1_2 + 3); 
			out3 += in0_3 * *(in1_3 + 3); 
			out4 += in0_3 * *(in1_4 + 3); 
			out5 += in0_3 * *(in1_5 + 3); 
			out6 += in0_3 * *(in1_6 + 3); 
			out7 += in0_3 * *(in1_7 + 3); 
			in1_0 += 4;
			in1_1 += 4;
			in1_2 += 4;
			in1_3 += 4;
			in1_4 += 4;
			in1_5 += 4;
			in1_6 += 4;
			in1_7 += 4;
		}
		*Out0 += out0;
		*Out1 += out1;
		*Out2 += out2;
		*Out3 += out3;
		*Out4 += out4;
		*Out5 += out5;
		*Out6 += out6;
		*Out7 += out7;
		Out0 += Outs1;
		Out1 += Outs1;
		Out2 += Outs1;
		Out3 += Outs1;
		Out4 += Outs1;
		Out5 += Outs1;
		Out6 += Outs1;
		Out7 += Outs1;
	}

	if (mod) {
		div = k - mod;
		mrdot_product_8x2 (Out, _In0 + div, In1 + div, m, mod, Outs0, Outs1, In0s, In1s);
	}
}

//------------------------------------------------------------------------------
template <class T, class U>
static inline void mrdot_product_8x8 (T* Out, 
																			T* _In0, 
																			T* In1, 
																			volatile const U m, 
																			volatile const U k,
																			volatile const U Outs0,
																			volatile const U Outs1 = 1,
																			volatile const U In0s = 1,
																			volatile const U In1s = 1) { 
	register T out0, out1, out2, out3, out4, out5, out6, out7;
	register T in0_0, in0_1, in0_2, in0_3, in0_4, in0_5, in0_6, in0_7;
	register T *in0;
	T *Out0, *Out1, *Out2, *Out3, *Out4, *Out5, *Out6, *Out7; 
	T *In0;
	T *in1_0, *in1_1, *in1_2, *in1_3, *in1_4, *in1_5, *in1_6, *in1_7;
	volatile U div, mod;
	register U i, j;

	div = k >> 3;
	mod = k & 7;

	Out0 = Out + Outs0 * 0;
	Out1 = Out + Outs0 * 1;
	Out2 = Out + Outs0 * 2;
	Out3 = Out + Outs0 * 3;
	Out4 = Out + Outs0 * 4;
	Out5 = Out + Outs0 * 5;
	Out6 = Out + Outs0 * 6;
	Out7 = Out + Outs0 * 7;
	In0 = _In0;

	for (i = m; i; i--) {
		in0 = In0;
		In0 += In0s;
		in1_0 = In1 + In1s * 0;
		in1_1 = In1 + In1s * 1;
		in1_2 = In1 + In1s * 2;
		in1_3 = In1 + In1s * 3;
		in1_4 = In1 + In1s * 4;
		in1_5 = In1 + In1s * 5;
		in1_6 = In1 + In1s * 6;
		in1_7 = In1 + In1s * 7;
		out0 = 0.;
		out1 = 0.;
		out2 = 0.;
		out3 = 0.;
		out4 = 0.;
		out5 = 0.;
		out6 = 0.;
		out7 = 0.;
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
			out2 += in0_0 * *(in1_2 + 0); 
			out3 += in0_0 * *(in1_3 + 0); 
			out4 += in0_0 * *(in1_4 + 0); 
			out5 += in0_0 * *(in1_5 + 0); 
			out6 += in0_0 * *(in1_6 + 0); 
			out7 += in0_0 * *(in1_7 + 0); 
			out0 += in0_1 * *(in1_0 + 1); 
			out1 += in0_1 * *(in1_1 + 1); 
			out2 += in0_1 * *(in1_2 + 1); 
			out3 += in0_1 * *(in1_3 + 1); 
			out4 += in0_1 * *(in1_4 + 1); 
			out5 += in0_1 * *(in1_5 + 1); 
			out6 += in0_1 * *(in1_6 + 1); 
			out7 += in0_1 * *(in1_7 + 1); 
			out0 += in0_2 * *(in1_0 + 2); 
			out1 += in0_2 * *(in1_1 + 2); 
			out2 += in0_2 * *(in1_2 + 2); 
			out3 += in0_2 * *(in1_3 + 2); 
			out4 += in0_2 * *(in1_4 + 2); 
			out5 += in0_2 * *(in1_5 + 2); 
			out6 += in0_2 * *(in1_6 + 2); 
			out7 += in0_2 * *(in1_7 + 2); 
			out0 += in0_3 * *(in1_0 + 3); 
			out1 += in0_3 * *(in1_1 + 3); 
			out2 += in0_3 * *(in1_2 + 3); 
			out3 += in0_3 * *(in1_3 + 3); 
			out4 += in0_3 * *(in1_4 + 3); 
			out5 += in0_3 * *(in1_5 + 3); 
			out6 += in0_3 * *(in1_6 + 3); 
			out7 += in0_3 * *(in1_7 + 3); 
			out0 += in0_4 * *(in1_0 + 4); 
			out1 += in0_4 * *(in1_1 + 4); 
			out2 += in0_4 * *(in1_2 + 4); 
			out3 += in0_4 * *(in1_3 + 4); 
			out4 += in0_4 * *(in1_4 + 4); 
			out5 += in0_4 * *(in1_5 + 4); 
			out6 += in0_4 * *(in1_6 + 4); 
			out7 += in0_4 * *(in1_7 + 4); 
			out0 += in0_5 * *(in1_0 + 5); 
			out1 += in0_5 * *(in1_1 + 5); 
			out2 += in0_5 * *(in1_2 + 5); 
			out3 += in0_5 * *(in1_3 + 5); 
			out4 += in0_5 * *(in1_4 + 5); 
			out5 += in0_5 * *(in1_5 + 5); 
			out6 += in0_5 * *(in1_6 + 5); 
			out7 += in0_5 * *(in1_7 + 5); 
			out0 += in0_6 * *(in1_0 + 6); 
			out1 += in0_6 * *(in1_1 + 6); 
			out2 += in0_6 * *(in1_2 + 6); 
			out3 += in0_6 * *(in1_3 + 6); 
			out4 += in0_6 * *(in1_4 + 6); 
			out5 += in0_6 * *(in1_5 + 6); 
			out6 += in0_6 * *(in1_6 + 6); 
			out7 += in0_6 * *(in1_7 + 6); 
			out0 += in0_7 * *(in1_0 + 7); 
			out1 += in0_7 * *(in1_1 + 7); 
			out2 += in0_7 * *(in1_2 + 7); 
			out3 += in0_7 * *(in1_3 + 7); 
			out4 += in0_7 * *(in1_4 + 7); 
			out5 += in0_7 * *(in1_5 + 7); 
			out6 += in0_7 * *(in1_6 + 7); 
			out7 += in0_7 * *(in1_7 + 7); 
			in1_0 += 8;
			in1_1 += 8;
			in1_2 += 8;
			in1_3 += 8;
			in1_4 += 8;
			in1_5 += 8;
			in1_6 += 8;
			in1_7 += 8;
		}
		*Out0 += out0;
		*Out1 += out1;
		*Out2 += out2;
		*Out3 += out3;
		*Out4 += out4;
		*Out5 += out5;
		*Out6 += out6;
		*Out7 += out7;
		Out0 += Outs1;
		Out1 += Outs1;
		Out2 += Outs1;
		Out3 += Outs1;
		Out4 += Outs1;
		Out5 += Outs1;
		Out6 += Outs1;
		Out7 += Outs1;
	}

	if (mod) {
		div = k - mod;
		mrdot_product_8x4 (Out, _In0 + div, In1 + div, m, mod, Outs0, Outs1, In0s, In1s);
	}
}

//------------------------------------------------------------------------------
template <class T, class U>
static inline void mrdot_product_8x16(T* Out, 
																			T* _In0, 
																			T* In1, 
																			volatile const U m, 
																			volatile const U k,
																			volatile const U Outs0,
																			volatile const U Outs1 = 1,
																			volatile const U In0s = 1,
																			volatile const U In1s = 1) { 
	register T out0, out1, out2, out3, out4, out5, out6, out7;
	register T in0_0, in0_1, in0_2, in0_3, in0_4, in0_5, in0_6, in0_7;
	register T *in0;
	T *Out0, *Out1, *Out2, *Out3, *Out4, *Out5, *Out6, *Out7; 
	T *In0;
	T *in1_0, *in1_1, *in1_2, *in1_3, *in1_4, *in1_5, *in1_6, *in1_7;
	volatile U div, mod;
	register U i, j;

	div = k >> 4;
	mod = k & 15;

	Out0 = Out + Outs0 * 0;
	Out1 = Out + Outs0 * 1;
	Out2 = Out + Outs0 * 2;
	Out3 = Out + Outs0 * 3;
	Out4 = Out + Outs0 * 4;
	Out5 = Out + Outs0 * 5;
	Out6 = Out + Outs0 * 6;
	Out7 = Out + Outs0 * 7;
	In0 = _In0;

	for (i = m; i; i--) {
		in0 = In0;
		In0 += In0s;
		in1_0 = In1 + In1s * 0;
		in1_1 = In1 + In1s * 1;
		in1_2 = In1 + In1s * 2;
		in1_3 = In1 + In1s * 3;
		in1_4 = In1 + In1s * 4;
		in1_5 = In1 + In1s * 5;
		in1_6 = In1 + In1s * 6;
		in1_7 = In1 + In1s * 7;
		out0 = 0.;
		out1 = 0.;
		out2 = 0.;
		out3 = 0.;
		out4 = 0.;
		out5 = 0.;
		out6 = 0.;
		out7 = 0.;
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
			out2 += in0_0 * *(in1_2 + 0); 
			out3 += in0_0 * *(in1_3 + 0); 
			out4 += in0_0 * *(in1_4 + 0); 
			out5 += in0_0 * *(in1_5 + 0); 
			out6 += in0_0 * *(in1_6 + 0); 
			out7 += in0_0 * *(in1_7 + 0); 
			out0 += in0_1 * *(in1_0 + 1); 
			out1 += in0_1 * *(in1_1 + 1); 
			out2 += in0_1 * *(in1_2 + 1); 
			out3 += in0_1 * *(in1_3 + 1); 
			out4 += in0_1 * *(in1_4 + 1); 
			out5 += in0_1 * *(in1_5 + 1); 
			out6 += in0_1 * *(in1_6 + 1); 
			out7 += in0_1 * *(in1_7 + 1); 
			out0 += in0_2 * *(in1_0 + 2); 
			out1 += in0_2 * *(in1_1 + 2); 
			out2 += in0_2 * *(in1_2 + 2); 
			out3 += in0_2 * *(in1_3 + 2); 
			out4 += in0_2 * *(in1_4 + 2); 
			out5 += in0_2 * *(in1_5 + 2); 
			out6 += in0_2 * *(in1_6 + 2); 
			out7 += in0_2 * *(in1_7 + 2); 
			out0 += in0_3 * *(in1_0 + 3); 
			out1 += in0_3 * *(in1_1 + 3); 
			out2 += in0_3 * *(in1_2 + 3); 
			out3 += in0_3 * *(in1_3 + 3); 
			out4 += in0_3 * *(in1_4 + 3); 
			out5 += in0_3 * *(in1_5 + 3); 
			out6 += in0_3 * *(in1_6 + 3); 
			out7 += in0_3 * *(in1_7 + 3); 
			out0 += in0_4 * *(in1_0 + 4); 
			out1 += in0_4 * *(in1_1 + 4); 
			out2 += in0_4 * *(in1_2 + 4); 
			out3 += in0_4 * *(in1_3 + 4); 
			out4 += in0_4 * *(in1_4 + 4); 
			out5 += in0_4 * *(in1_5 + 4); 
			out6 += in0_4 * *(in1_6 + 4); 
			out7 += in0_4 * *(in1_7 + 4); 
			out0 += in0_5 * *(in1_0 + 5); 
			out1 += in0_5 * *(in1_1 + 5); 
			out2 += in0_5 * *(in1_2 + 5); 
			out3 += in0_5 * *(in1_3 + 5); 
			out4 += in0_5 * *(in1_4 + 5); 
			out5 += in0_5 * *(in1_5 + 5); 
			out6 += in0_5 * *(in1_6 + 5); 
			out7 += in0_5 * *(in1_7 + 5); 
			out0 += in0_6 * *(in1_0 + 6); 
			out1 += in0_6 * *(in1_1 + 6); 
			out2 += in0_6 * *(in1_2 + 6); 
			out3 += in0_6 * *(in1_3 + 6); 
			out4 += in0_6 * *(in1_4 + 6); 
			out5 += in0_6 * *(in1_5 + 6); 
			out6 += in0_6 * *(in1_6 + 6); 
			out7 += in0_6 * *(in1_7 + 6); 
			out0 += in0_7 * *(in1_0 + 7); 
			out1 += in0_7 * *(in1_1 + 7); 
			out2 += in0_7 * *(in1_2 + 7); 
			out3 += in0_7 * *(in1_3 + 7); 
			out4 += in0_7 * *(in1_4 + 7); 
			out5 += in0_7 * *(in1_5 + 7); 
			out6 += in0_7 * *(in1_6 + 7); 
			out7 += in0_7 * *(in1_7 + 7); 
			in1_0 += 8;
			in1_1 += 8;
			in1_2 += 8;
			in1_3 += 8;
			in1_4 += 8;
			in1_5 += 8;
			in1_6 += 8;
			in1_7 += 8;
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
			out2 += in0_0 * *(in1_2 + 0); 
			out3 += in0_0 * *(in1_3 + 0); 
			out4 += in0_0 * *(in1_4 + 0); 
			out5 += in0_0 * *(in1_5 + 0); 
			out6 += in0_0 * *(in1_6 + 0); 
			out7 += in0_0 * *(in1_7 + 0); 
			out0 += in0_1 * *(in1_0 + 1); 
			out1 += in0_1 * *(in1_1 + 1); 
			out2 += in0_1 * *(in1_2 + 1); 
			out3 += in0_1 * *(in1_3 + 1); 
			out4 += in0_1 * *(in1_4 + 1); 
			out5 += in0_1 * *(in1_5 + 1); 
			out6 += in0_1 * *(in1_6 + 1); 
			out7 += in0_1 * *(in1_7 + 1); 
			out0 += in0_2 * *(in1_0 + 2); 
			out1 += in0_2 * *(in1_1 + 2); 
			out2 += in0_2 * *(in1_2 + 2); 
			out3 += in0_2 * *(in1_3 + 2); 
			out4 += in0_2 * *(in1_4 + 2); 
			out5 += in0_2 * *(in1_5 + 2); 
			out6 += in0_2 * *(in1_6 + 2); 
			out7 += in0_2 * *(in1_7 + 2); 
			out0 += in0_3 * *(in1_0 + 3); 
			out1 += in0_3 * *(in1_1 + 3); 
			out2 += in0_3 * *(in1_2 + 3); 
			out3 += in0_3 * *(in1_3 + 3); 
			out4 += in0_3 * *(in1_4 + 3); 
			out5 += in0_3 * *(in1_5 + 3); 
			out6 += in0_3 * *(in1_6 + 3); 
			out7 += in0_3 * *(in1_7 + 3); 
			out0 += in0_4 * *(in1_0 + 4); 
			out1 += in0_4 * *(in1_1 + 4); 
			out2 += in0_4 * *(in1_2 + 4); 
			out3 += in0_4 * *(in1_3 + 4); 
			out4 += in0_4 * *(in1_4 + 4); 
			out5 += in0_4 * *(in1_5 + 4); 
			out6 += in0_4 * *(in1_6 + 4); 
			out7 += in0_4 * *(in1_7 + 4); 
			out0 += in0_5 * *(in1_0 + 5); 
			out1 += in0_5 * *(in1_1 + 5); 
			out2 += in0_5 * *(in1_2 + 5); 
			out3 += in0_5 * *(in1_3 + 5); 
			out4 += in0_5 * *(in1_4 + 5); 
			out5 += in0_5 * *(in1_5 + 5); 
			out6 += in0_5 * *(in1_6 + 5); 
			out7 += in0_5 * *(in1_7 + 5); 
			out0 += in0_6 * *(in1_0 + 6); 
			out1 += in0_6 * *(in1_1 + 6); 
			out2 += in0_6 * *(in1_2 + 6); 
			out3 += in0_6 * *(in1_3 + 6); 
			out4 += in0_6 * *(in1_4 + 6); 
			out5 += in0_6 * *(in1_5 + 6); 
			out6 += in0_6 * *(in1_6 + 6); 
			out7 += in0_6 * *(in1_7 + 6); 
			out0 += in0_7 * *(in1_0 + 7); 
			out1 += in0_7 * *(in1_1 + 7); 
			out2 += in0_7 * *(in1_2 + 7); 
			out3 += in0_7 * *(in1_3 + 7); 
			out4 += in0_7 * *(in1_4 + 7); 
			out5 += in0_7 * *(in1_5 + 7); 
			out6 += in0_7 * *(in1_6 + 7); 
			out7 += in0_7 * *(in1_7 + 7); 
			in1_0 += 8;
			in1_1 += 8;
			in1_2 += 8;
			in1_3 += 8;
			in1_4 += 8;
			in1_5 += 8;
			in1_6 += 8;
			in1_7 += 8;
		}
		*Out0 += out0;
		*Out1 += out1;
		*Out2 += out2;
		*Out3 += out3;
		*Out4 += out4;
		*Out5 += out5;
		*Out6 += out6;
		*Out7 += out7;
		Out0 += Outs1;
		Out1 += Outs1;
		Out2 += Outs1;
		Out3 += Outs1;
		Out4 += Outs1;
		Out5 += Outs1;
		Out6 += Outs1;
		Out7 += Outs1;
	}

	if (mod) {
		div = k - mod;
		mrdot_product_8x8 (Out, _In0 + div, In1 + div, m, mod, Outs0, Outs1, In0s, In1s);
	}
}

//------------------------------------------------------------------------------
template <class T, class U>
static inline void mrdot_product_8x32(T* Out, 
																			T* _In0, 
																			T* In1, 
																			volatile const U m, 
																			volatile const U k,
																			volatile const U Outs0,
																			volatile const U Outs1 = 1,
																			volatile const U In0s = 1,
																			volatile const U In1s = 1) { 
	register T out0, out1, out2, out3, out4, out5, out6, out7;
	register T in0_0, in0_1, in0_2, in0_3, in0_4, in0_5, in0_6, in0_7;
	register T *in0;
	T *Out0, *Out1, *Out2, *Out3, *Out4, *Out5, *Out6, *Out7; 
	T *In0;
	T *in1_0, *in1_1, *in1_2, *in1_3, *in1_4, *in1_5, *in1_6, *in1_7;
	volatile U div, mod;
	register U i, j;

	div = k >> 5;
	mod = k & 31;

	Out0 = Out + Outs0 * 0;
	Out1 = Out + Outs0 * 1;
	Out2 = Out + Outs0 * 2;
	Out3 = Out + Outs0 * 3;
	Out4 = Out + Outs0 * 4;
	Out5 = Out + Outs0 * 5;
	Out6 = Out + Outs0 * 6;
	Out7 = Out + Outs0 * 7;
	In0 = _In0;

	for (i = m; i; i--) {
		in0 = In0;
		In0 += In0s;
		in1_0 = In1 + In1s * 0;
		in1_1 = In1 + In1s * 1;
		in1_2 = In1 + In1s * 2;
		in1_3 = In1 + In1s * 3;
		in1_4 = In1 + In1s * 4;
		in1_5 = In1 + In1s * 5;
		in1_6 = In1 + In1s * 6;
		in1_7 = In1 + In1s * 7;
		out0 = 0.;
		out1 = 0.;
		out2 = 0.;
		out3 = 0.;
		out4 = 0.;
		out5 = 0.;
		out6 = 0.;
		out7 = 0.;
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
			out2 += in0_0 * *(in1_2 + 0); 
			out3 += in0_0 * *(in1_3 + 0); 
			out4 += in0_0 * *(in1_4 + 0); 
			out5 += in0_0 * *(in1_5 + 0); 
			out6 += in0_0 * *(in1_6 + 0); 
			out7 += in0_0 * *(in1_7 + 0); 
			out0 += in0_1 * *(in1_0 + 1); 
			out1 += in0_1 * *(in1_1 + 1); 
			out2 += in0_1 * *(in1_2 + 1); 
			out3 += in0_1 * *(in1_3 + 1); 
			out4 += in0_1 * *(in1_4 + 1); 
			out5 += in0_1 * *(in1_5 + 1); 
			out6 += in0_1 * *(in1_6 + 1); 
			out7 += in0_1 * *(in1_7 + 1); 
			out0 += in0_2 * *(in1_0 + 2); 
			out1 += in0_2 * *(in1_1 + 2); 
			out2 += in0_2 * *(in1_2 + 2); 
			out3 += in0_2 * *(in1_3 + 2); 
			out4 += in0_2 * *(in1_4 + 2); 
			out5 += in0_2 * *(in1_5 + 2); 
			out6 += in0_2 * *(in1_6 + 2); 
			out7 += in0_2 * *(in1_7 + 2); 
			out0 += in0_3 * *(in1_0 + 3); 
			out1 += in0_3 * *(in1_1 + 3); 
			out2 += in0_3 * *(in1_2 + 3); 
			out3 += in0_3 * *(in1_3 + 3); 
			out4 += in0_3 * *(in1_4 + 3); 
			out5 += in0_3 * *(in1_5 + 3); 
			out6 += in0_3 * *(in1_6 + 3); 
			out7 += in0_3 * *(in1_7 + 3); 
			out0 += in0_4 * *(in1_0 + 4); 
			out1 += in0_4 * *(in1_1 + 4); 
			out2 += in0_4 * *(in1_2 + 4); 
			out3 += in0_4 * *(in1_3 + 4); 
			out4 += in0_4 * *(in1_4 + 4); 
			out5 += in0_4 * *(in1_5 + 4); 
			out6 += in0_4 * *(in1_6 + 4); 
			out7 += in0_4 * *(in1_7 + 4); 
			out0 += in0_5 * *(in1_0 + 5); 
			out1 += in0_5 * *(in1_1 + 5); 
			out2 += in0_5 * *(in1_2 + 5); 
			out3 += in0_5 * *(in1_3 + 5); 
			out4 += in0_5 * *(in1_4 + 5); 
			out5 += in0_5 * *(in1_5 + 5); 
			out6 += in0_5 * *(in1_6 + 5); 
			out7 += in0_5 * *(in1_7 + 5); 
			out0 += in0_6 * *(in1_0 + 6); 
			out1 += in0_6 * *(in1_1 + 6); 
			out2 += in0_6 * *(in1_2 + 6); 
			out3 += in0_6 * *(in1_3 + 6); 
			out4 += in0_6 * *(in1_4 + 6); 
			out5 += in0_6 * *(in1_5 + 6); 
			out6 += in0_6 * *(in1_6 + 6); 
			out7 += in0_6 * *(in1_7 + 6); 
			out0 += in0_7 * *(in1_0 + 7); 
			out1 += in0_7 * *(in1_1 + 7); 
			out2 += in0_7 * *(in1_2 + 7); 
			out3 += in0_7 * *(in1_3 + 7); 
			out4 += in0_7 * *(in1_4 + 7); 
			out5 += in0_7 * *(in1_5 + 7); 
			out6 += in0_7 * *(in1_6 + 7); 
			out7 += in0_7 * *(in1_7 + 7); 
			in1_0 += 8;
			in1_1 += 8;
			in1_2 += 8;
			in1_3 += 8;
			in1_4 += 8;
			in1_5 += 8;
			in1_6 += 8;
			in1_7 += 8;
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
			out2 += in0_0 * *(in1_2 + 0); 
			out3 += in0_0 * *(in1_3 + 0); 
			out4 += in0_0 * *(in1_4 + 0); 
			out5 += in0_0 * *(in1_5 + 0); 
			out6 += in0_0 * *(in1_6 + 0); 
			out7 += in0_0 * *(in1_7 + 0); 
			out0 += in0_1 * *(in1_0 + 1); 
			out1 += in0_1 * *(in1_1 + 1); 
			out2 += in0_1 * *(in1_2 + 1); 
			out3 += in0_1 * *(in1_3 + 1); 
			out4 += in0_1 * *(in1_4 + 1); 
			out5 += in0_1 * *(in1_5 + 1); 
			out6 += in0_1 * *(in1_6 + 1); 
			out7 += in0_1 * *(in1_7 + 1); 
			out0 += in0_2 * *(in1_0 + 2); 
			out1 += in0_2 * *(in1_1 + 2); 
			out2 += in0_2 * *(in1_2 + 2); 
			out3 += in0_2 * *(in1_3 + 2); 
			out4 += in0_2 * *(in1_4 + 2); 
			out5 += in0_2 * *(in1_5 + 2); 
			out6 += in0_2 * *(in1_6 + 2); 
			out7 += in0_2 * *(in1_7 + 2); 
			out0 += in0_3 * *(in1_0 + 3); 
			out1 += in0_3 * *(in1_1 + 3); 
			out2 += in0_3 * *(in1_2 + 3); 
			out3 += in0_3 * *(in1_3 + 3); 
			out4 += in0_3 * *(in1_4 + 3); 
			out5 += in0_3 * *(in1_5 + 3); 
			out6 += in0_3 * *(in1_6 + 3); 
			out7 += in0_3 * *(in1_7 + 3); 
			out0 += in0_4 * *(in1_0 + 4); 
			out1 += in0_4 * *(in1_1 + 4); 
			out2 += in0_4 * *(in1_2 + 4); 
			out3 += in0_4 * *(in1_3 + 4); 
			out4 += in0_4 * *(in1_4 + 4); 
			out5 += in0_4 * *(in1_5 + 4); 
			out6 += in0_4 * *(in1_6 + 4); 
			out7 += in0_4 * *(in1_7 + 4); 
			out0 += in0_5 * *(in1_0 + 5); 
			out1 += in0_5 * *(in1_1 + 5); 
			out2 += in0_5 * *(in1_2 + 5); 
			out3 += in0_5 * *(in1_3 + 5); 
			out4 += in0_5 * *(in1_4 + 5); 
			out5 += in0_5 * *(in1_5 + 5); 
			out6 += in0_5 * *(in1_6 + 5); 
			out7 += in0_5 * *(in1_7 + 5); 
			out0 += in0_6 * *(in1_0 + 6); 
			out1 += in0_6 * *(in1_1 + 6); 
			out2 += in0_6 * *(in1_2 + 6); 
			out3 += in0_6 * *(in1_3 + 6); 
			out4 += in0_6 * *(in1_4 + 6); 
			out5 += in0_6 * *(in1_5 + 6); 
			out6 += in0_6 * *(in1_6 + 6); 
			out7 += in0_6 * *(in1_7 + 6); 
			out0 += in0_7 * *(in1_0 + 7); 
			out1 += in0_7 * *(in1_1 + 7); 
			out2 += in0_7 * *(in1_2 + 7); 
			out3 += in0_7 * *(in1_3 + 7); 
			out4 += in0_7 * *(in1_4 + 7); 
			out5 += in0_7 * *(in1_5 + 7); 
			out6 += in0_7 * *(in1_6 + 7); 
			out7 += in0_7 * *(in1_7 + 7); 
			in1_0 += 8;
			in1_1 += 8;
			in1_2 += 8;
			in1_3 += 8;
			in1_4 += 8;
			in1_5 += 8;
			in1_6 += 8;
			in1_7 += 8;
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
			out2 += in0_0 * *(in1_2 + 0); 
			out3 += in0_0 * *(in1_3 + 0); 
			out4 += in0_0 * *(in1_4 + 0); 
			out5 += in0_0 * *(in1_5 + 0); 
			out6 += in0_0 * *(in1_6 + 0); 
			out7 += in0_0 * *(in1_7 + 0); 
			out0 += in0_1 * *(in1_0 + 1); 
			out1 += in0_1 * *(in1_1 + 1); 
			out2 += in0_1 * *(in1_2 + 1); 
			out3 += in0_1 * *(in1_3 + 1); 
			out4 += in0_1 * *(in1_4 + 1); 
			out5 += in0_1 * *(in1_5 + 1); 
			out6 += in0_1 * *(in1_6 + 1); 
			out7 += in0_1 * *(in1_7 + 1); 
			out0 += in0_2 * *(in1_0 + 2); 
			out1 += in0_2 * *(in1_1 + 2); 
			out2 += in0_2 * *(in1_2 + 2); 
			out3 += in0_2 * *(in1_3 + 2); 
			out4 += in0_2 * *(in1_4 + 2); 
			out5 += in0_2 * *(in1_5 + 2); 
			out6 += in0_2 * *(in1_6 + 2); 
			out7 += in0_2 * *(in1_7 + 2); 
			out0 += in0_3 * *(in1_0 + 3); 
			out1 += in0_3 * *(in1_1 + 3); 
			out2 += in0_3 * *(in1_2 + 3); 
			out3 += in0_3 * *(in1_3 + 3); 
			out4 += in0_3 * *(in1_4 + 3); 
			out5 += in0_3 * *(in1_5 + 3); 
			out6 += in0_3 * *(in1_6 + 3); 
			out7 += in0_3 * *(in1_7 + 3); 
			out0 += in0_4 * *(in1_0 + 4); 
			out1 += in0_4 * *(in1_1 + 4); 
			out2 += in0_4 * *(in1_2 + 4); 
			out3 += in0_4 * *(in1_3 + 4); 
			out4 += in0_4 * *(in1_4 + 4); 
			out5 += in0_4 * *(in1_5 + 4); 
			out6 += in0_4 * *(in1_6 + 4); 
			out7 += in0_4 * *(in1_7 + 4); 
			out0 += in0_5 * *(in1_0 + 5); 
			out1 += in0_5 * *(in1_1 + 5); 
			out2 += in0_5 * *(in1_2 + 5); 
			out3 += in0_5 * *(in1_3 + 5); 
			out4 += in0_5 * *(in1_4 + 5); 
			out5 += in0_5 * *(in1_5 + 5); 
			out6 += in0_5 * *(in1_6 + 5); 
			out7 += in0_5 * *(in1_7 + 5); 
			out0 += in0_6 * *(in1_0 + 6); 
			out1 += in0_6 * *(in1_1 + 6); 
			out2 += in0_6 * *(in1_2 + 6); 
			out3 += in0_6 * *(in1_3 + 6); 
			out4 += in0_6 * *(in1_4 + 6); 
			out5 += in0_6 * *(in1_5 + 6); 
			out6 += in0_6 * *(in1_6 + 6); 
			out7 += in0_6 * *(in1_7 + 6); 
			out0 += in0_7 * *(in1_0 + 7); 
			out1 += in0_7 * *(in1_1 + 7); 
			out2 += in0_7 * *(in1_2 + 7); 
			out3 += in0_7 * *(in1_3 + 7); 
			out4 += in0_7 * *(in1_4 + 7); 
			out5 += in0_7 * *(in1_5 + 7); 
			out6 += in0_7 * *(in1_6 + 7); 
			out7 += in0_7 * *(in1_7 + 7); 
			in1_0 += 8;
			in1_1 += 8;
			in1_2 += 8;
			in1_3 += 8;
			in1_4 += 8;
			in1_5 += 8;
			in1_6 += 8;
			in1_7 += 8;
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
			out2 += in0_0 * *(in1_2 + 0); 
			out3 += in0_0 * *(in1_3 + 0); 
			out4 += in0_0 * *(in1_4 + 0); 
			out5 += in0_0 * *(in1_5 + 0); 
			out6 += in0_0 * *(in1_6 + 0); 
			out7 += in0_0 * *(in1_7 + 0); 
			out0 += in0_1 * *(in1_0 + 1); 
			out1 += in0_1 * *(in1_1 + 1); 
			out2 += in0_1 * *(in1_2 + 1); 
			out3 += in0_1 * *(in1_3 + 1); 
			out4 += in0_1 * *(in1_4 + 1); 
			out5 += in0_1 * *(in1_5 + 1); 
			out6 += in0_1 * *(in1_6 + 1); 
			out7 += in0_1 * *(in1_7 + 1); 
			out0 += in0_2 * *(in1_0 + 2); 
			out1 += in0_2 * *(in1_1 + 2); 
			out2 += in0_2 * *(in1_2 + 2); 
			out3 += in0_2 * *(in1_3 + 2); 
			out4 += in0_2 * *(in1_4 + 2); 
			out5 += in0_2 * *(in1_5 + 2); 
			out6 += in0_2 * *(in1_6 + 2); 
			out7 += in0_2 * *(in1_7 + 2); 
			out0 += in0_3 * *(in1_0 + 3); 
			out1 += in0_3 * *(in1_1 + 3); 
			out2 += in0_3 * *(in1_2 + 3); 
			out3 += in0_3 * *(in1_3 + 3); 
			out4 += in0_3 * *(in1_4 + 3); 
			out5 += in0_3 * *(in1_5 + 3); 
			out6 += in0_3 * *(in1_6 + 3); 
			out7 += in0_3 * *(in1_7 + 3); 
			out0 += in0_4 * *(in1_0 + 4); 
			out1 += in0_4 * *(in1_1 + 4); 
			out2 += in0_4 * *(in1_2 + 4); 
			out3 += in0_4 * *(in1_3 + 4); 
			out4 += in0_4 * *(in1_4 + 4); 
			out5 += in0_4 * *(in1_5 + 4); 
			out6 += in0_4 * *(in1_6 + 4); 
			out7 += in0_4 * *(in1_7 + 4); 
			out0 += in0_5 * *(in1_0 + 5); 
			out1 += in0_5 * *(in1_1 + 5); 
			out2 += in0_5 * *(in1_2 + 5); 
			out3 += in0_5 * *(in1_3 + 5); 
			out4 += in0_5 * *(in1_4 + 5); 
			out5 += in0_5 * *(in1_5 + 5); 
			out6 += in0_5 * *(in1_6 + 5); 
			out7 += in0_5 * *(in1_7 + 5); 
			out0 += in0_6 * *(in1_0 + 6); 
			out1 += in0_6 * *(in1_1 + 6); 
			out2 += in0_6 * *(in1_2 + 6); 
			out3 += in0_6 * *(in1_3 + 6); 
			out4 += in0_6 * *(in1_4 + 6); 
			out5 += in0_6 * *(in1_5 + 6); 
			out6 += in0_6 * *(in1_6 + 6); 
			out7 += in0_6 * *(in1_7 + 6); 
			out0 += in0_7 * *(in1_0 + 7); 
			out1 += in0_7 * *(in1_1 + 7); 
			out2 += in0_7 * *(in1_2 + 7); 
			out3 += in0_7 * *(in1_3 + 7); 
			out4 += in0_7 * *(in1_4 + 7); 
			out5 += in0_7 * *(in1_5 + 7); 
			out6 += in0_7 * *(in1_6 + 7); 
			out7 += in0_7 * *(in1_7 + 7); 
			in1_0 += 8;
			in1_1 += 8;
			in1_2 += 8;
			in1_3 += 8;
			in1_4 += 8;
			in1_5 += 8;
			in1_6 += 8;
			in1_7 += 8;
		}
		*Out0 += out0;
		*Out1 += out1;
		*Out2 += out2;
		*Out3 += out3;
		*Out4 += out4;
		*Out5 += out5;
		*Out6 += out6;
		*Out7 += out7;
		Out0 += Outs1;
		Out1 += Outs1;
		Out2 += Outs1;
		Out3 += Outs1;
		Out4 += Outs1;
		Out5 += Outs1;
		Out6 += Outs1;
		Out7 += Outs1;
	}

	if (mod) {
		div = k - mod;
		mrdot_product_8x16(Out, _In0 + div, In1 + div, m, mod, Outs0, Outs1, In0s, In1s);
	}
}

//------------------------------------------------------------------------------
#endif
