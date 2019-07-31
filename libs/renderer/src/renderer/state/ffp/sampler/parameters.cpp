//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/renderer/state/ffp/sampler/alpha_op.hpp>
#include <sge/renderer/state/ffp/sampler/color_op.hpp>
#include <sge/renderer/state/ffp/sampler/parameters.hpp>


sge::renderer::state::ffp::sampler::parameters::parameters(
	sge::renderer::state::ffp::sampler::color_op const _color_op,
	sge::renderer::state::ffp::sampler::alpha_op const _alpha_op
)
:
	color_op_(
		_color_op
	),
	alpha_op_(
		_alpha_op
	)
{
}

sge::renderer::state::ffp::sampler::color_op
sge::renderer::state::ffp::sampler::parameters::color_op() const
{
	return
		color_op_;
}

sge::renderer::state::ffp::sampler::alpha_op
sge::renderer::state::ffp::sampler::parameters::alpha_op() const
{
	return
		alpha_op_;
}
