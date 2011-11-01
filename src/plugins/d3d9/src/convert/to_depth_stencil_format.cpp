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
#include <sge/d3d9/convert/to_depth_stencil_format.hpp>
#include <sge/renderer/depth_stencil_format.hpp>
#include <fcppt/assert/unreachable.hpp>


sge::renderer::depth_stencil_format::type
sge::d3d9::convert::to_depth_stencil_format(
	D3DFORMAT const _format
)
{
	switch(
		_format
	)
	{
	case D3DFMT_D16:
		return sge::renderer::depth_stencil_format::d16;
	case D3DFMT_D24S8:
		return sge::renderer::depth_stencil_format::d24s8;
	case D3DFMT_D32:
		return sge::renderer::depth_stencil_format::d32;
	default:
		break;
	}

	FCPPT_ASSERT_UNREACHABLE;
}
