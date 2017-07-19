#ifndef vmdot_product_2_txx
#define vmdot_product_1_txx

//------------------------------------------------------------------------------
template <class T, class U>
static inline void vmdot_product_1x1 (T* Out, 
																			T* _In0, 
																			T* _In1, 
																			volatile const U k, 
																			volatile const U n = 1,
																			volatile const U In1s = 0) { 

	register T out0;
	register T in00;
	register T in10;
	register T* in0;
	register T* in1;
	register U i, j;
	register T *In0, *In1;

	In0 = _In0;
	In1 = _In1;

	for (i = n; i; i--) {
		out0 = 0.;
		in0 = In0;
		in1 = In1;
		In1 ++;
		for (j = k; j; j--) {
			in00 = * in0;
			in10 = * in1;
			in0 ++;
			in1 += In1s;
			out0 += in00 * in10;
		}
		*Out += out0;
		Out ++;
	}
}

//------------------------------------------------------------------------------
template <class T, class U>
static inline void vmdot_product_1x2 (T* Out, 
																			T* _In0, 
																			T* _In1, 
																			volatile const U k, 
																			volatile const U n = 1,
																			volatile const U In1s = 0) { 

	register T out0, out1;
	register T in10, in11;
	T in00;
	register T *in1, *in0;
	register T *In0, *In1;

  register U i, j;
  volatile U div, mod;

	In0 = _In0;
	In1 = _In1;

	div = n >> 1;
	mod = n & 1;

	for (i = div; i; i--) {
		out0 = 0.;
		out1 = 0.;
		in0 = In0;
		in1 = In1;
		In1 += 2;
		for (j = k; j; j--) {
			in00 = * in0;
			in0 ++;
			in10 = *(in1 + 0);
			in11 = *(in1 + 1);
			in1 += In1s;
			out0 += in00 * in10;
			out1 += in00 * in11;
		}
		*(Out + 0) += out0;
		*(Out + 1) += out1;
		Out += 2;
	}

	if (mod) {
		div = n - mod;
		vmdot_product_1x1 (Out, _In0, _In1 + div, k, mod, In1s);
	}
}

//------------------------------------------------------------------------------
template <class T, class U>
static inline void vmdot_product_1x4 (T* Out, 
																			T* _In0, 
																			T* _In1, 
																			volatile const U k, 
																			volatile const U n = 1,
																			volatile const U In1s = 0) { 

	register T out0, out1, out2, out3;
	register T in10, in11, in12, in13;
	T in00;
	register T *in1, *in0;
	register T *In0, *In1;

  register U i, j;
  volatile U div, mod;

	In0 = _In0;
	In1 = _In1;

	div = n >> 2;
	mod = n & 3;

	for (i = div; i; i--) {
	  ///*
		out0 = 0.;
		out1 = 0.;
		out2 = 0.;
		out3 = 0.;
		//*/
		/*
		out0 = *(Out + 0);
		out1 = *(Out + 1);
		out2 = *(Out + 2);
		out3 = *(Out + 3);
		*/
		in0 = In0;
		in1 = In1;
		In1 += 4;
		for (j = k; j; j--) {
			in00 = * in0;
			in0 ++;
			in10 = *(in1 + 0);
			in11 = *(in1 + 1);
			in12 = *(in1 + 2);
			in13 = *(in1 + 3);
			in1 += In1s;
			out0 += in00 * in10;
			out1 += in00 * in11;
			out2 += in00 * in12;
			out3 += in00 * in13;
		}
		///*
		*(Out + 0) += out0;
		*(Out + 1) += out1;
		*(Out + 2) += out2;
		*(Out + 3) += out3;
		//*/
		/*
		*(Out + 0) = out0;
		*(Out + 1) = out1;
		*(Out + 2) = out2;
		*(Out + 3) = out3;
		*/
		Out += 4;
	}

	if (mod) {
		div = n - mod;
		vmdot_product_1x2 (Out, _In0, _In1 + div, k, mod, In1s);
	}
}

//------------------------------------------------------------------------------
template <class T, class U>
static inline void vmdot_product_1x8 (T* Out, 
																			T* _In0, 
																			T* _In1, 
																			volatile const U k, 
																			volatile const U n = 1,
																			volatile const U In1s = 0) { 

	register T out0, out1, out2, out3, out4, out5, out6, out7;
	register T in10, in11, in12, in13, in14, in15, in16, in17;
	T in00;
	register T *in1, *in0;
	register T *In0, *In1;

  register U i, j;
  volatile U div, mod;

	In0 = _In0;
	In1 = _In1;

	div = n >> 3;
	mod = n & 7;

	for (i = div; i; i--) {
		out0 = 0.;
		out1 = 0.;
		out2 = 0.;
		out3 = 0.;
		out4 = 0.;
		out5 = 0.;
		out6 = 0.;
		out7 = 0.;
		in0 = In0;
		in1 = In1;
		In1 += 8;
		for (j = k; j; j--) {
			in00 = * in0;
			in0 ++;
			in10 = *(in1 + 0);
			in11 = *(in1 + 1);
			in12 = *(in1 + 2);
			in13 = *(in1 + 3);
			in14 = *(in1 + 4);
			in15 = *(in1 + 5);
			in16 = *(in1 + 6);
			in17 = *(in1 + 7);
			in1 += In1s;
			out0 += in00 * in10;
			out1 += in00 * in11;
			out2 += in00 * in12;
			out3 += in00 * in13;
			out4 += in00 * in14;
			out5 += in00 * in15;
			out6 += in00 * in16;
			out7 += in00 * in17;
		}
		*(Out + 0) += out0;
		*(Out + 1) += out1;
		*(Out + 2) += out2;
		*(Out + 3) += out3;
		*(Out + 4) += out4;
		*(Out + 5) += out5;
		*(Out + 6) += out6;
		*(Out + 7) += out7;
		Out += 8;
	}

	if (mod) {
		div = n - mod;
		vmdot_product_1x4 (Out, _In0, _In1 + div, k, mod, In1s);
	}
}



//------------------------------------------------------------------------------
#endif

