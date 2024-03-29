//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_OPENCL_COMMAND_QUEUE_PROFILING_MODE_HPP_INCLUDED
#define SGE_OPENCL_COMMAND_QUEUE_PROFILING_MODE_HPP_INCLUDED

#include <sge/opencl/command_queue/profiling_mode_fwd.hpp> // IWYU pragma: keep

namespace sge::opencl::command_queue
{

enum class profiling_mode
{
  enabled,
  disabled
};

}

#endif
