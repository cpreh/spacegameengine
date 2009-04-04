#include <sge/endianness/swap.hpp>
#include <algorithm>

void sge::endianness::swap(
	unsigned char* const t, 
	std::size_t const len)
{
	for(std::size_t i = 0; i < len/2; ++i)
		std::swap(t[i], t[len-i-1]);
}
