//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/opengl/context/object_ref.hpp>
#include <sge/opengl/texture/readwrite_lock.hpp>
#include <sge/renderer/resource_flags_field_fwd.hpp>
#include <sge/renderer/lock_flags/method.hpp>

sge::opengl::texture::readwrite_lock::readwrite_lock(
    sge::opengl::context::object_ref const _context,
    size_type const _read_size,
    size_type const _write_size,
    size_type const _stride,
    sge::renderer::resource_flags_field const &_flags)
    : read_lock_(_context, _read_size, _stride, _flags),
      write_lock_(_context, _write_size, _stride, _flags)
{
}

sge::opengl::texture::readwrite_lock::~readwrite_lock() = default;

void sge::opengl::texture::readwrite_lock::lock() { read_lock_.lock(); }

void sge::opengl::texture::readwrite_lock::unlock() { write_lock_.unlock(); }

void sge::opengl::texture::readwrite_lock::pre_unlock() { write_lock_.lock(); }

void sge::opengl::texture::readwrite_lock::post_copy() { read_lock_.unlock(); }

sge::opengl::texture::readwrite_lock::pointer sge::opengl::texture::readwrite_lock::read_pointer()
{
  return read_lock_.read_pointer();
}

sge::opengl::texture::readwrite_lock::pointer sge::opengl::texture::readwrite_lock::write_pointer()
{
  return write_lock_.write_pointer();
}

sge::opengl::texture::readwrite_lock::pointer
sge::opengl::texture::readwrite_lock::read_view_pointer()
{
  return read_lock_.read_view_pointer();
}

sge::opengl::texture::readwrite_lock::pointer
sge::opengl::texture::readwrite_lock::write_view_pointer()
{
  return write_lock_.write_view_pointer();
}

sge::renderer::lock_flags::method sge::opengl::texture::readwrite_lock::method() const
{
  return renderer::lock_flags::method::readwrite;
}
