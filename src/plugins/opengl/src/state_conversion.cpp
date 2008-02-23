/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2007  Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include "../../../exception.hpp"
#include "../state_conversion.hpp"

// TODO: make it more obvious what happens here
/*
GLbitfield sge::ogl::state_to_stack_type(const int_state::type state)
{
	return GL_STENCIL_BUFFER_BIT;
}

GLbitfield sge::ogl::state_to_stack_type(const float_state::type state)
{
	return GL_FOG_BIT;
}

GLbitfield sge::ogl::state_to_stack_type(const bool_state::type state)
{
	return GL_ENABLE_BIT;
}

GLbitfield sge::ogl::state_to_stack_type(const color_state::type state)
{
	
	switch(state.state_id) {
	case rs::clear_color:
		return GL_DEPTH_BUFFER_BIT;
	case rs::ambient_light_color:
		return GL_LIGHTING_BIT;
	case rs::fog_color:
		return GL_FOG_BIT;
	default:
		throw exception(SGE_TEXT("state_to_stack_type(color_state): invalid color_state!"));
	}
}
*/
