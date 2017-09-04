//------------------------------------------------------------------------------
// Single-threaded mmdot matrix-matrix dot product class
//------------------------------------------------------------------------------
# ifndef tmmdot_txx
# define tmmdot_txx

//------------------------------------------------------------------------------

// A double-precision read cache scheme (for thread-safety do not cache Out):
// Fast: In0 (8x64)    , In1T (64x8)      - 8192  bytes
// Slow: In0 ([_8x8x64), In1T (64x[8x_8]) - 65536 bytes
// Shared: In0 and In1                    - 1048576 bytes per thread

//------------------------------------------------------------------------------
// Minimum double length:	pre-outer-aligned  8192 
//												post-outer-aligned 8256 (for 2 outer-aligned caches)
# define CACHE_DOUBLE_LENGTH 		8256
# define CACHE_OUTER_ALIGNMENT 	256
# define CACHE_INNER_ALIGNMENT 	64

//------------------------------------------------------------------------------
# ifndef HAVE_ARCHITECTURE 							// calling template C++ code
# define THIS_DOUBLE_MKN this -> mkn
# define THIS_DOUBLE_MKN_1X1X1 this -> mkn_1x1x1
# define THIS_DOUBLE_MKN_4X4X4 this -> mkn_4x4x4
# define THIS_DOUBLE_MKN_8X8X8 this -> mkn_8x8x8
# define THIS_DOUBLE_MKN_8X64X8 this -> mkn_8x64x8
# define THIS_DOUBLE_MKN_64X8X64 this -> mkn_64x8x64
# define THIS_DOUBLE_MKN_64X64X64 this -> mkn_64x64x64
# define DOT_PRODUCT_DOUBLE_MNK_8X8X8 dot_product_MNK_8x8x8
# define DOT_PRODUCT_DOUBLE_MKN_4X4X4 dot_product_mkn_4x4x4
# define DOT_PRODUCT_DOUBLE_MKC_4X4X4 dot_product_mkc_4x4x4
# define DOT_PRODUCT_DOUBLE_MKN_1X1X8 dot_product_mkn_1x1x8
# define DOT_PRODUCT_DOUBLE_MKC_1X8X1 dot_product_mkc_1x8x1
# else                     							// calling wrapper C and assembler
# ifndef CLAS_HEADERS_ONLY
# include "dot_product_double_mkn.c" 
# include "dot_product_double_mkc.c" 
# include "dot_product_double_mnk.c" 
# else
# include "dot_product_double_mkn.h" 
# include "dot_product_double_mkc.h" 
# include "dot_product_double_mnk.h" 
# endif
# define THIS_DOUBLE_MKN this -> double_mkn
# define THIS_DOUBLE_MKN_1X1X1 this -> double_mkn_1x1x1
# define THIS_DOUBLE_MKN_4X4X4 this -> double_mkn_4x4x4
# define THIS_DOUBLE_MKN_8X8X8 this -> double_mkn_8x8x8
# define THIS_DOUBLE_MKN_8X64X8 this -> double_mkn_8x64x8
# define THIS_DOUBLE_MKN_64X8X64 this -> double_mkn_64x8x64
# define THIS_DOUBLE_MKN_64X64X64 this -> double_mkn_64x64x64
# define DOT_PRODUCT_DOUBLE_MNK_8X8X8 dot_product_double_MNK_8x8x8
# define DOT_PRODUCT_DOUBLE_MKN_4X4X4 dot_product_double_mkn_4x4x4
# define DOT_PRODUCT_DOUBLE_MKC_4X4X4 dot_product_double_mkc_4x4x4
# define DOT_PRODUCT_DOUBLE_MKN_1X1X8 dot_product_double_mkn_1x1x8
# define DOT_PRODUCT_DOUBLE_MKC_1X8X1 dot_product_double_mkc_1x8x1
# endif

