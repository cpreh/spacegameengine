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
