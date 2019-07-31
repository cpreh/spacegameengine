//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_RENDERER_STATE_FFP_SAMPLER_UNARY_OP_HPP_INCLUDED
#define SGE_RENDERER_STATE_FFP_SAMPLER_UNARY_OP_HPP_INCLUDED

#include <sge/renderer/detail/symbol.hpp>
#include <sge/renderer/state/ffp/sampler/arg1.hpp>
#include <sge/renderer/state/ffp/sampler/unary_op_fwd.hpp>
#include <sge/renderer/state/ffp/sampler/unary_op_type.hpp>


namespace sge
{
namespace renderer
{
namespace state
{
namespace ffp
{
namespace sampler
{

class unary_op
{
public:
	SGE_RENDERER_DETAIL_SYMBOL
	unary_op(
		sge::renderer::state::ffp::sampler::unary_op_type,
		sge::renderer::state::ffp::sampler::arg1
	);

	SGE_RENDERER_DETAIL_SYMBOL
	sge::renderer::state::ffp::sampler::unary_op_type
	type() const;

	SGE_RENDERER_DETAIL_SYMBOL
	sge::renderer::state::ffp::sampler::arg1
	arg1() const;
private:
	sge::renderer::state::ffp::sampler::unary_op_type type_;

	sge::renderer::state::ffp::sampler::arg1 arg1_;
};

}
}
}
}
}

#endif
