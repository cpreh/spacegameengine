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
#include <sge/d3d9/state/convert/float.hpp>
#include <fcppt/assert/unreachable.hpp>


D3DRENDERSTATETYPE
sge::d3d9::state::convert::float_(
	sge::renderer::state::float_::available_states::type const _type
)
{
	switch(
		_type
	)
	{
	case sge::renderer::state::float_::available_states::depth_buffer_clear_val:
		break;
	case sge::renderer::state::float_::available_states::alpha_test_ref:
		return D3DRS_ALPHAREF;
	case sge::renderer::state::float_::available_states::fog_start:
		return D3DRS_FOGSTART;
	case sge::renderer::state::float_::available_states::fog_end:
		return D3DRS_FOGEND;
	case sge::renderer::state::float_::available_states::fog_density:
		return D3DRS_FOGDENSITY;
	}

	FCPPT_ASSERT_UNREACHABLE;
}
