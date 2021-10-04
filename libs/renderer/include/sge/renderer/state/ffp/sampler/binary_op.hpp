//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_RENDERER_STATE_FFP_SAMPLER_BINARY_OP_HPP_INCLUDED
#define SGE_RENDERER_STATE_FFP_SAMPLER_BINARY_OP_HPP_INCLUDED

#include <sge/renderer/detail/symbol.hpp>
#include <sge/renderer/state/ffp/sampler/arg1.hpp>
#include <sge/renderer/state/ffp/sampler/arg2.hpp>
#include <sge/renderer/state/ffp/sampler/binary_op_fwd.hpp>
#include <sge/renderer/state/ffp/sampler/binary_op_type.hpp>


namespace sge::renderer::state::ffp::sampler
{

class binary_op
{
public:
	SGE_RENDERER_DETAIL_SYMBOL
	binary_op(
		sge::renderer::state::ffp::sampler::binary_op_type,
		sge::renderer::state::ffp::sampler::arg1,
		sge::renderer::state::ffp::sampler::arg2
	);

	[[nodiscard]]
	SGE_RENDERER_DETAIL_SYMBOL
	sge::renderer::state::ffp::sampler::binary_op_type
	type() const;

	[[nodiscard]]
	SGE_RENDERER_DETAIL_SYMBOL
	sge::renderer::state::ffp::sampler::arg1
	arg1() const;

	[[nodiscard]]
	SGE_RENDERER_DETAIL_SYMBOL
	sge::renderer::state::ffp::sampler::arg2
	arg2() const;
private:
	sge::renderer::state::ffp::sampler::binary_op_type type_;

	sge::renderer::state::ffp::sampler::arg1 arg1_;

	sge::renderer::state::ffp::sampler::arg2 arg2_;
};

}

#endif
