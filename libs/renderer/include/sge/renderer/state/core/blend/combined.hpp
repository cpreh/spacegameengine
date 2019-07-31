//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_RENDERER_STATE_CORE_BLEND_COMBINED_HPP_INCLUDED
#define SGE_RENDERER_STATE_CORE_BLEND_COMBINED_HPP_INCLUDED

#include <sge/renderer/detail/symbol.hpp>
#include <sge/renderer/state/core/blend/combined_fwd.hpp>
#include <sge/renderer/state/core/blend/dest.hpp>
#include <sge/renderer/state/core/blend/source.hpp>


namespace sge
{
namespace renderer
{
namespace state
{
namespace core
{
namespace blend
{

class combined
{
public:
	SGE_RENDERER_DETAIL_SYMBOL
	combined(
		sge::renderer::state::core::blend::source,
		sge::renderer::state::core::blend::dest
	);

	SGE_RENDERER_DETAIL_SYMBOL
	sge::renderer::state::core::blend::source
	source() const;

	SGE_RENDERER_DETAIL_SYMBOL
	sge::renderer::state::core::blend::dest
	dest() const;
private:
	sge::renderer::state::core::blend::source source_;

	sge::renderer::state::core::blend::dest dest_;
};

}
}
}
}
}

#endif

