#include <sge/opencl/command_queue/map_flags_to_native.hpp>
#include <fcppt/assert/unreachable.hpp>

cl_map_flags
sge::opencl::command_queue::map_flags_to_native(
	sge::opencl::command_queue::map_flags::type const _flags)
{
	switch(
		_flags)
	{
		case sge::opencl::command_queue::map_flags::read:
			return CL_MAP_READ;
		case sge::opencl::command_queue::map_flags::write:
			return CL_MAP_WRITE;
		case sge::opencl::command_queue::map_flags::read_write:
			return CL_MAP_READ | CL_MAP_WRITE;

	}

	FCPPT_ASSERT_UNREACHABLE;
}
