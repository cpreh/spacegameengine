//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/opencl/impl/memory_object/to_opencl_mem_flags.hpp>
#include <sge/opencl/memory_object/flags.hpp>
#include <sge/opencl/memory_object/flags_field.hpp>
#include <fcppt/container/bitfield/operators.hpp>
#include <fcppt/config/external_begin.hpp>
#include <CL/cl.h>
#include <fcppt/config/external_end.hpp>

cl_mem_flags sge::opencl::impl::memory_object::to_opencl_mem_flags(
    sge::opencl::memory_object::flags_field const &f)
{
  cl_mem_flags result = 0;

  if (f & sge::opencl::memory_object::flags::read && f & sge::opencl::memory_object::flags::write)
  {
    result = CL_MEM_READ_WRITE; // NOLINT(hicpp-signed-bitwise)
  }
  else if (f & sge::opencl::memory_object::flags::read)
  {
    result = CL_MEM_READ_ONLY; // NOLINT(hicpp-signed-bitwise)
  }
  else if (f & sge::opencl::memory_object::flags::write)
  {
    result = CL_MEM_WRITE_ONLY; // NOLINT(hicpp-signed-bitwise)
  }

  if (f & sge::opencl::memory_object::flags::alloc_host_ptr)
  {
    result |= CL_MEM_ALLOC_HOST_PTR; // NOLINT(hicpp-signed-bitwise)
  }

  return result;
}
