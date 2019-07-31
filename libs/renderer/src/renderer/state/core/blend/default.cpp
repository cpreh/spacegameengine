//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/renderer/state/core/blend/alpha_off.hpp>
#include <sge/renderer/state/core/blend/alpha_variant.hpp>
#include <sge/renderer/state/core/blend/default.hpp>
#include <sge/renderer/state/core/blend/parameters.hpp>
#include <sge/renderer/state/core/blend/write_mask_all.hpp>


sge::renderer::state::core::blend::parameters
sge::renderer::state::core::blend::default_()
{
	return
		sge::renderer::state::core::blend::parameters(
			sge::renderer::state::core::blend::alpha_variant{
				sge::renderer::state::core::blend::alpha_off()
			},
			sge::renderer::state::core::blend::write_mask_all()
		);
}
