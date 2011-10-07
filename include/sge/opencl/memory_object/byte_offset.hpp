#ifndef SGE_OPENCL_MEMORY_OBJECT_BYTE_OFFSET_HPP_INCLUDED
#define SGE_OPENCL_MEMORY_OBJECT_BYTE_OFFSET_HPP_INCLUDED

#include <fcppt/strong_typedef.hpp>
#include <cstddef>

namespace sge
{
namespace opencl
{
namespace memory_object
{
FCPPT_MAKE_STRONG_TYPEDEF(
	std::size_t,
	byte_offset);
}
}
}

#endif