//------------------------------------------------------------------------------
# include "mcache.txx"
# include "clas_threads.txx"
# include "_dot_product_mnk.txx"
# include "_dot_product_mkn.txx"
# include "_dot_product_mkc.txx"

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
template <class T, class U>
class tmmdot {
	public:
		double cache[CACHE_DOUBLE_LENGTH];
		tmmdot();
		tmmdot (T* _OP, T* _I0 = (T*)0, T* _I1 = (T*)0,
						U _M = (U)0, U _K = (U)0, U _N = (U)0,
						bool _OPT = false, bool _I0T = false, bool _I1T = false, 
						bool _ColM = false, T* _I2 = (T*)0, 
						U _D = (U)0, U _R = (U)0, U _A = (U)0);
		~tmmdot<T, U>();
		virtual void init(T* _OP = (T*)0 , T* _I0 = (T*)0, T* _I1 = (T*)0,
											U _M = (U)0, U _K = (U)0, U _N = (U)0,
											bool _OPT = false, bool _I0T = false, bool _I1T = false, 
											bool _ColM = false, T* _I2 = (T*)0, 
											U _D = (U)0, U _R = (U)0, U _A = (U)0);
		void setAln(U al0 = (U)CACHE_OUTER_ALIGNMENT, U al1 = (U)CACHE_INNER_ALIGNMENT);
		void setPtr(T* _OP = (T*)0 , T* _I0 = (T*)0, T* _I1 = (T*)0, T* _I2 = (T*)0);
		void setDim(U _M = (U)0, U _K = (U)0, U _N = (U)0);
		void setCmj(bool _OPT = false, bool _I0T = false, bool _I1T = false, bool _ColM = false);
		void setStr(U _OPS = (U)0, U _I0S = (U)0, U _I1S = (U)0, U _I2S = (U)0,
								U _OPs = (U)0, U _I0s = (U)0, U _I1s = (U)0, U _I2s = (U)0);
		void chkStr();
		void setDRA(U _D = (U)0, U _R = (U)0, U _A = (U)0);
		void exec();
		void mkn();
		void nop() {};
		void mkn_kmn_64x64x64(T* _OP, T* _I0, T* _I1, U M, U K, U N); // an experiment
		void mkn_64x64x64(T* _OP, T* _I0, T* _I1, U M, U K, U N);
		void mkn_64x8x64(T* _OP, T* _I0, T* _I1, U M, U K, U N);
		void mkn_8x64x8(T* _OP, T* _I0, T* _I1, U M, U K, U N);
		void mkn_8x8x8(T* _OP, T* _I0, T* _I1, U M, U K, U N);
		void mkn_4x4x4(T* _OP, T* _I0, T* _I1, U M, U K, U N);
		void mkn_1x1x1(T* _OP, T* _I0, T* _I1, U M, U K, U N);
		void double_mkn();
		void double_mkn_64x64x64(T* _OP, T* _I0, T* _I1, U M, U K, U N);
		void double_mkn_64x8x64(T* _OP, T* _I0, T* _I1, U M, U K, U N);
		void double_mkn_8x64x8(T* _OP, T* _I0, T* _I1, U M, U K, U N);
		void double_mkn_8x8x8(T* _OP, T* _I0, T* _I1, U M, U K, U N);
		void double_mkn_4x4x4(T* _OP, T* _I0, T* _I1, U M, U K, U N);
		void double_mkn_1x1x1(T* _OP, T* _I0, T* _I1, U M, U K, U N);
		std::thread Thread;
	protected:
		T* OP;
		T* I0;
		T* I1;
		T* I2;
		U M;
		U K;
		U N;
		bool OPC;
		bool I0C;
		bool I1C;
		T* op;
		T* i0;
		T* i1;
		T* i2;
		U m;
		U k;
		U n;
		bool opc;
		bool i0c;
		bool i1c;
		U OPS;
		U I0S;
		U I1S;
		U I2S;
		U OPs;
		U I0s;
		U I1s;
		U I2s;
		U opS;
		U i0S;
		U i1S;
		U i2S;
		U ops;
		U i0s;
		U i1s;
		U i2s;
		U D;
		U R;
		U A;
		U sizeofT;
		mcache<T, U> cacher;
	private:
};

//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
template <class T, class U>
tmmdot<T, U>::tmmdot() {
	this -> sizeofT = sizeof(T);
	this -> cacher.init((T*)this -> cache, (U)2);
	this -> setAln();
	this -> init();
}

//---------------------------------------------------------------------------
template <class T, class U>
tmmdot<T, U>::tmmdot( T* _OP, T* _I0, T* _I1, U _M, U _K, U _N,
											bool _OPT, bool _I0T, bool _I1T, 
											bool _ColM, T* _I2, U _D, U _R, U _A) {
	this -> init(	_OP, _I0, _I1, _M, _K, _N, _OPT, _I0T, _I1T, _ColM, _I2, _D, _R, _A);
}

//---------------------------------------------------------------------------
template <class T, class U>
tmmdot<T, U>::~tmmdot() {
	this -> init();
}

//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
template <class T, class U>
void tmmdot<T, U>::init(T* _OP, T* _I0, T* _I1, U _M, U _K, U _N,
												bool _OPT, bool _I0T, bool _I1T, 
												bool _ColM, T* _I2, U _D, U _R, U _A) {
	this -> setPtr(_OP, _I0, _I1, _I2);
	if (!this -> OP) {return;}
	this -> setDim(_M, _K, _N);
	this -> setCmj(_OPT, _I0T, _I1T, _ColM);
	this -> setDRA(_D, _R, _A);
}

//---------------------------------------------------------------------------
template <class T, class U>
void tmmdot<T, U>::setAln(U _al0, U _al1) {
	this -> cacher.setAlign(_al0, _al1);
}

//---------------------------------------------------------------------------
template <class T, class U>
void tmmdot<T, U>::setPtr(T* _OP, T* _I0, T* _I1, T* _I2) {
	this -> OP = _OP;
	this -> I0 = _I0;
	this -> I1 = _I1;
	this -> I2 = _I2;
}

//---------------------------------------------------------------------------
template <class T, class U>
void tmmdot<T, U>::setDim(U _M, U _K, U _N) {
	this -> M = _M;
	this -> K = _K;
	this -> N = _N;
}

//---------------------------------------------------------------------------
template <class T, class U>
void tmmdot<T, U>::setCmj(bool _OPT, bool _I0T, bool _I1T, bool _ColM) {
	if (!_ColM) {
		this -> OPC = _OPT;
		this -> I0C = _I0T;
		this -> I1C = _I1T;
	}
	else {
		this -> OPC = !_OPT;
		this -> I0C = !_I0T;
		this -> I1C = !_I1T;
	}
	this -> setStr();
	this -> chkStr();
}

