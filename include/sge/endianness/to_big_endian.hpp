#ifndef SGE_ENDIANNESS_TO_big_ENDIAN_HPP_INCLUDED
#define SGE_ENDIANNESS_TO_big_ENDIAN_HPP_INCLUDED

#include <sge/endianness/is_little_endian.hpp>
#include <sge/endianness/swap.hpp>

namespace sge
{
namespace endianness
{
template<typename T>
T to_big_endian(T const &t)
{
	if(is_little_endian())
		return swap(t);
	return t;
}
}
}
