/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2015 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#include <sge/renderer/state/core/blend/alpha_dest.hpp>
#include <sge/renderer/state/core/blend/alpha_source.hpp>
#include <sge/renderer/state/core/blend/color_dest.hpp>
#include <sge/renderer/state/core/blend/color_source.hpp>
#include <sge/renderer/state/core/blend/separate.hpp>


sge::renderer::state::core::blend::separate::separate(
	sge::renderer::state::core::blend::color_source const _color_source,
	sge::renderer::state::core::blend::color_dest const _color_dest,
	sge::renderer::state::core::blend::alpha_source const _alpha_source,
	sge::renderer::state::core::blend::alpha_dest const _alpha_dest
)
:
	color_source_(
		_color_source
	),
	color_dest_(
		_color_dest
	),
	alpha_source_(
		_alpha_source
	),
	alpha_dest_(
		_alpha_dest
	)
{
}

sge::renderer::state::core::blend::color_source const
sge::renderer::state::core::blend::separate::color_source() const
{
	return color_source_;
}

sge::renderer::state::core::blend::color_dest const
sge::renderer::state::core::blend::separate::color_dest() const
{
	return color_dest_;
}

sge::renderer::state::core::blend::alpha_source const
sge::renderer::state::core::blend::separate::alpha_source() const
{
	return alpha_source_;
}

sge::renderer::state::core::blend::alpha_dest const
sge::renderer::state::core::blend::separate::alpha_dest() const
{
	return alpha_dest_;
}
