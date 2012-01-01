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


#include <sge/d3d9/state/clear.hpp>
#include <sge/d3d9/state/float.hpp>
#include <sge/d3d9/state/parameters.hpp>
#include <sge/d3d9/state/set_render_state_float.hpp>
#include <sge/d3d9/state/convert/float.hpp>
#include <sge/renderer/state/var.hpp>
#include <sge/renderer/state/float/available_states.hpp>
#include <sge/renderer/state/float/type.hpp>


void
sge::d3d9::state::float_(
	state::parameters const &_parameters,
	sge::renderer::state::float_::type const &_state
)
{
	if(
		_state.state()
		== sge::renderer::state::float_::available_states::depth_buffer_clear_val
	)
	{
		_parameters.clear().depth(
			_state.value()
		);

		return;
	}

	d3d9::state::set_render_state_float(
		_parameters.device(),
		state::convert::float_(
			_state.state()
		),
		_state.value()
	);
}
