//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/d3d9/d3dinclude.hpp>
#include <sge/d3d9/state/core/sampler/state_vector.hpp>
#include <sge/d3d9/state/core/sampler/filter/make_states.hpp>
#include <sge/d3d9/state/core/sampler/filter/visitor.hpp>
#include <sge/renderer/state/core/sampler/filter/parameters.hpp>
#include <fcppt/variant/apply.hpp>


sge::d3d9::state::core::sampler::state_vector
sge::d3d9::state::core::sampler::filter::make_states(
	sge::renderer::state::core::sampler::filter::parameters const &_parameters
)
{
	return
		fcppt::variant::apply(
			sge::d3d9::state::core::sampler::filter::visitor(),
			_parameters.variant()
		);
}
