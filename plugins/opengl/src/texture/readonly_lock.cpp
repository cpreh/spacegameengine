//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/opengl/buffer/pbo_context.hpp>
#include <sge/opengl/context/object_ref.hpp>
#include <sge/opengl/context/use.hpp>
#include <sge/opengl/texture/readonly_lock.hpp>
#include <sge/renderer/lock_flags/method.hpp>
#include <fcppt/make_ref.hpp>
#include <fcppt/assert/unreachable.hpp>

sge::opengl::texture::readonly_lock::readonly_lock(
    sge::opengl::context::object_ref const _context,
    size_type const _whole_size,
    size_type const _stride,
    sge::renderer::resource_flags_field const &_flags)
    : buffer_(
          fcppt::make_ref(
              sge::opengl::context::use<sge::opengl::buffer::pbo_context>(_context, _context)
                  .pack_buffer()),
          _whole_size,
          _stride,
          _flags,
          nullptr)
{
}

sge::opengl::texture::readonly_lock::~readonly_lock() = default;

void sge::opengl::texture::readonly_lock::lock() { buffer_.lock(this->method()); }

void sge::opengl::texture::readonly_lock::unlock() { buffer_.unlock(); }

void sge::opengl::texture::readonly_lock::pre_unlock() {}

void sge::opengl::texture::readonly_lock::post_copy() {}

sge::opengl::texture::readonly_lock::pointer sge::opengl::texture::readonly_lock::read_pointer()
{
  return buffer_.raw_buffer();
}

sge::opengl::texture::readonly_lock::pointer sge::opengl::texture::readonly_lock::write_pointer()
{
  FCPPT_ASSERT_UNREACHABLE;
}

sge::opengl::texture::readonly_lock::pointer
sge::opengl::texture::readonly_lock::read_view_pointer()
{
  return buffer_.data();
}

sge::opengl::texture::readonly_lock::pointer
sge::opengl::texture::readonly_lock::write_view_pointer()
{
  FCPPT_ASSERT_UNREACHABLE;
}

sge::renderer::lock_flags::method sge::opengl::texture::readonly_lock::method() const
{
  return sge::renderer::lock_flags::method::read;
}
