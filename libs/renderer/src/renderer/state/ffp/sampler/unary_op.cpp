//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/renderer/state/ffp/sampler/arg1.hpp>
#include <sge/renderer/state/ffp/sampler/unary_op.hpp>
#include <sge/renderer/state/ffp/sampler/unary_op_type.hpp>


sge::renderer::state::ffp::sampler::unary_op::unary_op(
	sge::renderer::state::ffp::sampler::unary_op_type const _type,
	sge::renderer::state::ffp::sampler::arg1 const _arg1
)
:
	type_(
		_type
	),
	arg1_(
		_arg1
	)
{
}

sge::renderer::state::ffp::sampler::unary_op_type
sge::renderer::state::ffp::sampler::unary_op::type() const
{
	return
		type_;
}

sge::renderer::state::ffp::sampler::arg1
sge::renderer::state::ffp::sampler::unary_op::arg1() const
{
	return
		arg1_;
}
