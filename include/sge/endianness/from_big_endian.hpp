#ifndef SGE_ENDIANNESS_FROM_BIG_ENDIAN_HPP_INCLUDED
#define SGE_ENDIANNESS_FROM_BIG_ENDIAN_HPP_INCLUDED

#include <sge/endianness/is_big_endian.hpp>
#include <sge/endianness/swap.hpp>

namespace sge
{
namespace endianness
{
template<typename T>
T from_big_endian(T const &t)
{
	if(!is_big_endian())
		return swap(t);
	return t;
}
}
}
