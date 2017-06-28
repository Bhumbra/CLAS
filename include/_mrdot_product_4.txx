# ifndef _mrdot_product_4_txx
# define _mrdot_product_4_txx

//------------------------------------------------------------------------------
template <class T, class U>
static inline void mrdot_product_4x1 (T* Out, 
																			T* _In0, 
																			T* In1, 
																			volatile const U m, 
																			volatile const U k,
																			volatile const U Outs0,
																			volatile const U Outs1 = 1,
																			volatile const U In0s = 1,
																			volatile const U In1s = 1) { 
	register T out0_0; 
	register T out1_0; 
	register T out2_0;
	register T out3_0;
	T in0_0;
	register T in1_0_0, in1_0_1;
	register T in1_1_0, in1_1_1;
	register T in1_2_0, in1_2_1;
	register T in1_3_0, in1_3_1;
	register T *in0, *in1_0, *in1_1, *in1_2, *in1_3;
	T *Out0, *Out1, *Out2, *Out3; 
	T* In0;
	T *In1_0, *In1_1, *In1_2, *In1_3; 
	register U i, j;

	Out0 = Out + Outs0 * 0;
	Out1 = Out + Outs0 * 1;
	Out2 = Out + Outs0 * 2;
	Out3 = Out + Outs0 * 3;
	In0 = _In0;
	In1_0 = In1 + In1s * 0;
	In1_1 = In1 + In1s * 1;
	In1_2 = In1 + In1s * 2;
	In1_3 = In1 + In1s * 3;

	for (i = m; i; i--) {
		in0 = In0;
		In0 += In0s;
		in1_0 = In1_0;
		in1_1 = In1_1;
		in1_2 = In1_2;
		in1_3 = In1_3;
		out0_0 = 0.;
		out1_0 = 0.;
		out2_0 = 0.;
		out3_0 = 0.;
		for (j = k; j; j--) {
			in0_0 = *(in0 + 0);
			in1_0_0 = *(in1_0 + 0);
			in1_1_0 = *(in1_1 + 0);
			in1_2_0 = *(in1_2 + 0);
			in1_3_0 = *(in1_3 + 0);
			out0_0 += in0_0 * in1_0_0; 
			out1_0 += in0_0 * in1_1_0; 
			out2_0 += in0_0 * in1_2_0; 
			out3_0 += in0_0 * in1_3_0; 
			in0 ++;
			in1_0 ++;
			in1_1 ++;
			in1_2 ++;
			in1_3 ++;
		}
		*Out0 += out0_0;
		*Out1 += out1_0;
		*Out2 += out2_0;
		*Out3 += out3_0;
		Out0 += Outs1;
		Out1 += Outs1;
		Out2 += Outs1;
		Out3 += Outs1;
	}
}

//------------------------------------------------------------------------------
template <class T, class U>
static inline void mrdot_product_4x2 (T* Out, 
																			T* _In0, 
																			T* In1, 
																			volatile const U m, 
																			volatile const U k,
																			volatile const U Outs0,
																			volatile const U Outs1 = 1,
																			volatile const U In0s = 1,
																			volatile const U In1s = 1) { 

	register T out0_0, out0_1; 
	register T out1_0, out1_1; 
	register T out2_0, out2_1; 
	register T out3_0, out3_1;
	T in0_0, in0_1;
	register T in1_0_0, in1_0_1;
	register T in1_1_0, in1_1_1;
	register T in1_2_0, in1_2_1;
	register T in1_3_0, in1_3_1;
	register T *in0, *in1_0, *in1_1, *in1_2, *in1_3;
	T *Out0, *Out1, *Out2, *Out3; 
	T* In0;
	T *In1_0, *In1_1, *In1_2, *In1_3; 
	volatile U div, mod;
	register U i, j;

	div = k >> 1;
	mod = k & 1;

	Out0 = Out + Outs0 * 0;
	Out1 = Out + Outs0 * 1;
	Out2 = Out + Outs0 * 2;
	Out3 = Out + Outs0 * 3;
	In0 = _In0;
	In1_0 = In1 + In1s * 0;
	In1_1 = In1 + In1s * 1;
	In1_2 = In1 + In1s * 2;
	In1_3 = In1 + In1s * 3;

	for (i = m; i; i--) {
		in0 = In0;
		In0 += In0s;
		in1_0 = In1_0;
		in1_1 = In1_1;
		in1_2 = In1_2;
		in1_3 = In1_3;
		out0_0 = 0.;
		out0_1 = 0.;
		out1_0 = 0.;
		out1_1 = 0.;
		out2_0 = 0.;
		out2_1 = 0.;
		out3_0 = 0.;
		out3_1 = 0.;
		for (j = div; j; j--) {
			in0_0 = *(in0 + 0);
			in0_1 = *(in0 + 1);
			in1_0_0 = *(in1_0 + 0);
			in1_0_1 = *(in1_0 + 1);
			in1_1_0 = *(in1_1 + 0);
			in1_1_1 = *(in1_1 + 1);
			in1_2_0 = *(in1_2 + 0);
			in1_2_1 = *(in1_2 + 1);
			in1_3_0 = *(in1_3 + 0);
			in1_3_1 = *(in1_3 + 1);
			out0_0 += in0_0 * in1_0_0; 
			out0_1 += in0_1 * in1_0_1; 
			out1_0 += in0_0 * in1_1_0; 
			out1_1 += in0_1 * in1_1_1; 
			out2_0 += in0_0 * in1_2_0; 
			out2_1 += in0_1 * in1_2_1; 
			out3_0 += in0_0 * in1_3_0; 
			out3_1 += in0_1 * in1_3_1; 
			in0 += 2;
			in1_0 += 2;
			in1_1 += 2;
			in1_2 += 2;
			in1_3 += 2;
		}
		*Out0 += out0_0 + out0_1;
		*Out1 += out1_0 + out1_1;
		*Out2 += out2_0 + out2_1;
		*Out3 += out3_0 + out3_1;
		Out0 += Outs1;
		Out1 += Outs1;
		Out2 += Outs1;
		Out3 += Outs1;
	}

	if (mod) {
		div = k - mod;
		mrdot_product_4x1(Out, _In0 + div, In1 + div, m, mod, Outs0, Outs1, In0s, In1s);
	}
}

