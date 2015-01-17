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


#include <sge/renderer/state/core/rasterizer/cull_mode.hpp>
#include <sge/renderer/state/core/rasterizer/enable_scissor_test.hpp>
#include <sge/renderer/state/core/rasterizer/fill_mode.hpp>
#include <sge/renderer/state/core/rasterizer/parameters.hpp>


sge::renderer::state::core::rasterizer::parameters::parameters(
	sge::renderer::state::core::rasterizer::cull_mode const _cull_mode,
	sge::renderer::state::core::rasterizer::fill_mode const _fill_mode,
	sge::renderer::state::core::rasterizer::enable_scissor_test const _enable_scissor_test
)
:
	cull_mode_(
		_cull_mode
	),
	fill_mode_(
		_fill_mode
	),
	enable_scissor_test_(
		_enable_scissor_test
	)
{
}

sge::renderer::state::core::rasterizer::cull_mode
sge::renderer::state::core::rasterizer::parameters::cull_mode() const
{
	return cull_mode_;
}

sge::renderer::state::core::rasterizer::fill_mode
sge::renderer::state::core::rasterizer::parameters::fill_mode() const
{
	return fill_mode_;
}

sge::renderer::state::core::rasterizer::enable_scissor_test const
sge::renderer::state::core::rasterizer::parameters::enable_scissor_test() const
{
	return enable_scissor_test_;
}
