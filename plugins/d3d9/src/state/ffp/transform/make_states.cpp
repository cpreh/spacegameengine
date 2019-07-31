//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/d3d9/convert/matrix.hpp>
#include <sge/d3d9/state/ffp/transform/make_states.hpp>
#include <sge/d3d9/state/ffp/transform/state.hpp>
#include <sge/renderer/state/ffp/transform/parameters.hpp>
#include <fcppt/math/matrix/transpose.hpp>


sge::d3d9::state::ffp::transform::state const
sge::d3d9::state::ffp::transform::make_states(
	sge::renderer::state::ffp::transform::parameters const &_parameters
)
{
	return
		sge::d3d9::state::ffp::transform::state(
			sge::d3d9::convert::matrix(
				fcppt::math::matrix::transpose(
					_parameters.matrix()
				)
			)
		);
}
