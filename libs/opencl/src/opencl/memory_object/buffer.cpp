//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/opencl/context/object.hpp>
#include <sge/opencl/context/object_ref.hpp>
#include <sge/opencl/impl/handle_error.hpp>
#include <sge/opencl/impl/memory_object/renderer_buffer_lock_mode_to_cl_mem_flags.hpp>
#include <sge/opencl/impl/memory_object/to_opencl_mem_flags.hpp>
#include <sge/opencl/memory_object/buffer.hpp>
#include <sge/opencl/memory_object/renderer_buffer_lock_mode.hpp>
#include <sge/renderer/opengl/buffer/base.hpp>
#include <sge/renderer/vertex/buffer.hpp>
#include <sge/renderer/vertex/buffer_ref.hpp>
#include <sge/renderer/vf/dynamic/part.hpp>
#include <fcppt/text.hpp>

sge::opencl::memory_object::buffer::buffer(
    sge::opencl::context::object_ref const _context,
    memory_object::flags_field const &_flags,
    memory_object::byte_size const &_byte_size)
    : impl_(nullptr), byte_size_(_byte_size)
{
  cl_int error_code{};
  impl_ = clCreateBuffer(
      _context.get().impl(),
      sge::opencl::impl::memory_object::to_opencl_mem_flags(_flags),
      _byte_size.get(),
      nullptr,
      &error_code);

  opencl::impl::handle_error(error_code, FCPPT_TEXT("clCreateBuffer"));
}

sge::opencl::memory_object::buffer::buffer(
    sge::opencl::context::object_ref const _context,
    sge::renderer::vertex::buffer_ref const _vb,
    memory_object::renderer_buffer_lock_mode const _lock_mode)
    : impl_(nullptr),
      byte_size_(static_cast<byte_size::value_type>(
          _vb.get().linear_size() * _vb.get().format().get().stride().get()))
{
  cl_int error_code{};

  impl_ = clCreateFromGLBuffer(
      _context.get().impl(),
      sge::opencl::impl::memory_object::renderer_buffer_lock_mode_to_cl_mem_flags(_lock_mode),
      dynamic_cast<sge::renderer::opengl::buffer::base &>(_vb.get()).id().get(),
      &error_code);

  opencl::impl::handle_error(error_code, FCPPT_TEXT("clCreateFromGLBuffer"));
}

cl_mem sge::opencl::memory_object::buffer::impl() { return impl_; }

sge::opencl::memory_object::byte_size sge::opencl::memory_object::buffer::byte_size() const
{
  return byte_size_;
}

sge::opencl::memory_object::buffer::~buffer()
{
  if (impl_ == nullptr)
  {
    return;
  }

  cl_int const error_code = clReleaseMemObject(impl_);

  opencl::impl::handle_error(error_code, FCPPT_TEXT("clReleaseMemObject(buffer)"));
}
