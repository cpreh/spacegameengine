//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/opengl/buffer/pbo_context.hpp>
#include <sge/opengl/buffer/stride.hpp>
#include <sge/opengl/context/object_ref.hpp>
#include <sge/opengl/context/use.hpp>
#include <sge/opengl/texture/write_size.hpp>
#include <sge/opengl/texture/writeonly_lock.hpp>
#include <sge/renderer/resource_flags_field.hpp>
#include <sge/renderer/lock_flags/method.hpp>
#include <fcppt/make_ref.hpp>
#include <fcppt/assert/unreachable.hpp>

sge::opengl::texture::writeonly_lock::writeonly_lock(
    sge::opengl::context::object_ref const _context,
    sge::opengl::texture::write_size const _lock_size,
    sge::opengl::buffer::stride const _stride,
    sge::renderer::resource_flags_field const &_flags)
    : buffer_(
          fcppt::make_ref(
              sge::opengl::context::use<sge::opengl::buffer::pbo_context>(_context, _context)
                  .unpack_buffer()),
          _lock_size.get(),
          _stride,
          _flags,
          nullptr)
{
}

sge::opengl::texture::writeonly_lock::~writeonly_lock() = default;

void sge::opengl::texture::writeonly_lock::lock() { buffer_.lock(this->method()); }

void sge::opengl::texture::writeonly_lock::unlock() { buffer_.unlock(); }

void sge::opengl::texture::writeonly_lock::pre_unlock() {}

void sge::opengl::texture::writeonly_lock::post_copy() {}

sge::opengl::texture::writeonly_lock::pointer sge::opengl::texture::writeonly_lock::read_pointer()
{
  FCPPT_ASSERT_UNREACHABLE;
}

sge::opengl::texture::writeonly_lock::pointer sge::opengl::texture::writeonly_lock::write_pointer()
{
  return buffer_.raw_buffer();
}

sge::opengl::texture::writeonly_lock::pointer
sge::opengl::texture::writeonly_lock::read_view_pointer()
{
  FCPPT_ASSERT_UNREACHABLE;
}

sge::opengl::texture::writeonly_lock::pointer
sge::opengl::texture::writeonly_lock::write_view_pointer()
{
  return buffer_.data();
}

sge::renderer::lock_flags::method sge::opengl::texture::writeonly_lock::method() const
{
  return sge::renderer::lock_flags::method::write;
}
