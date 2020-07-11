//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/systems/renderer.hpp>
#include <sge/systems/renderer_caps.hpp>
#include <sge/systems/detail/renderer.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>


sge::systems::detail::renderer::renderer(
	sge::systems::renderer &&_parameters,
	sge::systems::renderer_caps const _caps
)
:
	parameters_{
		std::move(
			_parameters
		)
	},
	caps_{
		_caps
	}
{
}

sge::systems::renderer const &
sge::systems::detail::renderer::parameters() const
{
	return
		parameters_;
}

sge::systems::renderer_caps
sge::systems::detail::renderer::caps() const
{
	return
		caps_;
}
