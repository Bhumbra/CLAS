// This header is a deprecated legacy inclusion and will soon be deleted.

# ifndef _replicate_txx
# define _replicate_txx
//------------------------------------------------------------------------------
# include "_replicate_1.txx"

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
			return replicate_1(O0, m, n, I0, oS, iS, Os, Is, U1);
		}
		case 4: {
			return replicate_1(O0, m, n, I0, oS, iS, Os, Is, U1);
		}
		default: {
			return replicate_1(O0, m, n, I0, oS, iS, Os, Is, U1);
		}
	}
}

//------------------------------------------------------------------------------
# endif
