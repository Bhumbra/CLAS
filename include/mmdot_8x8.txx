# ifndef _mmdot_8x8_txx
# define _mmdot_8x8_txx

# include "cacher.txx"

using namespace std;
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
template <class T, class U>
static inline void mmdot_product_8x4x4 (T* _Out, 
																				T* _In0, 
																				T* _In1, 
																				volatile const U m,
																				volatile const U k, 
																				volatile const U n) { 

	register T o0, o1, o2, o3;
	register T in1_0_0, in1_0_1, in1_0_2, in1_0_3; 
	register T in1_1_0, in1_1_1, in1_1_2, in1_1_3; 
	register T in1_2_0, in1_2_1, in1_2_2, in1_2_3; 
	register T in1_3_0, in1_3_1, in1_3_2, in1_3_3; 

	T in0_0_0, in0_0_1, in0_0_2, in0_0_3;
	T in0_1_0, in0_1_1, in0_1_2, in0_1_3;
	T in0_2_0, in0_2_1, in0_2_2, in0_2_3;
	T in0_3_0, in0_3_1, in0_3_2, in0_3_3;
	T in0_4_0, in0_4_1, in0_4_2, in0_4_3;
	T in0_5_0, in0_5_1, in0_5_2, in0_5_3;
	T in0_6_0, in0_6_1, in0_6_2, in0_6_3;
	T in0_7_0, in0_7_1, in0_7_2, in0_7_3;

	T *Out_0, *Out_1, *Out_2, *Out_3, *Out_4, *Out_5, *Out_6, *Out_7;
	T *In1_0, *In1_1, *In1_2, *In1_3;

	T *out_0, *out_1, *out_2, *out_3, *out_4, *out_5, *out_6, *out_7;
	T *in0_0, *in0_1, *in0_2, *in0_3, *in0_4, *in0_5, *in0_6, *in0_7;
	T *in1_0, *in1_1, *in1_2, *in1_3;

	T* Out = _Out;
	T* In0 = _In0;
	T* In1;

	U mdiv = m >> 3;
	U kdiv = k >> 2;
	U ndiv = n >> 2;

	register U h;
	register U i;
	register U j;

	for (h = mdiv; h; h--) {
		Out_0 = Out + n * 0;
		Out_1 = Out + n * 1;
		Out_2 = Out + n * 2;
		Out_3 = Out + n * 3;
		Out_4 = Out + n * 4;
		Out_5 = Out + n * 5;
		Out_6 = Out + n * 6;
		Out_7 = Out + n * 7;
		Out += n * 8;

		in0_0 = In0 + k * 0;
		in0_1 = In0 + k * 1;
		in0_2 = In0 + k * 2;
		in0_3 = In0 + k * 3;
		in0_4 = In0 + k * 4;
		in0_5 = In0 + k * 5;
		in0_6 = In0 + k * 6;
		in0_7 = In0 + k * 7;
		In0 += k * 8;

		In1 = _In1;

		for (i = kdiv; i; i--) {
			out_0 = Out_0;
			out_1 = Out_1;
			out_2 = Out_2;
			out_3 = Out_3;
			out_4 = Out_4;
			out_5 = Out_5;
			out_6 = Out_6;
			out_7 = Out_7;
			in0_0_0 = *(in0_0 + 0);
			in0_0_1 = *(in0_0 + 1);
			in0_0_2 = *(in0_0 + 2);
			in0_0_3 = *(in0_0 + 3);
			in0_0 += 4;
			in0_1_0 = *(in0_1 + 0);
			in0_1_1 = *(in0_1 + 1);
			in0_1_2 = *(in0_1 + 2);
			in0_1_3 = *(in0_1 + 3);
			in0_1 += 4;
			in0_2_0 = *(in0_2 + 0);
			in0_2_1 = *(in0_2 + 1);
			in0_2_2 = *(in0_2 + 2);
			in0_2_3 = *(in0_2 + 3);
			in0_2 += 4;
			in0_3_0 = *(in0_3 + 0);
			in0_3_1 = *(in0_3 + 1);
			in0_3_2 = *(in0_3 + 2);
			in0_3_3 = *(in0_3 + 3);
			in0_3 += 4;
			in0_4_0 = *(in0_4 + 0);
			in0_4_1 = *(in0_4 + 1);
			in0_4_2 = *(in0_4 + 2);
			in0_4_3 = *(in0_4 + 3);
			in0_4 += 4;
			in0_5_0 = *(in0_5 + 0);
			in0_5_1 = *(in0_5 + 1);
			in0_5_2 = *(in0_5 + 2);
			in0_5_3 = *(in0_5 + 3);
			in0_5 += 4;
			in0_6_0 = *(in0_6 + 0);
			in0_6_1 = *(in0_6 + 1);
			in0_6_2 = *(in0_6 + 2);
			in0_6_3 = *(in0_6 + 3);
			in0_6 += 4;
			in0_7_0 = *(in0_7 + 0);
			in0_7_1 = *(in0_7 + 1);
			in0_7_2 = *(in0_7 + 2);
			in0_7_3 = *(in0_7 + 3);
			in0_7 += 4;
			In1_0 = In1 + n * 0;
			In1_1 = In1 + n * 1;
			In1_2 = In1 + n * 2;
			In1_3 = In1 + n * 3;
			In1 += n * 4;
			for (j = ndiv; j; j--) {
				in1_0_0 = *(In1_0 + 0);
				in1_0_1 = *(In1_0 + 1);
				in1_0_2 = *(In1_0 + 2);
				in1_0_3 = *(In1_0 + 3);
				In1_0 += 4;
				in1_1_0 = *(In1_1 + 0);
				in1_1_1 = *(In1_1 + 1);
				in1_1_2 = *(In1_1 + 2);
				in1_1_3 = *(In1_1 + 3);
				In1_1 += 4;
				in1_2_0 = *(In1_2 + 0);
				in1_2_1 = *(In1_2 + 1);
				in1_2_2 = *(In1_2 + 2);
				in1_2_3 = *(In1_2 + 3);
				In1_2 += 4;
				in1_3_0 = *(In1_3 + 0);
				in1_3_1 = *(In1_3 + 1);
				in1_3_2 = *(In1_3 + 2);
				in1_3_3 = *(In1_3 + 3);
				In1_3 += 4;

				o0 = *(out_0 + 0);
				o1 = *(out_0 + 1);
				o2 = *(out_0 + 2);
				o3 = *(out_0 + 3);
				o0 += in0_0_0 * in1_0_0;
				o1 += in0_0_0 * in1_0_1;
				o2 += in0_0_0 * in1_0_2;
				o3 += in0_0_0 * in1_0_3;
				o0 += in0_0_1 * in1_1_0;
				o1 += in0_0_1 * in1_1_1;
				o2 += in0_0_1 * in1_1_2;
				o3 += in0_0_1 * in1_1_3;
				o0 += in0_0_2 * in1_2_0;
				o1 += in0_0_2 * in1_2_1;
				o2 += in0_0_2 * in1_2_2;
				o3 += in0_0_2 * in1_2_3;
				o0 += in0_0_3 * in1_3_0;
				o1 += in0_0_3 * in1_3_1;
				o2 += in0_0_3 * in1_3_2;
				o3 += in0_0_3 * in1_3_3;
				*(out_0 + 0) = o0;
				*(out_0 + 1) = o1;
				*(out_0 + 2) = o2;
				*(out_0 + 3) = o3;
				out_0 += 4;

				o0 = *(out_1 + 0);
				o1 = *(out_1 + 1);
				o2 = *(out_1 + 2);
				o3 = *(out_1 + 3);
				o0 += in0_1_0 * in1_0_0;
				o1 += in0_1_0 * in1_0_1;
				o2 += in0_1_0 * in1_0_2;
				o3 += in0_1_0 * in1_0_3;
				o0 += in0_1_1 * in1_1_0;
				o1 += in0_1_1 * in1_1_1;
				o2 += in0_1_1 * in1_1_2;
				o3 += in0_1_1 * in1_1_3;
				o0 += in0_1_2 * in1_2_0;
				o1 += in0_1_2 * in1_2_1;
				o2 += in0_1_2 * in1_2_2;
				o3 += in0_1_2 * in1_2_3;
				o0 += in0_1_3 * in1_3_0;
				o1 += in0_1_3 * in1_3_1;
				o2 += in0_1_3 * in1_3_2;
				o3 += in0_1_3 * in1_3_3;
				*(out_1 + 0) = o0;
				*(out_1 + 1) = o1;
				*(out_1 + 2) = o2;
				*(out_1 + 3) = o3;
				out_1 += 4;

				o0 = *(out_2 + 0);
				o1 = *(out_2 + 1);
				o2 = *(out_2 + 2);
				o3 = *(out_2 + 3);
				o0 += in0_2_0 * in1_0_0;
				o1 += in0_2_0 * in1_0_1;
				o2 += in0_2_0 * in1_0_2;
				o3 += in0_2_0 * in1_0_3;
				o0 += in0_2_1 * in1_1_0;
				o1 += in0_2_1 * in1_1_1;
				o2 += in0_2_1 * in1_1_2;
				o3 += in0_2_1 * in1_1_3;
				o0 += in0_2_2 * in1_2_0;
				o1 += in0_2_2 * in1_2_1;
				o2 += in0_2_2 * in1_2_2;
				o3 += in0_2_2 * in1_2_3;
				o0 += in0_2_3 * in1_3_0;
				o1 += in0_2_3 * in1_3_1;
				o2 += in0_2_3 * in1_3_2;
				o3 += in0_2_3 * in1_3_3;
				*(out_2 + 0) = o0;
				*(out_2 + 1) = o1;
				*(out_2 + 2) = o2;
				*(out_2 + 3) = o3;
				out_2 += 4;

				o0 = *(out_3 + 0);
				o1 = *(out_3 + 1);
				o2 = *(out_3 + 2);
				o3 = *(out_3 + 3);
				o0 += in0_3_0 * in1_0_0;
				o1 += in0_3_0 * in1_0_1;
				o2 += in0_3_0 * in1_0_2;
				o3 += in0_3_0 * in1_0_3;
				o0 += in0_3_1 * in1_1_0;
				o1 += in0_3_1 * in1_1_1;
				o2 += in0_3_1 * in1_1_2;
				o3 += in0_3_1 * in1_1_3;
				o0 += in0_3_2 * in1_2_0;
				o1 += in0_3_2 * in1_2_1;
				o2 += in0_3_2 * in1_2_2;
				o3 += in0_3_2 * in1_2_3;
				o0 += in0_3_3 * in1_3_0;
				o1 += in0_3_3 * in1_3_1;
				o2 += in0_3_3 * in1_3_2;
				o3 += in0_3_3 * in1_3_3;
				*(out_3 + 0) = o0;
				*(out_3 + 1) = o1;
				*(out_3 + 2) = o2;
				*(out_3 + 3) = o3;
				out_3 += 4;
				
				o0 = *(out_4 + 0);
				o1 = *(out_4 + 1);
				o2 = *(out_4 + 2);
				o3 = *(out_4 + 3);
				o0 += in0_4_0 * in1_0_0;
				o1 += in0_4_0 * in1_0_1;
				o2 += in0_4_0 * in1_0_2;
				o3 += in0_4_0 * in1_0_3;
				o0 += in0_4_1 * in1_1_0;
				o1 += in0_4_1 * in1_1_1;
				o2 += in0_4_1 * in1_1_2;
				o3 += in0_4_1 * in1_1_3;
				o0 += in0_4_2 * in1_2_0;
				o1 += in0_4_2 * in1_2_1;
				o2 += in0_4_2 * in1_2_2;
				o3 += in0_4_2 * in1_2_3;
				o0 += in0_4_3 * in1_3_0;
				o1 += in0_4_3 * in1_3_1;
				o2 += in0_4_3 * in1_3_2;
				o3 += in0_4_3 * in1_3_3;
				*(out_4 + 0) = o0;
				*(out_4 + 1) = o1;
				*(out_4 + 2) = o2;
				*(out_4 + 3) = o3;
				out_4 += 4;

				o0 = *(out_5 + 0);
				o1 = *(out_5 + 1);
				o2 = *(out_5 + 2);
				o3 = *(out_5 + 3);
				o0 += in0_5_0 * in1_0_0;
				o1 += in0_5_0 * in1_0_1;
				o2 += in0_5_0 * in1_0_2;
				o3 += in0_5_0 * in1_0_3;
				o0 += in0_5_1 * in1_1_0;
				o1 += in0_5_1 * in1_1_1;
				o2 += in0_5_1 * in1_1_2;
				o3 += in0_5_1 * in1_1_3;
				o0 += in0_5_2 * in1_2_0;
				o1 += in0_5_2 * in1_2_1;
				o2 += in0_5_2 * in1_2_2;
				o3 += in0_5_2 * in1_2_3;
				o0 += in0_5_3 * in1_3_0;
				o1 += in0_5_3 * in1_3_1;
				o2 += in0_5_3 * in1_3_2;
				o3 += in0_5_3 * in1_3_3;
				*(out_5 + 0) = o0;
				*(out_5 + 1) = o1;
				*(out_5 + 2) = o2;
				*(out_5 + 3) = o3;
				out_5 += 4;

				o0 = *(out_6 + 0);
				o1 = *(out_6 + 1);
				o2 = *(out_6 + 2);
				o3 = *(out_6 + 3);
				o0 += in0_6_0 * in1_0_0;
				o1 += in0_6_0 * in1_0_1;
				o2 += in0_6_0 * in1_0_2;
				o3 += in0_6_0 * in1_0_3;
				o0 += in0_6_1 * in1_1_0;
				o1 += in0_6_1 * in1_1_1;
				o2 += in0_6_1 * in1_1_2;
				o3 += in0_6_1 * in1_1_3;
				o0 += in0_6_2 * in1_2_0;
				o1 += in0_6_2 * in1_2_1;
				o2 += in0_6_2 * in1_2_2;
				o3 += in0_6_2 * in1_2_3;
				o0 += in0_6_3 * in1_3_0;
				o1 += in0_6_3 * in1_3_1;
				o2 += in0_6_3 * in1_3_2;
				o3 += in0_6_3 * in1_3_3;
				*(out_6 + 0) = o0;
				*(out_6 + 1) = o1;
				*(out_6 + 2) = o2;
				*(out_6 + 3) = o3;
				out_6 += 4;

				o0 = *(out_7 + 0);
				o1 = *(out_7 + 1);
				o2 = *(out_7 + 2);
				o3 = *(out_7 + 3);
				o0 += in0_7_0 * in1_0_0;
				o1 += in0_7_0 * in1_0_1;
				o2 += in0_7_0 * in1_0_2;
				o3 += in0_7_0 * in1_0_3;
				o0 += in0_7_1 * in1_1_0;
				o1 += in0_7_1 * in1_1_1;
				o2 += in0_7_1 * in1_1_2;
				o3 += in0_7_1 * in1_1_3;
				o0 += in0_7_2 * in1_2_0;
				o1 += in0_7_2 * in1_2_1;
				o2 += in0_7_2 * in1_2_2;
				o3 += in0_7_2 * in1_2_3;
				o0 += in0_7_3 * in1_3_0;
				o1 += in0_7_3 * in1_3_1;
				o2 += in0_7_3 * in1_3_2;
				o3 += in0_7_3 * in1_3_3;
				*(out_7 + 0) = o0;
				*(out_7 + 1) = o1;
				*(out_7 + 2) = o2;
				*(out_7 + 3) = o3;
				out_7 += 4;
			}
		}
	}
}

