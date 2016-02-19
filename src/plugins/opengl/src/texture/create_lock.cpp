/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2016 Carl Philipp Reh (carlphilippreh <at> gmail.com)

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/


#include <sge/opengl/context/object_fwd.hpp>
#include <sge/opengl/texture/create_lock.hpp>
#include <sge/opengl/texture/lock_base.hpp>
#include <sge/opengl/texture/lock_base_unique_ptr.hpp>
#include <sge/opengl/texture/readonly_lock.hpp>
#include <sge/opengl/texture/readwrite_lock.hpp>
#include <sge/opengl/texture/writeonly_lock.hpp>
#include <sge/renderer/resource_flags_field.hpp>
#include <sge/renderer/lock_flags/method.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/unique_ptr_to_base.hpp>
#include <fcppt/assert/unreachable.hpp>


sge::opengl::texture::lock_base_unique_ptr
sge::opengl::texture::create_lock(
	sge::opengl::context::object &_context,
	sge::renderer::lock_flags::method const _method,
	sge::opengl::texture::lock_base::size_type const _read_size,
	sge::opengl::texture::lock_base::size_type const _write_size,
	sge::opengl::texture::lock_base::size_type const _stride,
	sge::renderer::resource_flags_field const &_flags
)
{
	switch(
		_method
	)
	{
	case sge::renderer::lock_flags::method::read:
		return
			fcppt::unique_ptr_to_base<
				sge::opengl::texture::lock_base
			>(
				fcppt::make_unique_ptr<
					sge::opengl::texture::readonly_lock
				>(
					_context,
					_read_size,
					_stride,
					_flags
				)
			);
	case sge::renderer::lock_flags::method::write:
		return
			fcppt::unique_ptr_to_base<
				sge::opengl::texture::lock_base
			>(
				fcppt::make_unique_ptr<
					sge::opengl::texture::writeonly_lock
				>(
					_context,
					_write_size,
					_stride,
					_flags
				)
			);
	case sge::renderer::lock_flags::method::readwrite:
		return
			fcppt::unique_ptr_to_base<
				sge::opengl::texture::lock_base
			>(
				fcppt::make_unique_ptr<
					sge::opengl::texture::readwrite_lock
				>(
					_context,
					_read_size,
					_write_size,
					_stride,
					_flags
				)
			);
	}

	FCPPT_ASSERT_UNREACHABLE;
}
