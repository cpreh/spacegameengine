//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_OPENCL_IMPL_MEMORY_OBJECT_RENDERER_BUFFER_LOCK_MODE_TO_CL_MEM_FLAGS_HPP_INCLUDED
#define SGE_OPENCL_IMPL_MEMORY_OBJECT_RENDERER_BUFFER_LOCK_MODE_TO_CL_MEM_FLAGS_HPP_INCLUDED

#include <sge/opencl/memory_object/renderer_buffer_lock_mode.hpp>
#include <fcppt/assert/unreachable.hpp>
#include <fcppt/config/external_begin.hpp>
#include <CL/cl.h>
#include <fcppt/config/external_end.hpp>

namespace sge::opencl::impl::memory_object
{

inline cl_mem_flags renderer_buffer_lock_mode_to_cl_mem_flags(
    sge::opencl::memory_object::renderer_buffer_lock_mode const _lock_mode)
{
  switch (_lock_mode)
  {
  case sge::opencl::memory_object::renderer_buffer_lock_mode::read_only:
    return CL_MEM_READ_ONLY; // NOLINT(hicpp-signed-bitwise)
  case sge::opencl::memory_object::renderer_buffer_lock_mode::write_only:
    return CL_MEM_WRITE_ONLY; // NOLINT(hicpp-signed-bitwise)
  case sge::opencl::memory_object::renderer_buffer_lock_mode::read_write:
    return CL_MEM_READ_WRITE; // NOLINT(hicpp-signed-bitwise)
  }
  FCPPT_ASSERT_UNREACHABLE;
}

}

#endif
