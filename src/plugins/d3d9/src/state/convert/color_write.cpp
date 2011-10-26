/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2011 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include <sge/d3d9/d3dinclude.hpp>
#include <sge/d3d9/state/convert/color_write.hpp>
#include <sge/renderer/state/bool.hpp>
#include <fcppt/assert/unreachable.hpp>


DWORD
sge::d3d9::state::convert::color_write(
	renderer::state::bool_::available_states::type const _state
)
{
	switch(
		_state
	)
	{
	case sge::renderer::state::bool_::available_states::write_alpha:
		return D3DCOLORWRITEENABLE_ALPHA;
	case sge::renderer::state::bool_::available_states::write_blue:
		return D3DCOLORWRITEENABLE_BLUE;
	case sge::renderer::state::bool_::available_states::write_green:
		return D3DCOLORWRITEENABLE_GREEN;
	case sge::renderer::state::bool_::available_states::write_red:
		return D3DCOLORWRITEENABLE_RED;
	case sge::renderer::state::bool_::available_states::clear_back_buffer:
	case sge::renderer::state::bool_::available_states::clear_depth_buffer:
	case sge::renderer::state::bool_::available_states::clear_stencil_buffer:
	case sge::renderer::state::bool_::available_states::enable_alpha_blending:
	case sge::renderer::state::bool_::available_states::enable_lighting:
	case sge::renderer::state::bool_::available_states::enable_multi_sampling:
	case sge::renderer::state::bool_::available_states::enable_point_sprites:
	case sge::renderer::state::bool_::available_states::enable_scissor_test:
	case sge::renderer::state::bool_::available_states::write_to_depth_buffer:
		break;
	}

	FCPPT_ASSERT_UNREACHABLE;
}
