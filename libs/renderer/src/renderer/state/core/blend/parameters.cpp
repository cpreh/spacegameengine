//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/renderer/state/core/blend/alpha_variant.hpp>
#include <sge/renderer/state/core/blend/parameters.hpp>
#include <sge/renderer/state/core/blend/write_mask.hpp>


sge::renderer::state::core::blend::parameters::parameters(
	sge::renderer::state::core::blend::alpha_variant const &_alpha_variant,
	sge::renderer::state::core::blend::write_mask const &_write_mask
)
:
	alpha_variant_(
		_alpha_variant
	),
	write_mask_(
		_write_mask
	)
{
}

sge::renderer::state::core::blend::alpha_variant const &
sge::renderer::state::core::blend::parameters::alpha_variant() const
{
	return alpha_variant_;
}

sge::renderer::state::core::blend::write_mask const &
sge::renderer::state::core::blend::parameters::write_mask() const
{
	return write_mask_;
}
