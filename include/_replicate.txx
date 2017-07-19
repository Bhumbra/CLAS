# ifndef _replicate_txx
# define _replicate_txx
//------------------------------------------------------------------------------
# include "_replicate_1.txx"
# include "_replicate_2.txx"
# include "_replicate_4.txx"
# include "_replicate_8.txx"

//------------------------------------------------------------------------------
template <class T, class U>
static inline void replicate_1 (T* O0, 
																volatile const U m,
																volatile const U n,
																T* I0 = 0,
																volatile const U oS = 1,
																volatile const U iS = 0,
																volatile const U Os = 1,
																volatile const U Is = 0,
																volatile U U1 = 0) { 
	if (O0 == I0) {return;}
	U h = m;
	switch (U1) {
		case 1: {
			for (; h; h--) {
				replicate_1x1 (O0, n, I0, Os, Is);
				O0 += oS;
				I0 += iS;
			}
			return;
		}
		case 2: {
			for (; h; h--) {
				replicate_1x2 (O0, n, I0, Os, Is);
				O0 += oS;
				I0 += iS;
			}
			return;
		}
		case 4: {
			for (; h; h--) {
				replicate_1x4 (O0, n, I0, Os, Is);
				O0 += oS;
				I0 += iS;
			}
			return;
		}
		case 8: {
			for (; h; h--) {
				replicate_1x8 (O0, n, I0, Os, Is);
				O0 += oS;
				I0 += iS;
			}
			return;
		}
		case 16: {
			for (; h; h--) {
				replicate_1x16(O0, n, I0, Os, Is);
				O0 += oS;
				I0 += iS;
			}
			return;
		}
		default: {
			for (; h; h--) {
				replicate_1x32(O0, n, I0, Os, Is);
				O0 += oS;
				I0 += iS;
			}
			return;
		}
	}
}

//------------------------------------------------------------------------------
template <class T, class U>
static inline void replicate_2 (T* O0, 
																volatile const U m,
																volatile const U n,
																T* I0 = 0,
																volatile const U oS = 1,
																volatile const U iS = 0,
																volatile const U Os = 1,
																volatile const U Is = 0,
																volatile U U1 = 0) { 

	if (O0 == I0) {return;}
	U h = m >> 1;
	U mod = m & 1;
	switch (U1) {
		case 1: {
			for (; h; h--) {
				replicate_2x1 (O0, n, I0, oS, iS, Os, Is);
				O0 += oS * 2;
				I0 += iS * 2;
			}
			if (mod) {
				replicate_1x1 (O0, n, I0, Os, Is);
				O0 += oS;
				I0 += iS;
			}
			return;
		}
		case 2: {
			for (; h; h--) {
				replicate_2x2 (O0, n, I0, oS, iS, Os, Is);
				O0 += oS * 2;
				I0 += iS * 2;
			}
			if (mod) {
				replicate_1x2 (O0, n, I0, Os, Is);
				O0 += oS;
				I0 += iS;
			}
			return;
		}
		case 4: {
			for (; h; h--) {
				replicate_2x4 (O0, n, I0, oS, iS, Os, Is);
				O0 += oS * 2;
				I0 += iS * 2;
			}
			if (mod) {
				replicate_1x4 (O0, n, I0, Os, Is);
				O0 += oS;
				I0 += iS;
			}
			return;
		}
		case 8: {
			for (; h; h--) {
				replicate_2x8 (O0, n, I0, oS, iS, Os, Is);
				O0 += oS * 2;
				I0 += iS * 2;
			}
			if (mod) {
				replicate_1x8 (O0, n, I0, Os, Is);
				O0 += oS;
				I0 += iS;
			}
			return;
		}
		case 16: {
			for (; h; h--) {
				replicate_2x16(O0, n, I0, oS, iS, Os, Is);
				O0 += oS * 2;
				I0 += iS * 2;
			}
			if (mod) {
				replicate_1x16(O0, n, I0, Os, Is);
				O0 += oS;
				I0 += iS;
			}
			return;
		}
		default: {
			for (; h; h--) {
				replicate_2x32(O0, n, I0, oS, iS, Os, Is);
				O0 += oS * 2;
				I0 += iS * 2;
			}
			if (mod) {
				replicate_1x32(O0, n, I0, Os, Is);
				O0 += oS;
				I0 += iS;
			}
			return;
		}
	}
}

