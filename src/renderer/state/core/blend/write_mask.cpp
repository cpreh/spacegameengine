/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2016 Carl Philipp Reh (carlphilippreh <at> gmail.com)

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/


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