//------------------------------------------------------------------------------
template <class T, class U>
static inline void mrdot_product_4x4 (T* Out, 
																			T* _In0, 
																			T* In1, 
																			volatile const U m, 
																			volatile const U k,
																			volatile const U Outs0,
																			volatile const U Outs1 = 1,
																			volatile const U In0s = 1,
																			volatile const U In1s = 1) { 

	register T out0_0, out0_1, out0_2, out0_3; 
	register T out1_0, out1_1, out1_2, out1_3;
	register T out2_0, out2_1, out2_2, out2_3; 
	register T out3_0, out3_1, out3_2, out3_3;
	T in0_0, in0_1, in0_2, in0_3;
	register T in1_0_0, in1_0_1, in1_0_2, in1_0_3;
	register T in1_1_0, in1_1_1, in1_1_2, in1_1_3;
	register T in1_2_0, in1_2_1, in1_2_2, in1_2_3;
	register T in1_3_0, in1_3_1, in1_3_2, in1_3_3;
	register T *in0, *in1_0, *in1_1, *in1_2, *in1_3;
	T *Out0, *Out1, *Out2, *Out3; 
	T* In0;
	T *In1_0, *In1_1, *In1_2, *In1_3; 
	volatile U div, mod;
	register U i, j;

	div = k >> 2;
	mod = k & 3;

	Out0 = Out + Outs0 * 0;
	Out1 = Out + Outs0 * 1;
	Out2 = Out + Outs0 * 2;
	Out3 = Out + Outs0 * 3;
	In0 = _In0;
	In1_0 = In1 + In1s * 0;
	In1_1 = In1 + In1s * 1;
	In1_2 = In1 + In1s * 2;
	In1_3 = In1 + In1s * 3;

	for (i = m; i; i--) {
		in0 = In0;
		In0 += In0s;
		in1_0 = In1_0;
		in1_1 = In1_1;
		in1_2 = In1_2;
		in1_3 = In1_3;
		out0_0 = 0.;
		out0_1 = 0.;
		out0_2 = 0.;
		out0_3 = 0.;
		out1_0 = 0.;
		out1_1 = 0.;
		out1_2 = 0.;
		out1_3 = 0.;
		out2_0 = 0.;
		out2_1 = 0.;
		out2_2 = 0.;
		out2_3 = 0.;
		out3_0 = 0.;
		out3_1 = 0.;
		out3_2 = 0.;
		out3_3 = 0.;
		for (j = div; j; j--) {
			in0_0 = *(in0 + 0);
			in0_1 = *(in0 + 1);
			in0_2 = *(in0 + 2);
			in0_3 = *(in0 + 3);
			in1_0_0 = *(in1_0 + 0);
			in1_0_1 = *(in1_0 + 1);
			in1_0_2 = *(in1_0 + 2);
			in1_0_3 = *(in1_0 + 3);
			in1_1_0 = *(in1_1 + 0);
			in1_1_1 = *(in1_1 + 1);
			in1_1_2 = *(in1_1 + 2);
			in1_1_3 = *(in1_1 + 3);
			in1_2_0 = *(in1_2 + 0);
			in1_2_1 = *(in1_2 + 1);
			in1_2_2 = *(in1_2 + 2);
			in1_2_3 = *(in1_2 + 3);
			in1_3_0 = *(in1_3 + 0);
			in1_3_1 = *(in1_3 + 1);
			in1_3_2 = *(in1_3 + 2);
			in1_3_3 = *(in1_3 + 3);
			out0_0 += in0_0 * in1_0_0; 
			out0_1 += in0_1 * in1_0_1; 
			out0_2 += in0_2 * in1_0_2; 
			out0_3 += in0_3 * in1_0_3; 
			out1_0 += in0_0 * in1_1_0; 
			out1_1 += in0_1 * in1_1_1; 
			out1_2 += in0_2 * in1_1_2; 
			out1_3 += in0_3 * in1_1_3; 
			out2_0 += in0_0 * in1_2_0; 
			out2_1 += in0_1 * in1_2_1; 
			out2_2 += in0_2 * in1_2_2; 
			out2_3 += in0_3 * in1_2_3; 
			out3_0 += in0_0 * in1_3_0; 
			out3_1 += in0_1 * in1_3_1; 
			out3_2 += in0_2 * in1_3_2; 
			out3_3 += in0_3 * in1_3_3; 
			in0 += 4;
			in1_0 += 4;
			in1_1 += 4;
			in1_2 += 4;
			in1_3 += 4;
		}
		*Out0 += (out0_0 + out0_2) + (out0_1 + out0_3);
		*Out1 += (out1_0 + out1_2) + (out1_1 + out1_3);
		*Out2 += (out2_0 + out2_2) + (out2_1 + out2_3);
		*Out3 += (out3_0 + out3_2) + (out3_1 + out3_3);
		Out0 += Outs1;
		Out1 += Outs1;
		Out2 += Outs1;
		Out3 += Outs1;
	}

	if (mod) {
		div = k - mod;
		mrdot_product_4x2 (Out, _In0 + div, In1 + div, m, mod, Outs0, Outs1, In0s, In1s);
	}
}

