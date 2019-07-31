//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


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
