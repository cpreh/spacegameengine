//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/renderer/state/core/blend/write_alpha.hpp>
#include <sge/renderer/state/core/blend/write_blue.hpp>
#include <sge/renderer/state/core/blend/write_green.hpp>
#include <sge/renderer/state/core/blend/write_mask.hpp>
#include <sge/renderer/state/core/blend/write_red.hpp>


sge::renderer::state::core::blend::write_mask::write_mask(
	sge::renderer::state::core::blend::write_red const _write_red,
	sge::renderer::state::core::blend::write_blue const _write_blue,
	sge::renderer::state::core::blend::write_green const _write_green,
	sge::renderer::state::core::blend::write_alpha const _write_alpha
)
:
	write_red_(
		_write_red
	),
	write_blue_(
		_write_blue
	),
	write_green_(
		_write_green
	),
	write_alpha_(
		_write_alpha
	)
{
}

sge::renderer::state::core::blend::write_red
sge::renderer::state::core::blend::write_mask::write_red() const
{
	return
		write_red_;
}

sge::renderer::state::core::blend::write_blue
sge::renderer::state::core::blend::write_mask::write_blue() const
{
	return
		write_blue_;
}

sge::renderer::state::core::blend::write_green
sge::renderer::state::core::blend::write_mask::write_green() const
{
	return
		write_green_;
}

sge::renderer::state::core::blend::write_alpha
sge::renderer::state::core::blend::write_mask::write_alpha() const
{
	return
		write_alpha_;
}

