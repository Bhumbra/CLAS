#ifndef vmdot_product_2_txx
#define vmdot_product_2_txx

//------------------------------------------------------------------------------
template <class T, class U>
static inline void vmdot_product_2x1 (T* Out, 
																			T* _In0, 
																			T* _In1, 
																			volatile const U k, 
																			volatile const U n = 1,
																			volatile const U In1s = 0) { 

	register T out0, out1;
	register T in00, in01;
	register T in10;
	register T* In00, *In01;
	register T* in1;

	register U i, j;
	T *Out0, *Out1;
	T *_In00, *_In01;
	register T *In1;

	Out0 = Out;
	Out1 = Out + In1s;
	_In00 = _In0;
	_In01 = _In0 + k;
	In1 = _In1;

	for (i = n; i; i--) {
		out0 = 0.;
		out1 = 0.;
		In00 = _In00;
		In01 = _In01;
		in1 = In1;
		In1 ++;
		for (j = k; j; j--) {
			in00 = * In00;
			in01 = * In01;
			In00 ++;
			In01 ++;
			in10 = * in1;
			in1 += In1s;
			out0 += in00 * in10;
			out1 += in01 * in10;
		}
		* Out0 += out0;
		* Out1 += out1;
		Out0 ++;
		Out1 ++;
	}
}

//------------------------------------------------------------------------------
template <class T, class U>
static inline void vmdot_product_2x2 (T* Out, 
																			T* _In0, 
																			T* _In1, 
																			volatile const U k, 
																			volatile const U n = 1,
																			volatile const U In1s = 0) { 

	register T out00, out01, out10, out11;
	register T in00, in01;
	register T in10, in11;
	register T* In00, *In01;
	register T* in1;

	register U i, j;
	volatile U mod, div;
	T *Out0, *Out1;
	T *_In00, *_In01;
	register T *In1;

	Out0 = Out;
	Out1 = Out + In1s;
	_In00 = _In0;
	_In01 = _In0 + k;
	In1 = _In1;

	div = n >> 1;
	mod = n & 1;

	for (i = div; i; i--) {
		out00 = 0.;
		out01 = 0.;
		out10 = 0.;
		out11 = 0.;
		In00 = _In00;
		In01 = _In01;
		in1 = In1;
		In1 += 2;
		for (j = k; j; j--) {
			in00 = * In00;
			in01 = * In01;
			In00 ++;
			In01 ++;
			in10 = *(in1 + 0);
			in11 = *(in1 + 1);
			in1 += In1s;
			out00 += in00 * in10;
			out01 += in00 * in11;
			out10 += in01 * in10;
			out11 += in01 * in11;
		}
		*(Out0 + 0) += out00;
		*(Out0 + 1) += out01;
		*(Out1 + 0) += out10;
		*(Out1 + 1) += out11;
		Out0 += 2;
		Out1 += 2;
	}

	if (mod) {
		div = n - mod;
		vmdot_product_2x1 (Out + div, _In0, _In1 + div, k, mod, In1s);
	}
}


//------------------------------------------------------------------------------
template <class T, class U>
static inline void vmdot_product_2x4 (T* Out, 
																			T* _In0, 
																			T* _In1, 
																			volatile const U k, 
																			volatile const U n = 1,
																			volatile const U In1s = 0) { 

	register T out00, out01, out02, out03, out10, out11, out12, out13;
	register T in00, in01;
	register T in10, in11, in12, in13;
	register T* In00, *In01;
	register T* in1;

	register U i, j;
	volatile U mod, div;
	T *Out0, *Out1;
	T *_In00, *_In01;
	register T *In1;

	Out0 = Out;
	Out1 = Out + In1s;
	_In00 = _In0;
	_In01 = _In0 + k;
	In1 = _In1;

	div = n >> 2;
	mod = n & 3;

	for (i = div; i; i--) {
		out00 = 0.;
		out01 = 0.;
		out02 = 0.;
		out03 = 0.;
		out10 = 0.;
		out11 = 0.;
		out12 = 0.;
		out13 = 0.;
		In00 = _In00;
		In01 = _In01;
		in1 = In1;
		In1 += 4;
		for (j = k; j; j--) {
			in00 = * In00;
			in01 = * In01;
			In00 ++;
			In01 ++;
			in10 = *(in1 + 0);
			in11 = *(in1 + 1);
			in12 = *(in1 + 2);
			in13 = *(in1 + 3);
			in1 += In1s;
			out00 += in00 * in10;
			out01 += in00 * in11;
			out02 += in00 * in12;
			out03 += in00 * in13;
			out10 += in01 * in10;
			out11 += in01 * in11;
			out12 += in01 * in12;
			out13 += in01 * in13;
		}
		*(Out0 + 0) += out00;
		*(Out0 + 1) += out01;
		*(Out0 + 2) += out02;
		*(Out0 + 3) += out03;
		*(Out1 + 0) += out10;
		*(Out1 + 1) += out11;
		*(Out1 + 2) += out12;
		*(Out1 + 3) += out13;
		Out0 += 4;
		Out1 += 4;
	}

	if (mod) {
		div = n - mod;
		vmdot_product_2x2 (Out + div, _In0, _In1 + div, k, mod, In1s);
	}
}

