/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2012 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include <sge/opengl/check_state.hpp>
#include <sge/opengl/common.hpp>
#include <sge/opengl/disable.hpp>
#include <sge/opengl/enable.hpp>
#include <sge/opengl/state/convert/stencil_func.hpp>
#include <sge/opengl/state/deferred/parameters.hpp>
#include <sge/opengl/state/deferred/stencil_func.hpp>
#include <sge/renderer/buffer_has_stencil.hpp>
#include <sge/renderer/exception.hpp>
#include <sge/renderer/state/extract.hpp>
#include <sge/renderer/state/extract_trampoline.hpp>
#include <sge/renderer/state/int.hpp>
#include <sge/renderer/state/list_fwd.hpp>
#include <sge/renderer/state/stencil_func.hpp>
#include <sge/renderer/state/uint.hpp>
#include <fcppt/text.hpp>


void
sge::opengl::state::deferred::stencil_func(
	deferred::parameters const &_parameters,
	sge::renderer::state::list const &_list
)
{
	renderer::state::stencil_func::type const method(
		sge::renderer::state::extract<
			renderer::state::stencil_func::type
		>(
			_list
		)
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

	if(
		!sge::renderer::buffer_has_stencil(
			_parameters.depth_stencil_buffer()
		)
	)
		throw sge::renderer::exception(
			FCPPT_TEXT("You tried to use a stencil_func besides stencil_func::off.")
			FCPPT_TEXT(" This will only work if you request a stencil buffer in renderer::parameters!")
		);

	opengl::enable(
		GL_STENCIL_TEST
	);

	::glStencilFunc(
		state::convert::stencil_func(
			method
		),
		static_cast<
			GLint
		>(
			sge::renderer::state::extract_trampoline(
				_list,
				renderer::state::int_::stencil_ref
			)
		),
		static_cast<
			GLuint
		>(
			sge::renderer::state::extract_trampoline(
				_list,
				renderer::state::uint::stencil_mask
			)
		)
	);

	SGE_OPENGL_CHECK_STATE(
		FCPPT_TEXT("glStencilFunc failed"),
		sge::renderer::exception
	)
}
