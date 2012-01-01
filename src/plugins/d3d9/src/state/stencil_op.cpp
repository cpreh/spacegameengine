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


#include <sge/d3d9/devicefuncs/set_render_state.hpp>
#include <sge/d3d9/state/parameters.hpp>
#include <sge/d3d9/state/stencil_op.hpp>
#include <sge/d3d9/state/convert/stencil_op.hpp>
#include <sge/d3d9/state/convert/stencil_op_value.hpp>
#include <sge/renderer/state/var.hpp>
#include <sge/renderer/state/stencil_op/type.hpp>


void
sge::d3d9::state::stencil_op(
	state::parameters const &_parameters,
	sge::renderer::state::stencil_op::type const &_state
)
{
	d3d9::devicefuncs::set_render_state(
		_parameters.device(),
		state::convert::stencil_op(
			_state.state()
		),
		state::convert::stencil_op_value(
			_state.value()
		)
	);
}
