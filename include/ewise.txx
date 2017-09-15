//------------------------------------------------------------------------------
// Multi-threaded ewise dot product class
//------------------------------------------------------------------------------
# ifndef ewise_txx
# define ewise_txx

//------------------------------------------------------------------------------
# include "tewise.txx"
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
template <class T, class U>
class ewise : public tewise<T, U> {
	public:
		ewise<T, U>();
		ewise    (T* _OP, T* _I0 = (T*)0, T* _I1 = (T*)0,
							U _M = (U)0, U _K = (U)0, U _P = (U)0, U _Q = (U)0,
							bool _I0C = false, bool _I1B = false, T* _I2 = (T*)0, 
							U _NT = (U)0, T _FT = (T)1., 
							U _D = (U)0, U _R = (U)0, U _A = (U)0);
		~ewise<T, U>();
		void init(T* _OP = (T*)0, T* _I0 = (T*)0, T* _I1 = (T*)0,
							U _M = (U)0, U _K = (U)0, U _P = (U)0, U _Q = (U)0,
							bool _I0C = false, bool _I1B = false, T* _I2 = (T*)0, 
							U _NT = (U)0, T _FT = (T)1., 
							U _D = (U)0, U _R = (U)0, U _A = (U)0);
		void exec();
	protected:
		void setThr(U _MT = (U)0, T _FT = (T)1.);
		tewise<T, U>* Tewise;
		U* T_load;
	private:
		U NT;
};

//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
template <class T, class U>
ewise<T, U>::ewise() {
	U Nt = std::thread::hardware_concurrency();
	this -> T_load = new U[Nt];
	this -> Tewise = new tewise<T, U>[Nt];
	this -> init();
}

//---------------------------------------------------------------------------
template <class T, class U>
ewise<T, U>::ewise (T* _OP, T* _I0, T* _I1, U _M, U _K, U _P, U _Q,
										bool _I0C, bool _I1B, T* _I2, U _MT, T _FT, 
										U _D, U _R, U _A) {
	this -> init(	_OP, _I0, _I1, _M, _K, _P, _Q,
								_I0C, _I1B, _I2, _MT, _FT, _D, _R, _A);
}

//---------------------------------------------------------------------------
template <class T, class U>
ewise<T, U>::~ewise() {
	this -> init();
	delete[] this -> T_load;
	delete[] this -> Tewise;
}

//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
template <class T, class U>
void ewise<T, U>::init (T* _OP, T* _I0, T* _I1, U _M, U _K, U _P, U _Q,
												bool _I0C, bool _I1B, T* _I2, U _MT, T _FT, 
												U _D, U _R, U _A) {
	this -> setPtr(_OP, _I0, _I1, _I2);
	if (!this -> op) {return;}
	this -> setDim(_M, _K, _P, _Q);
	this -> setTra(_I0C, _I1B);
	this -> setDRA(_D, _R, _A);
	this -> setThr(_MT, _FT);
}

//---------------------------------------------------------------------------
template <class T, class U>
void ewise<T, U>::setThr(U _MT, T _FT) {
	this -> NT = set_max_threads(_MT, _FT);
}

//---------------------------------------------------------------------------
template <class T, class U>
void ewise<T, U>::exec() {
	bool unitp, unitm;
	U d, g, G, Nt, M, P, Q;
	U N, outs, in0s, in1s, in2s, _p, _m;

	// If no threads, run execution from thread-blind class thread-blind 
	if (!this -> NT) {
		tewise<T, U>::exec();
		return;
	}
	if (this -> p * this -> m * this -> q * this -> k < 262144) {
		tewise<T, U>::exec();
		return;
	}

	unitp = this -> p == 1;
	unitm = unitp && this -> m == 1;

	P = this -> p;
	M = this -> m;
	Q = this -> q;

	if (!unitp) {
		G = P;
		outs = this -> opS;
		in0s = (U)0;
		in1s = this -> i1S;
		in2s = (U)0;
	}
	else if (!unitm) {
		G = M;
		outs = this -> ops;
		in0s = this -> i0S;
		in1s = this -> i1s;
		in2s = this -> i2 ? (U)1 : (U)0;
	}
	else {
		G = Q;
		outs = this -> k;
		in0s = (U)0;
		in1s = this -> k;
		in2s = (U)0;
	}

	g = unitm ? (U)4 : (U)1;
	
	Nt = set_thread_load(this -> T_load, G, this -> NT, g);

	for (d = 0, G = 0; d<Nt; d++, G += g) {
		g = this -> T_load[d];
		if (!unitp) {
			P = g;
		}
		else if (!unitm) {
			M = g;
		}
		else {
			Q = g;
		}
	
		this -> Tewise[d].init   (this -> op + G * outs,
															this -> i0 + G * in0s,
															this -> i1 + G * in1s,
															M, this -> k, P, Q, 
															this -> i0c, this -> i1b, 
															this -> i2 + G * in2s,
															this -> D, this -> R, this -> A);
	}
	/* // A thread-free version
	for (d = 0, G = 0; d<Nt; d++, G += g) {
		// this -> Tewise[d].nop();
		this -> Tewise[d].exec();
	}
  */
	///* // Threaded version
	for (d = 0; d<Nt; d++) {
		this -> Tewise[d].Thread = std::thread(&tewise<T,U>::exec, &this -> Tewise[d]);
		//this -> Tewise[d].Thread = std::thread(&tewise<T,U>::nop, &this -> Tewise[d]);
	}
	for (d = 0; d<Nt; d++) {
		this -> Tewise[d].Thread.join();
	}
	//*/
}

//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------

template <class T, class U>
static inline void ewise_product (T* OP, 
																	T* I0, 
																	T* I1, 
																	U m, 
																	U k,
																	U p,
																	U q,
																	bool i0c = false,
																	bool i1b = false,
																	T* I2 = (T*)0,
																	U Nt = (U)0,
																	T Ft = 0.,
																	U D = (U)0,
																	U R = (U)0,
																	U A = (U)0) {
	ewise<T, U> Ewise;
  Ewise.init (OP, I0, I1, m, k, p, q, i0c, i1b, I2, Nt, Ft, D, R, A); 
  Ewise.exec();
}

//------------------------------------------------------------------------------
# endif