//------------------------------------------------------------------------------
template <class T, class U>
static inline void mrdot_product_4x8 (T* Out, 
																			T* _In0, 
																			T* In1, 
																			volatile const U m, 
																			volatile const U k,
																			volatile const U Outs0,
																			volatile const U Outs1 = 1,
																			volatile const U In0s = 1,
																			volatile const U In1s = 1) { 

	register T out0_0, out0_1, out0_2, out0_3; 
	register T out1_0, out1_1, out1_2, out1_3;
	register T out2_0, out2_1, out2_2, out2_3; 
	register T out3_0, out3_1, out3_2, out3_3;
	T in0_0, in0_1, in0_2, in0_3;
	register T in1_0_0, in1_0_1, in1_0_2, in1_0_3;
	register T in1_1_0, in1_1_1, in1_1_2, in1_1_3;
	register T in1_2_0, in1_2_1, in1_2_2, in1_2_3;
	register T in1_3_0, in1_3_1, in1_3_2, in1_3_3;
	register T *in0, *in1_0, *in1_1, *in1_2, *in1_3;
	T *Out0, *Out1, *Out2, *Out3; 
	T* In0;
	T *In1_0, *In1_1, *In1_2, *In1_3; 
	volatile U div, mod;
	register U i, j;

	div = k >> 3;
	mod = k & 7;

	Out0 = Out + Outs0 * 0;
	Out1 = Out + Outs0 * 1;
	Out2 = Out + Outs0 * 2;
	Out3 = Out + Outs0 * 3;
	In0 = _In0;
	In1_0 = In1 + In1s * 0;
	In1_1 = In1 + In1s * 1;
	In1_2 = In1 + In1s * 2;
	In1_3 = In1 + In1s * 3;

	for (i = m; i; i--) {
		in0 = In0;
		In0 += In0s;
		in1_0 = In1_0;
		in1_1 = In1_1;
		in1_2 = In1_2;
		in1_3 = In1_3;
		out0_0 = 0.;
		out0_1 = 0.;
		out0_2 = 0.;
		out0_3 = 0.;
		out1_0 = 0.;
		out1_1 = 0.;
		out1_2 = 0.;
		out1_3 = 0.;
		out2_0 = 0.;
		out2_1 = 0.;
		out2_2 = 0.;
		out2_3 = 0.;
		out3_0 = 0.;
		out3_1 = 0.;
		out3_2 = 0.;
		out3_3 = 0.;
		for (j = div; j; j--) {
			in0_0 = *(in0 + 0);
			in0_1 = *(in0 + 1);
			in0_2 = *(in0 + 2);
			in0_3 = *(in0 + 3);
			in1_0_0 = *(in1_0 + 0);
			in1_0_1 = *(in1_0 + 1);
			in1_0_2 = *(in1_0 + 2);
			in1_0_3 = *(in1_0 + 3);
			in1_1_0 = *(in1_1 + 0);
			in1_1_1 = *(in1_1 + 1);
			in1_1_2 = *(in1_1 + 2);
			in1_1_3 = *(in1_1 + 3);
			in1_2_0 = *(in1_2 + 0);
			in1_2_1 = *(in1_2 + 1);
			in1_2_2 = *(in1_2 + 2);
			in1_2_3 = *(in1_2 + 3);
			in1_3_0 = *(in1_3 + 0);
			in1_3_1 = *(in1_3 + 1);
			in1_3_2 = *(in1_3 + 2);
			in1_3_3 = *(in1_3 + 3);
			out0_0 += in0_0 * in1_0_0; 
			out0_1 += in0_1 * in1_0_1; 
			out0_2 += in0_2 * in1_0_2; 
			out0_3 += in0_3 * in1_0_3; 
			out1_0 += in0_0 * in1_1_0; 
			out1_1 += in0_1 * in1_1_1; 
			out1_2 += in0_2 * in1_1_2; 
			out1_3 += in0_3 * in1_1_3; 
			out2_0 += in0_0 * in1_2_0; 
			out2_1 += in0_1 * in1_2_1; 
			out2_2 += in0_2 * in1_2_2; 
			out2_3 += in0_3 * in1_2_3; 
			out3_0 += in0_0 * in1_3_0; 
			out3_1 += in0_1 * in1_3_1; 
			out3_2 += in0_2 * in1_3_2; 
			out3_3 += in0_3 * in1_3_3; 
			in0 += 4;
			in1_0 += 4;
			in1_1 += 4;
			in1_2 += 4;
			in1_3 += 4;
			in0_0 = *(in0 + 0);
			in0_1 = *(in0 + 1);
			in0_2 = *(in0 + 2);
			in0_3 = *(in0 + 3);
			in1_0_0 = *(in1_0 + 0);
			in1_0_1 = *(in1_0 + 1);
			in1_0_2 = *(in1_0 + 2);
			in1_0_3 = *(in1_0 + 3);
			in1_1_0 = *(in1_1 + 0);
			in1_1_1 = *(in1_1 + 1);
			in1_1_2 = *(in1_1 + 2);
			in1_1_3 = *(in1_1 + 3);
			in1_2_0 = *(in1_2 + 0);
			in1_2_1 = *(in1_2 + 1);
			in1_2_2 = *(in1_2 + 2);
			in1_2_3 = *(in1_2 + 3);
			in1_3_0 = *(in1_3 + 0);
			in1_3_1 = *(in1_3 + 1);
			in1_3_2 = *(in1_3 + 2);
			in1_3_3 = *(in1_3 + 3);
			out0_0 += in0_0 * in1_0_0; 
			out0_1 += in0_1 * in1_0_1; 
			out0_2 += in0_2 * in1_0_2; 
			out0_3 += in0_3 * in1_0_3; 
			out1_0 += in0_0 * in1_1_0; 
			out1_1 += in0_1 * in1_1_1; 
			out1_2 += in0_2 * in1_1_2; 
			out1_3 += in0_3 * in1_1_3; 
			out2_0 += in0_0 * in1_2_0; 
			out2_1 += in0_1 * in1_2_1; 
			out2_2 += in0_2 * in1_2_2; 
			out2_3 += in0_3 * in1_2_3; 
			out3_0 += in0_0 * in1_3_0; 
			out3_1 += in0_1 * in1_3_1; 
			out3_2 += in0_2 * in1_3_2; 
			out3_3 += in0_3 * in1_3_3; 
			in0 += 4;
			in1_0 += 4;
			in1_1 += 4;
			in1_2 += 4;
			in1_3 += 4;
		}
		*Out0 += (out0_0 + out0_2) + (out0_1 + out0_3);
		*Out1 += (out1_0 + out1_2) + (out1_1 + out1_3);
		*Out2 += (out2_0 + out2_2) + (out2_1 + out2_3);
		*Out3 += (out3_0 + out3_2) + (out3_1 + out3_3);
		Out0 += Outs1;
		Out1 += Outs1;
		Out2 += Outs1;
		Out3 += Outs1;
	}

	if (mod) {
		div = k - mod;
		mrdot_product_4x4 (Out, _In0 + div, In1 + div, m, mod, Outs0, Outs1, In0s, In1s);
	}
}

