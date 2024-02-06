//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/opengl/buffer/stride.hpp>
#include <sge/opengl/context/object_ref.hpp>
#include <sge/opengl/texture/create_lock.hpp>
#include <sge/opengl/texture/lock_base.hpp>
#include <sge/opengl/texture/lock_base_unique_ptr.hpp>
#include <sge/opengl/texture/read_size.hpp>
#include <sge/opengl/texture/readonly_lock.hpp>
#include <sge/opengl/texture/readwrite_lock.hpp>
#include <sge/opengl/texture/write_size.hpp>
#include <sge/opengl/texture/writeonly_lock.hpp>
#include <sge/renderer/resource_flags_field.hpp>
#include <sge/renderer/lock_flags/method.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/unique_ptr_to_base.hpp>
#include <fcppt/assert/unreachable.hpp>

sge::opengl::texture::lock_base_unique_ptr sge::opengl::texture::create_lock(
    sge::opengl::context::object_ref const _context,
    sge::renderer::lock_flags::method const _method,
    sge::opengl::texture::read_size const _read_size,
    sge::opengl::texture::write_size const _write_size,
    sge::opengl::buffer::stride const _stride,
    sge::renderer::resource_flags_field const &_flags)
{
  switch (_method)
  {
  case sge::renderer::lock_flags::method::read:
    return fcppt::unique_ptr_to_base<sge::opengl::texture::lock_base>(
        fcppt::make_unique_ptr<sge::opengl::texture::readonly_lock>(
            _context, _read_size, _stride, _flags));
  case sge::renderer::lock_flags::method::write:
    return fcppt::unique_ptr_to_base<sge::opengl::texture::lock_base>(
        fcppt::make_unique_ptr<sge::opengl::texture::writeonly_lock>(
            _context, _write_size, _stride, _flags));
  case sge::renderer::lock_flags::method::readwrite:
    return fcppt::unique_ptr_to_base<sge::opengl::texture::lock_base>(
        fcppt::make_unique_ptr<sge::opengl::texture::readwrite_lock>(
            _context, _read_size, _write_size, _stride, _flags));
  }

  FCPPT_ASSERT_UNREACHABLE;
}
