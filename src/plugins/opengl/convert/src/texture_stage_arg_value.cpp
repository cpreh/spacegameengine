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


#include "../texture_stage_arg_value.hpp"
#include <sge/exception.hpp>
#include <sge/text.hpp>

GLenum
sge::opengl::convert::texture_stage_value(
	renderer::texture_stage_arg_value::type const value
)
{
	switch(value) {
	case renderer::texture_stage_arg_value::current:
		return GL_PRIMARY_COLOR;
	case renderer::texture_stage_arg_value::texture:
		return GL_TEXTURE;
	case renderer::texture_stage_arg_value::constant:
		return GL_CONSTANT;
	}

	throw exception(
		FCPPT_TEXT("Invalid texture_stage_arg_value!")
	);
}
