//------------------------------------------------------------------------------
// Multi-threaded mmdot matrix-matrix dot product class
//------------------------------------------------------------------------------
# ifndef mmdot_txx
# define mmdot_txx
//------------------------------------------------------------------------------
# include "tmmdot.txx"
# include <iostream>
using namespace std;

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
		void exec();
		void execute(U d);
	protected:
		void setThr(U _MT = (U)0, T _FT = (T)1.);
		tmmdot<T, U>* Tmmdot;
		U* T_load;
	private:
		U NT;
		U nt;
};

//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
template <class T, class U>
mmdot<T, U>::mmdot() {
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
void mmdot<T, U>::exec() {
	// If no threads, run execution from thread-blind class thread-blind 
	if (!this -> NT) {
		tmmdot<T, U>::exec();
		return;
	}
	U d, g, G;

	U Nt = set_thread_load(this -> T_load, this -> m, this -> NT);
	std::thread th[Nt];

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
		this -> Tmmdot[d].setStr (this -> m, this -> i0S,
															this -> i1S, this -> i2S,
															(U)1, this -> i0s, 
															this -> i1s, this -> i2s);
		th[d] = std::thread(&mmdot<T,U>::execute, this, d);
	}
	for (d = 0; d < Nt; d++) {
		th[d].join();
	}
}

//---------------------------------------------------------------------------
template <class T, class U>
void mmdot<T, U>::execute(U d) {
	this -> Tmmdot[d].exec();
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------

template <class T, class U>
static inline void mmdot_product (T* _OP, 
																	T* _I0, 
																	T* _I1, 
																	U _m, 
																	U _k,
																	U _n,
																	bool OPT = false,
																	bool I0T = false,
																	bool I1T = false,
																	T* _I2 = (T*)0) {
	mmdot<T, U> Mmdot;
	Mmdot.init(_OP, _I0, _I1, _m, _k, _n, OPT, I0T, I1T, false, _I2);
  Mmdot.exec();
}

//---------------------------------------------------------------------------

# endif