//------------------------------------------------------------------------------
template <class T, class U>
static inline void mmdot_product_4x2x8 (T* _Out, 
																				T* _In0, 
																				T* _In1, 
																				volatile const U m,
																				volatile const U k, 
																				volatile const U n) { 

	register T o0, o1, o2, o3, o4, o5, o6, o7;
	register T in1_0_0, in1_0_1, in1_0_2, in1_0_3, in1_0_4, in1_0_5, in1_0_6, in1_0_7; 
	register T in1_1_0, in1_1_1, in1_1_2, in1_1_3, in1_1_4, in1_1_5, in1_1_6, in1_1_7; 

	T in0_0_0, in0_0_1;
	T in0_1_0, in0_1_1;
	T in0_2_0, in0_2_1;
	T in0_3_0, in0_3_1;

	T *Out_0, *Out_1, *Out_2, *Out_3;
	T *In1_0, *In1_1;

	T *out_0, *out_1, *out_2, *out_3;
	T *in0_0, *in0_1, *in0_2, *in0_3;
	T *in1_0, *in1_1;

	T* Out = _Out;
	T* In0 = _In0;
	T* In1;

	U mdiv = m >> 2;
	U kdiv = k >> 1;
	U ndiv = n >> 3;

	register U h;
	register U i;
	register U j;

	for (h = mdiv; h; h--) {
		Out_0 = Out + n * 0;
		Out_1 = Out + n * 1;
		Out_2 = Out + n * 2;
		Out_3 = Out + n * 3;
		Out += n * 4;

		in0_0 = In0 + k * 0;
		in0_1 = In0 + k * 1;
		in0_2 = In0 + k * 2;
		in0_3 = In0 + k * 3;
		In0 += k * 4;

		In1 = _In1;

		for (i = kdiv; i; i--) {
			out_0 = Out_0;
			out_1 = Out_1;
			out_2 = Out_2;
			out_3 = Out_3;
			in0_0_0 = *(in0_0 + 0);
			in0_0_1 = *(in0_0 + 1);
			in0_0 += 2;
			in0_1_0 = *(in0_1 + 0);
			in0_1_1 = *(in0_1 + 1);
			in0_1 += 2;
			in0_2_0 = *(in0_2 + 0);
			in0_2_1 = *(in0_2 + 1);
			in0_2 += 2;
			in0_3_0 = *(in0_3 + 0);
			in0_3_1 = *(in0_3 + 1);
			in0_3 += 2;
			In1_0 = In1 + n * 0;
			In1_1 = In1 + n * 1;
			In1 += n * 2;
			for (j = ndiv; j; j--) {
				in1_0_0 = *(In1_0 + 0);
				in1_0_1 = *(In1_0 + 1);
				in1_0_2 = *(In1_0 + 2);
				in1_0_3 = *(In1_0 + 3);
				in1_0_4 = *(In1_0 + 4);
				in1_0_5 = *(In1_0 + 5);
				in1_0_6 = *(In1_0 + 6);
				in1_0_7 = *(In1_0 + 7);
				In1_0 += 8;
				in1_1_0 = *(In1_1 + 0);
				in1_1_1 = *(In1_1 + 1);
				in1_1_2 = *(In1_1 + 2);
				in1_1_3 = *(In1_1 + 3);
				in1_1_4 = *(In1_1 + 4);
				in1_1_5 = *(In1_1 + 5);
				in1_1_6 = *(In1_1 + 6);
				in1_1_7 = *(In1_1 + 7);
				In1_1 += 8;

				o0 = *(out_0 + 0);
				o1 = *(out_0 + 1);
				o2 = *(out_0 + 2);
				o3 = *(out_0 + 3);
				o4 = *(out_0 + 4);
				o5 = *(out_0 + 5);
				o6 = *(out_0 + 6);
				o7 = *(out_0 + 7);
				o0 += in0_0_0 * in1_0_0;
				o1 += in0_0_0 * in1_0_1;
				o2 += in0_0_0 * in1_0_2;
				o3 += in0_0_0 * in1_0_3;
				o4 += in0_0_0 * in1_0_4;
				o5 += in0_0_0 * in1_0_5;
				o6 += in0_0_0 * in1_0_6;
				o7 += in0_0_0 * in1_0_7;
				o0 += in0_0_1 * in1_1_0;
				o1 += in0_0_1 * in1_1_1;
				o2 += in0_0_1 * in1_1_2;
				o3 += in0_0_1 * in1_1_3;
				o4 += in0_0_1 * in1_1_4;
				o5 += in0_0_1 * in1_1_5;
				o6 += in0_0_1 * in1_1_6;
				o7 += in0_0_1 * in1_1_7;
				*(out_0 + 0) = o0;
				*(out_0 + 1) = o1;
				*(out_0 + 2) = o2;
				*(out_0 + 3) = o3;
				*(out_0 + 4) = o4;
				*(out_0 + 5) = o5;
				*(out_0 + 6) = o6;
				*(out_0 + 7) = o7;
				out_0 += 8;

				o0 = *(out_1 + 0);
				o1 = *(out_1 + 1);
				o2 = *(out_1 + 2);
				o3 = *(out_1 + 3);
				o4 = *(out_1 + 4);
				o5 = *(out_1 + 5);
				o6 = *(out_1 + 6);
				o7 = *(out_1 + 7);
				o0 += in0_1_0 * in1_0_0;
				o1 += in0_1_0 * in1_0_1;
				o2 += in0_1_0 * in1_0_2;
				o3 += in0_1_0 * in1_0_3;
				o4 += in0_1_0 * in1_0_4;
				o5 += in0_1_0 * in1_0_5;
				o6 += in0_1_0 * in1_0_6;
				o7 += in0_1_0 * in1_0_7;
				o0 += in0_1_1 * in1_1_0;
				o1 += in0_1_1 * in1_1_1;
				o2 += in0_1_1 * in1_1_2;
				o3 += in0_1_1 * in1_1_3;
				o4 += in0_1_1 * in1_1_4;
				o5 += in0_1_1 * in1_1_5;
				o6 += in0_1_1 * in1_1_6;
				o7 += in0_1_1 * in1_1_7;
				*(out_1 + 0) = o0;
				*(out_1 + 1) = o1;
				*(out_1 + 2) = o2;
				*(out_1 + 3) = o3;
				*(out_1 + 4) = o4;
				*(out_1 + 5) = o5;
				*(out_1 + 6) = o6;
				*(out_1 + 7) = o7;
				out_1 += 8;

				o0 = *(out_2 + 0);
				o1 = *(out_2 + 1);
				o2 = *(out_2 + 2);
				o3 = *(out_2 + 3);
				o4 = *(out_2 + 4);
				o5 = *(out_2 + 5);
				o6 = *(out_2 + 6);
				o7 = *(out_2 + 7);
				o0 += in0_2_0 * in1_0_0;
				o1 += in0_2_0 * in1_0_1;
				o2 += in0_2_0 * in1_0_2;
				o3 += in0_2_0 * in1_0_3;
				o4 += in0_2_0 * in1_0_4;
				o5 += in0_2_0 * in1_0_5;
				o6 += in0_2_0 * in1_0_6;
				o7 += in0_2_0 * in1_0_7;
				o0 += in0_2_1 * in1_1_0;
				o1 += in0_2_1 * in1_1_1;
				o2 += in0_2_1 * in1_1_2;
				o3 += in0_2_1 * in1_1_3;
				o4 += in0_2_1 * in1_1_4;
				o5 += in0_2_1 * in1_1_5;
				o6 += in0_2_1 * in1_1_6;
				o7 += in0_2_1 * in1_1_7;
				*(out_2 + 0) = o0;
				*(out_2 + 1) = o1;
				*(out_2 + 2) = o2;
				*(out_2 + 3) = o3;
				*(out_2 + 4) = o4;
				*(out_2 + 5) = o5;
				*(out_2 + 6) = o6;
				*(out_2 + 7) = o7;
				out_2 += 8;

				o0 = *(out_3 + 0);
				o1 = *(out_3 + 1);
				o2 = *(out_3 + 2);
				o3 = *(out_3 + 3);
				o4 = *(out_3 + 4);
				o5 = *(out_3 + 5);
				o6 = *(out_3 + 6);
				o7 = *(out_3 + 7);
				o0 += in0_3_0 * in1_0_0;
				o1 += in0_3_0 * in1_0_1;
				o2 += in0_3_0 * in1_0_2;
				o3 += in0_3_0 * in1_0_3;
				o4 += in0_3_0 * in1_0_4;
				o5 += in0_3_0 * in1_0_5;
				o6 += in0_3_0 * in1_0_6;
				o7 += in0_3_0 * in1_0_7;
				o0 += in0_3_1 * in1_1_0;
				o1 += in0_3_1 * in1_1_1;
				o2 += in0_3_1 * in1_1_2;
				o3 += in0_3_1 * in1_1_3;
				o4 += in0_3_1 * in1_1_4;
				o5 += in0_3_1 * in1_1_5;
				o6 += in0_3_1 * in1_1_6;
				o7 += in0_3_1 * in1_1_7;
				*(out_3 + 0) = o0;
				*(out_3 + 1) = o1;
				*(out_3 + 2) = o2;
				*(out_3 + 3) = o3;
				*(out_3 + 4) = o4;
				*(out_3 + 5) = o5;
				*(out_3 + 6) = o6;
				*(out_3 + 7) = o7;
				out_3 += 8;
			}
		}
	}
}

