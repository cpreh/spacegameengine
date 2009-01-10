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


#include "../split_states.hpp"
#include "../common.hpp"
#include "../error.hpp"
#include "../convert_states.hpp"
#include "../enable.hpp"
#include <sge/renderer/state/list.hpp>
#include <sge/renderer/arithmetic_convert.hpp>

sge::ogl::split_states::split_states(
	renderer::state::list &states)
:
	states(states)
{}

// TODO: those functions can be optimized
// to set all things in one go for a state::list

void sge::ogl::split_states::update_stencil()
{
	renderer::state::stencil_func::type const method(
		states.get<renderer::state::stencil_func::type>());
		
	if(method == renderer::state::stencil_func::off)
	{
		disable(GL_STENCIL_TEST);
		return;
	}

	enable(GL_STENCIL_TEST);

	SGE_OPENGL_SENTRY

	glStencilFunc(
		convert_states(
			method),
		static_cast<GLint>(
			states.get(renderer::state::int_::stencil_ref)),
		static_cast<GLuint>(
			states.get(renderer::state::uint_::stencil_mask)));
}

void sge::ogl::split_states::update_blend()
{
	SGE_OPENGL_SENTRY

	glBlendFunc(
		convert_states(
			states.get<renderer::state::source_blend_func::type>()),
		convert_states(
			states.get<renderer::state::dest_blend_func::type>()));
}

void sge::ogl::split_states::update_alpha_test()
{
	renderer::state::alpha_func::type const func(
		states.get<renderer::state::alpha_func::type>());

	if(func == renderer::state::alpha_func::off)
	{
		disable(GL_ALPHA_TEST);
		return;
	}
	
	enable(GL_ALPHA_TEST);

	SGE_OPENGL_SENTRY

	glAlphaFunc(
		convert_states(
			func),
		renderer::arithmetic_convert<
			GLfloat
		>(
			states.get(
				renderer::state::float_::alpha_test_ref)));
}
