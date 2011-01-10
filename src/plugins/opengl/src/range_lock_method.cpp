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


#include "../range_lock_method.hpp"
#include <sge/renderer/exception.hpp>
#include <fcppt/text.hpp>

GLenum
sge::opengl::range_lock_method(
	lock_method::type const _method
)
{
	switch(
		_method
	)
	{
	case lock_method::readonly:
		return GL_MAP_READ_BIT | GL_MAP_INVALIDATE_RANGE_BIT;
	case lock_method::writeonly:
		return GL_MAP_WRITE_BIT;
	case lock_method::readwrite:
		return GL_MAP_READ_BIT | GL_MAP_WRITE_BIT;
	}

	throw renderer::exception(
		FCPPT_TEXT("Invalid lock_method!")
	);
}
