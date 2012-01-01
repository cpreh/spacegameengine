/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2012 Carl Philipp Reh (sefi@s-e-f-i.de)

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
#include <sge/d3d9/state/convert/dest_blend_func.hpp>
#include <fcppt/assert/unreachable.hpp>


D3DBLEND
sge::d3d9::state::convert::dest_blend_func(
	sge::renderer::state::dest_blend_func::type const _type
)
{
	switch(
		_type
	)
	{
	case sge::renderer::state::dest_blend_func::zero:
		return D3DBLEND_ZERO;
	case sge::renderer::state::dest_blend_func::one:
		return D3DBLEND_ONE;
	case sge::renderer::state::dest_blend_func::src_color:
		return D3DBLEND_SRCCOLOR;
	case sge::renderer::state::dest_blend_func::inv_src_color:
		return D3DBLEND_INVSRCCOLOR;
	case sge::renderer::state::dest_blend_func::src_alpha:
		return D3DBLEND_SRCALPHA;
	case sge::renderer::state::dest_blend_func::inv_src_alpha:
		return D3DBLEND_INVSRCALPHA;
	case sge::renderer::state::dest_blend_func::dest_alpha:
		return D3DBLEND_DESTALPHA;
	case sge::renderer::state::dest_blend_func::inv_dest_alpha:
		return D3DBLEND_INVDESTALPHA;
	}

	FCPPT_ASSERT_UNREACHABLE;
}
