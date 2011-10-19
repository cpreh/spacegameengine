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


#include "../color.hpp"
#include "../../../d3dinclude.hpp"
#include <fcppt/assert/unreachable.hpp>

D3DRENDERSTATETYPE
sge::d3d9::state::convert::color(
	sge::renderer::state::color::available_states::type const _type
)
{
	switch(
		_type
	)
	{
	case sge::renderer::state::color::available_states::back_buffer_clear_color:
		break;
	case sge::renderer::state::color::available_states::ambient_light_color:
		return D3DRS_AMBIENT;
	case sge::renderer::state::color::available_states::fog_color:
		return D3DRS_FOGCOLOR;
	}

	FCPPT_ASSERT_UNREACHABLE;
}
