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


#include <sge/opengl/common.hpp>
#include <sge/opengl/convert/index_format.hpp>
#include <sge/renderer/index/dynamic/format.hpp>
#include <fcppt/assert/unreachable.hpp>


GLenum
sge::opengl::convert::index_format(
	renderer::index::dynamic::format::type const _format
)
{
	switch(
		_format
	)
	{
	case renderer::index::dynamic::format::i16:
		return GL_UNSIGNED_SHORT;
	case renderer::index::dynamic::format::i32:
		return GL_UNSIGNED_INT;
	}

	FCPPT_ASSERT_UNREACHABLE;
}
