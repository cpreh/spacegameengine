#ifndef SGE_OPENCL_RENDERER_MEMORY_OBJECT_BUFFER_LOCK_MODE_TO_CL_MEM_FLAGS_HPP_INCLUDED
#define SGE_OPENCL_RENDERER_MEMORY_OBJECT_BUFFER_LOCK_MODE_TO_CL_MEM_FLAGS_HPP_INCLUDED

#include <sge/opencl/memory_object/renderer_buffer_lock_mode.hpp>
#include <fcppt/assert/unreachable.hpp>
#include <fcppt/config/external_begin.hpp>
#include <CL/cl.h>
#include <fcppt/config/external_end.hpp>

namespace sge
{
namespace opencl
{
namespace memory_object
{
inline cl_mem_flags
renderer_buffer_lock_mode_to_cl_mem_flags(
	memory_object::renderer_buffer_lock_mode::type const _lock_mode)
{
	switch(_lock_mode)
	{
		case memory_object::renderer_buffer_lock_mode::read_only:
			return
				CL_MEM_READ_ONLY;
		case renderer_buffer_lock_mode::write_only:
			return
				CL_MEM_WRITE_ONLY;
		case renderer_buffer_lock_mode::read_write:
			return
				CL_MEM_READ_WRITE;
	}
	FCPPT_ASSERT_UNREACHABLE;
}
}
}
}

#endif