//---------------------------------------------------------------------------
template <class T, class U>
void tmmdot<T, U>::setStr(U _OPS, U _I0S, U _I1S, U _I2S,
													U _OPs, U _I0s, U _I1s, U _I2s) {

	this -> op  = this -> OP;
	this -> opc = this -> OPC;
	this -> i2  = this -> I2;
	this -> k   = this -> K;

	this -> OPS = _OPS;
	this -> I0S = _I0S;
	this -> I1S = _I1S;
	this -> I2S = _I2S;
	this -> OPs = _OPs;
	this -> I0s = _I0s;
	this -> I1s = _I1s;
	this -> I2s = _I2s;

	if (!this -> opc) {
		this -> m = this -> M;
		this -> n = this -> N;
		this -> i0 = this -> I0;
		this -> i1 = this -> I1;
		this -> i0c = this -> I0C;
		this -> i1c = this -> I1C;
		this -> opS = this -> OPS;
		this -> ops = this -> OPs;
		this -> i0S = this -> I0S;
		this -> i0s = this -> I0s;
		this -> i1S = this -> I1S;
		this -> i1s = this -> I1s;
		this -> i2S = this -> I2S;
		this -> i2s = this -> I2s;
	}
	else {
		this -> m = this -> N;
		this -> n = this -> M;
		this -> i0 = this -> I1;
		this -> i1 = this -> I0;
		this -> i0c = !this -> I1C;
		this -> i1c = !this -> I0C;
		this -> opS = this -> OPs;
		this -> ops = this -> OPS;
		this -> i0S = this -> I1s;
		this -> i0s = this -> I1S;
		this -> i1S = this -> I0s;
		this -> i1s = this -> I0S;
		this -> i2S = this -> I2s;
		this -> i2s = this -> I2S;
	}
}

//---------------------------------------------------------------------------
template <class T, class U>
void tmmdot<T, U>::chkStr() {
	if (! (this -> opS || this -> ops) ) {
		this -> opS = this -> n;
		this -> ops = (U)1;
	}
	if (! (this -> i0S || this -> i0s) ) {
		if (!this -> i0c) {
			this -> i0S = this -> k;
			this -> i0s = (U)1;
		}
		else {
			this -> i0S = (U)1;
			this -> i0s = this -> m;
		}
	}
	if (! (this -> i1S || this -> i1s) ) {
		if (!this -> i1c) {
			this -> i1S = this -> n;
			this -> i1s = (U)1;
		}
		else {
			this -> i1S = (U)1;
			this -> i1s = this -> k;
		}
	}
	if (! (this -> i2S || this -> i2s) ) {
		this -> i2S = (U)0;
		this -> i2s = (U)0;
		if (this -> i2) {
			if (!this -> opc) {
				this -> i2S = (U)1;
			}
			else {
				this -> i2s = (U)1;
			}
		}
	}
}

//---------------------------------------------------------------------------
template <class T, class U>
void tmmdot<T, U>::setDRA(U _D, U _R, U _A) {
	this -> D = _D; // (future diagnostic) Direction matrix unrolling
	this -> R = _R; // (future diagnostic) Radix
	this -> A = _A; // Architecture
}

//---------------------------------------------------------------------------
template <class T, class U>
void tmmdot<T, U>::exec() {
	if (this -> op != this -> i2) {
		replicate(this -> op, this -> m, this -> n, this -> opS,
							this -> i2, this -> i2S, this -> i2s, (U)1);
	}
	if (this -> A == (U)1) {return this -> mkn();}
	switch (this -> sizeofT) {
		case (U)8: {return THIS_DOUBLE_MKN();}
		default: {return this -> mkn();}
	}
}
//---------------------------------------------------------------------------
template <class T, class U>
void tmmdot<T, U>::mkn() {
	U r = this -> m <= this -> n ? this -> m : this -> n;
	if (this -> m == (U)1) {
		this -> mkn_1x1x1    (this -> op, this -> i0, this -> i1, 
													this -> m,  this -> k,  this -> n);
	}
	else if (this -> k < (U)8 || r < (U)8) {
		this -> mkn_4x4x4    (this -> op, this -> i0, this -> i1, 
													this -> m,  this -> k,  this -> n);
	}
	else if (this -> k < (U)64 || r < (U)64) {
		this -> mkn_8x8x8    (this -> op, this -> i0, this -> i1, 
													this -> m,  this -> k,  this -> n);
	}
	else if (r < (U)64) {
		this -> mkn_8x64x8   (this -> op, this -> i0, this -> i1, 
													this -> m,  this -> k,  this -> n);
	}
	else if (this -> k < (U)64) {
		this -> mkn_64x8x64  (this -> op, this -> i0, this -> i1, 
													this -> m,  this -> k,  this -> n);
	}
	else {
		this -> mkn_64x64x64 (this -> op, this -> i0, this -> i1, 
													this -> m,  this -> k,  this -> n);
	}
}

//---------------------------------------------------------------------------
template <class T, class U>
void tmmdot<T, U>::double_mkn() {
	U r = this -> m <= this -> n ? this -> m : this -> n;
	if (this -> m == (U)1) {
		THIS_DOUBLE_MKN_1X1X1  (this -> op, this -> i0, this -> i1, 
														this -> m,  this -> k,  this -> n);
	}
	else if (this -> k < (U)8 || r < (U)8) {
		THIS_DOUBLE_MKN_4X4X4  (this -> op, this -> i0, this -> i1, 
														this -> m,  this -> k,  this -> n);
	}
	else if (this -> k < (U)64 || r < (U)64) {
		THIS_DOUBLE_MKN_8X8X8  (this -> op, this -> i0, this -> i1, 
														this -> m,  this -> k,  this -> n);
	}
	else if (r < (U)64) {
		THIS_DOUBLE_MKN_8X64X8 (this -> op, this -> i0, this -> i1, 
														this -> m,  this -> k,  this -> n);
	}
	else if (this -> k < (U)64) {
		THIS_DOUBLE_MKN_64X8X64(this -> op, this -> i0, this -> i1, 
														this -> m,  this -> k,  this -> n);
	}
	else {
		THIS_DOUBLE_MKN_64X64X64 (this -> op, this -> i0, this -> i1, 
															this -> m,  this -> k,  this -> n);
	}
}

