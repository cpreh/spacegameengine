//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_RENDERER_STATE_CORE_DEPTH_STENCIL_STENCIL_ENABLED_HPP_INCLUDED
#define SGE_RENDERER_STATE_CORE_DEPTH_STENCIL_STENCIL_ENABLED_HPP_INCLUDED

#include <sge/renderer/detail/symbol.hpp>
#include <sge/renderer/state/core/depth_stencil/stencil/enabled_fwd.hpp>
#include <sge/renderer/state/core/depth_stencil/stencil/enabled_variant.hpp>
#include <sge/renderer/state/core/depth_stencil/stencil/read_mask.hpp>
#include <sge/renderer/state/core/depth_stencil/stencil/ref.hpp>
#include <sge/renderer/state/core/depth_stencil/stencil/write_mask.hpp>


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

class enabled
{
public:
	SGE_RENDERER_DETAIL_SYMBOL
	enabled(
		sge::renderer::state::core::depth_stencil::stencil::enabled_variant const &,
		sge::renderer::state::core::depth_stencil::stencil::ref,
		sge::renderer::state::core::depth_stencil::stencil::read_mask,
		sge::renderer::state::core::depth_stencil::stencil::write_mask
	);

	[[nodiscard]]
	SGE_RENDERER_DETAIL_SYMBOL
	sge::renderer::state::core::depth_stencil::stencil::enabled_variant const &
	enabled_variant() const;

	[[nodiscard]]
	SGE_RENDERER_DETAIL_SYMBOL
	sge::renderer::state::core::depth_stencil::stencil::ref
	ref() const;

	[[nodiscard]]
	SGE_RENDERER_DETAIL_SYMBOL
	sge::renderer::state::core::depth_stencil::stencil::read_mask
	read_mask() const;

	[[nodiscard]]
	SGE_RENDERER_DETAIL_SYMBOL
	sge::renderer::state::core::depth_stencil::stencil::write_mask
	write_mask() const;
private:
	sge::renderer::state::core::depth_stencil::stencil::enabled_variant enabled_variant_;

	sge::renderer::state::core::depth_stencil::stencil::ref ref_;

	sge::renderer::state::core::depth_stencil::stencil::read_mask read_mask_;

	sge::renderer::state::core::depth_stencil::stencil::write_mask write_mask_;
};

}
}
}
}
}
}

#endif
