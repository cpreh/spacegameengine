#ifndef SGE_DLLAPI_HPP_INCLUDED
#define SGE_DLLAPI_HPP_INCLUDED

#if defined(_MSC_VER) || defined(MINGW)
	#define SGEDLLEXPORT __declspec(dllexport)
	#define SGEDLLIMPORT __declspec(dllimport)
#else
	#define SGEDLLEXPORT
	#define SGEDLLIMPORT
#endif

#endif
