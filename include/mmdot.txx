//------------------------------------------------------------------------------
// Multi-threaded mmdot matrix-matrix dot product class
//------------------------------------------------------------------------------
# ifndef mmdot_txx
# define mmdot_txx

//------------------------------------------------------------------------------
# include "tmmdot.txx"
//------------------------------------------------------------------------------
# ifndef DO_NOT_PREFETCH
# define THIS_PREF(NUM_THREADS) this -> pref(NUM_THREADS)
# else
# define THIS_PREF(NUM_THREADS) NUM_THREADS
# endif
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
template <class T, class U>
class mmdot: public tmmdot<T, U> {
	public:
		mmdot<T, U>();
		mmdot(		T* _OP, T* _I0 = (T*)0, T* _I1 = (T*)0,
							U _M = (U)0, U _K = (U)0, U _N = (U)0,
							bool _OPT = false, bool _I0T = false, bool _I1T = false, 
							bool _ColM = false, T* _I2 = (T*)0, U _MT = (U)0, T _FT = (T)1., 
							U _D = (U)0, U _R = (U)0, U _A = (U)0);
		~mmdot<T, U>();
		void init(T* _OP = (T*)0 , T* _I0 = (T*)0, T* _I1 = (T*)0,
							U _M = (U)0, U _K = (U)0, U _N = (U)0,
							bool _OPT = false, bool _I0T = false, bool _I1T = false, 
							bool _ColM = false, T* _I2 = (T*)0, U _MT = (U)0, T _FT = (T)1., 
							U _D = (U)0, U _R = (U)0, U _A = (U)0);
		void pref(U Nt);
		void exec();
	protected:
		void setThr(U _MT = (U)0, T _FT = (T)1.);
		tmmdot<T, U>* Tmmdot;
		U* T_load;
	private:
		U PCPT; // Pooled cache per thread
		U NT;
};

//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
template <class T, class U>
mmdot<T, U>::mmdot() {
	this -> PCPT = 1048576; 
	U Nt = std::thread::hardware_concurrency();
	this -> T_load = new U[Nt];
	this -> Tmmdot = new tmmdot<T, U>[Nt];
	this -> cacher.init((T*)this -> cache, (U)2);
	this -> setAln();
	this -> init();
}

//---------------------------------------------------------------------------
template <class T, class U>
mmdot<T, U>::mmdot( T* _OP, T* _I0, T* _I1, U _M, U _K, U _N,
										bool _OPT, bool _I0T, bool _I1T,  bool _ColM, 
										T* _I2, U _MT, T _FT, U _D, U _R, U _A) {
	this -> init(	_OP, _I0, _I1, _M, _K, _N, _OPT, _I0T, _I1T, _ColM, 
								_I2, _MT, _FT, _D, _R, _A);
}

//---------------------------------------------------------------------------
template <class T, class U>
mmdot<T, U>::~mmdot() {
	this -> init();
	delete[] this -> T_load;
	delete[] this -> Tmmdot;
}

//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
template <class T, class U>
void mmdot<T, U>::init (T* _OP, T* _I0, T* _I1, U _M, U _K, U _N,
												bool _OPT, bool _I0T, bool _I1T,  bool _ColM, 
												T* _I2, U _MT, T _FT, U _D, U _R, U _A) {
	this -> setPtr(_OP, _I0, _I1, _I2);
	if (!this -> OP) {return;}
	this -> setDim(_M, _K, _N);
	this -> setCmj(_OPT, _I0T, _I1T, _ColM);
	this -> setDRA(_D, _R, _A);
	this -> setThr(_MT, _FT);
}

//---------------------------------------------------------------------------
template <class T, class U>
void mmdot<T, U>::setThr(U _MT, T _FT) {
	this -> NT = set_max_threads(_MT, _FT);
}

