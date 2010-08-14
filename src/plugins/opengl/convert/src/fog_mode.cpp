/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2010 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include "../fog_mode.hpp"
#include <sge/exception.hpp>
#include <fcppt/text.hpp>

GLenum
sge::opengl::convert::fog_mode(
	renderer::state::fog_mode::type const m
)
{
	switch(m) {
	case renderer::state::fog_mode::linear:
		return GL_LINEAR;
	case renderer::state::fog_mode::exp:
		return GL_EXP;
	case renderer::state::fog_mode::exp2:
		return GL_EXP2;
	case renderer::state::fog_mode::off:
		break;
	}

	throw exception(
		FCPPT_TEXT("Invalid fog_mode!")
	);
}
