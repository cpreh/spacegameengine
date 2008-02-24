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
#include "../common.hpp"
#include "../push_visitor.hpp"
#include "../renderer.hpp"

sge::ogl::push_visitor::push_visitor(renderer& rend)
: rend(rend)
{}

void sge::ogl::push_visitor::operator()(const int_state::type s)
{
	typedef renderer_state_var_traits<int> rs;

	switch(s.state_id) {
	case rs::stencil_clear_val:
		rend.add_push_bit(GL_STENCIL_BUFFER_BIT);
		break;
	default:
		throw exception(SGE_TEXT("Invalid int_state!"));
	}
}

void sge::ogl::push_visitor::operator()(const float_state::type s)
{
	typedef renderer_state_var_traits<float> rs;

	switch(s.state_id) {
	case rs::fog_start:
	case rs::fog_end:
	case rs::fog_density:
		rend.add_push_bit(GL_FOG_BIT);
		break;
	default:
		throw exception(SGE_TEXT("Invalid float_state!"));
	}
}

void sge::ogl::push_visitor::operator()(const bool_state::type s)
{
	typedef renderer_state_var_traits<bool> rs;

	switch(s.state_id) {
	case rs::enable_alpha_blending:
	case rs::enable_lighting:
		rend.add_push_bit(GL_ENABLE_BIT);
		break;
	default:
		throw exception(SGE_TEXT("Invalid bool_state!"));
	}
}

void sge::ogl::push_visitor::operator()(const color_state::type s)
{
	typedef renderer_state_var_traits<color> rs;

	switch(s.state_id) {
	case rs::clear_color:
		rend.add_push_bit(GL_DEPTH_BUFFER_BIT);
		break;
	case rs::ambient_light_color:
		rend.add_push_bit(GL_LIGHTING_BIT);
		break;
	case rs::fog_color:
		rend.add_push_bit(GL_FOG_BIT);
		break;
	default:
		throw exception(SGE_TEXT("Invalid color_state!"));
	}
}

void sge::ogl::push_visitor::operator()(const cull_mode::type)
{
	rend.add_push_bit(GL_POLYGON_BIT);
}

void sge::ogl::push_visitor::operator()(const depth_func::type)
{
	rend.add_push_bit(GL_DEPTH_BUFFER_BIT);
}

void sge::ogl::push_visitor::operator()(const stencil_func::type)
{
	rend.add_push_bit(GL_STENCIL_BUFFER_BIT);
}

void sge::ogl::push_visitor::operator()(const fog_mode::type)
{
	rend.add_push_bit(GL_FOG_BIT);
}

void sge::ogl::push_visitor::operator()(const draw_mode::type)
{
	rend.add_push_bit(GL_POLYGON_BIT);
}

void sge::ogl::push_visitor::operator()(const source_blend_func::type)
{
	rend.add_push_bit(GL_COLOR_BUFFER_BIT);
}

void sge::ogl::push_visitor::operator()(const dest_blend_func::type)
{
	rend.add_push_bit(GL_COLOR_BUFFER_BIT);
}