//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
template <class T, class U>
void tmmdot<T, U>::mkn_64x64x64(T* _OP, T* _I0, T* _I1, U _M, U _K, U _N) {
	U e, f, g, F;
	T *_Out, *_In0, *_In1, *Out, *In0, *In1;
	U Ms, Ks, Ns, _m, _k, _n;

	Ms = (U)64;
	Ks = (U)64;
	Ns = (U)64;

	if (_M < Ms || _N < Ns) {
		return this -> mkn_8x64x8(_OP, _I0, _I1, _M, _K, _N);
	}
	else if (_K < Ks) {
		return this -> mkn_64x8x64(_OP, _I0, _I1, _M, _K, _N);
	}

	_m = _M & (U)-Ms;
	_k = _K & (U)-Ks;
	_n = _N & (U)-Ns;

	In0 = this -> cacher.setUnit((U)0, Ms, Ks);
	In1 = this -> cacher.setUnit((U)1, Ks, Ns);
	
	this -> cacher.retUnit((U)0).prefetch((U)1, (U)2);
	this -> cacher.retUnit((U)1).prefetch((U)1, (U)2);

	for (e = 0; e < _m; e += Ms) {
		_Out = _OP + e * this -> opS;
		_In0 = _I0 + e * this -> i0S;
		for (f = 0; f < _k; f += Ks) {
			cacher.retUnit((U)0).copyFr(_In0 + f * this -> i0s, this -> i0S, this -> i0s);
			_In1 = _I1 + f * this -> i1S;
			for (g = 0; g < _n; g += Ns) {
				Out = _Out + g * this -> ops;
				cacher.retUnit((U)1).copyFr(_In1 + g * this -> i1s, this -> i1S, this -> i1s);
				dot_product_MNK_8x8x8(Out, In0, In1, Ms, Ks, Ns, this -> opS, this -> A);
			}
		}
	}

	if (_k < _K) {
		_Out = _OP; 
		_In0 = _I0 + _k * this -> i0s;
		_In1 = _I1 + _k * this -> i1S;
		this -> mkn_64x8x64(_Out, _In0, _In1, _m, _K - _k, _n);
	}

	if (_n < _N) {
		_Out = _OP + _n * this -> ops;
		_In0 = _I0;
		_In1 = _I1 + _n * this -> i1s;
		this -> mkn_8x64x8(_Out, _In0, _In1, _m, _K, _N - _n);
	}

	if (_m < _M) {
		_Out = _OP + _m * this -> opS;
		_In0 = _I0 + _m * this -> i0S;
		_In1 = _I1;
		this -> mkn_8x64x8(_Out, _In0, _In1, _M - _m, _K, _N);
	}
}

//---------------------------------------------------------------------------
template <class T, class U>
void tmmdot<T, U>::mkn_64x8x64(T* _OP, T* _I0, T* _I1, U _M, U _K, U _N) {
	U e, f, g, F;
	T *_Out, *_In0, *_In1, *Out, *In0, *In1;
	U Ms, Ks, Ns, _m, _k, _n;

	Ms = (U)64;
	Ks = (U)8;
	Ns = (U)64;

	if (_M < Ms || _N < Ns) {
		return this -> mkn_8x8x8(_OP, _I0, _I1, _M, _K, _N);
	}
	else if (_K < Ks) {
		return this -> mkn_4x4x4(_OP, _I0, _I1, _M, _K, _N);
	}

	_m = _M & (U)-Ms;
	_k = _K & (U)-Ks;
	_n = _N & (U)-Ns;

	In0 = this -> cacher.setUnit((U)0, Ms, Ks);
	In1 = this -> cacher.setUnit((U)1, Ks, Ns);
	
	this -> cacher.retUnit((U)0).prefetch((U)1, (U)3);
	this -> cacher.retUnit((U)1).prefetch((U)1, (U)3);

	for (e = 0; e < _m; e += Ms) {
		_Out = _OP + e * this -> opS;
		_In0 = _I0 + e * this -> i0S;
		for (f = 0; f < _k; f += Ks) {
			cacher.retUnit((U)0).copyFr(_In0 + f * this -> i0s, this -> i0S, this -> i0s);
			_In1 = _I1 + f * this -> i1S;
			for (g = 0; g < _n; g += Ns) {
				Out = _Out + g * this -> ops;
				cacher.retUnit((U)1).copyFr(_In1 + g * this -> i1s, this -> i1S, this -> i1s);
				dot_product_MNK_8x8x8(Out, In0, In1, Ms, Ks, Ns, this -> opS, this -> A);
			}
		}
	}

	if (_k < _K) {
		_Out = _OP; 
		_In0 = _I0 + _k * this -> i0s;
		_In1 = _I1 + _k * this -> i1S;
		this -> mkn_4x4x4(_Out, _In0, _In1, _m, _K - _k, _n);
	}

	if (_n < _N) {
		_Out = _OP + _n * this -> ops;
		_In0 = _I0;
		_In1 = _I1 + _n * this -> i1s;
		this -> mkn_8x8x8(_Out, _In0, _In1, _m, _K, _N - _n);
	}

	if (_m < _M) {
		_Out = _OP + _m * this -> opS;
		_In0 = _I0 + _m * this -> i0S;
		_In1 = _I1;
		this -> mkn_8x8x8(_Out, _In0, _In1, _M - _m, _K, _N);
	}
}

