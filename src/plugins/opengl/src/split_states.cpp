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


#include "../split_states.hpp"
#include "../common.hpp"
#include "../check_state.hpp"
#include "../enable.hpp"
#include "../convert/stencil_func.hpp"
#include "../convert/source_blend_func.hpp"
#include "../convert/dest_blend_func.hpp"
#include "../convert/alpha_func.hpp"
#include <sge/renderer/state/list.hpp>
#include <sge/renderer/arithmetic_convert.hpp>
#include <sge/renderer/exception.hpp>
#include <fcppt/text.hpp>

sge::opengl::split_states::split_states(
	renderer::state::list &states
)
:
	states(states)
{}

// TODO: those functions can be optimized
// to set all things in one go for a state::list

void
sge::opengl::split_states::update_stencil(
	renderer::stencil_buffer::type const _stencil_type
)
{
	renderer::state::stencil_func::type const method(
		states.get<renderer::state::stencil_func::type>()
	);

	if(method == renderer::state::stencil_func::off)
	{
		disable(GL_STENCIL_TEST);
		return;
	}

	if(
		_stencil_type == sge::renderer::stencil_buffer::off
	)
		throw sge::renderer::exception(
			FCPPT_TEXT("You tried to use a stencil_func besides stencil_func::off.")
			FCPPT_TEXT(" This will only work if you request a stencil buffer in renderer::parameters!")
		);

	enable(GL_STENCIL_TEST);

	glStencilFunc(
		convert::stencil_func(
			method
		),
		static_cast<GLint>(
			states.get(
				renderer::state::int_::stencil_ref
			)
		),
		static_cast<GLuint>(
			states.get(
				renderer::state::uint::stencil_mask
			)
		)
	);

	SGE_OPENGL_CHECK_STATE(
		FCPPT_TEXT("glStencilFunc failed"),
		sge::renderer::exception
	)
}

void
sge::opengl::split_states::update_blend()
{
	glBlendFunc(
		convert::source_blend_func(
			states.get<
				renderer::state::source_blend_func::type
			>()
		),
		convert::dest_blend_func(
			states.get<
				renderer::state::dest_blend_func::type
			>()
		)
	);

	SGE_OPENGL_CHECK_STATE(
		FCPPT_TEXT("glBlendFunc failed"),
		sge::renderer::exception
	)
}

void
sge::opengl::split_states::update_alpha_test()
{
	renderer::state::alpha_func::type const func(
		states.get<renderer::state::alpha_func::type>()
	);

	if(func == renderer::state::alpha_func::off)
	{
		disable(GL_ALPHA_TEST);
		return;
	}

	enable(GL_ALPHA_TEST);

	glAlphaFunc(
		convert::alpha_func(
			func
		),
		renderer::arithmetic_convert<
			GLfloat
		>(
			states.get(
				renderer::state::float_::alpha_test_ref
			)
		)
	);

	SGE_OPENGL_CHECK_STATE(
		FCPPT_TEXT("glAlphaFunc failed"),
		sge::renderer::exception
	)
}
