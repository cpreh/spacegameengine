#include <sge/endianness/is_big_endian.hpp>
#include <sge/endianness/is_little_endian.hpp>

bool sge::endianness::is_big_endian()
{
	return !is_little_endian();
}
