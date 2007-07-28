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


#include "../../../exception.hpp"
#include "../conversion.hpp"

GLuint sge::ogl::convert_lock_flags(const lock_flag_t f)
{
	if(f & lock_flags::discard)
		return GL_WRITE_ONLY_ARB;
	return GL_READ_WRITE_ARB;
}

GLuint sge::ogl::convert_resource_flags(const resource_flag_t f)
{
	if(f & resource_flags::dynamic)
		return GL_DYNAMIC_DRAW_ARB;
	return GL_STATIC_DRAW_ARB;
}

template<> GLenum sge::ogl::convert_cast(const nonindexed_primitive_type::type& t)
{
	switch(t) {
	case nonindexed_primitive_type::point:
		return GL_POINTS;
	case nonindexed_primitive_type::line_strip:
		return GL_LINE_STRIP;
	case nonindexed_primitive_type::triangle_strip:
		return GL_TRIANGLE_STRIP;
	case nonindexed_primitive_type::triangle_fan:
		return GL_TRIANGLE_FAN;
	case nonindexed_primitive_type::line_loop:
		return GL_LINE_LOOP;
	default:
		throw exception("Invalid indexed_primitive_type!");
	}
}

template<> GLenum sge::ogl::convert_cast(const indexed_primitive_type::type& t)
{
	switch(t) {
	case indexed_primitive_type::line:
		return GL_LINES;
	case indexed_primitive_type::triangle:
		return GL_TRIANGLES;
	default:
		throw exception("Invalid nonindexed_primitive_type!");
	}
}

template<> GLenum sge::ogl::convert_cast(const bool_state::type& state)
{
	switch(state) {
	case bool_state::enable_alpha_blending:
		return GL_BLEND;
	case bool_state::enable_zbuffer:
		return GL_DEPTH_TEST;
	case bool_state::enable_stencil:
		return GL_STENCIL_TEST;
	case bool_state::enable_fog:
		return GL_FOG;
	case bool_state::enable_lighting:
		return GL_LIGHTING;
	case bool_state::enable_culling:
		return GL_CULL_FACE;
	default:
		throw exception("Invalid bool_state!");
	}
}

template<> GLenum sge::ogl::convert_cast(const min_filter::type& arg)
{
	switch(arg) {
	case min_filter::point:
		return GL_NEAREST;
	case min_filter::linear:
		return GL_LINEAR;
	case min_filter::mipmap:
		return GL_LINEAR_MIPMAP_NEAREST;
	case min_filter::trilinear:
		return GL_LINEAR_MIPMAP_LINEAR;
	default:
		throw exception("Invalid min_filter!");
	}
}

template<> GLenum sge::ogl::convert_cast(const mag_filter::type& arg)
{
	switch(arg) {
	case mag_filter::point:
		return GL_NEAREST;
	case mag_filter::linear:
		return GL_LINEAR;
	default:
		throw exception("Invalid mag_filter!");
	}
}
template<> GLenum sge::ogl::convert_cast(const cube_side::type& s)
{
	switch(s) {
	case cube_side::left:
		return GL_TEXTURE_CUBE_MAP_NEGATIVE_X_ARB;
	case cube_side::right:
		return GL_TEXTURE_CUBE_MAP_POSITIVE_X_ARB;
	case cube_side::front:
		return GL_TEXTURE_CUBE_MAP_POSITIVE_Z_ARB;
	case cube_side::back:
		return GL_TEXTURE_CUBE_MAP_NEGATIVE_Z_ARB;
	case cube_side::top:
		return GL_TEXTURE_CUBE_MAP_POSITIVE_Y_ARB;
	case cube_side::bottom:
		return GL_TEXTURE_CUBE_MAP_NEGATIVE_Y_ARB;
	default:
		throw exception("Invalid cube_side!");
	}
}

template<> GLenum sge::ogl::convert_cast(const cull_mode::type& m)
{
	switch(m) {
	case cull_mode::back:
		return GL_BACK;
	case cull_mode::front:
		return GL_FRONT;
	default:
		throw exception("Invalid cull_mode!");
	}
}

template<> GLenum sge::ogl::convert_cast(const depth_func::type& f)
{
	switch(f) {
	case depth_func::greater:
		return GL_GREATER;
	case depth_func::less_equal:
		return GL_LEQUAL;
	case depth_func::never:
		return GL_NEVER;
	case depth_func::always:
		return GL_ALWAYS;
	default:
		throw exception("Invalid depth_func!");
	}
}

template<> GLenum sge::ogl::convert_cast(const fog_mode::type& m)
{
	switch(m) {
	case fog_mode::linear:
		return GL_LINEAR;
	case fog_mode::exp:
		return GL_EXP;
	case fog_mode::exp2:
		return GL_EXP2;
	default:
		throw exception("Invalid fog_mode!");
	}
}

GLenum sge::ogl::convert_fog_float_state(const float_state::type& s)
{
	switch(s) {
	case float_state::fog_start:
		return GL_FOG_START;
	case float_state::fog_end:
		return GL_FOG_END;
	case float_state::fog_density:
		return GL_FOG_DENSITY;
	default:
		throw exception("Invalid fog float_state!");
	}
}
