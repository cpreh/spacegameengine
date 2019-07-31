//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_RENDERER_STATE_CORE_BLEND_WRITE_MASK_HPP_INCLUDED
#define SGE_RENDERER_STATE_CORE_BLEND_WRITE_MASK_HPP_INCLUDED

#include <sge/renderer/detail/symbol.hpp>
#include <sge/renderer/state/core/blend/write_alpha.hpp>
#include <sge/renderer/state/core/blend/write_blue.hpp>
#include <sge/renderer/state/core/blend/write_green.hpp>
#include <sge/renderer/state/core/blend/write_mask_fwd.hpp>
#include <sge/renderer/state/core/blend/write_red.hpp>


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

class write_mask
{
public:
	SGE_RENDERER_DETAIL_SYMBOL
	write_mask(
		sge::renderer::state::core::blend::write_red,
		sge::renderer::state::core::blend::write_blue,
		sge::renderer::state::core::blend::write_green,
		sge::renderer::state::core::blend::write_alpha
	);

	SGE_RENDERER_DETAIL_SYMBOL
	sge::renderer::state::core::blend::write_red
	write_red() const;

	SGE_RENDERER_DETAIL_SYMBOL
	sge::renderer::state::core::blend::write_blue
	write_blue() const;

	SGE_RENDERER_DETAIL_SYMBOL
	sge::renderer::state::core::blend::write_green
	write_green() const;

	SGE_RENDERER_DETAIL_SYMBOL
	sge::renderer::state::core::blend::write_alpha
	write_alpha() const;
private:
	sge::renderer::state::core::blend::write_red write_red_;

	sge::renderer::state::core::blend::write_blue write_blue_;

	sge::renderer::state::core::blend::write_green write_green_;

	sge::renderer::state::core::blend::write_alpha write_alpha_;
};

}
}
}
}
}

#endif
