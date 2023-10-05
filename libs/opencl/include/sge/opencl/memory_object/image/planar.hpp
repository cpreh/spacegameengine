//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_OPENCL_MEMORY_OBJECT_IMAGE_PLANAR_HPP_INCLUDED
#define SGE_OPENCL_MEMORY_OBJECT_IMAGE_PLANAR_HPP_INCLUDED

#include <sge/core/detail/class_symbol.hpp>
#include <sge/opencl/dim2.hpp>
#include <sge/opencl/context/object_ref.hpp>
#include <sge/opencl/detail/symbol.hpp>
#include <sge/opencl/memory_object/base.hpp>
#include <sge/opencl/memory_object/flags_field.hpp>
#include <sge/opencl/memory_object/image/planar_pitch.hpp>
#include <sge/renderer/texture/planar_ref.hpp>
#include <fcppt/nonmovable.hpp>
#include <fcppt/config/external_begin.hpp>
#include <CL/cl.h>
#include <fcppt/config/external_end.hpp>

namespace sge::opencl::memory_object::image
{
class SGE_CORE_DETAIL_CLASS_SYMBOL planar : public sge::opencl::memory_object::base
{
  FCPPT_NONMOVABLE(planar);

public:
  SGE_OPENCL_DETAIL_SYMBOL
  planar(
      sge::opencl::context::object_ref,
      sge::opencl::memory_object::flags_field const &,
      cl_image_format const &,
      sge::opencl::dim2 size,
      sge::opencl::memory_object::image::planar_pitch const &);

  SGE_OPENCL_DETAIL_SYMBOL
  planar(
      sge::opencl::context::object_ref,
      sge::opencl::memory_object::flags_field const &,
      sge::renderer::texture::planar_ref);

  [[nodiscard]] SGE_OPENCL_DETAIL_SYMBOL cl_mem impl() override;

  [[nodiscard]] SGE_OPENCL_DETAIL_SYMBOL cl_image_format const &image_format() const;

  [[nodiscard]] SGE_OPENCL_DETAIL_SYMBOL sge::opencl::dim2 const &size() const;

  SGE_OPENCL_DETAIL_SYMBOL
  ~planar() override;

private:
  cl_mem impl_;
  cl_image_format image_format_;
  sge::opencl::dim2 size_;
};
}

#endif
