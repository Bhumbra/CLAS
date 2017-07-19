#ifndef _mmdot_8x8_txx
#define _mmdot_8x8_txx

//------------------------------------------------------------------------------
// Note In1s is also the output stride
//------------------------------------------------------------------------------
template <class T, class U>
static inline void mmdot_product_8x8 (T* _Out, 
																			T* _In0, 
																			T* _In1, 
																			volatile const U m,
																			volatile const U k, 
																			volatile const U n) { 

	register T out0, out1, out2, out3, out4, out5, out6, out7;
	register T in00, in01, in02, in03, in04, in05, in06, in07;
	register T in10, in11, in12, in13, in14, in15, in16, in17;

	T* Out;
	T* In0;
	T* In1;

	register T* out;
	register T* in0;
	register T* in1;

	register U g, h, i, j;

	volatile U m8 = m >> 3;
	volatile U k8 = k >> 3;
	volatile U n8 = n >> 3;

	for (g = 0; g<m; g++) {
		Out = _Out + g*n;
		In0 = _In0 + g*k;
		for (h = 0; h<n8;  h++) {
			out = Out + h*8;
			In1 = _In1 + h*8;
			out0 = *(out + 0);
			out1 = *(out + 1);
			out2 = *(out + 2);
			out3 = *(out + 3);
			out4 = *(out + 4);
			out5 = *(out + 5);
			out6 = *(out + 6);
			out7 = *(out + 7);
			for (i = 0; i<k8; i++) {
				in0 = In0 + i*8;
				in00 = *(in0 + 0);
				in01 = *(in0 + 1);
				in02 = *(in0 + 2);
				in03 = *(in0 + 3);
				in04 = *(in0 + 4);
				in05 = *(in0 + 5);
				in06 = *(in0 + 6);
				in07 = *(in0 + 7);
				in1 = In1 + i*n*8;
				in10 = *(in1 + 0);
				in11 = *(in1 + 1);
				in12 = *(in1 + 2);
				in13 = *(in1 + 3);
				in14 = *(in1 + 4);
				in15 = *(in1 + 5);
				in16 = *(in1 + 6);
				in17 = *(in1 + 7);
				out0 += in00 * in10;
				out1 += in00 * in11;
				out2 += in00 * in12;
				out3 += in00 * in13;
				out4 += in00 * in14;
				out5 += in00 * in15;
				out6 += in00 * in16;
				out7 += in00 * in17;
				in1 += n;
				in10 = *(in1 + 0);
				in11 = *(in1 + 1);
				in12 = *(in1 + 2);
				in13 = *(in1 + 3);
				in14 = *(in1 + 4);
				in15 = *(in1 + 5);
				in16 = *(in1 + 6);
				in17 = *(in1 + 7);
				out0 += in01 * in10;
				out1 += in01 * in11;
				out2 += in01 * in12;
				out3 += in01 * in13;
				out4 += in01 * in14;
				out5 += in01 * in15;
				out6 += in01 * in16;
				out7 += in01 * in17;
				in1 += n;
				in10 = *(in1 + 0);
				in11 = *(in1 + 1);
				in12 = *(in1 + 2);
				in13 = *(in1 + 3);
				in14 = *(in1 + 4);
				in15 = *(in1 + 5);
				in16 = *(in1 + 6);
				in17 = *(in1 + 7);
				out0 += in02 * in10;
				out1 += in02 * in11;
				out2 += in02 * in12;
				out3 += in02 * in13;
				out4 += in02 * in14;
				out5 += in02 * in15;
				out6 += in02 * in16;
				out7 += in02 * in17;
				in1 += n;
				in10 = *(in1 + 0);
				in11 = *(in1 + 1);
				in12 = *(in1 + 2);
				in13 = *(in1 + 3);
				in14 = *(in1 + 4);
				in15 = *(in1 + 5);
				in16 = *(in1 + 6);
				in17 = *(in1 + 7);
				out0 += in03 * in10;
				out1 += in03 * in11;
				out2 += in03 * in12;
				out3 += in03 * in13;
				out4 += in03 * in14;
				out5 += in03 * in15;
				out6 += in03 * in16;
				out7 += in03 * in17;
				in1 += n;
				in10 = *(in1 + 0);
				in11 = *(in1 + 1);
				in12 = *(in1 + 2);
				in13 = *(in1 + 3);
				in14 = *(in1 + 4);
				in15 = *(in1 + 5);
				in16 = *(in1 + 6);
				in17 = *(in1 + 7);
				out0 += in04 * in10;
				out1 += in04 * in11;
				out2 += in04 * in12;
				out3 += in04 * in13;
				out4 += in04 * in14;
				out5 += in04 * in15;
				out6 += in04 * in16;
				out7 += in04 * in17;
				in1 += n;
				in10 = *(in1 + 0);
				in11 = *(in1 + 1);
				in12 = *(in1 + 2);
				in13 = *(in1 + 3);
				in14 = *(in1 + 4);
				in15 = *(in1 + 5);
				in16 = *(in1 + 6);
				in17 = *(in1 + 7);
				out0 += in05 * in10;
				out1 += in05 * in11;
				out2 += in05 * in12;
				out3 += in05 * in13;
				out4 += in05 * in14;
				out5 += in05 * in15;
				out6 += in05 * in16;
				out7 += in05 * in17;
				in1 += n;
				in10 = *(in1 + 0);
				in11 = *(in1 + 1);
				in12 = *(in1 + 2);
				in13 = *(in1 + 3);
				in14 = *(in1 + 4);
				in15 = *(in1 + 5);
				in16 = *(in1 + 6);
				in17 = *(in1 + 7);
				out0 += in06 * in10;
				out1 += in06 * in11;
				out2 += in06 * in12;
				out3 += in06 * in13;
				out4 += in06 * in14;
				out5 += in06 * in15;
				out6 += in06 * in16;
				out7 += in06 * in17;
				in1 += n;
				in10 = *(in1 + 0);
				in11 = *(in1 + 1);
				in12 = *(in1 + 2);
				in13 = *(in1 + 3);
				in14 = *(in1 + 4);
				in15 = *(in1 + 5);
				in16 = *(in1 + 6);
				in17 = *(in1 + 7);
				out0 += in07 * in10;
				out1 += in07 * in11;
				out2 += in07 * in12;
				out3 += in07 * in13;
				out4 += in07 * in14;
				out5 += in07 * in15;
				out6 += in07 * in16;
				out7 += in07 * in17;
				in1 += n;
			}
			*(out + 0) = out0;
			*(out + 1) = out1;
			*(out + 2) = out2;
			*(out + 3) = out3;
			*(out + 4) = out4;
			*(out + 5) = out5;
			*(out + 6) = out6;
			*(out + 7) = out7;
		}
	}
}

//------------------------------------------------------------------------------
#endif

