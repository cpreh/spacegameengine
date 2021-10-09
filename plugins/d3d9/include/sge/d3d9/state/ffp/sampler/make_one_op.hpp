//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_D3D9_STATE_FFP_SAMPLER_MAKE_ONE_OP_HPP_INCLUDED
#define SGE_D3D9_STATE_FFP_SAMPLER_MAKE_ONE_OP_HPP_INCLUDED

#include <sge/d3d9/state/convert/sampler_op.hpp>
#include <sge/d3d9/state/convert/sampler_op_type.hpp>
#include <sge/d3d9/state/ffp/sampler/state.hpp>

namespace sge
{
namespace d3d9
{
namespace state
{
namespace ffp
{
namespace sampler
{

template <typename OpType, typename Op>
sge::d3d9::state::ffp::sampler::state const make_one_op(Op const _op)
{
  return sge::d3d9::state::ffp::sampler::state(
      sge::d3d9::state::convert::sampler_op_type<OpType>::get(),
      sge::d3d9::state::convert::sampler_op(_op));
}

}
}
}
}
}

#endif
