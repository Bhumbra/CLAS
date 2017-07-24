# ifndef _mrdot_product_1_txx
# define _mrdot_product_1_txx

//------------------------------------------------------------------------------
template <class T>
static inline void mrdot_product_1x1 (T* _Out, 
																			T* _In0, 
																			T* In1, 
																			volatile const uint64_t m, 
																			volatile const uint64_t k,
																			volatile const uint64_t Outs = 1,
																			volatile const uint64_t In0s = 1) {
	register T out0;
	register T in0_0; 
	T in1_0;
	register T *Out, *In0;
	register T *in0, *in1;
	register uint64_t i, j;

	Out = _Out;
	In0 = _In0;

	for (i = m; i; i--) {
		in0 = In0;
		in1 = In1;
		out0 = 0.;
		In0 += In0s;
		for (j = k; j; j--) {
			in0_0 = *(in0 + 0);
			in0 ++;
			in1_0 = *(in1 + 0);
			in1 ++;
			out0 += in0_0 * in1_0; 
		}
		*Out += out0;
		Out += Outs;
	}
}

//------------------------------------------------------------------------------
template <class T>
static inline void mrdot_product_1x2 (T* _Out, 
																			T* _In0, 
																			T* In1, 
																			volatile const uint64_t m, 
																			volatile const uint64_t k,
																			volatile const uint64_t Outs = 1,
																			volatile const uint64_t In0s = 1) { 
	register T out0;
	register T in0_0, in0_1;
	T in1_0;
	register T *Out, *In0;
	register T *in0, *in1;
	register uint64_t i, j;
	volatile uint64_t div, mod;

	div = k >> 1;
	mod = k & 1;

	Out = _Out;
	In0 = _In0;

	for (i = m; i; i--) {
		in0 = In0;
		in1 = In1;
		out0 = 0.;
		In0 += In0s;
		for (j = div; j; j--) {
			in0_0 = *(in0 + 0);
			in0_1 = *(in0 + 1);
			in0 += 2;
			in1_0 = *(in1 + 0);
			in1 ++;
			out0 += in0_0 * in1_0; 
			in1_0 = *(in1 + 0);
			in1 ++;
			out0 += in0_1 * in1_0; 
		}
		*Out += out0;
		Out += Outs;
	}

	if (mod) {
		div = k - mod;
		mrdot_product_1x1 (_Out, _In0 + div, In1 + div, m, mod, Outs, In0s);
	}
}

//------------------------------------------------------------------------------
template <class T>
static inline void mrdot_product_1x4 (T* _Out, 
																			T* _In0, 
																			T* In1, 
																			volatile const uint64_t m, 
																			volatile const uint64_t k,
																			volatile const uint64_t Outs = 1,
																			volatile const uint64_t In0s = 1) { 
	register T out0;
	register T in0_0, in0_1, in0_2, in0_3;
	T in1_0;
	register T *Out, *In0;
	register T *in0, *in1;
	register uint64_t i, j;
	volatile uint64_t div, mod;

	div = k >> 2;
	mod = k & 3;

	Out = _Out;
	In0 = _In0;

	for (i = m; i; i--) {
		in0 = In0;
		in1 = In1;
		out0 = 0.;
		In0 += In0s;
		for (j = div; j; j--) {
			in0_0 = *(in0 + 0);
			in0_1 = *(in0 + 1);
			in0_2 = *(in0 + 2);
			in0_3 = *(in0 + 3);
			in0 += 4;
			in1_0 = *(in1 + 0);
			in1 ++;
			out0 += in0_0 * in1_0; 
			in1_0 = *(in1 + 0);
			in1 ++;
			out0 += in0_1 * in1_0; 
			in1_0 = *(in1 + 0);
			in1 ++;
			out0 += in0_2 * in1_0; 
			in1_0 = *(in1 + 0);
			in1 ++;
			out0 += in0_3 * in1_0; 
		}
		*Out += out0;
		Out += Outs;
	}

	if (mod) {
		div = k - mod;
		mrdot_product_1x2 (_Out, _In0 + div, In1 + div, m, mod, Outs, In0s);
	}
}