//---------------------------------------------------------------------------
template <class T, class U>
void mmdot<T, U>::pref(U Nt) {
	// Prefetches to pooled cache over Nt threads
	U i, d, mk, kn, k0, k1, pc;
	T *in0, *in1, *In0, *In1;
	mk = this -> m * this -> k;
	kn = this -> k * this -> n;
	in0 = this -> i0;
	in1 = this -> i1;
	In0 = in0 + mk;
	In1 = in1 + kn;

	d = (U)64/this -> sizeofT;
	pc = (this -> PCPT * Nt) / this -> sizeofT;

	if ( (In1-in1) + (In0-in0) <= pc) {
		for (; in0 < In0; in0 += d) {
			PREFETCH_READ_0(in0);
		}
		for (; in1 < In1; in1 += d) {
			PREFETCH_READ_0(in1);
		}
		return;
	}

	pc /= 2; 
	if (mk > pc) {mk = pc;}
	if (kn > pc) {kn = pc;}
	In0 = in0 + mk;
	In1 = in1 + kn;
	for (; in0 < In0; in0 += d) {
		PREFETCH_READ_0(in0);
	}
	for (; in1 < In1; in1 += d) {
		PREFETCH_READ_0(in1);
	}

}
//---------------------------------------------------------------------------
template <class T, class U>
void mmdot<T, U>::exec() {
	U mkn, d, g, G, Nt, R, r;

	// If no threads, run execution from thread-blind class thread-blind 
	if (!this -> NT) {
		tmmdot<T, U>::exec();
		return;
	}

	mkn = this -> m * this -> k * this -> n;
	if (this -> m >= this -> n) {
		R = this -> m;
		r = this -> n;
	}
	else {
		R = this -> n;
		r = this -> m;
	}
	if ((r <= 4 && R <= 32) || mkn <= 524288) {
		tmmdot<T, U>::exec();
		return;
	}
	G = (U)64;
	R = r;
	if (mkn >= 2097152) {
		while (G*G > R) {
			G >>= 1;
		}
	}
	else {
		while (G > R || ( G*G*G << 6) >= mkn) {
			G >>= 1;
		}
	}

	r = R >> 1;
	g = G > 4 ? G >> 1 : (U)4;

	if (G < 4) {
		g = G;
	}
	else if (G < R && G > r) {
		G = r + R % 2;
	}
	else if (G > 4) {
		r = G + g;
		d = R % G;
		if ( (d && d <= G >> 1) && d < R % (G + g) ) {
			G += g;
		}
		if (g < 3)  {g = 4;}
	}

	Nt = set_thread_load(this -> T_load, this -> m, this -> NT, G, g);

	THIS_PREF(Nt);

	/* // A thread-free version
	for (d = 0, G = 0; d<Nt; d++, G += g) {
		g = this -> T_load[d];
	
		this -> Tmmdot[d].init   (this -> op + G * this -> opS,
															this -> i0 + G * this -> i0S,
															this -> i1, g, 
															this -> k, this -> n, 
															false, this -> i0c,
															this -> i1c, false,
															this -> i2 + G * this -> i2S,
															this -> D, this -> R, this -> A);
		this -> Tmmdot[d].setStr (this -> n, this -> i0S,
															this -> i1S, this -> i2S,
															(U)1, this -> i0s, 
															this -> i1s, this -> i2s);
	}
	for (d = 0, G = 0; d<Nt; d++, G += g) {
		// this -> Tmmdot[d].nop();
		this -> Tmmdot[d].exec();
	}
  */

	///* // Threaded version
	for (d = 0, G = 0; d<Nt; d++, G += g) {
		g = this -> T_load[d];
		this -> Tmmdot[d].init   (this -> op + G * this -> opS,
															this -> i0 + G * this -> i0S,
															this -> i1, g, 
															this -> k, this -> n, 
															false, this -> i0c,
															this -> i1c, false,
															this -> i2 + G * this -> i2S,
															this -> D, this -> R, this -> A);
		this -> Tmmdot[d].setStr (this -> n, this -> i0S,
															this -> i1S, this -> i2S,
															(U)1, this -> i0s, 
															this -> i1s, this -> i2s);
		this -> Tmmdot[d].Thread = std::thread(&tmmdot<T,U>::exec, &this -> Tmmdot[d]);
		//this -> Tmmdot[d].Thread = std::thread(&tmmdot<T,U>::nop, &this -> Tmmdot[d]);
	}
	for (d = 0; d<Nt; d++) {
		this -> Tmmdot[d].Thread.join();
	}
	//*/
}

//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------

template <class T, class U>
static inline void mmdot_product (T* OP, 
																	T* I0, 
																	T* I1, 
																	U m, 
																	U k,
																	U n,
																	bool OPT = false,
																	bool I0T = false,
																	bool I1T = false,
																	bool Cmj = false,
																	T* I2 = (T*)0,
																	U Nt = (U)0,
																	T Ft = 0.,
																	U D = (U)0,
																	U R = (U)0,
																	U A = (U)0) {
	mmdot<T, U> Mmdot;
  Mmdot.init (OP, I0, I1, m, k, n, OPT, I0T, I1T, Cmj, I2, Nt, Ft, D, R, A); 
  Mmdot.exec();
}

//------------------------------------------------------------------------------
# endif

