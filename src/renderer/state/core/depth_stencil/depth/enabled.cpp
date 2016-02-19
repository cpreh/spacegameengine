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


#include <sge/renderer/state/core/depth_stencil/depth/enabled.hpp>
#include <sge/renderer/state/core/depth_stencil/depth/func.hpp>
#include <sge/renderer/state/core/depth_stencil/depth/write_enable.hpp>


sge::renderer::state::core::depth_stencil::depth::enabled::enabled(
	sge::renderer::state::core::depth_stencil::depth::func const _func,
	sge::renderer::state::core::depth_stencil::depth::write_enable const _write_enable
)
:
	func_(
		_func
	),
	write_enable_(
		_write_enable
	)
{
}

sge::renderer::state::core::depth_stencil::depth::func
sge::renderer::state::core::depth_stencil::depth::enabled::func() const
{
	return
		func_;
}

sge::renderer::state::core::depth_stencil::depth::write_enable
sge::renderer::state::core::depth_stencil::depth::enabled::write_enable() const
{
	return
		write_enable_;
}