//------------------------------------------------------------------------------
template <class T, class U>
static inline void vmdot_product_2x8 (T* Out, 
																			T* _In0, 
																			T* _In1, 
																			volatile const U k, 
																			volatile const U n = 1,
																			volatile const U In1s = 0) { 

	register T out00, out01, out02, out03, out04, out05, out06, out07;
	register T out10, out11, out12, out13, out14, out15, out16, out17;
	register T in00, in01;
	register T in10, in11, in12, in13, in14, in15, in16, in17;
	register T* In00, *In01;
	register T* in1;

	register U i, j;
	volatile U mod, div;
	T *Out0, *Out1;
	T *_In00, *_In01;
	register T *In1;

	Out0 = Out;
	Out1 = Out + In1s;
	_In00 = _In0;
	_In01 = _In0 + k;
	In1 = _In1;

	div = n >> 3;
	mod = n & 7;

	for (i = div; i; i--) {
		out00 = 0.;
		out01 = 0.;
		out02 = 0.;
		out03 = 0.;
		out04 = 0.;
		out05 = 0.;
		out06 = 0.;
		out07 = 0.;
		out10 = 0.;
		out11 = 0.;
		out12 = 0.;
		out13 = 0.;
		out14 = 0.;
		out15 = 0.;
		out16 = 0.;
		out17 = 0.;
		In00 = _In00;
		In01 = _In01;
		in1 = In1;
		In1 += 8;
		for (j = k; j; j--) {
			in00 = * In00;
			in01 = * In01;
			In00 ++;
			In01 ++;
			in10 = *(in1 + 0);
			in11 = *(in1 + 1);
			in12 = *(in1 + 2);
			in13 = *(in1 + 3);
			in14 = *(in1 + 4);
			in15 = *(in1 + 5);
			in16 = *(in1 + 6);
			in17 = *(in1 + 7);
			in1 += In1s;
			out00 += in00 * in10;
			out01 += in00 * in11;
			out02 += in00 * in12;
			out03 += in00 * in13;
			out04 += in00 * in14;
			out05 += in00 * in15;
			out06 += in00 * in16;
			out07 += in00 * in17;
			out10 += in01 * in10;
			out11 += in01 * in11;
			out12 += in01 * in12;
			out13 += in01 * in13;
			out14 += in01 * in14;
			out15 += in01 * in15;
			out16 += in01 * in16;
			out17 += in01 * in17;
		}
		*(Out0 + 0) += out00;
		*(Out0 + 1) += out01;
		*(Out0 + 2) += out02;
		*(Out0 + 3) += out03;
		*(Out0 + 4) += out04;
		*(Out0 + 5) += out05;
		*(Out0 + 6) += out06;
		*(Out0 + 7) += out07;
		*(Out1 + 0) += out10;
		*(Out1 + 1) += out11;
		*(Out1 + 2) += out12;
		*(Out1 + 3) += out13;
		*(Out1 + 4) += out14;
		*(Out1 + 5) += out15;
		*(Out1 + 6) += out16;
		*(Out1 + 7) += out17;
		Out0 += 8;
		Out1 += 8;
	}

	if (mod) {
		div = n - mod;
		vmdot_product_2x4 (Out + div, _In0, _In1 + div, k, mod, In1s);
	}
}



//------------------------------------------------------------------------------
#endif