//---------------------------------------------------------------------------
template <class T, class U>
void tmmdot<T, U>::mkn_8x64x8(T* _OP, T* _I0, T* _I1, U _M, U _K, U _N) {
	U e, f, g, F;
	T *_Out, *_In0, *_In1, *Out, *In0, *In1;
	U Ms, Ks, Ns, _m, _k, _n;

	Ms = (U)8;
	Ks = (U)64;
	Ns = (U)8;

	if (_M < Ms || _N < Ns) {
		return this -> mkn_4x4x4(_OP, _I0, _I1, _M, _K, _N);
	}
	else if (_K < Ks) {
		return this -> mkn_8x8x8(_OP, _I0, _I1, _M, _K, _N);
	}

	_m = _M & (U)-Ms;
	_k = _K & (U)-Ks;
	_n = _N & (U)-Ns;

	In0 = this -> cacher.setUnit((U)0, Ms, Ks);
	In1 = this -> cacher.setUnit((U)1, Ks, Ns);
	
	this -> cacher.retUnit((U)0).prefetch((U)1, (U)3);
	this -> cacher.retUnit((U)1).prefetch((U)1, (U)3);

	for (e = 0; e < _m; e += Ms) {
		_Out = _OP + e * this -> opS;
		_In0 = _I0 + e * this -> i0S;
		for (f = 0; f < _k; f += Ks) {
			cacher.retUnit((U)0).copyFr(_In0 + f * this -> i0s, this -> i0S, this -> i0s);
			_In1 = _I1 + f * this -> i1S;
			for (g = 0; g < _n; g += Ns) {
				Out = _Out + g * this -> ops;
				cacher.retUnit((U)1).copyFr(_In1 + g * this -> i1s, this -> i1S, this -> i1s);
				dot_product_MNK_8x8x8(Out, In0, In1, Ms, Ks, Ns, this -> opS, this -> A);
			}
		}
	}

	if (_k < _K) {
		_Out = _OP; 
		_In0 = _I0 + _k * this -> i0s;
		_In1 = _I1 + _k * this -> i1S;
		this -> mkn_8x8x8(_Out, _In0, _In1, _m, _K - _k, _n);
	}

	if (_n < _N) {
		_Out = _OP + _n * this -> ops;
		_In0 = _I0;
		_In1 = _I1 + _n * this -> i1s;
		this -> mkn_4x4x4(_Out, _In0, _In1, _m, _K, _N - _n);
	}

	if (_m < _M) {
		_Out = _OP + _m * this -> opS;
		_In0 = _I0 + _m * this -> i0S;
		_In1 = _I1;
		this -> mkn_4x4x4(_Out, _In0, _In1, _M - _m, _K, _N);
	}
}

//---------------------------------------------------------------------------
template <class T, class U>
void tmmdot<T, U>::mkn_8x8x8(T* _OP, T* _I0, T* _I1, U _M, U _K, U _N) {
	U e, f, g, F;
	T *_Out, *_In0, *_In1, *Out, *In0, *In1;
	U Ms, Ks, Ns, _m, _k, _n;

	Ms = (U)8;
	Ks = (U)8;
	Ns = (U)8;

	if (_M < Ms || _N < Ns) {
		return this -> mkn_4x4x4(_OP, _I0, _I1, _M, _K, _N);
	}
	else if (_K < Ks) {
		return this -> mkn_4x4x4(_OP, _I0, _I1, _M, _K, _N);
	}

	_m = _M & (U)-Ms;
	_k = _K & (U)-Ks;
	_n = _N & (U)-Ns;

	In0 = this -> cacher.setUnit((U)0, Ms, Ks);
	In1 = this -> cacher.setUnit((U)1, Ks, Ns);
	
	this -> cacher.retUnit((U)0).prefetch((U)1, (U)3);
	this -> cacher.retUnit((U)1).prefetch((U)1, (U)3);

	for (e = 0; e < _m; e += Ms) {
		_Out = _OP + e * this -> opS;
		_In0 = _I0 + e * this -> i0S;
		for (f = 0; f < _k; f += Ks) {
			cacher.retUnit((U)0).copyFr(_In0 + f * this -> i0s, this -> i0S, this -> i0s);
			_In1 = _I1 + f * this -> i1S;
			for (g = 0; g < _n; g += Ns) {
				Out = _Out + g * this -> ops;
				cacher.retUnit((U)1).copyFr(_In1 + g * this -> i1s, this -> i1S, this -> i1s);
				dot_product_MNK_8x8x8(Out, In0, In1, Ms, Ks, Ns, this -> opS, this -> A);
			}
		}
	}

	if (_k < _K) {
		_Out = _OP; 
		_In0 = _I0 + _k * this -> i0s;
		_In1 = _I1 + _k * this -> i1S;
		this -> mkn_4x4x4(_Out, _In0, _In1, _m, _K - _k, _n);
	}


	if (_n < _N) {
		_Out = _OP + _n * this -> ops;
		_In0 = _I0;
		_In1 = _I1 + _n * this -> i1s;
		this -> mkn_4x4x4(_Out, _In0, _In1, _m, _K, _N - _n);
	}

	if (_m < _M) {
		_Out = _OP + _m * this -> opS;
		_In0 = _I0 + _m * this -> i0S;
		_In1 = _I1;
		this -> mkn_4x4x4(_Out, _In0, _In1, _M - _m, _K, _N);
	}
}

