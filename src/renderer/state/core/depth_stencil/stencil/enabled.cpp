/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2014 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#include <sge/renderer/state/core/depth_stencil/stencil/enabled.hpp>
#include <sge/renderer/state/core/depth_stencil/stencil/enabled_variant.hpp>
#include <sge/renderer/state/core/depth_stencil/stencil/read_mask.hpp>
#include <sge/renderer/state/core/depth_stencil/stencil/ref.hpp>
#include <sge/renderer/state/core/depth_stencil/stencil/write_mask.hpp>


sge::renderer::state::core::depth_stencil::stencil::enabled::enabled(
	sge::renderer::state::core::depth_stencil::stencil::enabled_variant const &_enabled_variant,
	sge::renderer::state::core::depth_stencil::stencil::ref const _ref,
	sge::renderer::state::core::depth_stencil::stencil::read_mask const _read_mask,
	sge::renderer::state::core::depth_stencil::stencil::write_mask const _write_mask
)
:
	enabled_variant_(
		_enabled_variant
	),
	ref_(
		_ref
	),
	read_mask_(
		_read_mask
	),
	write_mask_(
		_write_mask
	)
{
}

sge::renderer::state::core::depth_stencil::stencil::enabled_variant const &
sge::renderer::state::core::depth_stencil::stencil::enabled::enabled_variant() const
{
	return enabled_variant_;
}

sge::renderer::state::core::depth_stencil::stencil::ref const
sge::renderer::state::core::depth_stencil::stencil::enabled::ref() const
{
	return ref_;
}

sge::renderer::state::core::depth_stencil::stencil::read_mask const
sge::renderer::state::core::depth_stencil::stencil::enabled::read_mask() const
{
	return read_mask_;
}

sge::renderer::state::core::depth_stencil::stencil::write_mask const
sge::renderer::state::core::depth_stencil::stencil::enabled::write_mask() const
{
	return write_mask_;
}