//------------------------------------------------------------------------------
template <class T>
static inline void mrdot_product_1x8 (T* _Out, 
																			T* _In0, 
																			T* In1, 
																			volatile const uint64_t m, 
																			volatile const uint64_t k,
																			volatile const uint64_t Outs = 1,
																			volatile const uint64_t In0s = 1) { 
	register T out0;
	register T in0_0, in0_1, in0_2, in0_3, in0_4, in0_5, in0_6, in0_7;
	T in1_0;
	register T *Out, *In0;
	register T *in0, *in1;
	register uint64_t i, j;
	volatile uint64_t div, mod;

	div = k >> 3;
	mod = k & 7;

	Out = _Out;
	In0 = _In0;

	for (i = m; i; i--) {
		in0 = In0;
		in1 = In1;
		out0 = 0.;
		In0 += In0s;
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
			in1 ++;
			out0 += in0_0 * in1_0; 
			in1_0 = *(in1 + 0);
			in1 ++;
			out0 += in0_1 * in1_0; 
			in1_0 = *(in1 + 0);
			in1 ++;
			out0 += in0_2 * in1_0; 
			in1_0 = *(in1 + 0);
			in1 ++;
			out0 += in0_3 * in1_0; 
			in1_0 = *(in1 + 0);
			in1 ++;
			out0 += in0_4 * in1_0; 
			in1_0 = *(in1 + 0);
			in1 ++;
			out0 += in0_5 * in1_0; 
			in1_0 = *(in1 + 0);
			in1 ++;
			out0 += in0_6 * in1_0; 
			in1_0 = *(in1 + 0);
			in1 ++;
			out0 += in0_7 * in1_0; 
		}
		*Out += out0;
		Out += Outs;
	}

	if (mod) {
		div = k - mod;
		mrdot_product_1x4 (_Out, _In0 + div, In1 + div, m, mod, Outs, In0s);
	}
}

//------------------------------------------------------------------------------
template <class T>
static inline void mrdot_product_1x16(T* _Out, 
																			T* _In0, 
																			T* In1, 
																			volatile const uint64_t m, 
																			volatile const uint64_t k,
																			volatile const uint64_t Outs = 1,
																			volatile const uint64_t In0s = 1) { 
	register T out0;
	register T in0_0, in0_1, in0_2, in0_3, in0_4, in0_5, in0_6, in0_7;
	T in1_0;
	register T *Out, *In0;
	register T *in0, *in1;
	register uint64_t i, j;
	volatile uint64_t div, mod;

	div = k >> 4;
	mod = k & 15;

	Out = _Out;
	In0 = _In0;

	for (i = m; i; i--) {
		in0 = In0;
		in1 = In1;
		out0 = 0.;
		In0 += In0s;
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
			in1 ++;
			out0 += in0_0 * in1_0; 
			in1_0 = *(in1 + 0);
			in1 ++;
			out0 += in0_1 * in1_0; 
			in1_0 = *(in1 + 0);
			in1 ++;
			out0 += in0_2 * in1_0; 
			in1_0 = *(in1 + 0);
			in1 ++;
			out0 += in0_3 * in1_0; 
			in1_0 = *(in1 + 0);
			in1 ++;
			out0 += in0_4 * in1_0; 
			in1_0 = *(in1 + 0);
			in1 ++;
			out0 += in0_5 * in1_0; 
			in1_0 = *(in1 + 0);
			in1 ++;
			out0 += in0_6 * in1_0; 
			in1_0 = *(in1 + 0);
			in1 ++;
			out0 += in0_7 * in1_0; 
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
			in1 ++;
			out0 += in0_0 * in1_0; 
			in1_0 = *(in1 + 0);
			in1 ++;
			out0 += in0_1 * in1_0; 
			in1_0 = *(in1 + 0);
			in1 ++;
			out0 += in0_2 * in1_0; 
			in1_0 = *(in1 + 0);
			in1 ++;
			out0 += in0_3 * in1_0; 
			in1_0 = *(in1 + 0);
			in1 ++;
			out0 += in0_4 * in1_0; 
			in1_0 = *(in1 + 0);
			in1 ++;
			out0 += in0_5 * in1_0; 
			in1_0 = *(in1 + 0);
			in1 ++;
			out0 += in0_6 * in1_0; 
			in1_0 = *(in1 + 0);
			in1 ++;
			out0 += in0_7 * in1_0; 
		}
		*Out += out0;
		Out += Outs;
	}

	if (mod) {
		div = k - mod;
		mrdot_product_1x8 (_Out, _In0 + div, In1 + div, m, mod, Outs, In0s);
	}
}

