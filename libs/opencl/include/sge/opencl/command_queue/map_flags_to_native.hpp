//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_OPENCL_COMMAND_QUEUE_MAP_FLAGS_TO_NATIVE_HPP_INCLUDED
#define SGE_OPENCL_COMMAND_QUEUE_MAP_FLAGS_TO_NATIVE_HPP_INCLUDED

#include <sge/opencl/clinclude.hpp>
#include <sge/opencl/command_queue/map_flags_fwd.hpp>

namespace sge::opencl::command_queue
{
// There's no DETAIL_SYMBOL missing here, this header is private. However, I didn't
// want to add a src/ and include/ directory to the implementation, so I put it
// here.
cl_map_flags map_flags_to_native(sge::opencl::command_queue::map_flags);
}

#endif
