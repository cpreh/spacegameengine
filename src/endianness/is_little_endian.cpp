#include <sge/endianness/is_little_endian.hpp>

#if defined(SGE_LITTLE_ENDIAN) && defined(SGE_BIG_ENDIAN)
#error "SGE_LITTLE_ENDIAN and SGE_BIG_ENDIAN defined!"
#endif

bool sge::endianness::is_little_endian()
{
#if   defined(SGE_LITTLE_ENDIAN)
	return true;
#elif defined(SGE_BIG_ENDIAN)
	return false;
#else
	typedef int type;
	union {
		type t;
		char c[sizeof(type)];
	} u;
	u.t = 1;

	return u.c[0] == u.t;
#endif
}
