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


#include "../clear.hpp"
#include "../../../d3dinclude.hpp"
#include <sge/renderer/exception.hpp>
#include <fcppt/text.hpp>

DWORD
sge::d3d9::state::convert::clear(
	sge::renderer::state::bool_::available_states::type const _type
)
{
	switch(
		_type
	)
	{
	case sge::renderer::state::bool_::available_states::clear_depth_buffer:
		return D3DCLEAR_ZBUFFER;
	case sge::renderer::state::bool_::available_states::clear_back_buffer:
		return D3DCLEAR_TARGET;
	case sge::renderer::state::bool_::available_states::clear_stencil_buffer:
		return D3DCLEAR_STENCIL;
	case sge::renderer::state::bool_::available_states::enable_alpha_blending:
	case sge::renderer::state::bool_::available_states::enable_lighting:
	case sge::renderer::state::bool_::available_states::enable_multi_sampling:
	case sge::renderer::state::bool_::available_states::enable_point_sprites:
	case sge::renderer::state::bool_::available_states::enable_scissor_test:
	case sge::renderer::state::bool_::available_states::write_to_depth_buffer:
		break;
	}

	throw sge::renderer::exception(
		FCPPT_TEXT("Invalid bool state!")
	);
}
