//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/d3d9/state/render_vector.hpp>
#include <sge/d3d9/state/ffp/lighting/make_states.hpp>
#include <sge/d3d9/state/ffp/lighting/visitor.hpp>
#include <sge/renderer/state/ffp/lighting/parameters.hpp>
#include <fcppt/variant/apply.hpp>


sge::d3d9::state::render_vector
sge::d3d9::state::ffp::lighting::make_states(
	sge::renderer::state::ffp::lighting::parameters const &_parameters
)
{
	return
		fcppt::variant::apply(
			sge::d3d9::state::ffp::lighting::visitor(),
			_parameters.variant()
		);
}
