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


#include "../uint.hpp"
#include "../parameters.hpp"
#include "../deferred/bundle.hpp"
#include "../deferred/object.hpp"
#include "../../check_state.hpp"
#include "../../common.hpp"
#include <sge/renderer/state/uint.hpp>
#include <sge/renderer/state/var.hpp>
#include <sge/renderer/exception.hpp>
#include <fcppt/assert/unreachable.hpp>

void
sge::opengl::state::uint(
	state::parameters const &_parameters,
	renderer::state::uint::type const &_state
)
{
	namespace rs = renderer::state::uint::available_states;

	switch(
		_state.state()
	)
	{
	case rs::stencil_mask:
		_parameters.deferred().add(
			deferred::bundle::stencil_func
		);
		return;
	case rs::stencil_write_mask:
		::glStencilMask(
			_state.value()
		);

		SGE_OPENGL_CHECK_STATE(
			FCPPT_TEXT("glStencilMask failed"),
			sge::renderer::exception
		)

		return;
	}

	FCPPT_ASSERT_UNREACHABLE;
}
