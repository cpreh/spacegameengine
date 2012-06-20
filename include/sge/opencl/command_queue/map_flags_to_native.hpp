#ifndef SGE_OPENCL_COMMAND_QUEUE_MAP_FLAGS_TO_NATIVE_HPP_INCLUDED
#define SGE_OPENCL_COMMAND_QUEUE_MAP_FLAGS_TO_NATIVE_HPP_INCLUDED

#include <sge/opencl/command_queue/map_flags.hpp>
#include <sge/opencl/clinclude.hpp>

namespace sge
{
namespace opencl
{
namespace command_queue
{
// There's no SYMBOL missing here, this header is private. However, I didn't
// want to add a src/ and include/ directory to the implementation, so I put it
// here.
cl_map_flags
map_flags_to_native(
	sge::opencl::command_queue::map_flags::type);
}
}
}

#endif

