//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/opencl/exception.hpp>
#include <sge/opencl/context/object.hpp>
#include <sge/opencl/context/object_ref.hpp>
#include <sge/opencl/impl/handle_error.hpp>
#include <sge/opencl/impl/memory_object/to_opencl_mem_flags.hpp>
#include <sge/opencl/memory_object/image/planar.hpp>
#include <sge/renderer/opengl/texture/base.hpp>
#include <sge/renderer/texture/planar.hpp>
#include <sge/renderer/texture/planar_ref.hpp>
#include <fcppt/not.hpp>
#include <fcppt/text.hpp>
#include <fcppt/cast/size_fun.hpp>
#include <fcppt/container/bitfield/object_impl.hpp>
#include <fcppt/math/box/object_impl.hpp>
#include <fcppt/math/dim/structure_cast.hpp>

sge::opencl::memory_object::image::planar::planar(
    sge::opencl::context::object_ref const _context,
    memory_object::flags_field const &_mem_flags,
    cl_image_format const &_image_format,
    sge::opencl::dim2 const _size,
    image::planar_pitch const &_pitch)
    : impl_(), image_format_(_image_format), size_(_size)
{
  if (fcppt::not_(
          _image_format.image_channel_order != CL_RGB ||
          (_image_format.image_channel_data_type != CL_UNORM_SHORT_565 &&
           _image_format.image_channel_data_type != CL_UNORM_SHORT_555)))
  {
    throw sge::opencl::exception{FCPPT_TEXT(
        "memory_object::image::planar: CL_RGB is incompatible with UNORM_SHORT_565/555")};
  }

  if (fcppt::not_(
          _image_format.image_channel_order != CL_INTENSITY ||
          (_image_format.image_channel_data_type == CL_UNORM_INT8 ||
           _image_format.image_channel_data_type == CL_UNORM_INT16 ||
           _image_format.image_channel_data_type == CL_SNORM_INT8 ||
           _image_format.image_channel_data_type == CL_SNORM_INT16 ||
           _image_format.image_channel_data_type == CL_HALF_FLOAT ||
           _image_format.image_channel_data_type == CL_FLOAT)))
  {
    throw sge::opencl::exception{FCPPT_TEXT(
        "memory_object::image::planar: CL_INTENSITY used with incompatible channel type")};
  }

  if (fcppt::not_(
          _image_format.image_channel_order != CL_LUMINANCE ||
          (_image_format.image_channel_data_type == CL_UNORM_INT8 ||
           _image_format.image_channel_data_type == CL_UNORM_INT16 ||
           _image_format.image_channel_data_type == CL_SNORM_INT8 ||
           _image_format.image_channel_data_type == CL_SNORM_INT16 ||
           _image_format.image_channel_data_type == CL_HALF_FLOAT ||
           _image_format.image_channel_data_type == CL_FLOAT)))
  {
    throw sge::opencl::exception{FCPPT_TEXT(
        "memory_object::image::planar: CL_LUMINANCE used with incompatible channel type")};
  }

  if (fcppt::not_(
          (_image_format.image_channel_order != CL_ARGB &&
           _image_format.image_channel_order != CL_BGRA) ||
          (_image_format.image_channel_data_type == CL_UNORM_INT8 ||
           _image_format.image_channel_data_type == CL_SNORM_INT8 ||
           _image_format.image_channel_data_type == CL_SIGNED_INT8 ||
           _image_format.image_channel_data_type == CL_UNSIGNED_INT8)))
  {
    throw sge::opencl::exception{FCPPT_TEXT(
        "memory_object::image::planar: CL_ARGB/BGRA used with incompatible channel type")};
  }

  cl_int error_code{};

#ifndef CL_USE_DEPRECATED_OPENCL_1_1_APIS
  cl_image_desc image_description;
  image_description.image_width = this->size_.w();
  image_description.image_height = this->size_.h();
  image_description.image_row_pitch = _pitch.get();
  image_description.num_mip_levels = 0;
  image_description.num_samples = 0;

  impl_ = clCreateImage(
      _context.get().impl(),
      sge::opencl::impl::memory_object::to_opencl_mem_flags(_mem_flags),
      &_image_format,
      &image_description,
      0,
      &error_code);

  opencl::impl::handle_error(error_code, FCPPT_TEXT("clCreateImage(planar texture)"));
#else
  impl_ = clCreateImage2D(
      _context.get().impl(),
      sge::opencl::impl::memory_object::to_opencl_mem_flags(_mem_flags),
      &_image_format,
      this->size_.w(),
      this->size_.h(),
      _pitch.get(),
      nullptr,
      &error_code);

  opencl::impl::handle_error(error_code, FCPPT_TEXT("clCreateImage(planar texture)"));
#endif
}

sge::opencl::memory_object::image::planar::planar(
    sge::opencl::context::object_ref const _context,
    sge::opencl::memory_object::flags_field const &_mem_flags,
    sge::renderer::texture::planar_ref const _renderer_texture)
    : impl_(),
      image_format_(),
      size_(fcppt::math::dim::structure_cast<sge::opencl::dim2, fcppt::cast::size_fun>(
          _renderer_texture.get().size()))
{
  cl_int error_code{};
  impl_ = clCreateFromGLTexture2D(
      _context.get().impl(),
      sge::opencl::impl::memory_object::to_opencl_mem_flags(_mem_flags),
      GL_TEXTURE_2D,
      // mip level
      0,
      dynamic_cast<renderer::opengl::texture::base &>(_renderer_texture.get()).id().get(),
      &error_code);

  opencl::impl::handle_error(error_code, FCPPT_TEXT("clCreateFromGLTexture2D()"));

  error_code =
      clGetImageInfo(impl_, CL_IMAGE_FORMAT, sizeof(cl_image_format), &image_format_, nullptr);

  opencl::impl::handle_error(error_code, FCPPT_TEXT("clGetImageInfo(image format)"));
}

cl_mem sge::opencl::memory_object::image::planar::impl() { return impl_; }

cl_image_format const &sge::opencl::memory_object::image::planar::image_format() const
{
  return image_format_;
}

sge::opencl::dim2 const &sge::opencl::memory_object::image::planar::size() const { return size_; }

sge::opencl::memory_object::image::planar::~planar()
{
  cl_int const error_code = clReleaseMemObject(impl_);

  opencl::impl::handle_error(error_code, FCPPT_TEXT("clReleaseMemObject(planar texture)"));
}
