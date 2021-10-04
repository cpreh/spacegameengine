//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_RENDERER_STATE_FFP_SAMPLER_SCOPED_HPP_INCLUDED
#define SGE_RENDERER_STATE_FFP_SAMPLER_SCOPED_HPP_INCLUDED

#include <sge/renderer/context/ffp_ref.hpp>
#include <sge/renderer/detail/symbol.hpp>
#include <sge/renderer/state/ffp/sampler/const_object_ref_vector.hpp>
#include <sge/renderer/state/ffp/sampler/scoped_fwd.hpp>
#include <fcppt/nonmovable.hpp>


namespace sge::renderer::state::ffp::sampler
{

class scoped
{
	FCPPT_NONMOVABLE(
		scoped
	);
public:
	SGE_RENDERER_DETAIL_SYMBOL
	scoped(
		sge::renderer::context::ffp_ref context,
		sge::renderer::state::ffp::sampler::const_object_ref_vector const &
	);

	SGE_RENDERER_DETAIL_SYMBOL
	~scoped();
private:
	sge::renderer::context::ffp_ref const context_;
};

}

#endif
