//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/renderer/state/core/blend/write_alpha.hpp>
#include <sge/renderer/state/core/blend/write_blue.hpp>
#include <sge/renderer/state/core/blend/write_green.hpp>
#include <sge/renderer/state/core/blend/write_mask.hpp>
#include <sge/renderer/state/core/blend/write_mask_all.hpp>
#include <sge/renderer/state/core/blend/write_red.hpp>


sge::renderer::state::core::blend::write_mask
sge::renderer::state::core::blend::write_mask_all()
{
	return
		sge::renderer::state::core::blend::write_mask(
			sge::renderer::state::core::blend::write_red(
				true
			),
			sge::renderer::state::core::blend::write_blue(
				true
			),
			sge::renderer::state::core::blend::write_green(
				true
			),
			sge::renderer::state::core::blend::write_alpha(
				true
			)
		);
}
