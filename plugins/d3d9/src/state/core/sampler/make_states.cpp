//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/d3d9/state/core/sampler/make_states.hpp>
#include <sge/d3d9/state/core/sampler/state_vector.hpp>
#include <sge/d3d9/state/core/sampler/address/make_states.hpp>
#include <sge/d3d9/state/core/sampler/filter/make_states.hpp>
#include <sge/renderer/state/core/sampler/parameters.hpp>
#include <fcppt/container/join.hpp>


sge::d3d9::state::core::sampler::state_vector
sge::d3d9::state::core::sampler::make_states(
	sge::renderer::state::core::sampler::parameters const &_parameters
)
{
	return
		fcppt::container::join(
			sge::d3d9::state::core::sampler::address::make_states(
				_parameters.address()
			),
			sge::d3d9::state::core::sampler::filter::make_states(
				_parameters.filter()
			)
		);
}