//------------------------------------------------------------------------------
template <class T>
static inline void mrdot_product_1x32(T* _Out, 
																			T* _In0, 
																			T* In1, 
																			volatile const uint64_t m, 
																			volatile const uint64_t k,
																			volatile const uint64_t Outs = 1,
																			volatile const uint64_t In0s = 1) { 
	register T out0;
	register T in0_0, in0_1, in0_2, in0_3, in0_4, in0_5, in0_6, in0_7;
	T in1_0;
	register T *Out, *In0;
	register T *in0, *in1;
	register uint64_t i, j;
	volatile uint64_t div, mod;

	div = k >> 5;
	mod = k & 31;

	Out = _Out;
	In0 = _In0;

	for (i = m; i; i--) {
		in0 = In0;
		in1 = In1;
		out0 = 0.;
		In0 += In0s;
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
			in1 ++;
			out0 += in0_0 * in1_0; 
			in1_0 = *(in1 + 0);
			in1 ++;
			out0 += in0_1 * in1_0; 
			in1_0 = *(in1 + 0);
			in1 ++;
			out0 += in0_2 * in1_0; 
			in1_0 = *(in1 + 0);
			in1 ++;
			out0 += in0_3 * in1_0; 
			in1_0 = *(in1 + 0);
			in1 ++;
			out0 += in0_4 * in1_0; 
			in1_0 = *(in1 + 0);
			in1 ++;
			out0 += in0_5 * in1_0; 
			in1_0 = *(in1 + 0);
			in1 ++;
			out0 += in0_6 * in1_0; 
			in1_0 = *(in1 + 0);
			in1 ++;
			out0 += in0_7 * in1_0; 
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
			in1 ++;
			out0 += in0_0 * in1_0; 
			in1_0 = *(in1 + 0);
			in1 ++;
			out0 += in0_1 * in1_0; 
			in1_0 = *(in1 + 0);
			in1 ++;
			out0 += in0_2 * in1_0; 
			in1_0 = *(in1 + 0);
			in1 ++;
			out0 += in0_3 * in1_0; 
			in1_0 = *(in1 + 0);
			in1 ++;
			out0 += in0_4 * in1_0; 
			in1_0 = *(in1 + 0);
			in1 ++;
			out0 += in0_5 * in1_0; 
			in1_0 = *(in1 + 0);
			in1 ++;
			out0 += in0_6 * in1_0; 
			in1_0 = *(in1 + 0);
			in1 ++;
			out0 += in0_7 * in1_0; 
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
			in1 ++;
			out0 += in0_0 * in1_0; 
			in1_0 = *(in1 + 0);
			in1 ++;
			out0 += in0_1 * in1_0; 
			in1_0 = *(in1 + 0);
			in1 ++;
			out0 += in0_2 * in1_0; 
			in1_0 = *(in1 + 0);
			in1 ++;
			out0 += in0_3 * in1_0; 
			in1_0 = *(in1 + 0);
			in1 ++;
			out0 += in0_4 * in1_0; 
			in1_0 = *(in1 + 0);
			in1 ++;
			out0 += in0_5 * in1_0; 
			in1_0 = *(in1 + 0);
			in1 ++;
			out0 += in0_6 * in1_0; 
			in1_0 = *(in1 + 0);
			in1 ++;
			out0 += in0_7 * in1_0; 
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
			in1 ++;
			out0 += in0_0 * in1_0; 
			in1_0 = *(in1 + 0);
			in1 ++;
			out0 += in0_1 * in1_0; 
			in1_0 = *(in1 + 0);
			in1 ++;
			out0 += in0_2 * in1_0; 
			in1_0 = *(in1 + 0);
			in1 ++;
			out0 += in0_3 * in1_0; 
			in1_0 = *(in1 + 0);
			in1 ++;
			out0 += in0_4 * in1_0; 
			in1_0 = *(in1 + 0);
			in1 ++;
			out0 += in0_5 * in1_0; 
			in1_0 = *(in1 + 0);
			in1 ++;
			out0 += in0_6 * in1_0; 
			in1_0 = *(in1 + 0);
			in1 ++;
			out0 += in0_7 * in1_0; 
		}
		*Out += out0;
		Out += Outs;
	}

	if (mod) {
		div = k - mod;
		mrdot_product_1x16(_Out, _In0 + div, In1 + div, m, mod, Outs, In0s);
	}
}

//------------------------------------------------------------------------------
#endif
