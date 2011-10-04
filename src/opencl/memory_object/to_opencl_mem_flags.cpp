#include "to_opencl_mem_flags.hpp"
#include <fcppt/container/bitfield/basic_impl.hpp>

cl_mem_flags
sge::opencl::memory_object::to_opencl_mem_flags(
	memory_object::flags_field const &f)
{
	cl_mem_flags result = 0;

	if(f & memory_object::flags::read && f & memory_object::flags::write)
		result = CL_MEM_READ_WRITE;
	else if(f & memory_object::flags::read)
		result = CL_MEM_READ_ONLY;
	else if(f & memory_object::flags::write)
		result = CL_MEM_WRITE_ONLY;

	if(f & memory_object::flags::alloc_host_ptr)
		result |= CL_MEM_USE_HOST_PTR;

	return result;
}