//------------------------------------------------------------------------------
template <class T, class U>
static inline void replicate_4 (T* O0, 
																volatile const U m,
																volatile const U n,
																T* I0 = 0,
																volatile const U oS = 1,
																volatile const U iS = 0,
																volatile const U Os = 1,
																volatile const U Is = 0,
																volatile U U1 = 0) { 

	if (O0 == I0) {return;}
	U h = m >> 2;
	U mod = m & 3;
	switch (U1) {
		case 1: {
			for (; h; h--) {
				replicate_4x1 (O0, n, I0, oS, iS, Os, Is);
				O0 += oS * 4;
				I0 += iS * 4;
			}
			if (mod > 1) {
				replicate_2x1 (O0, n, I0, oS, iS, Os, Is);
				O0 += oS * 2;
				I0 += iS * 2;
				mod &= 1;
			}
			if (mod) {
				replicate_1x1 (O0, n, I0, Os, Is);
				O0 += oS;
				I0 += iS;
			}
			return;
		}
		case 2: {
			for (; h; h--) {
				replicate_4x2 (O0, n, I0, oS, iS, Os, Is);
				O0 += oS * 4;
				I0 += iS * 4;
			}
			if (mod > 1) {
				replicate_2x2 (O0, n, I0, oS, iS, Os, Is);
				O0 += oS * 2;
				I0 += iS * 2;
				mod &= 1;
			}
			if (mod) {
				replicate_1x2 (O0, n, I0, Os, Is);
				O0 += oS;
				I0 += iS;
			}
			return;
		}
		case 4: {
			for (; h; h--) {
				replicate_4x4 (O0, n, I0, oS, iS, Os, Is);
				O0 += oS * 4;
				I0 += iS * 4;
			}
			if (mod > 1) {
				replicate_2x4 (O0, n, I0, oS, iS, Os, Is);
				O0 += oS * 2;
				I0 += iS * 2;
				mod &= 1;
			}
			if (mod) {
				replicate_1x4 (O0, n, I0, Os, Is);
				O0 += oS;
				I0 += iS;
			}
			return;
		}
		case 8: {
			for (; h; h--) {
				replicate_4x8 (O0, n, I0, oS, iS, Os, Is);
				O0 += oS * 4;
				I0 += iS * 4;
			}
			if (mod > 1) {
				replicate_2x8 (O0, n, I0, oS, iS, Os, Is);
				O0 += oS * 2;
				I0 += iS * 2;
				mod &= 1;
			}
			if (mod) {
				replicate_1x8 (O0, n, I0, Os, Is);
				O0 += oS;
				I0 += iS;
			}
			return;
		}
		case 16: {
			for (; h; h--) {
				replicate_4x16(O0, n, I0, oS, iS, Os, Is);
				O0 += oS * 4;
				I0 += iS * 4;
			}
			if (mod > 1) {
				replicate_2x16(O0, n, I0, oS, iS, Os, Is);
				O0 += oS * 2;
				I0 += iS * 2;
				mod &= 1;
			}
			if (mod) {
				replicate_1x16(O0, n, I0, Os, Is);
				O0 += oS;
				I0 += iS;
			}
			return;
		}
		default: {
			for (; h; h--) {
				replicate_4x32(O0, n, I0, oS, iS, Os, Is);
				O0 += oS * 4;
				I0 += iS * 4;
			}
			if (mod > 1) {
				replicate_2x32(O0, n, I0, oS, iS, Os, Is);
				O0 += oS * 2;
				I0 += iS * 2;
				mod &= 1;
			}
			if (mod) {
				replicate_1x32(O0, n, I0, Os, Is);
				O0 += oS;
				I0 += iS;
			}
			return;
		}
	}
}

