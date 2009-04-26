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



#include "../convert_clear_bit.hpp"
#include <sge/exception.hpp>
#include <sge/text.hpp>

GLenum
sge::ogl::convert_clear_bit(
	renderer::state::bool_::trampoline_type const &s)
{
	typedef renderer::state::traits<
		renderer::state::bool_type
	> rs;

	switch(s.state()) {
	case rs::clear_backbuffer:
		return GL_COLOR_BUFFER_BIT;
	case rs::clear_zbuffer:
		return GL_DEPTH_BUFFER_BIT;
	case rs::clear_stencil:
		return GL_STENCIL_BUFFER_BIT;
	default:
		throw exception(
			SGE_TEXT("Invalid bool_state in convert_clear_bit()!"));
	}
}
