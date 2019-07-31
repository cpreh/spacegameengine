//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/renderer/state/ffp/sampler/alpha_op.hpp>
#include <sge/renderer/state/ffp/sampler/color_op.hpp>
#include <sge/renderer/state/ffp/sampler/op.hpp>
#include <sge/renderer/state/ffp/sampler/parameters.hpp>
#include <sge/renderer/state/ffp/sampler/parameters_both.hpp>


sge::renderer::state::ffp::sampler::parameters
sge::renderer::state::ffp::sampler::parameters_both(
	sge::renderer::state::ffp::sampler::op const &_op
)
{
	return
		sge::renderer::state::ffp::sampler::parameters(
			sge::renderer::state::ffp::sampler::color_op(
				_op
			),
			sge::renderer::state::ffp::sampler::alpha_op(
				_op
			)
		);
}
