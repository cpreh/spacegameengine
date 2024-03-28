//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_OPENCL_COMMAND_QUEUE_MAP_FLAGS_HPP_INCLUDED
#define SGE_OPENCL_COMMAND_QUEUE_MAP_FLAGS_HPP_INCLUDED

#include <sge/opencl/command_queue/map_flags_fwd.hpp> // IWYU pragma: keep
#include <fcppt/config/external_begin.hpp>
#include <cstdint>
#include <fcppt/config/external_end.hpp>

namespace sge::opencl::command_queue
{

enum class map_flags : std::uint8_t
{
  read,
  write,
  read_write
};

}

#endif
