/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2011 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include "../create_texture_lock.hpp"
#include "../readonly_texture_lock.hpp"
#include "../writeonly_texture_lock.hpp"
#include "../readwrite_texture_lock.hpp"
#include <sge/exception.hpp>
#include <fcppt/tr1/functional.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/text.hpp>

sge::opengl::texture_lock_unique_ptr
sge::opengl::create_texture_lock(
	context::object &_context,
	lock_method::type const _method,
	texture_lock::size_type const _read_size,
	texture_lock::size_type const _write_size,
	texture_lock::size_type const _stride,
	renderer::resource_flags_field const &_flags
)
{
	switch(
		_method
	)
	{
	case lock_method::readonly:
		return
			texture_lock_unique_ptr(
				fcppt::make_unique_ptr<
					opengl::readonly_texture_lock
				>(
					std::tr1::ref(
						_context
					),
					_read_size,
					_stride,
					_flags
				)
			);
	case lock_method::writeonly:
		return
			texture_lock_unique_ptr(
				fcppt::make_unique_ptr<
					writeonly_texture_lock
				>(
					std::tr1::ref(
						_context
					),
					_write_size,
					_stride,
					_flags
				)
			);
	case lock_method::readwrite:
		return
			texture_lock_unique_ptr(
				fcppt::make_unique_ptr<
					readwrite_texture_lock
				>(
					std::tr1::ref(
						_context
					),
					_read_size,
					_write_size,
					_stride,
					_flags
				)
			);
	}

	throw sge::exception(
		FCPPT_TEXT("Invalid lock_method in opengl!")
	);
}

