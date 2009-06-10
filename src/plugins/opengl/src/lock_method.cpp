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


#include "../lock_method.hpp"
#include <sge/exception.hpp>
#include <sge/text.hpp>

sge::opengl::lock_method::type
sge::opengl::convert_lock_method(
	renderer::lock_flag_t const m)
{
	switch(m) {
	case renderer::lock_flags::writeonly:
		return lock_method::writeonly;
	case renderer::lock_flags::readwrite:
		return lock_method::readwrite;
	default:
		throw exception(
			SGE_TEXT("Invalid lock_flags in opengl!"));
	}
}

GLuint sge::opengl::ogl_lock_method(
	lock_method::type const m)
{
	switch(m) {
	case lock_method::readonly:
		return GL_READ_ONLY;
	case lock_method::writeonly:
		return GL_WRITE_ONLY;
	case lock_method::readwrite:
		return GL_READ_WRITE;
	default:
		throw exception(
			SGE_TEXT("Invalid lock_method!"));
	}
}

bool sge::opengl::lock_flag_write(
	lock_method::type const m)
{
	return m != lock_method::readonly;
}

bool sge::opengl::lock_flag_read(
	lock_method::type const m)
{
	return m != lock_method::writeonly;
}
