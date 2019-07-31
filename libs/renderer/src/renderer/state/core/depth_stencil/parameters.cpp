//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/renderer/state/core/depth_stencil/parameters.hpp>
#include <sge/renderer/state/core/depth_stencil/depth/variant.hpp>
#include <sge/renderer/state/core/depth_stencil/stencil/variant.hpp>


sge::renderer::state::core::depth_stencil::parameters::parameters(
	sge::renderer::state::core::depth_stencil::depth::variant const &_depth_variant,
	sge::renderer::state::core::depth_stencil::stencil::variant const &_stencil_variant
)
:
	depth_variant_(
		_depth_variant
	),
	stencil_variant_(
		_stencil_variant
	)
{
}

sge::renderer::state::core::depth_stencil::depth::variant const &
sge::renderer::state::core::depth_stencil::parameters::depth_variant() const
{
	return depth_variant_;
}

sge::renderer::state::core::depth_stencil::stencil::variant const &
sge::renderer::state::core::depth_stencil::parameters::stencil_variant() const
{
	return stencil_variant_;
}
