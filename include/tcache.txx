# ifndef tcache_txx
# define tcache_txx

//------------------------------------------------------------------------------
// Data cache unit class for with capability to copy, transpose,
// and internally clone matrix elements at the same time with
// read/write prefetching calls.

//------------------------------------------------------------------------------
# include "replicate.txx"

//------------------------------------------------------------------------------
// PREFETCH MACROS
// RW = 0 (read), 1 (write)
// LOCALITY = 0(NTA), 1(L3), 2(L2), 3(L1)
//------------------------------------------------------------------------------

// uncomment next line to disable C++ prefetching
# define DO_NOT_PREFETCH 1

# ifndef DO_NOT_PREFETCH
# define PREFETCH_READ_0(PREFETCH_PTR) __builtin_prefetch (PREFETCH_PTR, 0, 0)
# define PREFETCH_READ_1(PREFETCH_PTR) __builtin_prefetch (PREFETCH_PTR, 0, 1) 
# define PREFETCH_READ_2(PREFETCH_PTR) __builtin_prefetch (PREFETCH_PTR, 0, 2)
# define PREFETCH_READ_3(PREFETCH_PTR) __builtin_prefetch (PREFETCH_PTR, 0, 3)
# define PREFETCH_WRITE_0(PREFETCH_PTR) __builtin_prefetch (PREFETCH_PTR, 1, 0)
# define PREFETCH_WRITE_1(PREFETCH_PTR) __builtin_prefetch (PREFETCH_PTR, 1, 1)
# define PREFETCH_WRITE_2(PREFETCH_PTR) __builtin_prefetch (PREFETCH_PTR, 1, 2)
# define PREFETCH_WRITE_3(PREFETCH_PTR) __builtin_prefetch (PREFETCH_PTR, 1, 3)
# else
# define PREFETCH_READ_0(PREFETCH_PTR) PREFETCH_PTR 
# define PREFETCH_READ_1(PREFETCH_PTR) PREFETCH_PTR  
# define PREFETCH_READ_2(PREFETCH_PTR) PREFETCH_PTR 
# define PREFETCH_READ_3(PREFETCH_PTR) PREFETCH_PTR 
# define PREFETCH_WRITE_0(PREFETCH_PTR) PREFETCH_PTR 
# define PREFETCH_WRITE_1(PREFETCH_PTR) PREFETCH_PTR 
# define PREFETCH_WRITE_2(PREFETCH_PTR) PREFETCH_PTR 
# define PREFETCH_WRITE_3(PREFETCH_PTR) PREFETCH_PTR 
# endif

//------------------------------------------------------------------------------
// template functions
//------------------------------------------------------------------------------
template <class T, class U>
U nextAlignedInd(const T* ptr, U alb) {
	// returns next index from ptr aligned according to alb (expressed in bytes)
	uint64_t sot, mod;
	sot = (uint64_t)(sizeof(T));
	if (!alb) {alb = sot;};
	mod = (uint64_t)(ptr) % (uint64_t)(alb);
	if (!mod) {return (U)0;}
	return ( (U) ((alb - mod)/sot) );
}

//------------------------------------------------------------------------------
template <class T, class U>
class tcache {
	public:
		tcache<T, U>();
		tcache<T, U>(T* _CP, U _C2);
		~tcache<T, U>();
		void init(T* _CP = (U)0, U _A1 = (U)0);
		void setA(U _A1);
		T* setC(T* _CP, U _C0 = (U)0, U _C1 = (U)1, U _C2 = (U)1);
		void setC(U _C0, U _C1 = (U)1, U _C2 = (U)1);
		void setI(T* _IP = (T*)0, U _I0 = (U)0, U _I1 = (U)1);
		void setO(T* _OP = (T*)0, U _OS = (U)0);
		T* retCP();
		U retCI();
		U retCL();
		void copyFr();
		void copyFr(T* _IP, U _I0 = (U)0, U _I1 = (U)0);
		void copyTo();
		void copyTo(T* _OP, U _OS = (U)0);
		U prefetch (U rw = (U)0, U locality = (U)3, U ind_beg = (U)0, U ind_end = (U)0);
	protected:
		U sot; // sizeof(T)
		U a1; // a1 = A1 / sot
		U A1; // alignment in bytes
		T* CP; // cache pointer
		U C0; // cache outer dimension
		U C1; // cache inner dimension
		U C2; // cache innermost cloned dimension
		U CI; // CI = C1 * C2
		U CL; // CL = C0 * C1 * C2
		T* IP; // input pointer
		U I0; // input outer stride
		U I1; // input inner stride
		T* OP; // output pointer
		U OS; // output outer stride
};

//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
template <class T, class U>
tcache<T, U>::tcache() {
	this -> init();
}

//---------------------------------------------------------------------------
template <class T, class U>
tcache<T, U>::tcache(T* _CP, U _A1) {
	this -> init(_CP, _A1);
}