//------------------------------------------------------------------------------
template <class T, class U>
static inline void mmdot_product_8x2x8 (T* _Out, 
																				T* _In0, 
																				T* _In1, 
																				volatile const U m,
																				volatile const U k, 
																				volatile const U n) { 

	register T o0, o1, o2, o3, o4, o5, o6, o7;
	register T in1_0_0, in1_0_1, in1_0_2, in1_0_3, in1_0_4, in1_0_5, in1_0_6, in1_0_7; 
	register T in1_1_0, in1_1_1, in1_1_2, in1_1_3, in1_1_4, in1_1_5, in1_1_6, in1_1_7; 

	T in0_0_0, in0_0_1;
	T in0_1_0, in0_1_1;
	T in0_2_0, in0_2_1;
	T in0_3_0, in0_3_1;
	T in0_4_0, in0_4_1;
	T in0_5_0, in0_5_1;
	T in0_6_0, in0_6_1;
	T in0_7_0, in0_7_1;

	T *Out_0, *Out_1, *Out_2, *Out_3, *Out_4, *Out_5, *Out_6, *Out_7;
	T *In1_0, *In1_1;

	T *out_0, *out_1, *out_2, *out_3, *out_4, *out_5, *out_6, *out_7;
	T *in0_0, *in0_1, *in0_2, *in0_3, *in0_4, *in0_5, *in0_6, *in0_7;
	T *in1_0, *in1_1;

	T* Out = _Out;
	T* In0 = _In0;
	T* In1;

	U mdiv = m >> 3;
	U kdiv = k >> 1;
	U ndiv = n >> 3;

	register U h;
	register U i;
	register U j;

	for (h = mdiv; h; h--) {
		Out_0 = Out + n * 0;
		Out_1 = Out + n * 1;
		Out_2 = Out + n * 2;
		Out_3 = Out + n * 3;
		Out_4 = Out + n * 4;
		Out_5 = Out + n * 5;
		Out_6 = Out + n * 6;
		Out_7 = Out + n * 7;
		Out += n * 8;

		in0_0 = In0 + k * 0;
		in0_1 = In0 + k * 1;
		in0_2 = In0 + k * 2;
		in0_3 = In0 + k * 3;
		in0_4 = In0 + k * 4;
		in0_5 = In0 + k * 5;
		in0_6 = In0 + k * 6;
		in0_7 = In0 + k * 7;
		In0 += k * 8;

		In1 = _In1;

		for (i = kdiv; i; i--) {
			out_0 = Out_0;
			out_1 = Out_1;
			out_2 = Out_2;
			out_3 = Out_3;
			out_4 = Out_4;
			out_5 = Out_5;
			out_6 = Out_6;
			out_7 = Out_7;

			in0_0_0 = *(in0_0 + 0);
			in0_0_1 = *(in0_0 + 1);
			in0_0 += 2;
			in0_1_0 = *(in0_1 + 0);
			in0_1_1 = *(in0_1 + 1);
			in0_1 += 2;
			in0_2_0 = *(in0_2 + 0);
			in0_2_1 = *(in0_2 + 1);
			in0_2 += 2;
			in0_3_0 = *(in0_3 + 0);
			in0_3_1 = *(in0_3 + 1);
			in0_3 += 2;
			in0_4_0 = *(in0_4 + 0);
			in0_4_1 = *(in0_4 + 1);
			in0_4 += 2;
			in0_5_0 = *(in0_5 + 0);
			in0_5_1 = *(in0_5 + 1);
			in0_5 += 2;
			in0_6_0 = *(in0_6 + 0);
			in0_6_1 = *(in0_6 + 1);
			in0_6 += 2;
			in0_7_0 = *(in0_7 + 0);
			in0_7_1 = *(in0_7 + 1);
			in0_7 += 2;

			In1_0 = In1 + n * 0;
			In1_1 = In1 + n * 1;
			In1 += n * 2;
			for (j = ndiv; j; j--) {
				in1_0_0 = *(In1_0 + 0);
				in1_0_1 = *(In1_0 + 1);
				in1_0_2 = *(In1_0 + 2);
				in1_0_3 = *(In1_0 + 3);
				in1_0_4 = *(In1_0 + 4);
				in1_0_5 = *(In1_0 + 5);
				in1_0_6 = *(In1_0 + 6);
				in1_0_7 = *(In1_0 + 7);
				In1_0 += 8;
				in1_1_0 = *(In1_1 + 0);
				in1_1_1 = *(In1_1 + 1);
				in1_1_2 = *(In1_1 + 2);
				in1_1_3 = *(In1_1 + 3);
				in1_1_4 = *(In1_1 + 4);
				in1_1_5 = *(In1_1 + 5);
				in1_1_6 = *(In1_1 + 6);
				in1_1_7 = *(In1_1 + 7);
				In1_1 += 8;

				o0 = *(out_0 + 0);
				o1 = *(out_0 + 1);
				o2 = *(out_0 + 2);
				o3 = *(out_0 + 3);
				o4 = *(out_0 + 4);
				o5 = *(out_0 + 5);
				o6 = *(out_0 + 6);
				o7 = *(out_0 + 7);
				o0 += in0_0_0 * in1_0_0;
				o1 += in0_0_0 * in1_0_1;
				o2 += in0_0_0 * in1_0_2;
				o3 += in0_0_0 * in1_0_3;
				o4 += in0_0_0 * in1_0_4;
				o5 += in0_0_0 * in1_0_5;
				o6 += in0_0_0 * in1_0_6;
				o7 += in0_0_0 * in1_0_7;
				o0 += in0_0_1 * in1_1_0;
				o1 += in0_0_1 * in1_1_1;
				o2 += in0_0_1 * in1_1_2;
				o3 += in0_0_1 * in1_1_3;
				o4 += in0_0_1 * in1_1_4;
				o5 += in0_0_1 * in1_1_5;
				o6 += in0_0_1 * in1_1_6;
				o7 += in0_0_1 * in1_1_7;
				*(out_0 + 0) = o0;
				*(out_0 + 1) = o1;
				*(out_0 + 2) = o2;
				*(out_0 + 3) = o3;
				*(out_0 + 4) = o4;
				*(out_0 + 5) = o5;
				*(out_0 + 6) = o6;
				*(out_0 + 7) = o7;
				out_0 += 8;

				o0 = *(out_1 + 0);
				o1 = *(out_1 + 1);
				o2 = *(out_1 + 2);
				o3 = *(out_1 + 3);
				o4 = *(out_1 + 4);
				o5 = *(out_1 + 5);
				o6 = *(out_1 + 6);
				o7 = *(out_1 + 7);
				o0 += in0_1_0 * in1_0_0;
				o1 += in0_1_0 * in1_0_1;
				o2 += in0_1_0 * in1_0_2;
				o3 += in0_1_0 * in1_0_3;
				o4 += in0_1_0 * in1_0_4;
				o5 += in0_1_0 * in1_0_5;
				o6 += in0_1_0 * in1_0_6;
				o7 += in0_1_0 * in1_0_7;
				o0 += in0_1_1 * in1_1_0;
				o1 += in0_1_1 * in1_1_1;
				o2 += in0_1_1 * in1_1_2;
				o3 += in0_1_1 * in1_1_3;
				o4 += in0_1_1 * in1_1_4;
				o5 += in0_1_1 * in1_1_5;
				o6 += in0_1_1 * in1_1_6;
				o7 += in0_1_1 * in1_1_7;
				*(out_1 + 0) = o0;
				*(out_1 + 1) = o1;
				*(out_1 + 2) = o2;
				*(out_1 + 3) = o3;
				*(out_1 + 4) = o4;
				*(out_1 + 5) = o5;
				*(out_1 + 6) = o6;
				*(out_1 + 7) = o7;
				out_1 += 8;

				o0 = *(out_2 + 0);
				o1 = *(out_2 + 1);
				o2 = *(out_2 + 2);
				o3 = *(out_2 + 3);
				o4 = *(out_2 + 4);
				o5 = *(out_2 + 5);
				o6 = *(out_2 + 6);
				o7 = *(out_2 + 7);
				o0 += in0_2_0 * in1_0_0;
				o1 += in0_2_0 * in1_0_1;
				o2 += in0_2_0 * in1_0_2;
				o3 += in0_2_0 * in1_0_3;
				o4 += in0_2_0 * in1_0_4;
				o5 += in0_2_0 * in1_0_5;
				o6 += in0_2_0 * in1_0_6;
				o7 += in0_2_0 * in1_0_7;
				o0 += in0_2_1 * in1_1_0;
				o1 += in0_2_1 * in1_1_1;
				o2 += in0_2_1 * in1_1_2;
				o3 += in0_2_1 * in1_1_3;
				o4 += in0_2_1 * in1_1_4;
				o5 += in0_2_1 * in1_1_5;
				o6 += in0_2_1 * in1_1_6;
				o7 += in0_2_1 * in1_1_7;
				*(out_2 + 0) = o0;
				*(out_2 + 1) = o1;
				*(out_2 + 2) = o2;
				*(out_2 + 3) = o3;
				*(out_2 + 4) = o4;
				*(out_2 + 5) = o5;
				*(out_2 + 6) = o6;
				*(out_2 + 7) = o7;
				out_2 += 8;

				o0 = *(out_3 + 0);
				o1 = *(out_3 + 1);
				o2 = *(out_3 + 2);
				o3 = *(out_3 + 3);
				o4 = *(out_3 + 4);
				o5 = *(out_3 + 5);
				o6 = *(out_3 + 6);
				o7 = *(out_3 + 7);
				o0 += in0_3_0 * in1_0_0;
				o1 += in0_3_0 * in1_0_1;
				o2 += in0_3_0 * in1_0_2;
				o3 += in0_3_0 * in1_0_3;
				o4 += in0_3_0 * in1_0_4;
				o5 += in0_3_0 * in1_0_5;
				o6 += in0_3_0 * in1_0_6;
				o7 += in0_3_0 * in1_0_7;
				o0 += in0_3_1 * in1_1_0;
				o1 += in0_3_1 * in1_1_1;
				o2 += in0_3_1 * in1_1_2;
				o3 += in0_3_1 * in1_1_3;
				o4 += in0_3_1 * in1_1_4;
				o5 += in0_3_1 * in1_1_5;
				o6 += in0_3_1 * in1_1_6;
				o7 += in0_3_1 * in1_1_7;
				*(out_3 + 0) = o0;
				*(out_3 + 1) = o1;
				*(out_3 + 2) = o2;
				*(out_3 + 3) = o3;
				*(out_3 + 4) = o4;
				*(out_3 + 5) = o5;
				*(out_3 + 6) = o6;
				*(out_3 + 7) = o7;
				out_3 += 8;

				o0 = *(out_4 + 0);
				o1 = *(out_4 + 1);
				o2 = *(out_4 + 2);
				o3 = *(out_4 + 3);
				o4 = *(out_4 + 4);
				o5 = *(out_4 + 5);
				o6 = *(out_4 + 6);
				o7 = *(out_4 + 7);
				o0 += in0_4_0 * in1_0_0;
				o1 += in0_4_0 * in1_0_1;
				o2 += in0_4_0 * in1_0_2;
				o3 += in0_4_0 * in1_0_3;
				o4 += in0_4_0 * in1_0_4;
				o5 += in0_4_0 * in1_0_5;
				o6 += in0_4_0 * in1_0_6;
				o7 += in0_4_0 * in1_0_7;
				o0 += in0_4_1 * in1_1_0;
				o1 += in0_4_1 * in1_1_1;
				o2 += in0_4_1 * in1_1_2;
				o3 += in0_4_1 * in1_1_3;
				o4 += in0_4_1 * in1_1_4;
				o5 += in0_4_1 * in1_1_5;
				o6 += in0_4_1 * in1_1_6;
				o7 += in0_4_1 * in1_1_7;
				*(out_4 + 0) = o0;
				*(out_4 + 1) = o1;
				*(out_4 + 2) = o2;
				*(out_4 + 3) = o3;
				*(out_4 + 4) = o4;
				*(out_4 + 5) = o5;
				*(out_4 + 6) = o6;
				*(out_4 + 7) = o7;
				out_4 += 8;

				o0 = *(out_5 + 0);
				o1 = *(out_5 + 1);
				o2 = *(out_5 + 2);
				o3 = *(out_5 + 3);
				o4 = *(out_5 + 4);
				o5 = *(out_5 + 5);
				o6 = *(out_5 + 6);
				o7 = *(out_5 + 7);
				o0 += in0_5_0 * in1_0_0;
				o1 += in0_5_0 * in1_0_1;
				o2 += in0_5_0 * in1_0_2;
				o3 += in0_5_0 * in1_0_3;
				o4 += in0_5_0 * in1_0_4;
				o5 += in0_5_0 * in1_0_5;
				o6 += in0_5_0 * in1_0_6;
				o7 += in0_5_0 * in1_0_7;
				o0 += in0_5_1 * in1_1_0;
				o1 += in0_5_1 * in1_1_1;
				o2 += in0_5_1 * in1_1_2;
				o3 += in0_5_1 * in1_1_3;
				o4 += in0_5_1 * in1_1_4;
				o5 += in0_5_1 * in1_1_5;
				o6 += in0_5_1 * in1_1_6;
				o7 += in0_5_1 * in1_1_7;
				*(out_5 + 0) = o0;
				*(out_5 + 1) = o1;
				*(out_5 + 2) = o2;
				*(out_5 + 3) = o3;
				*(out_5 + 4) = o4;
				*(out_5 + 5) = o5;
				*(out_5 + 6) = o6;
				*(out_5 + 7) = o7;
				out_5 += 8;

				o0 = *(out_6 + 0);
				o1 = *(out_6 + 1);
				o2 = *(out_6 + 2);
				o3 = *(out_6 + 3);
				o4 = *(out_6 + 4);
				o5 = *(out_6 + 5);
				o6 = *(out_6 + 6);
				o7 = *(out_6 + 7);
				o0 += in0_6_0 * in1_0_0;
				o1 += in0_6_0 * in1_0_1;
				o2 += in0_6_0 * in1_0_2;
				o3 += in0_6_0 * in1_0_3;
				o4 += in0_6_0 * in1_0_4;
				o5 += in0_6_0 * in1_0_5;
				o6 += in0_6_0 * in1_0_6;
				o7 += in0_6_0 * in1_0_7;
				o0 += in0_6_1 * in1_1_0;
				o1 += in0_6_1 * in1_1_1;
				o2 += in0_6_1 * in1_1_2;
				o3 += in0_6_1 * in1_1_3;
				o4 += in0_6_1 * in1_1_4;
				o5 += in0_6_1 * in1_1_5;
				o6 += in0_6_1 * in1_1_6;
				o7 += in0_6_1 * in1_1_7;
				*(out_6 + 0) = o0;
				*(out_6 + 1) = o1;
				*(out_6 + 2) = o2;
				*(out_6 + 3) = o3;
				*(out_6 + 4) = o4;
				*(out_6 + 5) = o5;
				*(out_6 + 6) = o6;
				*(out_6 + 7) = o7;
				out_6 += 8;

				o0 = *(out_7 + 0);
				o1 = *(out_7 + 1);
				o2 = *(out_7 + 2);
				o3 = *(out_7 + 3);
				o4 = *(out_7 + 4);
				o5 = *(out_7 + 5);
				o6 = *(out_7 + 6);
				o7 = *(out_7 + 7);
				o0 += in0_7_0 * in1_0_0;
				o1 += in0_7_0 * in1_0_1;
				o2 += in0_7_0 * in1_0_2;
				o3 += in0_7_0 * in1_0_3;
				o4 += in0_7_0 * in1_0_4;
				o5 += in0_7_0 * in1_0_5;
				o6 += in0_7_0 * in1_0_6;
				o7 += in0_7_0 * in1_0_7;
				o0 += in0_7_1 * in1_1_0;
				o1 += in0_7_1 * in1_1_1;
				o2 += in0_7_1 * in1_1_2;
				o3 += in0_7_1 * in1_1_3;
				o4 += in0_7_1 * in1_1_4;
				o5 += in0_7_1 * in1_1_5;
				o6 += in0_7_1 * in1_1_6;
				o7 += in0_7_1 * in1_1_7;
				*(out_7 + 0) = o0;
				*(out_7 + 1) = o1;
				*(out_7 + 2) = o2;
				*(out_7 + 3) = o3;
				*(out_7 + 4) = o4;
				*(out_7 + 5) = o5;
				*(out_7 + 6) = o6;
				*(out_7 + 7) = o7;
				out_7 += 8;
			}
		}
	}
}

