//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_RENDERER_STATE_CORE_BLEND_PARAMETERS_HPP_INCLUDED
#define SGE_RENDERER_STATE_CORE_BLEND_PARAMETERS_HPP_INCLUDED

#include <sge/renderer/detail/symbol.hpp>
#include <sge/renderer/state/core/blend/alpha_variant.hpp>
#include <sge/renderer/state/core/blend/parameters_fwd.hpp>
#include <sge/renderer/state/core/blend/write_mask.hpp>


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

class parameters
{
public:
	SGE_RENDERER_DETAIL_SYMBOL
	parameters(
		sge::renderer::state::core::blend::alpha_variant const &,
		sge::renderer::state::core::blend::write_mask const &
	);

	[[nodiscard]]
	SGE_RENDERER_DETAIL_SYMBOL
	sge::renderer::state::core::blend::alpha_variant const &
	alpha_variant() const;

	[[nodiscard]]
	SGE_RENDERER_DETAIL_SYMBOL
	sge::renderer::state::core::blend::write_mask const &
	write_mask() const;
private:
	sge::renderer::state::core::blend::alpha_variant alpha_variant_;

	sge::renderer::state::core::blend::write_mask write_mask_;
};

}
}
}
}
}

#endif
