//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_OPENCL_MEMORY_OBJECT_RENDERER_BUFFER_LOCK_MODE_HPP_INCLUDED
#define SGE_OPENCL_MEMORY_OBJECT_RENDERER_BUFFER_LOCK_MODE_HPP_INCLUDED

#include <sge/opencl/memory_object/renderer_buffer_lock_mode_fwd.hpp> // IWYU pragma: keep
#include <fcppt/config/external_begin.hpp>
#include <cstdint>
#include <fcppt/config/external_end.hpp>

namespace sge::opencl::memory_object
{

enum class renderer_buffer_lock_mode : std::uint8_t
{
  read_only,
  write_only,
  read_write
};

}

#endif
