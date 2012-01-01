/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2012 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include <sge/opengl/texture/create_lock.hpp>
#include <sge/opengl/texture/lock_base.hpp>
#include <sge/opengl/texture/lock_base_unique_ptr.hpp>
#include <sge/opengl/texture/readonly_lock.hpp>
#include <sge/opengl/texture/readwrite_lock.hpp>
#include <sge/opengl/texture/writeonly_lock.hpp>
#include <sge/renderer/resource_flags_field.hpp>
#include <sge/renderer/lock_flags/method.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/ref.hpp>
#include <fcppt/assert/unreachable.hpp>


sge::opengl::texture::lock_base_unique_ptr
sge::opengl::texture::create_lock(
	opengl::context::object &_context,
	renderer::lock_flags::method::type const _method,
	texture::lock_base::size_type const _read_size,
	texture::lock_base::size_type const _write_size,
	texture::lock_base::size_type const _stride,
	renderer::resource_flags_field const &_flags
)
{
	switch(
		_method
	)
	{
	case renderer::lock_flags::method::read:
		return
			texture::lock_base_unique_ptr(
				fcppt::make_unique_ptr<
					opengl::texture::readonly_lock
				>(
					fcppt::ref(
						_context
					),
					_read_size,
					_stride,
					_flags
				)
			);
	case renderer::lock_flags::method::write:
		return
			texture::lock_base_unique_ptr(
				fcppt::make_unique_ptr<
					texture::writeonly_lock
				>(
					fcppt::ref(
						_context
					),
					_write_size,
					_stride,
					_flags
				)
			);
	case renderer::lock_flags::method::readwrite:
		return
			texture::lock_base_unique_ptr(
				fcppt::make_unique_ptr<
					texture::readwrite_lock
				>(
					fcppt::ref(
						_context
					),
					_read_size,
					_write_size,
					_stride,
					_flags
				)
			);
	}

	FCPPT_ASSERT_UNREACHABLE;
}

