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


#include "../depth_func.hpp"
#include "../parameters.hpp"
#include "../convert/depth_func.hpp"
#include "../../check_state.hpp"
#include "../../common.hpp"
#include "../../disable.hpp"
#include "../../enable.hpp"
#include <sge/renderer/buffer_has_depth.hpp>
#include <sge/renderer/state/depth_func.hpp>
#include <sge/renderer/exception.hpp>
#include <fcppt/text.hpp>

void
sge::opengl::state::depth_func(
	state::parameters const &_parameters,
	renderer::state::depth_func::type const _func
)
{
	if(
		_func == renderer::state::depth_func::off
	)
	{
		opengl::disable(
			GL_DEPTH_TEST
		);

		return;
	}

	if(
		!sge::renderer::buffer_has_depth(
			_parameters.depth_stencil_buffer()
		)
	)
		throw sge::renderer::exception(
			FCPPT_TEXT("You tried to use a depth_func besides depth_func::off.")
			FCPPT_TEXT(" This will only work if you request a depth buffer in renderer::parameters!")
		);

	opengl::enable(
		GL_DEPTH_TEST
	);

	::glDepthFunc(
		state::convert::depth_func(
			_func
		)
	);

	SGE_OPENGL_CHECK_STATE(
		FCPPT_TEXT("glDepthFunc failed"),
		sge::renderer::exception
	)
}
