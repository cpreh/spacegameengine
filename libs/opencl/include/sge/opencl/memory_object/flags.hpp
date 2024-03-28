//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_OPENCL_MEMORY_OBJECT_FLAGS_HPP_INCLUDED
#define SGE_OPENCL_MEMORY_OBJECT_FLAGS_HPP_INCLUDED

#include <sge/opencl/memory_object/flags_fwd.hpp> // IWYU pragma: keep
#include <fcppt/config/external_begin.hpp>
#include <cstdint>
#include <fcppt/config/external_end.hpp>

namespace sge::opencl::memory_object
{

enum class flags : std::uint8_t
{
  read,
  write,
  alloc_host_ptr,
  fcppt_maximum = alloc_host_ptr
};

}

#endif
