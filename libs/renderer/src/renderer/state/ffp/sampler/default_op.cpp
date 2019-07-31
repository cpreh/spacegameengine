//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/renderer/state/ffp/sampler/arg.hpp>
#include <sge/renderer/state/ffp/sampler/arg1.hpp>
#include <sge/renderer/state/ffp/sampler/arg2.hpp>
#include <sge/renderer/state/ffp/sampler/binary_op.hpp>
#include <sge/renderer/state/ffp/sampler/binary_op_type.hpp>
#include <sge/renderer/state/ffp/sampler/default_op.hpp>
#include <sge/renderer/state/ffp/sampler/op.hpp>


sge::renderer::state::ffp::sampler::op
sge::renderer::state::ffp::sampler::default_op()
{
	return
		sge::renderer::state::ffp::sampler::op(
			sge::renderer::state::ffp::sampler::binary_op(
				sge::renderer::state::ffp::sampler::binary_op_type::modulate,
				sge::renderer::state::ffp::sampler::arg1(
					sge::renderer::state::ffp::sampler::arg::texture
				),
				sge::renderer::state::ffp::sampler::arg2(
					sge::renderer::state::ffp::sampler::arg::previous
				)
			)
		);
}