//------------------------------------------------------------------------------
template <class T, class U>
static inline void mrdot_product_4x16(T* Out, 
																			T* _In0, 
																			T* In1, 
																			volatile const U m, 
																			volatile const U k,
																			volatile const U Outs0,
																			volatile const U Outs1 = 1,
																			volatile const U In0s = 1,
																			volatile const U In1s = 1) { 

	register T out0_0, out0_1, out0_2, out0_3; 
	register T out1_0, out1_1, out1_2, out1_3;
	register T out2_0, out2_1, out2_2, out2_3; 
	register T out3_0, out3_1, out3_2, out3_3;
	T in0_0, in0_1, in0_2, in0_3;
	register T in1_0_0, in1_0_1, in1_0_2, in1_0_3;
	register T in1_1_0, in1_1_1, in1_1_2, in1_1_3;
	register T in1_2_0, in1_2_1, in1_2_2, in1_2_3;
	register T in1_3_0, in1_3_1, in1_3_2, in1_3_3;
	register T *in0, *in1_0, *in1_1, *in1_2, *in1_3;
	T *Out0, *Out1, *Out2, *Out3; 
	T* In0;
	T *In1_0, *In1_1, *In1_2, *In1_3; 
	volatile U div, mod;
	register U i, j;

	div = k >> 4;
	mod = k & 15;

	Out0 = Out + Outs0 * 0;
	Out1 = Out + Outs0 * 1;
	Out2 = Out + Outs0 * 2;
	Out3 = Out + Outs0 * 3;
	In0 = _In0;
	In1_0 = In1 + In1s * 0;
	In1_1 = In1 + In1s * 1;
	In1_2 = In1 + In1s * 2;
	In1_3 = In1 + In1s * 3;

	for (i = m; i; i--) {
		in0 = In0;
		In0 += In0s;
		in1_0 = In1_0;
		in1_1 = In1_1;
		in1_2 = In1_2;
		in1_3 = In1_3;
		out0_0 = 0.;
		out0_1 = 0.;
		out0_2 = 0.;
		out0_3 = 0.;
		out1_0 = 0.;
		out1_1 = 0.;
		out1_2 = 0.;
		out1_3 = 0.;
		out2_0 = 0.;
		out2_1 = 0.;
		out2_2 = 0.;
		out2_3 = 0.;
		out3_0 = 0.;
		out3_1 = 0.;
		out3_2 = 0.;
		out3_3 = 0.;
		for (j = div; j; j--) {
			in0_0 = *(in0 + 0);
			in0_1 = *(in0 + 1);
			in0_2 = *(in0 + 2);
			in0_3 = *(in0 + 3);
			in1_0_0 = *(in1_0 + 0);
			in1_0_1 = *(in1_0 + 1);
			in1_0_2 = *(in1_0 + 2);
			in1_0_3 = *(in1_0 + 3);
			in1_1_0 = *(in1_1 + 0);
			in1_1_1 = *(in1_1 + 1);
			in1_1_2 = *(in1_1 + 2);
			in1_1_3 = *(in1_1 + 3);
			in1_2_0 = *(in1_2 + 0);
			in1_2_1 = *(in1_2 + 1);
			in1_2_2 = *(in1_2 + 2);
			in1_2_3 = *(in1_2 + 3);
			in1_3_0 = *(in1_3 + 0);
			in1_3_1 = *(in1_3 + 1);
			in1_3_2 = *(in1_3 + 2);
			in1_3_3 = *(in1_3 + 3);
			out0_0 += in0_0 * in1_0_0; 
			out0_1 += in0_1 * in1_0_1; 
			out0_2 += in0_2 * in1_0_2; 
			out0_3 += in0_3 * in1_0_3; 
			out1_0 += in0_0 * in1_1_0; 
			out1_1 += in0_1 * in1_1_1; 
			out1_2 += in0_2 * in1_1_2; 
			out1_3 += in0_3 * in1_1_3; 
			out2_0 += in0_0 * in1_2_0; 
			out2_1 += in0_1 * in1_2_1; 
			out2_2 += in0_2 * in1_2_2; 
			out2_3 += in0_3 * in1_2_3; 
			out3_0 += in0_0 * in1_3_0; 
			out3_1 += in0_1 * in1_3_1; 
			out3_2 += in0_2 * in1_3_2; 
			out3_3 += in0_3 * in1_3_3; 
			in0 += 4;
			in1_0 += 4;
			in1_1 += 4;
			in1_2 += 4;
			in1_3 += 4;
			in0_0 = *(in0 + 0);
			in0_1 = *(in0 + 1);
			in0_2 = *(in0 + 2);
			in0_3 = *(in0 + 3);
			in1_0_0 = *(in1_0 + 0);
			in1_0_1 = *(in1_0 + 1);
			in1_0_2 = *(in1_0 + 2);
			in1_0_3 = *(in1_0 + 3);
			in1_1_0 = *(in1_1 + 0);
			in1_1_1 = *(in1_1 + 1);
			in1_1_2 = *(in1_1 + 2);
			in1_1_3 = *(in1_1 + 3);
			in1_2_0 = *(in1_2 + 0);
			in1_2_1 = *(in1_2 + 1);
			in1_2_2 = *(in1_2 + 2);
			in1_2_3 = *(in1_2 + 3);
			in1_3_0 = *(in1_3 + 0);
			in1_3_1 = *(in1_3 + 1);
			in1_3_2 = *(in1_3 + 2);
			in1_3_3 = *(in1_3 + 3);
			out0_0 += in0_0 * in1_0_0; 
			out0_1 += in0_1 * in1_0_1; 
			out0_2 += in0_2 * in1_0_2; 
			out0_3 += in0_3 * in1_0_3; 
			out1_0 += in0_0 * in1_1_0; 
			out1_1 += in0_1 * in1_1_1; 
			out1_2 += in0_2 * in1_1_2; 
			out1_3 += in0_3 * in1_1_3; 
			out2_0 += in0_0 * in1_2_0; 
			out2_1 += in0_1 * in1_2_1; 
			out2_2 += in0_2 * in1_2_2; 
			out2_3 += in0_3 * in1_2_3; 
			out3_0 += in0_0 * in1_3_0; 
			out3_1 += in0_1 * in1_3_1; 
			out3_2 += in0_2 * in1_3_2; 
			out3_3 += in0_3 * in1_3_3; 
			in0 += 4;
			in1_0 += 4;
			in1_1 += 4;
			in1_2 += 4;
			in1_3 += 4;
			in0_0 = *(in0 + 0);
			in0_1 = *(in0 + 1);
			in0_2 = *(in0 + 2);
			in0_3 = *(in0 + 3);
			in1_0_0 = *(in1_0 + 0);
			in1_0_1 = *(in1_0 + 1);
			in1_0_2 = *(in1_0 + 2);
			in1_0_3 = *(in1_0 + 3);
			in1_1_0 = *(in1_1 + 0);
			in1_1_1 = *(in1_1 + 1);
			in1_1_2 = *(in1_1 + 2);
			in1_1_3 = *(in1_1 + 3);
			in1_2_0 = *(in1_2 + 0);
			in1_2_1 = *(in1_2 + 1);
			in1_2_2 = *(in1_2 + 2);
			in1_2_3 = *(in1_2 + 3);
			in1_3_0 = *(in1_3 + 0);
			in1_3_1 = *(in1_3 + 1);
			in1_3_2 = *(in1_3 + 2);
			in1_3_3 = *(in1_3 + 3);
			out0_0 += in0_0 * in1_0_0; 
			out0_1 += in0_1 * in1_0_1; 
			out0_2 += in0_2 * in1_0_2; 
			out0_3 += in0_3 * in1_0_3; 
			out1_0 += in0_0 * in1_1_0; 
			out1_1 += in0_1 * in1_1_1; 
			out1_2 += in0_2 * in1_1_2; 
			out1_3 += in0_3 * in1_1_3; 
			out2_0 += in0_0 * in1_2_0; 
			out2_1 += in0_1 * in1_2_1; 
			out2_2 += in0_2 * in1_2_2; 
			out2_3 += in0_3 * in1_2_3; 
			out3_0 += in0_0 * in1_3_0; 
			out3_1 += in0_1 * in1_3_1; 
			out3_2 += in0_2 * in1_3_2; 
			out3_3 += in0_3 * in1_3_3; 
			in0 += 4;
			in1_0 += 4;
			in1_1 += 4;
			in1_2 += 4;
			in1_3 += 4;
			in0_0 = *(in0 + 0);
			in0_1 = *(in0 + 1);
			in0_2 = *(in0 + 2);
			in0_3 = *(in0 + 3);
			in1_0_0 = *(in1_0 + 0);
			in1_0_1 = *(in1_0 + 1);
			in1_0_2 = *(in1_0 + 2);
			in1_0_3 = *(in1_0 + 3);
			in1_1_0 = *(in1_1 + 0);
			in1_1_1 = *(in1_1 + 1);
			in1_1_2 = *(in1_1 + 2);
			in1_1_3 = *(in1_1 + 3);
			in1_2_0 = *(in1_2 + 0);
			in1_2_1 = *(in1_2 + 1);
			in1_2_2 = *(in1_2 + 2);
			in1_2_3 = *(in1_2 + 3);
			in1_3_0 = *(in1_3 + 0);
			in1_3_1 = *(in1_3 + 1);
			in1_3_2 = *(in1_3 + 2);
			in1_3_3 = *(in1_3 + 3);
			out0_0 += in0_0 * in1_0_0; 
			out0_1 += in0_1 * in1_0_1; 
			out0_2 += in0_2 * in1_0_2; 
			out0_3 += in0_3 * in1_0_3; 
			out1_0 += in0_0 * in1_1_0; 
			out1_1 += in0_1 * in1_1_1; 
			out1_2 += in0_2 * in1_1_2; 
			out1_3 += in0_3 * in1_1_3; 
			out2_0 += in0_0 * in1_2_0; 
			out2_1 += in0_1 * in1_2_1; 
			out2_2 += in0_2 * in1_2_2; 
			out2_3 += in0_3 * in1_2_3; 
			out3_0 += in0_0 * in1_3_0; 
			out3_1 += in0_1 * in1_3_1; 
			out3_2 += in0_2 * in1_3_2; 
			out3_3 += in0_3 * in1_3_3; 
			in0 += 4;
			in1_0 += 4;
			in1_1 += 4;
			in1_2 += 4;
			in1_3 += 4;
		}
		*Out0 += (out0_0 + out0_2) + (out0_1 + out0_3);
		*Out1 += (out1_0 + out1_2) + (out1_1 + out1_3);
		*Out2 += (out2_0 + out2_2) + (out2_1 + out2_3);
		*Out3 += (out3_0 + out3_2) + (out3_1 + out3_3);
		Out0 += Outs1;
		Out1 += Outs1;
		Out2 += Outs1;
		Out3 += Outs1;
	}

	if (mod) {
		div = k - mod;
		mrdot_product_4x8 (Out, _In0 + div, In1 + div, m, mod, Outs0, Outs1, In0s, In1s);
	}
}

