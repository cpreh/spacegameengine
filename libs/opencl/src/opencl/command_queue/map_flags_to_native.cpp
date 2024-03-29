//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/opencl/command_queue/map_flags.hpp>
#include <sge/opencl/command_queue/map_flags_to_native.hpp>
#include <fcppt/assert/unreachable.hpp>
#include <fcppt/config/external_begin.hpp>
#include <CL/cl.h>
#include <fcppt/config/external_end.hpp>

cl_map_flags
sge::opencl::command_queue::map_flags_to_native(sge::opencl::command_queue::map_flags const _flags)
{
  switch (_flags)
  {
  case sge::opencl::command_queue::map_flags::read:
    return CL_MAP_READ; // NOLINT(hicpp-signed-bitwise)
  case sge::opencl::command_queue::map_flags::write:
    return CL_MAP_WRITE; // NOLINT(hicpp-signed-bitwise)
  case sge::opencl::command_queue::map_flags::read_write:
    return CL_MAP_READ | CL_MAP_WRITE; // NOLINT(hicpp-signed-bitwise)
  }

  FCPPT_ASSERT_UNREACHABLE;
}