//---------------------------------------------------------------------------
template <class T, class U>
tcache<T, U>::~tcache() {
	this -> init();
}

//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
template <class T, class U>
void tcache<T, U>::init(T* _CP, U _A1) {
	this -> sot = sizeof(T);
	this -> setA(_A1);
	this -> setC(_CP);
	this -> setI();
	this -> setO();
}

//---------------------------------------------------------------------------
template <class T, class U>
void tcache<T, U>::setA(U _A1) {
	this -> A1 = (U)_A1 ? (U)_A1 : this -> sot;
	this -> a1 = this -> A1 / this -> sot;
}

//---------------------------------------------------------------------------
template <class T, class U>
T* tcache<T, U>::setC(T* _CP, U _C0, U _C1, U _C2) {
	this -> CP = _CP + nextAlignedInd(_CP, this -> A1);
	this -> C0 = _C0;
	this -> C1 = _C1;
	this -> C2 = _C2;
	this -> CI = this -> C1 * this -> C2;
	this -> CL = this -> C0 * this -> CI;
	return (this -> CP);
}

//---------------------------------------------------------------------------
template <class T, class U>
void tcache<T, U>::setC(U _C0, U _C1, U _C2) {
	this -> setC(this -> CP, _C0, _C1, _C2);
}

//---------------------------------------------------------------------------
template <class T, class U>
void tcache<T, U>::setI(T* _IP, U _I0, U _I1) {
	this -> IP = _IP;
	this -> I0 = _I0;
	this -> I1 = _I1;
}

//---------------------------------------------------------------------------
template <class T, class U>
void tcache<T, U>::setO(T* _OP, U _OS) {
	this -> OP = _OP;
	this -> OS = (U)_OS ? _OS : this -> C0;
}

//---------------------------------------------------------------------------
template <class T, class U>
T* tcache<T, U>::retCP() {
	return (this -> CP);
}

//---------------------------------------------------------------------------
template <class T, class U>
U tcache<T, U>::retCL() {
	return (this -> CL);
}

//---------------------------------------------------------------------------
template <class T, class U>
U tcache<T, U>::retCI() {
	return (this -> CI);
}

//---------------------------------------------------------------------------
template <class T, class U>
void tcache<T, U>::copyFr() {
	replicate(this -> CP,
						this -> C0,
						this -> C1,
						this -> CI,
						this -> IP,
						this -> I0,
						this -> I1,
						this -> C2);
}
//---------------------------------------------------------------------------
template <class T, class U>
void tcache<T, U>::copyFr(T* _IP, U _I0, U _I1) {
	this -> setI(_IP, _I0, _I1);
	return (this -> copyFr());
}

//---------------------------------------------------------------------------
template <class T, class U>
void tcache<T, U>::copyTo() {
	replicate(this -> OP, 
						this -> C0, 
						this -> CI,
						this -> OS, 
						this -> CP,
						this -> CI,
						(U)1,
						this -> C2);
}
//---------------------------------------------------------------------------
template <class T, class U>
void tcache<T, U>::copyTo(T* _OP, U _OS) {
	this -> setO(_OP, _OS);
	this -> copyTo();
}

//---------------------------------------------------------------------------
template <class T, class U>
U tcache<T, U>::prefetch (U rw, U locality, U ind_beg, U ind_end) {
	// Returns number of cache prefetch calls
	
	if (!ind_end) {ind_end = this -> C0 * this -> C1 * this -> C2;}
	ind_beg += nextAlignedInd(this -> CP + ind_beg, this -> A1);
	if (ind_beg + this -> a1 > ind_end) {return ((U)0);}

	U ind_len, calls;
	ind_len = ind_end - ind_beg;   
	calls = ind_len / this -> a1; // this rounds down

	register U i = calls;
	register U s = this -> a1;
	register T* ptr = this -> CP  + ind_beg;

	if (!rw) {
		switch (locality) {
			case 0: {for (; i; i--) {PREFETCH_READ_0(ptr); ptr += s;} break;}
			case 1: {for (; i; i--) {PREFETCH_READ_1(ptr); ptr += s;} break;}
			case 2: {for (; i; i--) {PREFETCH_READ_2(ptr); ptr += s;} break;}
			case 3: {for (; i; i--) {PREFETCH_READ_3(ptr); ptr += s;} break;}
			default: {calls = (U)0;}
		}
	}
	else {
		switch (locality) {
			case 0: {for (; i; i--) {PREFETCH_WRITE_0(ptr); ptr += s;} break;}
			case 1: {for (; i; i--) {PREFETCH_WRITE_1(ptr); ptr += s;} break;}
			case 2: {for (; i; i--) {PREFETCH_WRITE_2(ptr); ptr += s;} break;}
			case 3: {for (; i; i--) {PREFETCH_WRITE_3(ptr); ptr += s;} break;}
			default: {calls = (U)0;}
		}
	}
	return (calls);
}

//---------------------------------------------------------------------------

# endif

