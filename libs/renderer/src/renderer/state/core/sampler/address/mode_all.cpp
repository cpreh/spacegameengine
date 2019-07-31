//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/renderer/state/core/sampler/address/mode.hpp>
#include <sge/renderer/state/core/sampler/address/mode_all.hpp>
#include <sge/renderer/state/core/sampler/address/mode_s.hpp>
#include <sge/renderer/state/core/sampler/address/mode_t.hpp>
#include <sge/renderer/state/core/sampler/address/mode_u.hpp>
#include <sge/renderer/state/core/sampler/address/parameters.hpp>


sge::renderer::state::core::sampler::address::parameters
sge::renderer::state::core::sampler::address::mode_all(
	sge::renderer::state::core::sampler::address::mode const _mode
)
{
	return
		sge::renderer::state::core::sampler::address::parameters(
			sge::renderer::state::core::sampler::address::mode_s(
				_mode
			),
			sge::renderer::state::core::sampler::address::mode_t(
				_mode
			),
			sge::renderer::state::core::sampler::address::mode_u(
				_mode
			)
		);
}
