//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/d3d9/state/ffp/sampler/instantiate_op_type.hpp>
#include <sge/d3d9/state/ffp/sampler/make_one_arg.hpp>
#include <sge/d3d9/state/ffp/sampler/make_one_op.hpp>
#include <sge/d3d9/state/ffp/sampler/op_visitor.hpp>
#include <sge/d3d9/state/ffp/sampler/state_vector.hpp>
#include <sge/renderer/state/ffp/sampler/binary_op.hpp>
#include <sge/renderer/state/ffp/sampler/ternary_op.hpp>
#include <sge/renderer/state/ffp/sampler/unary_op.hpp>

template <typename OpType>
typename sge::d3d9::state::ffp::sampler::op_visitor<OpType>::result_type
sge::d3d9::state::ffp::sampler::op_visitor<OpType>::operator()(
    sge::renderer::state::ffp::sampler::unary_op const &_unary_op) const
{
  return sge::d3d9::state::ffp::sampler::state_vector{
      sge::d3d9::state::ffp::sampler::make_one_op<OpType>(_unary_op.type()),
      sge::d3d9::state::ffp::sampler::make_one_arg<OpType>(_unary_op.arg1())};
}

template <typename OpType>
typename sge::d3d9::state::ffp::sampler::op_visitor<OpType>::result_type
sge::d3d9::state::ffp::sampler::op_visitor<OpType>::operator()(
    sge::renderer::state::ffp::sampler::binary_op const &_binary_op) const
{
  return sge::d3d9::state::ffp::sampler::state_vector{
      sge::d3d9::state::ffp::sampler::make_one_op<OpType>(_binary_op.type()),
      sge::d3d9::state::ffp::sampler::make_one_arg<OpType>(_binary_op.arg1()),
      sge::d3d9::state::ffp::sampler::make_one_arg<OpType>(_binary_op.arg2())};
}

template <typename OpType>
typename sge::d3d9::state::ffp::sampler::op_visitor<OpType>::result_type
sge::d3d9::state::ffp::sampler::op_visitor<OpType>::operator()(
    sge::renderer::state::ffp::sampler::ternary_op const &_ternary_op) const
{
  return sge::d3d9::state::ffp::sampler::state_vector{
      sge::d3d9::state::ffp::sampler::make_one_op<OpType>(_ternary_op.type()),
      sge::d3d9::state::ffp::sampler::make_one_arg<OpType>(_ternary_op.arg1()),
      sge::d3d9::state::ffp::sampler::make_one_arg<OpType>(_ternary_op.arg2()),
      sge::d3d9::state::ffp::sampler::make_one_arg<OpType>(_ternary_op.arg3())};
}

#define SGE_D3D9_STATE_FFP_SAMPLER_INSTANTIATE_OP_VISITOR(op_type) \
  template class sge::d3d9::state::ffp::sampler::op_visitor<op_type>

SGE_D3D9_STATE_FFP_SAMPLER_INSTANTIATE_OP_TYPE(SGE_D3D9_STATE_FFP_SAMPLER_INSTANTIATE_OP_VISITOR);