//------------------------------------------------------------------------------
template <class T, class U>
static void __attribute__((noinline)) mmdot_product_4x4x4 (T* _Out, 
																				T* _In0, 
																				T* _In1, 
																				volatile const U m,
																				volatile const U k, 
																				volatile const U n) { 

	register T o0, o1, o2, o3, i0, i1, i2, i3;
	register T in1_0_0, in1_0_1, in1_0_2, in1_0_3; 
	register T in1_1_0, in1_1_1, in1_1_2, in1_1_3; 
	register T in1_2_0, in1_2_1, in1_2_2, in1_2_3; 
	register T in1_3_0, in1_3_1, in1_3_2, in1_3_3; 

	T in0_0_0, in0_0_1, in0_0_2, in0_0_3;
	T in0_1_0, in0_1_1, in0_1_2, in0_1_3;
	T in0_2_0, in0_2_1, in0_2_2, in0_2_3;
	T in0_3_0, in0_3_1, in0_3_2, in0_3_3;

	T *Out_0, *Out_1, *Out_2, *Out_3;
	T *In1_0, *In1_1, *In1_2, *In1_3;

	T *out_0, *out_1, *out_2, *out_3;
	T *in0_0, *in0_1, *in0_2, *in0_3;
	T *in1_0, *in1_1, *in1_2, *in1_3;

	T* Out = _Out;
	T* In0 = _In0;
	T* In1;

	U mdiv = m >> 2;
	U kdiv = k >> 2;
	U ndiv = n >> 2;

	register U h;
	register U i;
	register U j;

	for (h = mdiv; h; h--) {
		Out_0 = Out + n * 0;
		Out_1 = Out + n * 1;
		Out_2 = Out + n * 2;
		Out_3 = Out + n * 3;
		Out += n * 4;

		in0_0 = In0 + k * 0;
		in0_1 = In0 + k * 1;
		in0_2 = In0 + k * 2;
		in0_3 = In0 + k * 3;
		In0 += k * 4;

		In1 = _In1;

		for (i = kdiv; i; i--) {
			out_0 = Out_0;
			out_1 = Out_1;
			out_2 = Out_2;
			out_3 = Out_3;
			in0_0_0 = *(in0_0 + 0);
			in0_0_1 = *(in0_0 + 1);
			in0_0_2 = *(in0_0 + 2);
			in0_0_3 = *(in0_0 + 3);
			in0_0 += 4;
			in0_1_0 = *(in0_1 + 0);
			in0_1_1 = *(in0_1 + 1);
			in0_1_2 = *(in0_1 + 2);
			in0_1_3 = *(in0_1 + 3);
			in0_1 += 4;
			in0_2_0 = *(in0_2 + 0);
			in0_2_1 = *(in0_2 + 1);
			in0_2_2 = *(in0_2 + 2);
			in0_2_3 = *(in0_2 + 3);
			in0_2 += 4;
			in0_3_0 = *(in0_3 + 0);
			in0_3_1 = *(in0_3 + 1);
			in0_3_2 = *(in0_3 + 2);
			in0_3_3 = *(in0_3 + 3);
			in0_3 += 4;
			In1_0 = In1 + n * 0;
			In1_1 = In1 + n * 1;
			In1_2 = In1 + n * 2;
			In1_3 = In1 + n * 3;
			In1 += n * 4;

			for (j = ndiv; j; j--) {
				in1_0_0 = *(In1_0 + 0);
				in1_0_1 = *(In1_0 + 1);
				in1_0_2 = *(In1_0 + 2);
				in1_0_3 = *(In1_0 + 3);
				In1_0 += 4;
				in1_1_0 = *(In1_1 + 0);
				in1_1_1 = *(In1_1 + 1);
				in1_1_2 = *(In1_1 + 2);
				in1_1_3 = *(In1_1 + 3);
				In1_1 += 4;
				in1_2_0 = *(In1_2 + 0);
				in1_2_1 = *(In1_2 + 1);
				in1_2_2 = *(In1_2 + 2);
				in1_2_3 = *(In1_2 + 3);
				In1_2 += 4;
				in1_3_0 = *(In1_3 + 0);
				in1_3_1 = *(In1_3 + 1);
				in1_3_2 = *(In1_3 + 2);
				in1_3_3 = *(In1_3 + 3);
				In1_3 += 4;

				i0 = in0_0_0;
				i1 = in0_0_1;
				i2 = in0_0_2;
				i3 = in0_0_3;
				o0 =  i0 * in1_0_0;
				o1 =  i0 * in1_0_1;
				o2 =  i0 * in1_0_2;
				o3 =  i0 * in1_0_3;
				o0 += i1 * in1_1_0;
				o1 += i1 * in1_1_1;
				o2 += i1 * in1_1_2;
				o3 += i1 * in1_1_3;
				o0 += i2 * in1_2_0;
				o1 += i2 * in1_2_1;
				o2 += i2 * in1_2_2;
				o3 += i2 * in1_2_3;
				o0 += i3 * in1_3_0;
				o1 += i3 * in1_3_1;
				o2 += i3 * in1_3_2;
				o3 += i3 * in1_3_3;
				*(out_0 + 0) += o0;
				*(out_0 + 1) += o1;
				*(out_0 + 2) += o2;
				*(out_0 + 3) += o3;
				out_0 += 4;

				i0 = in0_1_0;
				i1 = in0_1_1;
				i2 = in0_1_2;
				i3 = in0_1_3;
				o0 =  i0 * in1_0_0;
				o1 =  i0 * in1_0_1;
				o2 =  i0 * in1_0_2;
				o3 =  i0 * in1_0_3;
				o0 += i1 * in1_1_0;
				o1 += i1 * in1_1_1;
				o2 += i1 * in1_1_2;
				o3 += i1 * in1_1_3;
				o0 += i2 * in1_2_0;
				o1 += i2 * in1_2_1;
				o2 += i2 * in1_2_2;
				o3 += i2 * in1_2_3;
				o0 += i3 * in1_3_0;
				o1 += i3 * in1_3_1;
				o2 += i3 * in1_3_2;
				o3 += i3 * in1_3_3;
				*(out_1 + 0) += o0;
				*(out_1 + 1) += o1;
				*(out_1 + 2) += o2;
				*(out_1 + 3) += o3;
				out_1 += 4;

				i0 = in0_2_0;
				i1 = in0_2_1;
				i2 = in0_2_2;
				i3 = in0_2_3;
				o0 =  i0 * in1_0_0;
				o1 =  i0 * in1_0_1;
				o2 =  i0 * in1_0_2;
				o3 =  i0 * in1_0_3;
				o0 += i1 * in1_1_0;
				o1 += i1 * in1_1_1;
				o2 += i1 * in1_1_2;
				o3 += i1 * in1_1_3;
				o0 += i2 * in1_2_0;
				o1 += i2 * in1_2_1;
				o2 += i2 * in1_2_2;
				o3 += i2 * in1_2_3;
				o0 += i3 * in1_3_0;
				o1 += i3 * in1_3_1;
				o2 += i3 * in1_3_2;
				o3 += i3 * in1_3_3;
				*(out_2 + 0) += o0;
				*(out_2 + 1) += o1;
				*(out_2 + 2) += o2;
				*(out_2 + 3) += o3;
				out_2 += 4;

				i0 = in0_3_0;
				i1 = in0_3_1;
				i2 = in0_3_2;
				i3 = in0_3_3;
				o0 =  i0 * in1_0_0;
				o1 =  i0 * in1_0_1;
				o2 =  i0 * in1_0_2;
				o3 =  i0 * in1_0_3;
				o0 += i1 * in1_1_0;
				o1 += i1 * in1_1_1;
				o2 += i1 * in1_1_2;
				o3 += i1 * in1_1_3;
				o0 += i2 * in1_2_0;
				o1 += i2 * in1_2_1;
				o2 += i2 * in1_2_2;
				o3 += i2 * in1_2_3;
				o0 += i3 * in1_3_0;
				o1 += i3 * in1_3_1;
				o2 += i3 * in1_3_2;
				o3 += i3 * in1_3_3;
				*(out_3 + 0) += o0;
				*(out_3 + 1) += o1;
				*(out_3 + 2) += o2;
				*(out_3 + 3) += o3;
				out_3 += 4;
			}
		}
	}
}

