//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_RENDERER_STATE_FFP_LIGHTING_SCOPED_HPP_INCLUDED
#define SGE_RENDERER_STATE_FFP_LIGHTING_SCOPED_HPP_INCLUDED

#include <sge/renderer/context/ffp_ref.hpp>
#include <sge/renderer/detail/symbol.hpp>
#include <sge/renderer/state/ffp/lighting/object_fwd.hpp>
#include <sge/renderer/state/ffp/lighting/scoped_fwd.hpp>
#include <fcppt/nonmovable.hpp>
#include <fcppt/reference_fwd.hpp>


namespace sge::renderer::state::ffp::lighting
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
		fcppt::reference<
			sge::renderer::state::ffp::lighting::object const
		>
	);

	SGE_RENDERER_DETAIL_SYMBOL
	~scoped();
private:
	sge::renderer::context::ffp_ref const context_;
};

}

#endif
