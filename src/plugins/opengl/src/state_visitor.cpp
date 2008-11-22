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
#include "../split_states.hpp"
#include "../conversion.hpp"
#include "../enable.hpp"
#include "../error.hpp"
#include <sge/renderer/any_color_convert.hpp>
#include <sge/renderer/arithmetic_convert.hpp>
#include <sge/renderer/raw_color.hpp>
#include <sge/renderer/state/var.hpp>
#include <sge/renderer/state/traits.hpp>
#include <sge/exception.hpp>
#include <sge/text.hpp>

sge::ogl::state_visitor::state_visitor(
	split_states &states)
:
	states(states)
{}

void sge::ogl::state_visitor::operator()(
	renderer::state::int_::type const s) const
{
	SGE_OPENGL_SENTRY

	typedef renderer::state::traits<
		renderer::state::int_type
	> rs;

	switch(s.state()) {
	case rs::stencil_clear_val:
		glClearStencil(s.value());
		break;
	case rs::stencil_ref:
		states.update_stencil();
		break;
	default:
		throw exception(
			SGE_TEXT("Invalid int_state!"));
	}
}

void sge::ogl::state_visitor::operator()(
	renderer::state::uint_::type const s) const
{
	typedef renderer::state::traits<
		renderer::state::uint_type
	> rs;

	switch(s.state()) {
	case rs::stencil_mask:
		states.update_stencil();
		break;
	default:
		throw exception(
			SGE_TEXT("Invalid uint_state!"));
	}
}

void sge::ogl::state_visitor::operator()(
	renderer::state::float_::type const s) const
{
	SGE_OPENGL_SENTRY

	typedef renderer::state::traits<
		renderer::state::float_type
	> rs;

	switch(s.state()) {
	case rs::zbuffer_clear_val:
		glClearDepth(
			renderer::arithmetic_convert<
				GLdouble
			>(
				s.value()));
		break;
	case rs::alpha_test_ref:
		states.update_alpha_test();
		break;
	case rs::fog_start:
	case rs::fog_end:
	case rs::fog_density:
		glFogf(
			convert_fog_float_state(s),
			renderer::arithmetic_convert<
				GLfloat
			>(
				s.value()));
		break;
	default:
		throw exception(
			SGE_TEXT("Invalid float_state!"));
	}
}

void sge::ogl::state_visitor::operator()(
	renderer::state::bool_::type const s) const
{
	typedef renderer::state::traits<
		renderer::state::bool_type
	> rs;

	switch(s.state()) {
	case rs::clear_backbuffer:
	case rs::clear_zbuffer:
	case rs::clear_stencil:
		break;
	case rs::enable_alpha_blending:
	case rs::enable_lighting:
		enable(convert_cast(s), s.value());
		break;
	default:
		throw exception(
			SGE_TEXT("Invalid bool_state!"));
	}
}

void sge::ogl::state_visitor::operator()(
	renderer::state::color_::type const s) const
{
	SGE_OPENGL_SENTRY

	typedef renderer::state::traits<
		renderer::state::color_type
	> rs;

	renderer::rgba32f_color const fcolor(
		renderer::any_color_convert<renderer::rgba32f_color>(
			s.value()));

	switch(s.state()) {
	case rs::clear_color:
		glClearColor(
			fcolor[0],
			fcolor[1],
			fcolor[2],
			fcolor[3]);
		break;
	case rs::ambient_light_color:
		glLightModelfv(
			GL_LIGHT_MODEL_AMBIENT,
			renderer::raw_color(
				fcolor).data());
		break;
	case rs::fog_color:
		glFogfv(
			GL_FOG_COLOR,
			renderer::raw_color(
				fcolor).data());
		break;
	default:
		throw exception(
			SGE_TEXT("Invalid color_state!"));
	}
}

void sge::ogl::state_visitor::operator()(
	renderer::state::cull_mode::type const m) const
{
	if(m == renderer::state::cull_mode::off)
	{
		disable(GL_CULL_FACE);
		return;
	}
	enable(GL_CULL_FACE);
	
	SGE_OPENGL_SENTRY
	glCullFace(convert_cast(m));
}

void sge::ogl::state_visitor::operator()(
	renderer::state::depth_func::type const f) const
{
	if(f == renderer::state::depth_func::off)
	{
		disable(GL_DEPTH_TEST);
		return;
	}

	enable(GL_DEPTH_TEST);

	SGE_OPENGL_SENTRY
	glDepthFunc(convert_cast(f));
}

void sge::ogl::state_visitor::operator()(
	renderer::state::stencil_func::type) const
{
	states.update_stencil();
}

void sge::ogl::state_visitor::operator()(
	renderer::state::alpha_func::type) const
{
	states.update_alpha_test();
}

void sge::ogl::state_visitor::operator()(
	renderer::state::fog_mode::type const m) const
{
	if(m == renderer::state::fog_mode::off)
	{
		disable(GL_FOG);
		return;
	}

	enable(GL_FOG);

	SGE_OPENGL_SENTRY
	glFogi(GL_FOG_MODE, convert_cast(m));
}

void sge::ogl::state_visitor::operator()(
	renderer::state::draw_mode::type const m) const
{
	SGE_OPENGL_SENTRY
	glPolygonMode(
		GL_FRONT_AND_BACK,
		convert_cast(m));
}

void sge::ogl::state_visitor::operator()(
	renderer::state::source_blend_func::type) const
{
	states.update_blend();
}

void sge::ogl::state_visitor::operator()(
	renderer::state::dest_blend_func::type) const
{
	states.update_blend();
}
