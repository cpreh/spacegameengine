//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_RENDERER_STATE_CORE_DEPTH_STENCIL_STENCIL_COMBINED_HPP_INCLUDED
#define SGE_RENDERER_STATE_CORE_DEPTH_STENCIL_STENCIL_COMBINED_HPP_INCLUDED

#include <sge/renderer/detail/symbol.hpp>
#include <sge/renderer/state/core/depth_stencil/stencil/combined_fwd.hpp>
#include <sge/renderer/state/core/depth_stencil/stencil/desc.hpp>


namespace sge
{
namespace renderer
{
namespace state
{
namespace core
{
namespace depth_stencil
{
namespace stencil
{

class combined
{
public:
	SGE_RENDERER_DETAIL_SYMBOL
	explicit
	combined(
		sge::renderer::state::core::depth_stencil::stencil::desc const &
	);

	SGE_RENDERER_DETAIL_SYMBOL
	sge::renderer::state::core::depth_stencil::stencil::desc const &
	desc() const;
private:
	sge::renderer::state::core::depth_stencil::stencil::desc desc_;
};

}
}
}
}
}
}

#endif
