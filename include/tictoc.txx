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
  double dt;

  dt = (double) t.millitm;
  dt = dt - t0.millitm;
  dt = dt / 1000;
  dt = dt + t.time - t0.time;

  return(dt);
}
//---------------------------------------------------------------------------
 
#endif

