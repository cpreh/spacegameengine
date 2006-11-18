/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006  Carl Philipp Reh (sefi@s-e-f-i.de)

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/


#include "../conversion.hpp"

GLuint sge::ogl::convert_lock_flags(const lock_flag_t f)
{
	if(f & LF_Discard)
		return GL_WRITE_ONLY_ARB;
	return GL_READ_WRITE_ARB;
}

GLuint sge::ogl::convert_resource_flags(const resource_flag_t f)
{
	if(f & RF_Dynamic)
		return GL_DYNAMIC_DRAW_ARB;
	return GL_STATIC_DRAW_ARB;
}

template<> GLenum sge::ogl::convert_cast(const primitive_type& t)
{
	switch(t) {
	case PT_Point:
		return GL_POINT;
	case PT_Line:
		return GL_LINES;
	case PT_LineStrip:
		return GL_LINE_STRIP;
	case PT_Triangle:
		return GL_TRIANGLES;
	case PT_TriangleStrip:
		return GL_TRIANGLE_STRIP;
	case PT_TriangleFan:
		return GL_TRIANGLE_FAN;
	case PT_LineLoop:
		return GL_LINE_LOOP;
	default:
		throw std::logic_error("unsupported primitive_type");
	}
}

template<> GLenum sge::ogl::convert_cast(const bool_state& state)
{
	switch(state) {
	case BS_EnableAlphaBlending:
		return GL_BLEND;
	case BS_EnableZBuffer:
		return GL_DEPTH_TEST;
	case BS_EnableStencil:
		return GL_STENCIL_TEST;
	case BS_EnableFog:
		return GL_FOG;
	case BS_EnableLighting:
		return GL_LIGHTING;
	default:
		throw std::logic_error("unsupported bool_state");
	}
}

template<> GLenum sge::ogl::convert_cast(const filter_arg& arg)
{
	switch(arg) {
	case FARG_MinFilter:
		return GL_TEXTURE_MIN_FILTER;
	case FARG_MagFilter:
		return GL_TEXTURE_MAG_FILTER;
	default:
		throw std::logic_error("unsupported filter_arg");
	}
}

template<> GLenum sge::ogl::convert_cast(const filter_arg_value& arg)
{
	switch(arg) {
	case FARGV_Point:
		return GL_NEAREST;
	case FARGV_Linear:
		return GL_LINEAR;
	default:
		throw std::logic_error("unsupported filter_arg_value");
	}
}

template<> GLenum sge::ogl::convert_cast(const cube_side& s)
{
	switch(s) {
	case CS_Left:
		return GL_TEXTURE_CUBE_MAP_NEGATIVE_X_ARB;
	case CS_Right:
		return GL_TEXTURE_CUBE_MAP_POSITIVE_X_ARB;
	case CS_Front:
		return GL_TEXTURE_CUBE_MAP_POSITIVE_Z_ARB;
	case CS_Back:
		return GL_TEXTURE_CUBE_MAP_NEGATIVE_Z_ARB;
	case CS_Top:
		return GL_TEXTURE_CUBE_MAP_POSITIVE_Y_ARB;
	case CS_Bottom:
		return GL_TEXTURE_CUBE_MAP_NEGATIVE_Y_ARB;
	default:
		throw std::logic_error("unsupported cube_side");
	}
}
