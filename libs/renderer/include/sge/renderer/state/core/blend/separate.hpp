//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_RENDERER_STATE_CORE_BLEND_SEPARATE_HPP_INCLUDED
#define SGE_RENDERER_STATE_CORE_BLEND_SEPARATE_HPP_INCLUDED

#include <sge/renderer/detail/symbol.hpp>
#include <sge/renderer/state/core/blend/alpha_dest.hpp>
#include <sge/renderer/state/core/blend/alpha_source.hpp>
#include <sge/renderer/state/core/blend/color_dest.hpp>
#include <sge/renderer/state/core/blend/color_source.hpp>
#include <sge/renderer/state/core/blend/separate_fwd.hpp>


namespace sge::renderer::state::core::blend
{

class separate
{
public:
	SGE_RENDERER_DETAIL_SYMBOL
	separate(
		sge::renderer::state::core::blend::color_source,
		sge::renderer::state::core::blend::color_dest,
		sge::renderer::state::core::blend::alpha_source,
		sge::renderer::state::core::blend::alpha_dest
	);

	[[nodiscard]]
	SGE_RENDERER_DETAIL_SYMBOL
	sge::renderer::state::core::blend::color_source
	color_source() const;

	[[nodiscard]]
	SGE_RENDERER_DETAIL_SYMBOL
	sge::renderer::state::core::blend::color_dest
	color_dest() const;

	[[nodiscard]]
	SGE_RENDERER_DETAIL_SYMBOL
	sge::renderer::state::core::blend::alpha_source
	alpha_source() const;

	[[nodiscard]]
	SGE_RENDERER_DETAIL_SYMBOL
	sge::renderer::state::core::blend::alpha_dest
	alpha_dest() const;
private:
	sge::renderer::state::core::blend::color_source color_source_;

	sge::renderer::state::core::blend::color_dest color_dest_;

	sge::renderer::state::core::blend::alpha_source alpha_source_;

	sge::renderer::state::core::blend::alpha_dest alpha_dest_;
};

}

#endif
