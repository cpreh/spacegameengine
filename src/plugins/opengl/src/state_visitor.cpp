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


#include "../state_visitor.hpp"
#include "../device.hpp"
#include "../conversion.hpp"
#include "../enable.hpp"
#include "../error.hpp"
#include <sge/exception.hpp>
#include <sge/text.hpp>

sge::ogl::state_visitor::state_visitor(
	device& rend)
: rend(rend)
{}

void sge::ogl::state_visitor::operator()(
	renderer::int_state::type const s) const
{
	SGE_OPENGL_SENTRY

	typedef renderer::state_var_traits<int> rs;

	switch(s.state_id) {
	case rs::stencil_clear_val:
		glClearStencil(s.value());
		break;
	default:
		throw exception(
			SGE_TEXT("Invalid int_state!"));
	}
}

void sge::ogl::state_visitor::operator()(
	renderer::float_state::type const s) const
{
	SGE_OPENGL_SENTRY

	typedef renderer::state_var_traits<float> rs;

	switch(s.state_id) {
	case rs::zbuffer_clear_val:
		glClearDepth(s.value());
		break;
	case rs::fog_start:
	case rs::fog_end:
	case rs::fog_density:
		glFogf(convert_fog_float_state(s), s.value());
		break;
	default:
		throw exception(SGE_TEXT("Invalid float_state!"));
	}
}

void sge::ogl::state_visitor::operator()(
	renderer::bool_state::type const s) const
{
	typedef renderer::state_var_traits<bool> rs;

	switch(s.state_id) {
	case rs::clear_backbuffer:
	case rs::clear_zbuffer:
	case rs::clear_stencil:
		break;
	case rs::enable_alpha_blending:
	case rs::enable_lighting:
		enable(convert_cast(s), s.value());
		break;
	default:
		throw exception(SGE_TEXT("Invalid bool_state!"));
	}
}

void sge::ogl::state_visitor::operator()(
	renderer::color_state::type const s) const
{
	SGE_OPENGL_SENTRY

	typedef renderer::state_var_traits<renderer::any_color> rs;

	switch(s.state_id) {
	case rs::clear_color:
		// FIXME: use gil here too!
/*		glClearColor(
			red_part_rgba_f(s.value()),
			green_part_rgba_f(s.value()),
			blue_part_rgba_f(s.value()),
			alpha_part_rgba_f(s.value()));*/
		break;
	case rs::ambient_light_color:
		{
			//const color4 fc = color_to_color4(s.value());
			//glLightModelfv(GL_LIGHT_MODEL_AMBIENT, reinterpret_cast<const GLfloat*>(&fc));
		}
		break;
	case rs::fog_color:
		{
			//const color4 fc = color_to_color4(s.value());
			//glFogfv(GL_FOG_COLOR, reinterpret_cast<const GLfloat*>(&fc));
		}
		break;
	default:
		throw exception(SGE_TEXT("Invalid color_state!"));
	}
}

void sge::ogl::state_visitor::operator()(
	renderer::cull_mode::type const m) const
{
	if(m.value() == renderer::state_cull_mode_type::off)
	{
		disable(GL_CULL_FACE);
		return;
	}
	enable(GL_CULL_FACE);
	
	SGE_OPENGL_SENTRY
	glCullFace(convert_cast(m));
}

void sge::ogl::state_visitor::operator()(
	renderer::depth_func::type const f) const
{
	if(f.value() == renderer::state_depth_func_type::off)
	{
		disable(GL_DEPTH_TEST);
		return;
	}

	enable(GL_DEPTH_TEST);

	SGE_OPENGL_SENTRY
	glDepthFunc(convert_cast(f));
}

void sge::ogl::state_visitor::operator()(
	renderer::stencil_func::type const f) const
{
	if(f.value() == renderer::state_stencil_func_type::off)
	{
		disable(GL_STENCIL_TEST);
		return;
	}

	enable(GL_STENCIL_TEST);
	rend.set_stencil_func();
}

void sge::ogl::state_visitor::operator()(
	renderer::fog_mode::type const m) const
{
	if(m.value() == renderer::state_fog_mode_type::off)
	{
		disable(GL_FOG);
		return;
	}

	enable(GL_FOG);

	SGE_OPENGL_SENTRY
	glFogi(GL_FOG_MODE, convert_cast(m));
}

void sge::ogl::state_visitor::operator()(
	renderer::draw_mode::type const m) const
{
	SGE_OPENGL_SENTRY
	glPolygonMode(
		GL_FRONT_AND_BACK,
		convert_cast(m));
}

void sge::ogl::state_visitor::operator()(
	renderer::source_blend_func::type) const
{
	rend.set_blend_func();
}

void sge::ogl::state_visitor::operator()(
	renderer::dest_blend_func::type) const
{
	rend.set_blend_func();
}
