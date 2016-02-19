/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2016 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#include <sge/d3d9/d3dinclude.hpp>
#include <sge/d3d9/state/convert/address_mode.hpp>
#include <sge/d3d9/state/core/sampler/state.hpp>
#include <sge/d3d9/state/core/sampler/state_vector.hpp>
#include <sge/d3d9/state/core/sampler/address/make_states.hpp>
#include <sge/renderer/state/core/sampler/address/parameters.hpp>


sge::d3d9::state::core::sampler::state_vector
sge::d3d9::state::core::sampler::address::make_states(
	sge::renderer::state::core::sampler::address::parameters const &_parameters
)
{
	return
		sge::d3d9::state::core::sampler::state_vector{
			sge::d3d9::state::core::sampler::state(
				D3DSAMP_ADDRESSU,
				sge::d3d9::state::convert::address_mode(
					_parameters.mode_s().get()
				)
			),
			sge::d3d9::state::core::sampler::state(
				D3DSAMP_ADDRESSV,
				sge::d3d9::state::convert::address_mode(
					_parameters.mode_t().get()
				)
			),
			sge::d3d9::state::core::sampler::state(
				D3DSAMP_ADDRESSW,
				sge::d3d9::state::convert::address_mode(
					_parameters.mode_u().get()
				)
			)
		};
}
