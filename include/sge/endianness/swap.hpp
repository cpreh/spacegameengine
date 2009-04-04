#ifndef SGE_ENDIANNESS_SWAP_HPP_INCLUDED
#define SGE_ENDIANNESS_SWAP_HPP_INCLUDED

#include <sge/export.hpp>
#include <cstddef>

namespace sge
{
namespace endianness
{
SGE_SYMBOL void swap(
	unsigned char*, 
	std::size_t len);

template<typename T>
T swap(T t)
{
	swap(
		reinterpret_cast<unsigned char*>(
			&t), 
		sizeof(
			T));
	return t;
}
}
}

#endif
