//------------------------------------------------------------------------------
// Architecture-unoependent class for caching multiple data units within a 
// single cache source.

//------------------------------------------------------------------------------
# ifndef cacher_txx
# define cacher_txx

//------------------------------------------------------------------------------
# include "replicator.txx"

//------------------------------------------------------------------------------
// PREFETCH MACROS
// RW = 0 (read), 1 (write)
// LOCALITY = 0(NTA), 1(L3), 2(L2), 3(L1)
//------------------------------------------------------------------------------

# define PREFETCH_READ_0(PREFETCH_PTR) __builtin_prefetch (PREFETCH_PTR, 0, 0)
# define PREFETCH_READ_1(PREFETCH_PTR) __builtin_prefetch (PREFETCH_PTR, 0, 1) 
# define PREFETCH_READ_2(PREFETCH_PTR) __builtin_prefetch (PREFETCH_PTR, 0, 2)
# define PREFETCH_READ_3(PREFETCH_PTR) __builtin_prefetch (PREFETCH_PTR, 0, 3)
# define PREFETCH_WRITE_0(PREFETCH_PTR) __builtin_prefetch (PREFETCH_PTR, 1, 0)
# define PREFETCH_WRITE_1(PREFETCH_PTR) __builtin_prefetch (PREFETCH_PTR, 1, 1)
# define PREFETCH_WRITE_2(PREFETCH_PTR) __builtin_prefetch (PREFETCH_PTR, 1, 2)
# define PREFETCH_WRITE_3(PREFETCH_PTR) __builtin_prefetch (PREFETCH_PTR, 1, 3)

//------------------------------------------------------------------------------
// template functions
//------------------------------------------------------------------------------
template <class T, class U>
U nextAlignedInd(const T* ptr, U alb) {
	// returns next index from ptr aligned according to alb (expressed in bytes)
	uint64_t sot, mod;
	sot = (uint64_t)(sizeof(T));
	if (!alb) {alb = sot;};
	mod = ((uint64_t)(ptr) * sot) % (uint64_t)(alb);
	if (!mod) {return (U)0;}
	return ( (U) (((uint64_t)(alb) - mod) / sot));
}

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// cacher class
//------------------------------------------------------------------------------
template <class T, class U>
class cacher {
	public:
		cacher();
		cacher(T* _Cac = (T*)0, U _Num = (U)0);
		~cacher<T, U>();
		void setAlign(U al0 = (U)0, U al1 = (U)0);
		void setCache(T* _cac = (T*)0,  U _num = (U)0);
		U nextAlignedIndOuter(const T* ptr);
		U nextAlignedIndInner(const T* ptr);
		T* setUnit(U uno = (U)0, U d0 = (U)0, U d1 = (U)0, U d2 = (U)1);
		void cpyToUnit(U uno, T* ip, U i0, U i1);
		U prefetch(U uno = (U)0, U rw = (U)0, U locality = (U)3, U ind_beg = (U)0, U ind_end = (U)0);
	protected:
		void init(T* _cac = (T*)0,  U _num = (U)0);
		replicator<T, U>* replicators; // replicator instances for copying to cache
		U sot; // sizeof(T);
		T cac; // pointer to cache source
		U num; // number of data units to cache
		U al0; // outer alignment in bytes = set associativity x line size
		U al1; // inner alignment in bytes = line size 
		U st1; // st1 = al1 / sot
	private:
		U nrep; // number of allocated replicators
};

//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
template <class T, class U>
cacher<T, U>::cacher() {
	this -> nrep = (U)0;
	this -> init();
}

//---------------------------------------------------------------------------
template <class T, class U>
cacher<T, U>::cacher(T* _cac, U _num) {
	this -> nrep = (U)0;
	this -> init(_cac, _num);
}

//---------------------------------------------------------------------------
template <class T, class U>
cacher<T, U>::~cacher() {
	this -> init();
}

//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
template <class T, class U>
void cacher<T, U>::init(T* _cac, U _num) {
	this -> sot = sizeof(T);
	this -> setAlign();
	this -> setCache(_cac, _num);
}

//---------------------------------------------------------------------------
template <class T, class U>
void cacher<T, U>::setAlign(U _al0, U _al1) {
	this -> al0 = _al0 ? _al0 : this -> sot;
	this -> al1 = _al1 ? _al1 : this -> sot;
	this -> st1 = this -> al1 / this -> sot;
}

//---------------------------------------------------------------------------
template <class T, class U>
void cacher<T, U>::setCache(T* _cac, U _num) {
	this -> cac = _cac;
	this -> num = _num;

	// Allocate or de-allocate replicators as required
	if (this -> num == this -> nrep) {return;}
	if (!this -> num) {
		delete[] this -> replicators;
	}
	else {
		if (this -> nrep) {
			delete[] this -> replicators;
		}
		this -> replicators = new replicator<T, U>[this -> num];
	}
	this -> nrep = this -> num;
}

//---------------------------------------------------------------------------
template <class T, class U>
U cacher<T, U>::nextAlignedIndOuter(const T* ptr) {
	return (nextAlignedInd(ptr, this -> al0));
}

//---------------------------------------------------------------------------
template <class T, class U>
U cacher<T, U>::nextAlignedIndInner(const T* ptr) {
	return (nextAlignedInd(ptr, this -> al1));
}

//---------------------------------------------------------------------------
template <class T, class U>
T* cacher<T, U>::setUnit(U uno, U d0, U d1, U d2) {
	T *last, next;
	last = uno ? this -> replicators[uno-1] -> retOP() : this -> cac;
	if (!last) {return last;} // force an error
	if (uno) {last += this -> replicators[uno-1] -> retOL;}
	next = this -> nextAlignedOuter(last);
	this -> replicator[uno] -> setO(next, d0, d1, d2);
	return (next);
}

//---------------------------------------------------------------------------
template <class T, class U>
void cacher<T, U>::cpyToUnit(U uno, T* ip, U i0, U i1) {
	this -> replicators[uno] -> setI(ip, i0, i1);
	return this -> replicators[uno] -> copy();
}

//---------------------------------------------------------------------------
template <class T, class U>
U cacher<T, U>::prefetch (U uno, U rw, U locality, U ind_beg, U ind_end) {
// Returns number of inner cache prefetch calls
	replicator<T, U> rep = replicators[uno];
	if (!ind_end) {ind_end = rep -> retOL();}
	T* Ptr = rep -> OP();
	ind_beg += this -> nextAlignedInnerInd(rep -> Ptr + ind_beg);
	if (ind_beg + this -> st1 > ind_end) {return ((U)0);}
	U ind_len = ind_end - ind_beg;   
	U calls = ind_len / this -> st1; // this rounds down

	register U i = calls;
	register U s = this -> st1;
	register T* ptr = Ptr + ind_beg;
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
//---------------------------------------------------------------------------

# endif

