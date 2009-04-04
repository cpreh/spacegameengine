#ifndef SGE_ENDIANNESS_TO_LITTLE_ENDIAN_HPP_INCLUDED
#define SGE_ENDIANNESS_TO_LITTLE_ENDIAN_HPP_INCLUDED

#include <sge/endianness/is_little_endian.hpp>
#include <sge/endianness/swap.hpp>

namespace sge
{
namespace endianness
{
template<typename T>
T to_little_endian(T const &t)
{
	if(!is_little_endian())
		return swap(t);
	return t;
}
}
}