//------------------------------------------------------------------------------
template <class T, class U>
static inline void mrdot_product_4x32(T* Out, 
																			T* _In0, 
																			T* In1, 
																			volatile const U m, 
																			volatile const U k,
																			volatile const U Outs0,
																			volatile const U Outs1 = 1,
																			volatile const U In0s = 1,
																			volatile const U In1s = 1) { 

	register T out0_0, out0_1, out0_2, out0_3; 
	register T out1_0, out1_1, out1_2, out1_3;
	register T out2_0, out2_1, out2_2, out2_3; 
	register T out3_0, out3_1, out3_2, out3_3;
	T in0_0, in0_1, in0_2, in0_3;
	register T in1_0_0, in1_0_1, in1_0_2, in1_0_3;
	register T in1_1_0, in1_1_1, in1_1_2, in1_1_3;
	register T in1_2_0, in1_2_1, in1_2_2, in1_2_3;
	register T in1_3_0, in1_3_1, in1_3_2, in1_3_3;
	register T *in0, *in1_0, *in1_1, *in1_2, *in1_3;
	T *Out0, *Out1, *Out2, *Out3; 
	T* In0;
	T *In1_0, *In1_1, *In1_2, *In1_3; 
	volatile U div, mod;
	register U i, j;

	div = k >> 5;
	mod = k & 31;

	Out0 = Out + Outs0 * 0;
	Out1 = Out + Outs0 * 1;
	Out2 = Out + Outs0 * 2;
	Out3 = Out + Outs0 * 3;
	In0 = _In0;
	In1_0 = In1 + In1s * 0;
	In1_1 = In1 + In1s * 1;
	In1_2 = In1 + In1s * 2;
	In1_3 = In1 + In1s * 3;

	for (i = m; i; i--) {
		in0 = In0;
		In0 += In0s;
		in1_0 = In1_0;
		in1_1 = In1_1;
		in1_2 = In1_2;
		in1_3 = In1_3;
		out0_0 = 0.;
		out0_1 = 0.;
		out0_2 = 0.;
		out0_3 = 0.;
		out1_0 = 0.;
		out1_1 = 0.;
		out1_2 = 0.;
		out1_3 = 0.;
		out2_0 = 0.;
		out2_1 = 0.;
		out2_2 = 0.;
		out2_3 = 0.;
		out3_0 = 0.;
		out3_1 = 0.;
		out3_2 = 0.;
		out3_3 = 0.;
		for (j = div; j; j--) {
			in0_0 = *(in0 + 0);
			in0_1 = *(in0 + 1);
			in0_2 = *(in0 + 2);
			in0_3 = *(in0 + 3);
			in1_0_0 = *(in1_0 + 0);
			in1_0_1 = *(in1_0 + 1);
			in1_0_2 = *(in1_0 + 2);
			in1_0_3 = *(in1_0 + 3);
			in1_1_0 = *(in1_1 + 0);
			in1_1_1 = *(in1_1 + 1);
			in1_1_2 = *(in1_1 + 2);
			in1_1_3 = *(in1_1 + 3);
			in1_2_0 = *(in1_2 + 0);
			in1_2_1 = *(in1_2 + 1);
			in1_2_2 = *(in1_2 + 2);
			in1_2_3 = *(in1_2 + 3);
			in1_3_0 = *(in1_3 + 0);
			in1_3_1 = *(in1_3 + 1);
			in1_3_2 = *(in1_3 + 2);
			in1_3_3 = *(in1_3 + 3);
			out0_0 += in0_0 * in1_0_0; 
			out0_1 += in0_1 * in1_0_1; 
			out0_2 += in0_2 * in1_0_2; 
			out0_3 += in0_3 * in1_0_3; 
			out1_0 += in0_0 * in1_1_0; 
			out1_1 += in0_1 * in1_1_1; 
			out1_2 += in0_2 * in1_1_2; 
			out1_3 += in0_3 * in1_1_3; 
			out2_0 += in0_0 * in1_2_0; 
			out2_1 += in0_1 * in1_2_1; 
			out2_2 += in0_2 * in1_2_2; 
			out2_3 += in0_3 * in1_2_3; 
			out3_0 += in0_0 * in1_3_0; 
			out3_1 += in0_1 * in1_3_1; 
			out3_2 += in0_2 * in1_3_2; 
			out3_3 += in0_3 * in1_3_3; 
			in0 += 4;
			in1_0 += 4;
			in1_1 += 4;
			in1_2 += 4;
			in1_3 += 4;
			in0_0 = *(in0 + 0);
			in0_1 = *(in0 + 1);
			in0_2 = *(in0 + 2);
			in0_3 = *(in0 + 3);
			in1_0_0 = *(in1_0 + 0);
			in1_0_1 = *(in1_0 + 1);
			in1_0_2 = *(in1_0 + 2);
			in1_0_3 = *(in1_0 + 3);
			in1_1_0 = *(in1_1 + 0);
			in1_1_1 = *(in1_1 + 1);
			in1_1_2 = *(in1_1 + 2);
			in1_1_3 = *(in1_1 + 3);
			in1_2_0 = *(in1_2 + 0);
			in1_2_1 = *(in1_2 + 1);
			in1_2_2 = *(in1_2 + 2);
			in1_2_3 = *(in1_2 + 3);
			in1_3_0 = *(in1_3 + 0);
			in1_3_1 = *(in1_3 + 1);
			in1_3_2 = *(in1_3 + 2);
			in1_3_3 = *(in1_3 + 3);
			out0_0 += in0_0 * in1_0_0; 
			out0_1 += in0_1 * in1_0_1; 
			out0_2 += in0_2 * in1_0_2; 
			out0_3 += in0_3 * in1_0_3; 
			out1_0 += in0_0 * in1_1_0; 
			out1_1 += in0_1 * in1_1_1; 
			out1_2 += in0_2 * in1_1_2; 
			out1_3 += in0_3 * in1_1_3; 
			out2_0 += in0_0 * in1_2_0; 
			out2_1 += in0_1 * in1_2_1; 
			out2_2 += in0_2 * in1_2_2; 
			out2_3 += in0_3 * in1_2_3; 
			out3_0 += in0_0 * in1_3_0; 
			out3_1 += in0_1 * in1_3_1; 
			out3_2 += in0_2 * in1_3_2; 
			out3_3 += in0_3 * in1_3_3; 
			in0 += 4;
			in1_0 += 4;
			in1_1 += 4;
			in1_2 += 4;
			in1_3 += 4;
			in0_0 = *(in0 + 0);
			in0_1 = *(in0 + 1);
			in0_2 = *(in0 + 2);
			in0_3 = *(in0 + 3);
			in1_0_0 = *(in1_0 + 0);
			in1_0_1 = *(in1_0 + 1);
			in1_0_2 = *(in1_0 + 2);
			in1_0_3 = *(in1_0 + 3);
			in1_1_0 = *(in1_1 + 0);
			in1_1_1 = *(in1_1 + 1);
			in1_1_2 = *(in1_1 + 2);
			in1_1_3 = *(in1_1 + 3);
			in1_2_0 = *(in1_2 + 0);
			in1_2_1 = *(in1_2 + 1);
			in1_2_2 = *(in1_2 + 2);
			in1_2_3 = *(in1_2 + 3);
			in1_3_0 = *(in1_3 + 0);
			in1_3_1 = *(in1_3 + 1);
			in1_3_2 = *(in1_3 + 2);
			in1_3_3 = *(in1_3 + 3);
			out0_0 += in0_0 * in1_0_0; 
			out0_1 += in0_1 * in1_0_1; 
			out0_2 += in0_2 * in1_0_2; 
			out0_3 += in0_3 * in1_0_3; 
			out1_0 += in0_0 * in1_1_0; 
			out1_1 += in0_1 * in1_1_1; 
			out1_2 += in0_2 * in1_1_2; 
			out1_3 += in0_3 * in1_1_3; 
			out2_0 += in0_0 * in1_2_0; 
			out2_1 += in0_1 * in1_2_1; 
			out2_2 += in0_2 * in1_2_2; 
			out2_3 += in0_3 * in1_2_3; 
			out3_0 += in0_0 * in1_3_0; 
			out3_1 += in0_1 * in1_3_1; 
			out3_2 += in0_2 * in1_3_2; 
			out3_3 += in0_3 * in1_3_3; 
			in0 += 4;
			in1_0 += 4;
			in1_1 += 4;
			in1_2 += 4;
			in1_3 += 4;
			in0_0 = *(in0 + 0);
			in0_1 = *(in0 + 1);
			in0_2 = *(in0 + 2);
			in0_3 = *(in0 + 3);
			in1_0_0 = *(in1_0 + 0);
			in1_0_1 = *(in1_0 + 1);
			in1_0_2 = *(in1_0 + 2);
			in1_0_3 = *(in1_0 + 3);
			in1_1_0 = *(in1_1 + 0);
			in1_1_1 = *(in1_1 + 1);
			in1_1_2 = *(in1_1 + 2);
			in1_1_3 = *(in1_1 + 3);
			in1_2_0 = *(in1_2 + 0);
			in1_2_1 = *(in1_2 + 1);
			in1_2_2 = *(in1_2 + 2);
			in1_2_3 = *(in1_2 + 3);
			in1_3_0 = *(in1_3 + 0);
			in1_3_1 = *(in1_3 + 1);
			in1_3_2 = *(in1_3 + 2);
			in1_3_3 = *(in1_3 + 3);
			out0_0 += in0_0 * in1_0_0; 
			out0_1 += in0_1 * in1_0_1; 
			out0_2 += in0_2 * in1_0_2; 
			out0_3 += in0_3 * in1_0_3; 
			out1_0 += in0_0 * in1_1_0; 
			out1_1 += in0_1 * in1_1_1; 
			out1_2 += in0_2 * in1_1_2; 
			out1_3 += in0_3 * in1_1_3; 
			out2_0 += in0_0 * in1_2_0; 
			out2_1 += in0_1 * in1_2_1; 
			out2_2 += in0_2 * in1_2_2; 
			out2_3 += in0_3 * in1_2_3; 
			out3_0 += in0_0 * in1_3_0; 
			out3_1 += in0_1 * in1_3_1; 
			out3_2 += in0_2 * in1_3_2; 
			out3_3 += in0_3 * in1_3_3; 
			in0 += 4;
			in1_0 += 4;
			in1_1 += 4;
			in1_2 += 4;
			in1_3 += 4;
			in0_0 = *(in0 + 0);
			in0_1 = *(in0 + 1);
			in0_2 = *(in0 + 2);
			in0_3 = *(in0 + 3);
			in1_0_0 = *(in1_0 + 0);
			in1_0_1 = *(in1_0 + 1);
			in1_0_2 = *(in1_0 + 2);
			in1_0_3 = *(in1_0 + 3);
			in1_1_0 = *(in1_1 + 0);
			in1_1_1 = *(in1_1 + 1);
			in1_1_2 = *(in1_1 + 2);
			in1_1_3 = *(in1_1 + 3);
			in1_2_0 = *(in1_2 + 0);
			in1_2_1 = *(in1_2 + 1);
			in1_2_2 = *(in1_2 + 2);
			in1_2_3 = *(in1_2 + 3);
			in1_3_0 = *(in1_3 + 0);
			in1_3_1 = *(in1_3 + 1);
			in1_3_2 = *(in1_3 + 2);
			in1_3_3 = *(in1_3 + 3);
			out0_0 += in0_0 * in1_0_0; 
			out0_1 += in0_1 * in1_0_1; 
			out0_2 += in0_2 * in1_0_2; 
			out0_3 += in0_3 * in1_0_3; 
			out1_0 += in0_0 * in1_1_0; 
			out1_1 += in0_1 * in1_1_1; 
			out1_2 += in0_2 * in1_1_2; 
			out1_3 += in0_3 * in1_1_3; 
			out2_0 += in0_0 * in1_2_0; 
			out2_1 += in0_1 * in1_2_1; 
			out2_2 += in0_2 * in1_2_2; 
			out2_3 += in0_3 * in1_2_3; 
			out3_0 += in0_0 * in1_3_0; 
			out3_1 += in0_1 * in1_3_1; 
			out3_2 += in0_2 * in1_3_2; 
			out3_3 += in0_3 * in1_3_3; 
			in0 += 4;
			in1_0 += 4;
			in1_1 += 4;
			in1_2 += 4;
			in1_3 += 4;
			in0_0 = *(in0 + 0);
			in0_1 = *(in0 + 1);
			in0_2 = *(in0 + 2);
			in0_3 = *(in0 + 3);
			in1_0_0 = *(in1_0 + 0);
			in1_0_1 = *(in1_0 + 1);
			in1_0_2 = *(in1_0 + 2);
			in1_0_3 = *(in1_0 + 3);
			in1_1_0 = *(in1_1 + 0);
			in1_1_1 = *(in1_1 + 1);
			in1_1_2 = *(in1_1 + 2);
			in1_1_3 = *(in1_1 + 3);
			in1_2_0 = *(in1_2 + 0);
			in1_2_1 = *(in1_2 + 1);
			in1_2_2 = *(in1_2 + 2);
			in1_2_3 = *(in1_2 + 3);
			in1_3_0 = *(in1_3 + 0);
			in1_3_1 = *(in1_3 + 1);
			in1_3_2 = *(in1_3 + 2);
			in1_3_3 = *(in1_3 + 3);
			out0_0 += in0_0 * in1_0_0; 
			out0_1 += in0_1 * in1_0_1; 
			out0_2 += in0_2 * in1_0_2; 
			out0_3 += in0_3 * in1_0_3; 
			out1_0 += in0_0 * in1_1_0; 
			out1_1 += in0_1 * in1_1_1; 
			out1_2 += in0_2 * in1_1_2; 
			out1_3 += in0_3 * in1_1_3; 
			out2_0 += in0_0 * in1_2_0; 
			out2_1 += in0_1 * in1_2_1; 
			out2_2 += in0_2 * in1_2_2; 
			out2_3 += in0_3 * in1_2_3; 
			out3_0 += in0_0 * in1_3_0; 
			out3_1 += in0_1 * in1_3_1; 
			out3_2 += in0_2 * in1_3_2; 
			out3_3 += in0_3 * in1_3_3; 
			in0 += 4;
			in1_0 += 4;
			in1_1 += 4;
			in1_2 += 4;
			in1_3 += 4;
			in0_0 = *(in0 + 0);
			in0_1 = *(in0 + 1);
			in0_2 = *(in0 + 2);
			in0_3 = *(in0 + 3);
			in1_0_0 = *(in1_0 + 0);
			in1_0_1 = *(in1_0 + 1);
			in1_0_2 = *(in1_0 + 2);
			in1_0_3 = *(in1_0 + 3);
			in1_1_0 = *(in1_1 + 0);
			in1_1_1 = *(in1_1 + 1);
			in1_1_2 = *(in1_1 + 2);
			in1_1_3 = *(in1_1 + 3);
			in1_2_0 = *(in1_2 + 0);
			in1_2_1 = *(in1_2 + 1);
			in1_2_2 = *(in1_2 + 2);
			in1_2_3 = *(in1_2 + 3);
			in1_3_0 = *(in1_3 + 0);
			in1_3_1 = *(in1_3 + 1);
			in1_3_2 = *(in1_3 + 2);
			in1_3_3 = *(in1_3 + 3);
			out0_0 += in0_0 * in1_0_0; 
			out0_1 += in0_1 * in1_0_1; 
			out0_2 += in0_2 * in1_0_2; 
			out0_3 += in0_3 * in1_0_3; 
			out1_0 += in0_0 * in1_1_0; 
			out1_1 += in0_1 * in1_1_1; 
			out1_2 += in0_2 * in1_1_2; 
			out1_3 += in0_3 * in1_1_3; 
			out2_0 += in0_0 * in1_2_0; 
			out2_1 += in0_1 * in1_2_1; 
			out2_2 += in0_2 * in1_2_2; 
			out2_3 += in0_3 * in1_2_3; 
			out3_0 += in0_0 * in1_3_0; 
			out3_1 += in0_1 * in1_3_1; 
			out3_2 += in0_2 * in1_3_2; 
			out3_3 += in0_3 * in1_3_3; 
			in0 += 4;
			in1_0 += 4;
			in1_1 += 4;
			in1_2 += 4;
			in1_3 += 4;
			in0_0 = *(in0 + 0);
			in0_1 = *(in0 + 1);
			in0_2 = *(in0 + 2);
			in0_3 = *(in0 + 3);
			in1_0_0 = *(in1_0 + 0);
			in1_0_1 = *(in1_0 + 1);
			in1_0_2 = *(in1_0 + 2);
			in1_0_3 = *(in1_0 + 3);
			in1_1_0 = *(in1_1 + 0);
			in1_1_1 = *(in1_1 + 1);
			in1_1_2 = *(in1_1 + 2);
			in1_1_3 = *(in1_1 + 3);
			in1_2_0 = *(in1_2 + 0);
			in1_2_1 = *(in1_2 + 1);
			in1_2_2 = *(in1_2 + 2);
			in1_2_3 = *(in1_2 + 3);
			in1_3_0 = *(in1_3 + 0);
			in1_3_1 = *(in1_3 + 1);
			in1_3_2 = *(in1_3 + 2);
			in1_3_3 = *(in1_3 + 3);
			out0_0 += in0_0 * in1_0_0; 
			out0_1 += in0_1 * in1_0_1; 
			out0_2 += in0_2 * in1_0_2; 
			out0_3 += in0_3 * in1_0_3; 
			out1_0 += in0_0 * in1_1_0; 
			out1_1 += in0_1 * in1_1_1; 
			out1_2 += in0_2 * in1_1_2; 
			out1_3 += in0_3 * in1_1_3; 
			out2_0 += in0_0 * in1_2_0; 
			out2_1 += in0_1 * in1_2_1; 
			out2_2 += in0_2 * in1_2_2; 
			out2_3 += in0_3 * in1_2_3; 
			out3_0 += in0_0 * in1_3_0; 
			out3_1 += in0_1 * in1_3_1; 
			out3_2 += in0_2 * in1_3_2; 
			out3_3 += in0_3 * in1_3_3; 
			in0 += 4;
			in1_0 += 4;
			in1_1 += 4;
			in1_2 += 4;
			in1_3 += 4;
		}
		*Out0 += (out0_0 + out0_2) + (out0_1 + out0_3);
		*Out1 += (out1_0 + out1_2) + (out1_1 + out1_3);
		*Out2 += (out2_0 + out2_2) + (out2_1 + out2_3);
		*Out3 += (out3_0 + out3_2) + (out3_1 + out3_3);
		Out0 += Outs1;
		Out1 += Outs1;
		Out2 += Outs1;
		Out3 += Outs1;
	}

	if (mod) {
		div = k - mod;
		mrdot_product_4x16(Out, _In0 + div, In1 + div, m, mod, Outs0, Outs1, In0s, In1s);
	}
}

//------------------------------------------------------------------------------
#endif
