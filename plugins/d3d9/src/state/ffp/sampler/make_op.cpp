//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/d3d9/state/ffp/sampler/instantiate_op_type.hpp>
#include <sge/d3d9/state/ffp/sampler/make_op.hpp>
#include <sge/d3d9/state/ffp/sampler/op_visitor.hpp>
#include <sge/d3d9/state/ffp/sampler/state_vector.hpp>
#include <sge/renderer/state/ffp/sampler/alpha_op.hpp>
#include <sge/renderer/state/ffp/sampler/color_op.hpp>
#include <fcppt/variant/apply.hpp>


template<
	typename OpType
>
sge::d3d9::state::ffp::sampler::state_vector
sge::d3d9::state::ffp::sampler::make_op(
	OpType const &_op
)
{
	return
		fcppt::variant::apply(
			sge::d3d9::state::ffp::sampler::op_visitor<
				OpType
			>(),
			_op.get()
		);
}

#define SGE_D3D9_STATE_FFP_SAMPLER_INSTANTIATE_MAKE_OP(\
	op_type\
)\
template \
sge::d3d9::state::ffp::sampler::state_vector \
sge::d3d9::state::ffp::sampler::make_op<\
	op_type\
>(\
	op_type const & \
)

SGE_D3D9_STATE_FFP_SAMPLER_INSTANTIATE_OP_TYPE(
	SGE_D3D9_STATE_FFP_SAMPLER_INSTANTIATE_MAKE_OP
);