//---------------------------------------------------------------------------
template <class T, class U>
void tmmdot<T, U>::mkn_4x4x4(T* _OP, T* _I0, T* _I1, U _M, U _K, U _N) {
	if (!this -> i1c) {
		dot_product_mkn_4x4x4(_OP, _I0, _I1, _M, _K, _N, 
		this -> opS, this -> i0S, this -> i0s, this -> i1S);
	}
	else {
		dot_product_mkc_4x4x4(_OP, _I0, _I1, _M, _K, _N, 
		this -> opS, this -> i0S, this -> i0s, this -> i1s);
	}
}

//---------------------------------------------------------------------------
template <class T, class U>
void tmmdot<T, U>::mkn_1x1x1(T* _OP, T* _I0, T* _I1, U _M, U _K, U _N) {
	if (!this -> i1c) {
		dot_product_mkn_1x1x8(_OP, _I0, _I1, _M, _K, _N, 
		this -> opS, this -> i0S, this -> i0s, this -> i1S);
	}
	else {
		dot_product_mkc_1x8x1(_OP, _I0, _I1, _M, _K, _N, 
		this -> opS, this -> i0S, this -> i0s, this -> i1s);
	}
}

//---------------------------------------------------------------------------
// DOUBLE ARCHITECTURE-DEPENDENT MEMBER FUNCTIONS
//---------------------------------------------------------------------------

template <class T, class U>
void tmmdot<T, U>::double_mkn_64x64x64(T* _OP, T* _I0, T* _I1, U _M, U _K, U _N) {
	U e, f, g, F;
	T *_Out, *_In0, *_In1, *Out, *In0, *In1;
	U Ms, Ks, Ns, _m, _k, _n;

	Ms = (U)64;
	Ks = (U)64;
	Ns = (U)64;

	if (_M < Ms || _N < Ns) {
		return this -> double_mkn_8x64x8(_OP, _I0, _I1, _M, _K, _N);
	}
	else if (_K < Ks) {
		return this -> double_mkn_64x8x64(_OP, _I0, _I1, _M, _K, _N);
	}

	_m = _M & (U)-Ms;
	_k = _K & (U)-Ks;
	_n = _N & (U)-Ns;

	In0 = this -> cacher.setUnit((U)0, Ms, Ks);
	In1 = this -> cacher.setUnit((U)1, Ks, Ns);
	
	this -> cacher.retUnit((U)0).prefetch((U)1, (U)2);
	this -> cacher.retUnit((U)1).prefetch((U)1, (U)2);

	for (e = 0; e < _m; e += Ms) {
		_Out = _OP + e * this -> opS;
		_In0 = _I0 + e * this -> i0S;
		for (f = 0; f < _k; f += Ks) {
			cacher.retUnit((U)0).copyFr(_In0 + f * this -> i0s, this -> i0S, this -> i0s);
			_In1 = _I1 + f * this -> i1S;
			for (g = 0; g < _n; g += Ns) {
				Out = _Out + g * this -> ops;
				cacher.retUnit((U)1).copyFr(_In1 + g * this -> i1s, this -> i1S, this -> i1s);
				DOT_PRODUCT_DOUBLE_MNK_8X8X8(Out, In0, In1, Ms, Ks, Ns, this -> opS, this -> A);
			}
		}
	}

	if (_k < _K) {
		_Out = _OP; 
		_In0 = _I0 + _k * this -> i0s;
		_In1 = _I1 + _k * this -> i1S;
		this -> double_mkn_64x8x64(_Out, _In0, _In1, _m, _K - _k, _n);
	}

	if (_n < _N) {
		_Out = _OP + _n * this -> ops;
		_In0 = _I0;
		_In1 = _I1 + _n * this -> i1s;
		this -> double_mkn_8x64x8(_Out, _In0, _In1, _m, _K, _N - _n);
	}

	if (_m < _M) {
		_Out = _OP + _m * this -> opS;
		_In0 = _I0 + _m * this -> i0S;
		_In1 = _I1;
		this -> double_mkn_8x64x8(_Out, _In0, _In1, _M - _m, _K, _N);
	}
}

