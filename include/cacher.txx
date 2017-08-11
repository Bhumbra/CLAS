// single cache source.

//------------------------------------------------------------------------------
# ifndef cacher_txx
# define cacher_txx

//------------------------------------------------------------------------------
# include "dcunit.txx"

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
		dcunit<T, U> retUnit(U uno = (U)0);
	protected:
		void init(T* _cac = (T*)0,  U _num = (U)0);
		dcunit<T, U>* dcunits; // dcunit instances for copy_toing to cache
		U sot; // sizeof(T);
		T* cac; // pointer to cache source
		U num; // number of data units to cache
		U al0; // outer alignment in bytes = set associativity x line size
		U al1; // inner alignment in bytes = line size 
	private:
		U nrep; // number of allocated dcunits
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
}

//---------------------------------------------------------------------------
template <class T, class U>
void cacher<T, U>::setCache(T* _cac, U _num) {
	this -> cac = _cac;
	this -> num = _num;

	// Allocate or de-allocate dcunits as required
	if (this -> num == this -> nrep) {return;}
	if (!this -> num) {
		delete[] this -> dcunits;
	}
	else {
		if (this -> nrep) {
			delete[] this -> dcunits;
		}
		this -> dcunits = new dcunit<T, U>[this -> num];
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
	T *last, *next;
	last = uno ? this -> dcunits[uno-1].retCP() : this -> cac;
	if (!last) {return last;} // force an error
	if (uno) {last += this -> dcunits[uno-1].retCL();}
	next = last + this -> nextAlignedIndOuter(last);
	this -> dcunits[uno].setA(this -> al1);
	this -> dcunits[uno].setC(next, d0, d1, d2);
	return (next);
}

//---------------------------------------------------------------------------
template <class T, class U>
dcunit<T, U> cacher<T, U>::retUnit(U uno) {
	return this -> dcunits[uno];
}

//---------------------------------------------------------------------------

# endif

