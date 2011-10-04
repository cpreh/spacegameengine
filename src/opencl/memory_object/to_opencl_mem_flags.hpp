#ifndef SGE_OPENCL_MEMORY_OBJECT_TO_OPENCL_MEM_FLAGS_HPP_INCLUDED
#define SGE_OPENCL_MEMORY_OBJECT_TO_OPENCL_MEM_FLAGS_HPP_INCLUDED

#include <sge/opencl/clinclude.hpp>
#include <sge/opencl/memory_object/flags_field.hpp>

namespace sge
{
namespace opencl
{
namespace memory_object
{
cl_mem_flags
to_opencl_mem_flags(
	memory_object::flags_field const &);
}
}
}

#endif
