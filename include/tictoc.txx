#ifndef tictoc_txx
#define tictoc_txx
//---------------------------------------------------------------------------
#include <time.h>
#include <sys/timeb.h>

//---------------------------------------------------------------------------
template <class T>
void tic(T& t0)
{
  ftime(&t0);
}
//---------------------------------------------------------------------------
template <class T>
double toc(T& t0)
{
  T t;
  ftime(&t);
  double Dt, dt;

  dt = (int) t.millitm - (int)t0.millitm;
	dt += 1000. * ((int) t.time    - (int)t0.time);
  return(0.001*dt);
}
//---------------------------------------------------------------------------
 
#endif

