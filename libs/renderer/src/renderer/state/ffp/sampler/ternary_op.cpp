//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/renderer/state/ffp/sampler/arg1.hpp>
#include <sge/renderer/state/ffp/sampler/arg2.hpp>
#include <sge/renderer/state/ffp/sampler/arg3.hpp>
#include <sge/renderer/state/ffp/sampler/ternary_op.hpp>
#include <sge/renderer/state/ffp/sampler/ternary_op_type.hpp>


sge::renderer::state::ffp::sampler::ternary_op::ternary_op(
	sge::renderer::state::ffp::sampler::ternary_op_type const _type,
	sge::renderer::state::ffp::sampler::arg1 const _arg1,
	sge::renderer::state::ffp::sampler::arg2 const _arg2,
	sge::renderer::state::ffp::sampler::arg3 const _arg3
)
:
	type_(
		_type
	),
	arg1_(
		_arg1
	),
	arg2_(
		_arg2
	),
	arg3_(
		_arg3
	)
{
}

sge::renderer::state::ffp::sampler::ternary_op_type
sge::renderer::state::ffp::sampler::ternary_op::type() const
{
	return
		type_;
}

sge::renderer::state::ffp::sampler::arg1
sge::renderer::state::ffp::sampler::ternary_op::arg1() const
{
	return
		arg1_;
}

sge::renderer::state::ffp::sampler::arg2
sge::renderer::state::ffp::sampler::ternary_op::arg2() const
{
	return
		arg2_;
}

sge::renderer::state::ffp::sampler::arg3
sge::renderer::state::ffp::sampler::ternary_op::arg3() const
{
	return
		arg3_;
}
