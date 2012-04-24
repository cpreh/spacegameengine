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


#include <sge/opengl/state/int.hpp>
#include <sge/opengl/state/parameters.hpp>
#include <sge/opengl/state/deferred/bundle.hpp>
#include <sge/opengl/state/deferred/object.hpp>
#include <sge/renderer/state/var.hpp>
#include <sge/renderer/state/int/available_states.hpp>
#include <sge/renderer/state/int/type.hpp>
#include <fcppt/assert/unreachable.hpp>


void
sge::opengl::state::int_(
	state::parameters const &_parameters,
	renderer::state::int_::type const &_state
)
{
	namespace rs = renderer::state::int_::available_states;

	switch(
		_state.state()
	)
	{
	case rs::stencil_ref:
		_parameters.deferred().add(
			deferred::bundle::stencil_func
		);
		return;
	}

	FCPPT_ASSERT_UNREACHABLE;
}
