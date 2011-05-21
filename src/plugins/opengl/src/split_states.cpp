/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2011 Carl Philipp Reh (sefi@s-e-f-i.de)

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
#include "../disable.hpp"
#include "../convert/stencil_func.hpp"
#include "../convert/stencil_op_value.hpp"
#include "../convert/source_blend_func.hpp"
#include "../convert/dest_blend_func.hpp"
#include "../convert/alpha_func.hpp"
#include <sge/renderer/state/list.hpp>
#include <sge/renderer/buffer_has_stencil.hpp>
#include <sge/renderer/exception.hpp>
#include <fcppt/text.hpp>

namespace
{

void
check_depth_stencil(
	sge::renderer::depth_stencil_buffer::type const _depth_stencil_type
)
{
	if(
		!sge::renderer::buffer_has_stencil(
			_depth_stencil_type
		)
	)
		throw sge::renderer::exception(
			FCPPT_TEXT("You tried to use a stencil_func besides stencil_func::off.")
			FCPPT_TEXT(" This will only work if you request a stencil buffer in renderer::parameters!")
		);
}

}

sge::opengl::split_states::split_states(
	renderer::state::list &_states
)
:
	states_(_states)
{
}

// TODO: those functions can be optimized
// to set all things in one go for a state::list

void
sge::opengl::split_states::update_stencil_func(
	renderer::depth_stencil_buffer::type const _depth_stencil_type
)
{
	renderer::state::stencil_func::type const method(
		states_.get<
			renderer::state::stencil_func::type
		>()
	);

	if(
		method == renderer::state::stencil_func::off
	)
	{
		opengl::disable(
			GL_STENCIL_TEST
		);

		return;
	}

	::check_depth_stencil(
		_depth_stencil_type
	);

	opengl::enable(
		GL_STENCIL_TEST
	);

	::glStencilFunc(
		convert::stencil_func(
			method
		),
		static_cast<
			GLint
		>(
			states_.get(
				renderer::state::int_::stencil_ref
			)
		),
		static_cast<
			GLuint
		>(
			states_.get(
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
sge::opengl::split_states::update_stencil_op()
{
	::glStencilOp(
		opengl::convert::stencil_op_value(
			states_.get(
				renderer::state::stencil_op::stencil_fail
			)
		),
		opengl::convert::stencil_op_value(
			states_.get(
				renderer::state::stencil_op::depth_fail
			)
		),
		opengl::convert::stencil_op_value(
			states_.get(
				renderer::state::stencil_op::pass
			)
		)
	);

	SGE_OPENGL_CHECK_STATE(
		FCPPT_TEXT("glStencilOp failed"),
		sge::renderer::exception
	)
}

void
sge::opengl::split_states::update_blend()
{
	::glBlendFunc(
		convert::source_blend_func(
			states_.get<
				renderer::state::source_blend_func::type
			>()
		),
		convert::dest_blend_func(
			states_.get<
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
		states_.get<
			renderer::state::alpha_func::type
		>()
	);

	if(
		func == renderer::state::alpha_func::off
	)
	{
		opengl::disable(
			GL_ALPHA_TEST
		);

		return;
	}

	opengl::enable(
		GL_ALPHA_TEST
	);

	::glAlphaFunc(
		convert::alpha_func(
			func
		),
		static_cast<
			GLfloat
		>(
			states_.get(
				renderer::state::float_::alpha_test_ref
			)
		)
	);

	SGE_OPENGL_CHECK_STATE(
		FCPPT_TEXT("glAlphaFunc failed"),
		sge::renderer::exception
	)
}
