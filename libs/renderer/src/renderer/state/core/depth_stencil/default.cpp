//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/renderer/state/core/depth_stencil/default.hpp>
#include <sge/renderer/state/core/depth_stencil/parameters.hpp>
#include <sge/renderer/state/core/depth_stencil/depth/off.hpp>
#include <sge/renderer/state/core/depth_stencil/depth/variant.hpp>
#include <sge/renderer/state/core/depth_stencil/stencil/off.hpp>
#include <sge/renderer/state/core/depth_stencil/stencil/variant.hpp>


sge::renderer::state::core::depth_stencil::parameters
sge::renderer::state::core::depth_stencil::default_()
{
	return
		sge::renderer::state::core::depth_stencil::parameters(
			sge::renderer::state::core::depth_stencil::depth::variant{
				sge::renderer::state::core::depth_stencil::depth::off()
			},
			sge::renderer::state::core::depth_stencil::stencil::variant{
				sge::renderer::state::core::depth_stencil::stencil::off()
			}
		);
}