//---------------------------------------------------------------------------
template <class T, class U>
void tmmdot<T, U>::double_mkn_64x8x64(T* _OP, T* _I0, T* _I1, U _M, U _K, U _N) {
	U e, f, g, F;
	T *_Out, *_In0, *_In1, *Out, *In0, *In1;
	U Ms, Ks, Ns, _m, _k, _n;

	Ms = (U)64;
	Ks = (U)8;
	Ns = (U)64;

	if (_M < Ms || _N < Ns) {
		return this -> double_mkn_8x8x8(_OP, _I0, _I1, _M, _K, _N);
	}
	else if (_K < Ks) {
		return this -> double_mkn_4x4x4(_OP, _I0, _I1, _M, _K, _N);
	}

	_m = _M & (U)-Ms;
	_k = _K & (U)-Ks;
	_n = _N & (U)-Ns;

	In0 = this -> cacher.setUnit((U)0, Ms, Ks);
	In1 = this -> cacher.setUnit((U)1, Ks, Ns);
	
	this -> cacher.retUnit((U)0).prefetch((U)1, (U)3);
	this -> cacher.retUnit((U)1).prefetch((U)1, (U)3);

	for (e = 0; e < _m; e += Ms) {
		_Out = _OP + e * this -> opS;
		_In0 = _I0 + e * this -> i0S;
		for (f = 0; f < _k; f += Ks) {
			cacher.retUnit((U)0).copyFr(_In0 + f * this -> i0s, this -> i0S, this -> i0s);
			_In1 = _I1 + f * this -> i1S;
			for (g = 0; g < _n; g += Ns) {
				Out = _Out + g * this -> ops;
				cacher.retUnit((U)1).copyFr(_In1 + g * this -> i1s, this -> i1S, this -> i1s);
				DOT_PRODUCT_DOUBLE_MNK_8X8X8(Out, In0, In1, Ms, Ks, Ns, this -> opS, this -> A);
			}
		}
	}

	if (_k < _K) {
		_Out = _OP; 
		_In0 = _I0 + _k * this -> i0s;
		_In1 = _I1 + _k * this -> i1S;
		this -> double_mkn_4x4x4(_Out, _In0, _In1, _m, _K - _k, _n);
	}

	if (_n < _N) {
		_Out = _OP + _n * this -> ops;
		_In0 = _I0;
		_In1 = _I1 + _n * this -> i1s;
		this -> double_mkn_8x8x8(_Out, _In0, _In1, _m, _K, _N - _n);
	}

	if (_m < _M) {
		_Out = _OP + _m * this -> opS;
		_In0 = _I0 + _m * this -> i0S;
		_In1 = _I1;
		this -> double_mkn_8x8x8(_Out, _In0, _In1, _M - _m, _K, _N);
	}
}

//---------------------------------------------------------------------------
template <class T, class U>
void tmmdot<T, U>::double_mkn_8x64x8(T* _OP, T* _I0, T* _I1, U _M, U _K, U _N) {
	U e, f, g, F;
	T *_Out, *_In0, *_In1, *Out, *In0, *In1;
	U Ms, Ks, Ns, _m, _k, _n;

	Ms = (U)8;
	Ks = (U)64;
	Ns = (U)8;

	if (_M < Ms || _N < Ns) {
		return this -> double_mkn_4x4x4(_OP, _I0, _I1, _M, _K, _N);
	}
	else if (_K < Ks) {
		return this -> double_mkn_8x8x8(_OP, _I0, _I1, _M, _K, _N);
	}

	_m = _M & (U)-Ms;
	_k = _K & (U)-Ks;
	_n = _N & (U)-Ns;

	In0 = this -> cacher.setUnit((U)0, Ms, Ks);
	In1 = this -> cacher.setUnit((U)1, Ks, Ns);
	
	this -> cacher.retUnit((U)0).prefetch((U)1, (U)3);
	this -> cacher.retUnit((U)1).prefetch((U)1, (U)3);

	for (e = 0; e < _m; e += Ms) {
		_Out = _OP + e * this -> opS;
		_In0 = _I0 + e * this -> i0S;
		for (f = 0; f < _k; f += Ks) {
			cacher.retUnit((U)0).copyFr(_In0 + f * this -> i0s, this -> i0S, this -> i0s);
			_In1 = _I1 + f * this -> i1S;
			for (g = 0; g < _n; g += Ns) {
				Out = _Out + g * this -> ops;
				cacher.retUnit((U)1).copyFr(_In1 + g * this -> i1s, this -> i1S, this -> i1s);
				DOT_PRODUCT_DOUBLE_MNK_8X8X8(Out, In0, In1, Ms, Ks, Ns, this -> opS, this -> A);
			}
		}
	}

	if (_k < _K) {
		_Out = _OP; 
		_In0 = _I0 + _k * this -> i0s;
		_In1 = _I1 + _k * this -> i1S;
		this -> double_mkn_8x8x8(_Out, _In0, _In1, _m, _K - _k, _n);
	}

	if (_n < _N) {
		_Out = _OP + _n * this -> ops;
		_In0 = _I0;
		_In1 = _I1 + _n * this -> i1s;
		this -> double_mkn_4x4x4(_Out, _In0, _In1, _m, _K, _N - _n);
	}

	if (_m < _M) {
		_Out = _OP + _m * this -> opS;
		_In0 = _I0 + _m * this -> i0S;
		_In1 = _I1;
		this -> double_mkn_4x4x4(_Out, _In0, _In1, _M - _m, _K, _N);
	}
}