//------------------------------------------------------------------------------
template <class T, class U>
static inline void replicate_8 (T* O0, 
																volatile const U m,
																volatile const U n,
																T* I0 = 0,
																volatile const U oS = 1,
																volatile const U iS = 0,
																volatile const U Os = 1,
																volatile const U Is = 0,
																volatile U U1 = 0) { 

	if (O0 == I0) {return;}
	U h = m >> 3;
	U mod = m & 7;
	switch (U1) {
		case 1: {
			for (; h; h--) {
				replicate_8x1 (O0, n, I0, oS, iS, Os, Is);
				O0 += oS * 8;
				I0 += iS * 8;
			}
			if (mod > 3) {
				replicate_4x1 (O0, n, I0, oS, iS, Os, Is);
				O0 += oS * 4;
				I0 += iS * 4;
				mod &= 3;
			}
			if (mod > 1) {
				replicate_2x1 (O0, n, I0, oS, iS, Os, Is);
				O0 += oS * 2;
				I0 += iS * 2;
				mod &= 1;
			}
			if (mod) {
				replicate_1x1 (O0, n, I0, Os, Is);
				O0 += oS;
				I0 += iS;
			}
			return;
		}
		case 2: {
			for (; h; h--) {
				replicate_8x2 (O0, n, I0, oS, iS, Os, Is);
				O0 += oS * 8;
				I0 += iS * 8;
			}
			if (mod > 3) {
				replicate_4x2 (O0, n, I0, oS, iS, Os, Is);
				O0 += oS * 4;
				I0 += iS * 4;
				mod &= 3;
			}
			if (mod > 1) {
				replicate_2x2 (O0, n, I0, oS, iS, Os, Is);
				O0 += oS * 2;
				I0 += iS * 2;
				mod &= 1;
			}
			if (mod) {
				replicate_1x2 (O0, n, I0, Os, Is);
				O0 += oS;
				I0 += iS;
			}
			return;
		}
		case 4: {
			for (; h; h--) {
				replicate_8x4 (O0, n, I0, oS, iS, Os, Is);
				O0 += oS * 8;
				I0 += iS * 8;
			}
			if (mod > 3) {
				replicate_4x4 (O0, n, I0, oS, iS, Os, Is);
				O0 += oS * 4;
				I0 += iS * 4;
				mod &= 3;
			}
			if (mod > 1) {
				replicate_2x4 (O0, n, I0, oS, iS, Os, Is);
				O0 += oS * 2;
				I0 += iS * 2;
				mod &= 1;
			}
			if (mod) {
				replicate_1x4 (O0, n, I0, Os, Is);
				O0 += oS;
				I0 += iS;
			}
			return;
		}
		case 8: {
			for (; h; h--) {
				replicate_8x8 (O0, n, I0, oS, iS, Os, Is);
				O0 += oS * 8;
				I0 += iS * 8;
			}
			if (mod > 3) {
				replicate_4x8 (O0, n, I0, oS, iS, Os, Is);
				O0 += oS * 4;
				I0 += iS * 4;
				mod &= 3;
			}
			if (mod > 1) {
				replicate_2x8 (O0, n, I0, oS, iS, Os, Is);
				O0 += oS * 2;
				I0 += iS * 2;
				mod &= 1;
			}
			if (mod) {
				replicate_1x8 (O0, n, I0, Os, Is);
				O0 += oS;
				I0 += iS;
			}
			return;
		}
		case 16: {
			for (; h; h--) {
				replicate_8x16(O0, n, I0, oS, iS, Os, Is);
				O0 += oS * 8;
				I0 += iS * 8;
			}
			if (mod > 3) {
				replicate_4x16(O0, n, I0, oS, iS, Os, Is);
				O0 += oS * 4;
				I0 += iS * 4;
				mod &= 3;
			}
			if (mod > 1) {
				replicate_2x16(O0, n, I0, oS, iS, Os, Is);
				O0 += oS * 2;
				I0 += iS * 2;
				mod &= 1;
			}
			if (mod) {
				replicate_1x16(O0, n, I0, Os, Is);
				O0 += oS;
				I0 += iS;
			}
			return;
		}
		default: {
			for (; h; h--) {
				replicate_8x32(O0, n, I0, oS, iS, Os, Is);
				O0 += oS * 8;
				I0 += iS * 8;
			}
			if (mod > 3) {
				replicate_4x32(O0, n, I0, oS, iS, Os, Is);
				O0 += oS * 4;
				I0 += iS * 4;
				mod &= 3;
			}
			if (mod > 1) {
				replicate_2x32(O0, n, I0, oS, iS, Os, Is);
				O0 += oS * 2;
				I0 += iS * 2;
				mod &= 1;
			}
			if (mod) {
				replicate_1x32(O0, n, I0, Os, Is);
				O0 += oS;
				I0 += iS;
			}
			return;
		}
	}
}

//------------------------------------------------------------------------------
template <class T, class U>
static inline void replicate_0 (T* O0, 
																volatile const U m,
																volatile const U n,
																T* I0 = 0,
																volatile const U oS = 1,
																volatile const U iS = 0,
																volatile const U Os = 1,
																volatile const U Is = 0,
																volatile U U0 = 0,
																volatile U U1 = 0) { 
	switch (U0) {
		case 1: {
			return replicate_1(O0, m, n, I0, oS, iS, Os, Is, U1);
		}
		case 2: {
			return replicate_2(O0, m, n, I0, oS, iS, Os, Is, U1);
		}
		case 4: {
			return replicate_4(O0, m, n, I0, oS, iS, Os, Is, U1);
		}
		default: {
			return replicate_8(O0, m, n, I0, oS, iS, Os, Is, U1);
		}
	}
}

//------------------------------------------------------------------------------
# endif
