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


#include "../state_visitor.hpp"
#include "../split_states.hpp"
#include "../convert_states.hpp"
#include "../convert_fog_float_state.hpp"
#include "../enable.hpp"
#include "../check_state.hpp"
#include <sge/image/color/any/convert.hpp>
#include <sge/image/color/raw.hpp>
#include <sge/renderer/arithmetic_convert.hpp>
#include <sge/renderer/state/var.hpp>
#include <sge/renderer/exception.hpp>
#include <sge/variant/object_impl.hpp>
#include <sge/exception.hpp>
#include <sge/text.hpp>

sge::ogl::state_visitor::state_visitor(
	split_states &states)
:
	states(states)
{}

sge::ogl::state_visitor::result_type
sge::ogl::state_visitor::operator()(
	renderer::state::int_::type const s) const
{
	namespace rs = renderer::state::int_::available_states;

	switch(s.state()) {
	case rs::stencil_clear_val:
		glClearStencil(s.value());
	
		SGE_OPENGL_CHECK_STATE(
			SGE_TEXT("glClearStencil failed"),
			sge::renderer::exception
		)
		break;
	case rs::stencil_ref:
		states.update_stencil();
		break;
	default:
		throw exception(
			SGE_TEXT("Invalid int_state!"));
	}
}

sge::ogl::state_visitor::result_type
sge::ogl::state_visitor::operator()(
	renderer::state::uint::type const s) const
{
	namespace rs = renderer::state::uint::available_states;

	switch(s.state()) {
	case rs::stencil_mask:
		states.update_stencil();
		break;
	default:
		throw exception(
			SGE_TEXT("Invalid uint_state!"));
	}
}

sge::ogl::state_visitor::result_type
sge::ogl::state_visitor::operator()(
	renderer::state::float_::type const &s) const
{
	namespace rs = renderer::state::float_::available_states;

	switch(s.state()) {
	case rs::zbuffer_clear_val:
		glClearDepth(
			renderer::arithmetic_convert<
				GLdouble
			>(
				s.value()
			)
		);

		SGE_OPENGL_CHECK_STATE(
			SGE_TEXT("glClearDepth failed"),
			sge::renderer::exception
		)
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
				s.value()
			)
		);

		SGE_OPENGL_CHECK_STATE(
			SGE_TEXT("glFogf failed"),
			sge::renderer::exception
		)
		break;
	default:
		throw exception(
			SGE_TEXT("Invalid float_state!"));
	}
}

sge::ogl::state_visitor::result_type
sge::ogl::state_visitor::operator()(
	renderer::state::bool_::type const s) const
{
	namespace rs = renderer::state::bool_::available_states;

	switch(s.state()) {
	case rs::clear_backbuffer:
	case rs::clear_zbuffer:
	case rs::clear_stencil:
		break;
	case rs::enable_alpha_blending:
	case rs::enable_lighting:
		enable(convert_states(s), s.value());
		break;
	default:
		throw exception(
			SGE_TEXT("Invalid bool_state!"));
	}
}

sge::ogl::state_visitor::result_type
sge::ogl::state_visitor::operator()(
	renderer::state::color::type const &s) const
{
	namespace rs = renderer::state::color::available_states;

	image::color::rgba32f const fcolor(
		image::color::any::convert<
			image::color::rgba32f
		>(
			s.value()
		)
	);

	switch(s.state()) {
	case rs::clear_color:
		glClearColor(
			fcolor[0],
			fcolor[1],
			fcolor[2],
			fcolor[3]
		);

		SGE_OPENGL_CHECK_STATE(
			SGE_TEXT("glClearColor failed"),
			sge::renderer::exception
		)
		break;
	case rs::ambient_light_color:
		glLightModelfv(
			GL_LIGHT_MODEL_AMBIENT,
			image::color::raw(
				fcolor
			).data()
		);
		SGE_OPENGL_CHECK_STATE(
			SGE_TEXT("glLightMOdelfv failed"),
			sge::renderer::exception
		)
		break;
	case rs::fog_color:
		glFogfv(
			GL_FOG_COLOR,
			image::color::raw(
				fcolor
			).data()
		);

		SGE_OPENGL_CHECK_STATE(
			SGE_TEXT("glFogfv failed"),
			sge::renderer::exception
		)
		break;
	default:
		throw exception(
			SGE_TEXT("Invalid color_state!"));
	}
}

sge::ogl::state_visitor::result_type
sge::ogl::state_visitor::operator()(
	renderer::state::cull_mode::type const m) const
{
	if(m == renderer::state::cull_mode::off)
	{
		disable(GL_CULL_FACE);
		return;
	}
	enable(GL_CULL_FACE);
	
	glCullFace(convert_states(m));

	SGE_OPENGL_CHECK_STATE(
		SGE_TEXT("glCullFace failed"),
		sge::renderer::exception
	)
}

sge::ogl::state_visitor::result_type
sge::ogl::state_visitor::operator()(
	renderer::state::depth_func::type const f) const
{
	if(f == renderer::state::depth_func::off)
	{
		disable(GL_DEPTH_TEST);
		return;
	}

	enable(GL_DEPTH_TEST);

	glDepthFunc(convert_states(f));

	SGE_OPENGL_CHECK_STATE(
		SGE_TEXT("glDepthFunc failed"),
		sge::renderer::exception
	)
}

sge::ogl::state_visitor::result_type
sge::ogl::state_visitor::operator()(
	renderer::state::stencil_func::type) const
{
	states.update_stencil();
}

sge::ogl::state_visitor::result_type
sge::ogl::state_visitor::operator()(
	renderer::state::alpha_func::type) const
{
	states.update_alpha_test();
}

sge::ogl::state_visitor::result_type
sge::ogl::state_visitor::operator()(
	renderer::state::fog_mode::type const m) const
{
	if(m == renderer::state::fog_mode::off)
	{
		disable(GL_FOG);
		return;
	}

	enable(GL_FOG);

	glFogi(GL_FOG_MODE, convert_states(m));

	SGE_OPENGL_CHECK_STATE(
		SGE_TEXT("glFogi failed"),
		sge::renderer::exception
	)
}

sge::ogl::state_visitor::result_type
sge::ogl::state_visitor::operator()(
	renderer::state::draw_mode::type const m) const
{
	glPolygonMode(
		GL_FRONT_AND_BACK,
		convert_states(m)
	);

	SGE_OPENGL_CHECK_STATE(
		SGE_TEXT("glPolygonMode failed"),
		sge::renderer::exception
	)
}

sge::ogl::state_visitor::result_type
sge::ogl::state_visitor::operator()(
	renderer::state::source_blend_func::type) const
{
	states.update_blend();
}

sge::ogl::state_visitor::result_type
sge::ogl::state_visitor::operator()(
	renderer::state::dest_blend_func::type) const
{
	states.update_blend();
}
