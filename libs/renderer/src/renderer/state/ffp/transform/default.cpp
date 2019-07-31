//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/renderer/matrix4.hpp>
#include <sge/renderer/state/ffp/transform/default.hpp>
#include <sge/renderer/state/ffp/transform/parameters.hpp>
#include <fcppt/math/matrix/identity.hpp>


sge::renderer::state::ffp::transform::parameters
sge::renderer::state::ffp::transform::default_()
{
	return
		sge::renderer::state::ffp::transform::parameters(
			fcppt::math::matrix::identity<
				sge::renderer::matrix4
			>()
		);
}
