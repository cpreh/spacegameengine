//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_OPENCL_KERNEL_OBJECT_HPP_INCLUDED
#define SGE_OPENCL_KERNEL_OBJECT_HPP_INCLUDED

#include <sge/opencl/detail/symbol.hpp>
#include <sge/opencl/device/object_fwd.hpp>
#include <sge/opencl/kernel/argument_index.hpp>
#include <sge/opencl/kernel/local_buffer_fwd.hpp>
#include <sge/opencl/kernel/name.hpp>
#include <sge/opencl/kernel/numeric_type.hpp>
#include <sge/opencl/memory_object/base_ref.hpp>
#include <sge/opencl/memory_object/byte_size.hpp>
#include <sge/opencl/program/object_ref.hpp>
#include <fcppt/nonmovable.hpp>
#include <fcppt/config/external_begin.hpp>
#include <CL/cl.h>
#include <CL/cl_platform.h>
#include <cstddef>
#include <fcppt/config/external_end.hpp>

namespace sge::opencl::kernel
{

class object
{
  FCPPT_NONMOVABLE(object);

public:
  SGE_OPENCL_DETAIL_SYMBOL
  object(sge::opencl::program::object_ref, sge::opencl::kernel::name &&);

  SGE_OPENCL_DETAIL_SYMBOL
  void argument(sge::opencl::kernel::argument_index const &, sge::opencl::memory_object::base_ref);

  SGE_OPENCL_DETAIL_SYMBOL
  void
  argument(sge::opencl::kernel::argument_index const &, sge::opencl::kernel::numeric_type const &);

  SGE_OPENCL_DETAIL_SYMBOL
  void argument(
      sge::opencl::kernel::argument_index const &,
      unsigned char const *,
      sge::opencl::memory_object::byte_size const &);

  SGE_OPENCL_DETAIL_SYMBOL
  void
  argument(sge::opencl::kernel::argument_index const &, sge::opencl::kernel::local_buffer const &);

  [[nodiscard]] SGE_OPENCL_DETAIL_SYMBOL std::size_t
  work_group_size(sge::opencl::device::object &) const; // NOLINT(google-runtime-references)

  [[nodiscard]] SGE_OPENCL_DETAIL_SYMBOL sge::opencl::kernel::name::value_type const &name() const;

  [[nodiscard]] SGE_OPENCL_DETAIL_SYMBOL cl_kernel impl();

  SGE_OPENCL_DETAIL_SYMBOL
  ~object();

private:
  sge::opencl::kernel::name name_;
  cl_kernel kernel_; // NOLINT(cppcoreguidelines-use-default-member-init,modernize-use-default-member-init)
  cl_uint argument_count_; // NOLINT(cppcoreguidelines-use-default-member-init,modernize-use-default-member-init)
};

}

#endif