//---------------------------------------------------------------------------
template <class T, class U>
void tmmdot<T, U>::double_mkn_8x8x8(T* _OP, T* _I0, T* _I1, U _M, U _K, U _N) {
	U e, f, g, F;
	T *_Out, *_In0, *_In1, *Out, *In0, *In1;
	U Ms, Ks, Ns, _m, _k, _n;

	Ms = (U)8;
	Ks = (U)8;
	Ns = (U)8;

	if (_M < Ms || _N < Ns) {
		return this -> double_mkn_4x4x4(_OP, _I0, _I1, _M, _K, _N);
	}
	else if (_K < Ks) {
		return this -> double_mkn_4x4x4(_OP, _I0, _I1, _M, _K, _N);
	}

	_m = _M & (U)-Ms;
	_k = _K & (U)-Ks;
	_n = _N & (U)-Ns;

	In0 = this -> cacher.setUnit((U)0, Ms, Ks);
	In1 = this -> cacher.setUnit((U)1, Ks, Ns);
	
	this -> cacher.retUnit((U)0).prefetch((U)1, (U)3);
	this -> cacher.retUnit((U)1).prefetch((U)1, (U)3);

	for (e = 0; e < _m; e += Ms) {
		_Out = _OP + e * this -> opS;
		_In0 = _I0 + e * this -> i0S;
		for (f = 0; f < _k; f += Ks) {
			cacher.retUnit((U)0).copyFr(_In0 + f * this -> i0s, this -> i0S, this -> i0s);
			_In1 = _I1 + f * this -> i1S;
			for (g = 0; g < _n; g += Ns) {
				Out = _Out + g * this -> ops;
				cacher.retUnit((U)1).copyFr(_In1 + g * this -> i1s, this -> i1S, this -> i1s);
				DOT_PRODUCT_DOUBLE_MNK_8X8X8(Out, In0, In1, Ms, Ks, Ns, this -> opS, this -> A);
			}
		}
	}

	if (_k < _K) {
		_Out = _OP; 
		_In0 = _I0 + _k * this -> i0s;
		_In1 = _I1 + _k * this -> i1S;
		this -> double_mkn_4x4x4(_Out, _In0, _In1, _m, _K - _k, _n);
	}


	if (_n < _N) {
		_Out = _OP + _n * this -> ops;
		_In0 = _I0;
		_In1 = _I1 + _n * this -> i1s;
		this -> double_mkn_4x4x4(_Out, _In0, _In1, _m, _K, _N - _n);
	}

	if (_m < _M) {
		_Out = _OP + _m * this -> opS;
		_In0 = _I0 + _m * this -> i0S;
		_In1 = _I1;
		this -> double_mkn_4x4x4(_Out, _In0, _In1, _M - _m, _K, _N);
	}
}

//---------------------------------------------------------------------------
template <class T, class U>
void tmmdot<T, U>::double_mkn_4x4x4(T* _OP, T* _I0, T* _I1, U _M, U _K, U _N) {
	if (!this -> i1c) {
		DOT_PRODUCT_DOUBLE_MKN_4X4X4(_OP, _I0, _I1, _M, _K, _N, 
		this -> opS, this -> i0S, this -> i0s, this -> i1S, this -> A);
	}
	else {
		DOT_PRODUCT_DOUBLE_MKC_4X4X4(_OP, _I0, _I1, _M, _K, _N, 
		this -> opS, this -> i0S, this -> i0s, this -> i1s, this -> A);
	}
}

//---------------------------------------------------------------------------
template <class T, class U>
void tmmdot<T, U>::double_mkn_1x1x1(T* _OP, T* _I0, T* _I1, U _M, U _K, U _N) {
	if (!this -> i1c) {
		DOT_PRODUCT_DOUBLE_MKN_1X1X8(_OP, _I0, _I1, _M, _K, _N, 
		this -> opS, this -> i0S, this -> i0s, this -> i1S, this -> A);
	}
	else {
		DOT_PRODUCT_DOUBLE_MKC_1X8X1(_OP, _I0, _I1, _M, _K, _N, 
		this -> opS, this -> i0S, this -> i0s, this -> i1s, this -> A);
	}
}

//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
template <class T, class U>
void tmmdot<T, U>::mkn_kmn_64x64x64(T* _OP, T* _I0, T* _I1, U _M, U _K, U _N) {

	U e, f, g, F;
	T *_Out, *_In0, *_In1, *Out, *In0, *In1;

	U M = _M & (U)-64;
	U K = _K;
	U N = _N & (U)-64;

	U Ms = (U)64;
	U Ks = (U)64;
	U Ns = (U)64;

	In0 = this -> cacher.setUnit((U)0, Ms, Ks);
	In1 = this -> cacher.setUnit((U)1, Ks, Ns);
	
	this -> cacher.retUnit((U)0).prefetch((U)1, (U)2);
	this -> cacher.retUnit((U)1).prefetch((U)1, (U)2);

	e = K >= (U)Ks ? 0 : M;

	for (; e < M; e += Ms) {
		_Out = _OP + e*_N;
		_In0 = _I0 + e*_K;
		for (f = 0; f < K; f += Ks) {
			cacher.retUnit((U)0).copyFr(_In0+f, (U)1, _K);
			_In1 = _I1 + f*_N;
			for (g = 0; g < N; g += Ns) {
				Out = _Out + g;
				cacher.retUnit((U)1).copyFr(_In1+g, _N, (U)1);
				dot_product_kmn_1x8x8(Out, In0, In1, Ms, Ks, Ns, _N);
			}
		}
	}
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------

template <class T, class U>
static inline void tmmdot_product(T* _OP, 
																	T* _I0, 
																	T* _I1, 
																	U _m, 
																	U _k,
																	U _n,
																	bool OPT = false,
																	bool I0T = false,
																	bool I1T = false,
																	T* _I2 = (T*)0) {
	tmmdot<T, U> Tmmdot;
	Tmmdot.init(_OP, _I0, _I1, _m, _k, _n, OPT, I0T, I1T, false, _I2);
  Tmmdot.exec();
}

//---------------------------------------------------------------------------


# endif

