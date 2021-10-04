//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_RENDERER_STATE_FFP_FOG_ENABLED_HPP_INCLUDED
#define SGE_RENDERER_STATE_FFP_FOG_ENABLED_HPP_INCLUDED

#include <sge/renderer/detail/symbol.hpp>
#include <sge/renderer/state/ffp/fog/color.hpp>
#include <sge/renderer/state/ffp/fog/density.hpp>
#include <sge/renderer/state/ffp/fog/enabled_fwd.hpp>
#include <sge/renderer/state/ffp/fog/end.hpp>
#include <sge/renderer/state/ffp/fog/mode.hpp>
#include <sge/renderer/state/ffp/fog/start.hpp>


namespace sge::renderer::state::ffp::fog
{

class enabled
{
public:
	SGE_RENDERER_DETAIL_SYMBOL
	enabled(
		sge::renderer::state::ffp::fog::mode,
		sge::renderer::state::ffp::fog::start,
		sge::renderer::state::ffp::fog::end,
		sge::renderer::state::ffp::fog::density,
		sge::renderer::state::ffp::fog::color
	);

	[[nodiscard]]
	SGE_RENDERER_DETAIL_SYMBOL
	sge::renderer::state::ffp::fog::mode
	mode() const;

	[[nodiscard]]
	SGE_RENDERER_DETAIL_SYMBOL
	sge::renderer::state::ffp::fog::start
	start() const;

	[[nodiscard]]
	SGE_RENDERER_DETAIL_SYMBOL
	sge::renderer::state::ffp::fog::end
	end() const;

	[[nodiscard]]
	SGE_RENDERER_DETAIL_SYMBOL
	sge::renderer::state::ffp::fog::density
	density() const;

	[[nodiscard]]
	SGE_RENDERER_DETAIL_SYMBOL
	sge::renderer::state::ffp::fog::color
	color() const;
private:
	sge::renderer::state::ffp::fog::mode mode_;

	sge::renderer::state::ffp::fog::start start_;

	sge::renderer::state::ffp::fog::end end_;

	sge::renderer::state::ffp::fog::density density_;

	sge::renderer::state::ffp::fog::color color_;
};

}

#endif
