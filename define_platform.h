#ifndef _Windows
 #if defined(_WIN32)
  #define _Win32
  #define _Windows
 #elif defined(WIN32)
  #define _Win32
  #define _Windows
 #elif defined(__WIN32__)
  #define _Win32
  #define _Windows
 #elif defined(__Win32__)
  #define _Win32
  #define _Windows
 #elif defined(_WINDOWS)
  #define _Windows
 #elif defined(__INTEL__) && defined(__MWERKS__)
 // Metrowerks CodeWarrior doesn't build anything other than Win32 on INTEL, no DOS
  #define _Windows
  #define _Win32
 #endif
#else
 #if defined __Win32__ || defined _WIN32
  #ifndef _Win32
   #define _Win32
  #endif
 #endif
#endif

#ifndef _MSDOS
 #ifdef _Windows
  #define _MSDOS
 #elif defined(MSDOS)
  #define _MSDOS
 #elif defined(__MSDOS__)
  #define _MSDOS
 #endif
#endif

#ifdef _Windows
 #ifndef STRICT
// some Windows headers define STRICT. In Visual C++ at least having it defined
// affects how static member signatures are mangled, so we define it up front  
  #define STRICT
 #endif
#endif


// if not a DOS machine by now, may be Mac or Unix
// cope with Metrowerks and Symantec (and MPW?)
#ifndef _MSDOS
 #ifndef _Macintosh
  #ifdef macintosh
   #define _Macintosh
  #endif
 #endif
 #ifndef _Macintosh
  #define _Unix
 #endif
#endif
