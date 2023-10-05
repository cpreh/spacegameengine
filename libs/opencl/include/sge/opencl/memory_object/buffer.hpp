//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_OPENCL_MEMORY_OBJECT_BUFFER_HPP_INCLUDED
#define SGE_OPENCL_MEMORY_OBJECT_BUFFER_HPP_INCLUDED

#include <sge/opencl/context/object_ref.hpp>
#include <sge/opencl/detail/symbol.hpp>
#include <sge/opencl/memory_object/base.hpp>
#include <sge/opencl/memory_object/byte_size.hpp>
#include <sge/opencl/memory_object/flags_field.hpp>
#include <sge/opencl/memory_object/renderer_buffer_lock_mode_fwd.hpp>
#include <sge/renderer/vertex/buffer_ref.hpp>
#include <fcppt/nonmovable.hpp>
#include <fcppt/config/external_begin.hpp>
#include <CL/cl.h>
#include <fcppt/config/external_end.hpp>

namespace sge::opencl::memory_object
{

class buffer : public sge::opencl::memory_object::base
{
  FCPPT_NONMOVABLE(buffer);

public:
  SGE_OPENCL_DETAIL_SYMBOL
  buffer(
      sge::opencl::context::object_ref,
      sge::opencl::memory_object::flags_field const &,
      sge::opencl::memory_object::byte_size const &);

  SGE_OPENCL_DETAIL_SYMBOL explicit buffer(
      sge::opencl::context::object_ref,
      sge::renderer::vertex::buffer_ref,
      sge::opencl::memory_object::renderer_buffer_lock_mode);

  [[nodiscard]] SGE_OPENCL_DETAIL_SYMBOL cl_mem impl() override;

  [[nodiscard]] SGE_OPENCL_DETAIL_SYMBOL sge::opencl::memory_object::byte_size byte_size() const;

  SGE_OPENCL_DETAIL_SYMBOL
  ~buffer() override;

private:
  cl_mem impl_; // NOLINT(cppcoreguidelines-use-default-member-init,modernize-use-default-member-init)
  sge::opencl::memory_object::byte_size const byte_size_;
};

}

#endif
