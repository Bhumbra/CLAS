# ifndef clas_arch
# define clas_arch

//------------------------------------------------------------------------------
# ifdef HAVE_ARCHITECTURE
# undef HAVE_ARCHITECTURE
# endif

//------------------------------------------------------------------------------
# ifdef __SSE4_1__
# define HAVE_ARCHITECTURE __SSE4_1__
# endif

//------------------------------------------------------------------------------
#endif

