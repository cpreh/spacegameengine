/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2009 Carl Philipp Reh (sefi@s-e-f-i.de)

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



#include "../texture_lock_factory.hpp"
#include "../readonly_texture_lock.hpp"
#include "../writeonly_texture_lock.hpp"
#include "../readwrite_texture_lock.hpp"
#include <sge/exception.hpp>
#include <sge/text.hpp>

sge::ogl::texture_lock_auto_ptr
sge::ogl::create_texture_lock(
	lock_method::type const method,
	texture_lock::size_type const lock_size,
	texture_lock::size_type const offset,
	texture_lock::size_type const whole_size,
	texture_lock::size_type const stride,
	texture_lock::size_type const pitch,
	texture_lock::size_type const block_size,
	renderer::resource_flag_t const flags)
{
	switch(method) {
	case lock_method::readonly:
		return texture_lock_auto_ptr(
			new readonly_texture_lock(
				lock_size,
				offset,
				whole_size,
				stride,
				pitch,
				block_size,
				flags));
	case lock_method::writeonly:
		return texture_lock_auto_ptr(
			new writeonly_texture_lock(
				lock_size,
				stride,
				flags));
	case lock_method::readwrite:
		return texture_lock_auto_ptr(
			new readwrite_texture_lock(
				lock_size,
				offset,
				whole_size,
				stride,
				pitch,
				block_size,
				flags));
	default:
		throw exception(
			SGE_TEXT("Invalid lock_method in opengl!"));
	}
}