//------------------------------------------------------------------------------
template <class T, class U>
static void mmdot_product_4x4x8 (T* _Out, 
																				T* _In0, 
																				T* _In1, 
																				volatile const U m,
																				volatile const U k, 
																				volatile const U n) { 

	register T o0, o1, o2, o3, o4, o5, o6, o7;
	T in1_0_0, in1_0_1, in1_0_2, in1_0_3, in1_0_4, in1_0_5, in1_0_6, in1_0_7; 
	T in1_1_0, in1_1_1, in1_1_2, in1_1_3, in1_1_4, in1_1_5, in1_1_6, in1_1_7; 
	T in1_2_0, in1_2_1, in1_2_2, in1_2_3, in1_2_4, in1_2_5, in1_2_6, in1_2_7; 
	T in1_3_0, in1_3_1, in1_3_2, in1_3_3, in1_3_4, in1_3_5, in1_3_6, in1_3_7; 

	T in0_0_0, in0_0_1, in0_0_2, in0_0_3;
	T in0_1_0, in0_1_1, in0_1_2, in0_1_3;
	T in0_2_0, in0_2_1, in0_2_2, in0_2_3;
	T in0_3_0, in0_3_1, in0_3_2, in0_3_3;

	T *Out_0, *Out_1, *Out_2, *Out_3;
	T *In1_0, *In1_1, *In1_2, *In1_3;

	T *out_0, *out_1, *out_2, *out_3;
	T *in0_0, *in0_1, *in0_2, *in0_3;
	T *in1_0, *in1_1, *in1_2, *in1_3;

	T* Out = _Out;
	T* In0 = _In0;
	T* In1;

	U mdiv = m >> 2;
	U kdiv = k >> 2;
	U ndiv = n >> 3;

	register U h;
	register U i;
	register U j;

	for (h = mdiv; h; h--) {
		Out_0 = Out + n * 0;
		Out_1 = Out + n * 1;
		Out_2 = Out + n * 2;
		Out_3 = Out + n * 3;
		Out += n * 4;

		in0_0 = In0 + k * 0;
		in0_1 = In0 + k * 1;
		in0_2 = In0 + k * 2;
		in0_3 = In0 + k * 3;
		In0 += k * 4;

		In1 = _In1;

		for (i = kdiv; i; i--) {
			out_0 = Out_0;
			out_1 = Out_1;
			out_2 = Out_2;
			out_3 = Out_3;
			in0_0_0 = *(in0_0 + 0);
			in0_0_1 = *(in0_0 + 1);
			in0_0_2 = *(in0_0 + 2);
			in0_0_3 = *(in0_0 + 3);
			in0_0 += 4;
			in0_1_0 = *(in0_1 + 0);
			in0_1_1 = *(in0_1 + 1);
			in0_1_2 = *(in0_1 + 2);
			in0_1_3 = *(in0_1 + 3);
			in0_1 += 4;
			in0_2_0 = *(in0_2 + 0);
			in0_2_1 = *(in0_2 + 1);
			in0_2_2 = *(in0_2 + 2);
			in0_2_3 = *(in0_2 + 3);
			in0_2 += 4;
			in0_3_0 = *(in0_3 + 0);
			in0_3_1 = *(in0_3 + 1);
			in0_3_2 = *(in0_3 + 2);
			in0_3_3 = *(in0_3 + 3);
			in0_3 += 4;
			In1_0 = In1 + n * 0;
			In1_1 = In1 + n * 1;
			In1_2 = In1 + n * 2;
			In1_3 = In1 + n * 3;
			In1 += n * 4;

			for (j = ndiv; j; j--) {
				in1_0_0 = *(In1_0 + 0);
				in1_0_1 = *(In1_0 + 1);
				in1_0_2 = *(In1_0 + 2);
				in1_0_3 = *(In1_0 + 3);
				in1_0_4 = *(In1_0 + 4);
				in1_0_5 = *(In1_0 + 5);
				in1_0_6 = *(In1_0 + 6);
				in1_0_7 = *(In1_0 + 7);
				In1_0 += 8;
				in1_1_0 = *(In1_1 + 0);
				in1_1_1 = *(In1_1 + 1);
				in1_1_2 = *(In1_1 + 2);
				in1_1_3 = *(In1_1 + 3);
				in1_1_4 = *(In1_1 + 4);
				in1_1_5 = *(In1_1 + 5);
				in1_1_6 = *(In1_1 + 6);
				in1_1_7 = *(In1_1 + 7);
				In1_1 += 8;
				in1_2_0 = *(In1_2 + 0);
				in1_2_1 = *(In1_2 + 1);
				in1_2_2 = *(In1_2 + 2);
				in1_2_3 = *(In1_2 + 3);
				in1_2_4 = *(In1_2 + 4);
				in1_2_5 = *(In1_2 + 5);
				in1_2_6 = *(In1_2 + 6);
				in1_2_7 = *(In1_2 + 7);
				In1_2 += 8;
				in1_3_0 = *(In1_3 + 0);
				in1_3_1 = *(In1_3 + 1);
				in1_3_2 = *(In1_3 + 2);
				in1_3_3 = *(In1_3 + 3);
				in1_3_4 = *(In1_3 + 4);
				in1_3_5 = *(In1_3 + 5);
				in1_3_6 = *(In1_3 + 6);
				in1_3_7 = *(In1_3 + 7);
				In1_3 += 8;

				o0  = in0_0_0 * in1_0_0;
				o1  = in0_0_0 * in1_0_1;
				o2  = in0_0_0 * in1_0_2;
				o3  = in0_0_0 * in1_0_3;
				o4  = in0_0_0 * in1_0_4;
				o5  = in0_0_0 * in1_0_5;
				o6  = in0_0_0 * in1_0_6;
				o7  = in0_0_0 * in1_0_7;
				o0 += in0_0_1 * in1_1_0;
				o1 += in0_0_1 * in1_1_1;
				o2 += in0_0_1 * in1_1_2;
				o3 += in0_0_1 * in1_1_3;
				o4 += in0_0_1 * in1_1_4;
				o5 += in0_0_1 * in1_1_5;
				o6 += in0_0_1 * in1_1_6;
				o7 += in0_0_1 * in1_1_7;
				o0 += in0_0_2 * in1_2_0;
				o1 += in0_0_2 * in1_2_1;
				o2 += in0_0_2 * in1_2_2;
				o3 += in0_0_2 * in1_2_3;
				o4 += in0_0_2 * in1_2_4;
				o5 += in0_0_2 * in1_2_5;
				o6 += in0_0_2 * in1_2_6;
				o7 += in0_0_2 * in1_2_7;
				o0 += in0_0_3 * in1_3_0;
				o1 += in0_0_3 * in1_3_1;
				o2 += in0_0_3 * in1_3_2;
				o3 += in0_0_3 * in1_3_3;
				o4 += in0_0_3 * in1_3_4;
				o5 += in0_0_3 * in1_3_5;
				o6 += in0_0_3 * in1_3_6;
				o7 += in0_0_3 * in1_3_7;
				*(out_0 + 0) += o0;
				*(out_0 + 1) += o1;
				*(out_0 + 2) += o2;
				*(out_0 + 3) += o3;
				*(out_0 + 4) += o4;
				*(out_0 + 5) += o5;
				*(out_0 + 6) += o6;
				*(out_0 + 7) += o7;
				out_0 += 8;

				o0  = in0_1_0 * in1_0_0;
				o1  = in0_1_0 * in1_0_1;
				o2  = in0_1_0 * in1_0_2;
				o3  = in0_1_0 * in1_0_3;
				o4  = in0_1_0 * in1_0_4;
				o5  = in0_1_0 * in1_0_5;
				o6  = in0_1_0 * in1_0_6;
				o7  = in0_1_0 * in1_0_7;
				o0 += in0_1_1 * in1_1_0;
				o1 += in0_1_1 * in1_1_1;
				o2 += in0_1_1 * in1_1_2;
				o3 += in0_1_1 * in1_1_3;
				o4 += in0_1_1 * in1_1_4;
				o5 += in0_1_1 * in1_1_5;
				o6 += in0_1_1 * in1_1_6;
				o7 += in0_1_1 * in1_1_7;
				o0 += in0_1_2 * in1_2_0;
				o1 += in0_1_2 * in1_2_1;
				o2 += in0_1_2 * in1_2_2;
				o3 += in0_1_2 * in1_2_3;
				o4 += in0_1_2 * in1_2_4;
				o5 += in0_1_2 * in1_2_5;
				o6 += in0_1_2 * in1_2_6;
				o7 += in0_1_2 * in1_2_7;
				o0 += in0_1_3 * in1_3_0;
				o1 += in0_1_3 * in1_3_1;
				o2 += in0_1_3 * in1_3_2;
				o3 += in0_1_3 * in1_3_3;
				o4 += in0_1_3 * in1_3_4;
				o5 += in0_1_3 * in1_3_5;
				o6 += in0_1_3 * in1_3_6;
				o7 += in0_1_3 * in1_3_7;
				*(out_1 + 0) += o0;
				*(out_1 + 1) += o1;
				*(out_1 + 2) += o2;
				*(out_1 + 3) += o3;
				*(out_1 + 4) += o4;
				*(out_1 + 5) += o5;
				*(out_1 + 6) += o6;
				*(out_1 + 7) += o7;
				out_1 += 8;

				o0  = in0_2_0 * in1_0_0;
				o1  = in0_2_0 * in1_0_1;
				o2  = in0_2_0 * in1_0_2;
				o3  = in0_2_0 * in1_0_3;
				o4  = in0_2_0 * in1_0_4;
				o5  = in0_2_0 * in1_0_5;
				o6  = in0_2_0 * in1_0_6;
				o7  = in0_2_0 * in1_0_7;
				o0 += in0_2_1 * in1_1_0;
				o1 += in0_2_1 * in1_1_1;
				o2 += in0_2_1 * in1_1_2;
				o3 += in0_2_1 * in1_1_3;
				o4 += in0_2_1 * in1_1_4;
				o5 += in0_2_1 * in1_1_5;
				o6 += in0_2_1 * in1_1_6;
				o7 += in0_2_1 * in1_1_7;
				o0 += in0_2_2 * in1_2_0;
				o1 += in0_2_2 * in1_2_1;
				o2 += in0_2_2 * in1_2_2;
				o3 += in0_2_2 * in1_2_3;
				o4 += in0_2_2 * in1_2_4;
				o5 += in0_2_2 * in1_2_5;
				o6 += in0_2_2 * in1_2_6;
				o7 += in0_2_2 * in1_2_7;
				o0 += in0_2_3 * in1_3_0;
				o1 += in0_2_3 * in1_3_1;
				o2 += in0_2_3 * in1_3_2;
				o3 += in0_2_3 * in1_3_3;
				o4 += in0_2_3 * in1_3_4;
				o5 += in0_2_3 * in1_3_5;
				o6 += in0_2_3 * in1_3_6;
				o7 += in0_2_3 * in1_3_7;
				*(out_2 + 0) += o0;
				*(out_2 + 1) += o1;
				*(out_2 + 2) += o2;
				*(out_2 + 3) += o3;
				*(out_2 + 4) += o4;
				*(out_2 + 5) += o5;
				*(out_2 + 6) += o6;
				*(out_2 + 7) += o7;
				out_2 += 8;

				o0  = in0_3_0 * in1_0_0;
				o1  = in0_3_0 * in1_0_1;
				o2  = in0_3_0 * in1_0_2;
				o3  = in0_3_0 * in1_0_3;
				o4  = in0_3_0 * in1_0_4;
				o5  = in0_3_0 * in1_0_5;
				o6  = in0_3_0 * in1_0_6;
				o7  = in0_3_0 * in1_0_7;
				o0 += in0_3_1 * in1_1_0;
				o1 += in0_3_1 * in1_1_1;
				o2 += in0_3_1 * in1_1_2;
				o3 += in0_3_1 * in1_1_3;
				o4 += in0_3_1 * in1_1_4;
				o5 += in0_3_1 * in1_1_5;
				o6 += in0_3_1 * in1_1_6;
				o7 += in0_3_1 * in1_1_7;
				o0 += in0_3_2 * in1_2_0;
				o1 += in0_3_2 * in1_2_1;
				o2 += in0_3_2 * in1_2_2;
				o3 += in0_3_2 * in1_2_3;
				o4 += in0_3_2 * in1_2_4;
				o5 += in0_3_2 * in1_2_5;
				o6 += in0_3_2 * in1_2_6;
				o7 += in0_3_2 * in1_2_7;
				o0 += in0_3_3 * in1_3_0;
				o1 += in0_3_3 * in1_3_1;
				o2 += in0_3_3 * in1_3_2;
				o3 += in0_3_3 * in1_3_3;
				o4 += in0_3_3 * in1_3_4;
				o5 += in0_3_3 * in1_3_5;
				o6 += in0_3_3 * in1_3_6;
				o7 += in0_3_3 * in1_3_7;
				*(out_3 + 0) += o0;
				*(out_3 + 1) += o1;
				*(out_3 + 2) += o2;
				*(out_3 + 3) += o3;
				*(out_3 + 4) += o4;
				*(out_3 + 5) += o5;
				*(out_3 + 6) += o6;
				*(out_3 + 7) += o7;
				out_3 += 8;
			}
		}
	}
}
//------------------------------------------------------------------------------
template <class T, class U>
static inline void mmdot_product_64x64 (T* _Out, 
																				T* _In0, 
																				T* _In1, 
																				volatile const U m,
																				volatile const U k, 
																			  volatile const U n) { 
// A possible vmdot read cache scheme (for thread-safety do not cache Out):
// Fast: In0 (8x64x2)    , In1T (64x8)       - 12288
// Slow: In0 ([_8x8x64x2), In1T (64x[8x_8]) - 98304
// Shared: In1
	double _cache[12544];
	T* cache = _cache + nextAlignedInd((T*)_cache, 256);
	T *Out, *_out, *out;
	T *In0, *_in0, *in0;
	T *In1, *_in1, *in1;

	U f, g, h, i, j; 
	U m6. k6, n6;
	U m3, k3, n3;
	U m0, k0, n0;
	m6 = m >> 6;
	k6 = k >> 6;
	n6 = n >> 6;
	m3 = m6 << 3;
	k3 = k6 << 3;
	n3 = n6 << 3;

	cacher<T, U> Cacher = cacher(cache, (U)2);
	_in0 = Cacher.setUnit((U)0, (U)64, (U)64, (U)2);
	_in1 = Cacher.setUnit((U)1, (U)64, (U)64, (U)1);

	In0 = _In0;
	Out = _Out;

	for (e = m6; e; e--) {
		Cacher.prefetch((U)0, (U)1, (U)2);
		Cacher.cpyToUnit((U)0, In0, k, (U)1);
		In0 += (U)8192;
		for (f = (U)0; f < (U)8192; f += (U)1024) {
			in0 = _in0;
			In1 = _In1;
			Cacher.prefetch(U)0, (U)0, (U)3, f, f+(U)1024);
			_out = Out;
			Out += (U)64 * n;
			for (g = n6; g; g--) {
				Cacher.prefetch((U)1, (U)1, (U)2);
				Cacher.cpyToUnit((U)1, (U)1, n, (U)1);
				In1 += (U)4096;
				for (h = (U)0; h < (U)4096; h += (U)512) {
					in1 = _in1;
					Cacher.prefetch((U)1, (U)0, (U)3, h, h+(U)512);
					out = _out;
					_out += (U)64;
					for (i = (U)8; i; i--) {
						for (j = (U)8; j; j--) {

						}
					}
				}
			}
		}
	}
}

//------------------------------------------------------------------------------
#endif

