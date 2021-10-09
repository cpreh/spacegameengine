//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/renderer/state/ffp/sampler/arg1.hpp>
#include <sge/renderer/state/ffp/sampler/arg2.hpp>
#include <sge/renderer/state/ffp/sampler/binary_op.hpp>
#include <sge/renderer/state/ffp/sampler/binary_op_type.hpp>

sge::renderer::state::ffp::sampler::binary_op::binary_op(
    sge::renderer::state::ffp::sampler::binary_op_type const _type,
    sge::renderer::state::ffp::sampler::arg1 const _arg1,
    sge::renderer::state::ffp::sampler::arg2 const _arg2)
    : type_(_type), arg1_(_arg1), arg2_(_arg2)
{
}

sge::renderer::state::ffp::sampler::binary_op_type
sge::renderer::state::ffp::sampler::binary_op::type() const
{
  return type_;
}

sge::renderer::state::ffp::sampler::arg1 sge::renderer::state::ffp::sampler::binary_op::arg1() const
{
  return arg1_;
}

sge::renderer::state::ffp::sampler::arg2 sge::renderer::state::ffp::sampler::binary_op::arg2() const
{
  return arg2_;
}
