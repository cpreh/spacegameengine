#ifndef SGE_TYPES_HPP_INCLUDED
#define SGE_TYPES_HPP_INCLUDED

#ifdef _WIN32
	#define SGE_WINDOWS_PLATFORM 1
#elif __linux__
	#define SGE_LINUX_PLATFORM 1
#endif

namespace sge
{

typedef unsigned char  uchar;
typedef unsigned short ushort;
typedef unsigned int   uint;
typedef unsigned long  ulong;
typedef char           int8;
typedef short int      int16;
typedef int            int32;
typedef uchar          uint8;
typedef ushort         uint16;
typedef uint           uint32;

typedef float space_unit;

}

#endif
