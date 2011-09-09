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


#include "../to_color_format.hpp"
#include "../../d3dinclude.hpp"
#include <fcppt/assert/unreachable.hpp>

sge::image::color::format::type
sge::d3d9::convert::to_color_format(
	D3DFORMAT const _format
)
{
	switch(
		_format
	)
	{
	case D3DFMT_A8:
		return sge::image::color::format::alpha8;
	case D3DFMT_L8:
		return sge::image::color::format::gray8;
	case D3DFMT_A8R8G8B8:
		return sge::image::color::format::argb8;
	case D3DFMT_X8R8G8B8:
		return sge::image::color::format::xrgb8;
	case D3DFMT_R8G8B8:
		return sge::image::color::format::rgb8;
	case D3DFMT_A32B32G32R32F:
		return sge::image::color::format::argb32f;
	case D3DFMT_A8L8:
		return sge::image::color::format::ag8;
	case D3DFMT_A1:
	case D3DFMT_A16B16G16R16:
	case D3DFMT_A16B16G16R16F:
	case D3DFMT_A1R5G5B5:
	case D3DFMT_A2B10G10R10:
	case D3DFMT_A2B10G10R10_XR_BIAS:
	case D3DFMT_A2R10G10B10:
	case D3DFMT_A2W10V10U10:
	case D3DFMT_A4L4:
	case D3DFMT_A4R4G4B4:
	case D3DFMT_A8B8G8R8:
	case D3DFMT_A8P8:
	case D3DFMT_A8R3G3B2:
	case D3DFMT_BINARYBUFFER:
	case D3DFMT_CxV8U8:
	case D3DFMT_D15S1:
	case D3DFMT_D16:
	case D3DFMT_D16_LOCKABLE:
	case D3DFMT_D24FS8:
	case D3DFMT_D24S8:
	case D3DFMT_D24X4S4:
	case D3DFMT_D24X8:
	case D3DFMT_D32:
	case D3DFMT_D32_LOCKABLE:
	case D3DFMT_D32F_LOCKABLE:
	case D3DFMT_DXT1:
	case D3DFMT_DXT2:
	case D3DFMT_DXT3:
	case D3DFMT_DXT4:
	case D3DFMT_DXT5:
	case D3DFMT_FORCE_DWORD:
	case D3DFMT_G16R16:
	case D3DFMT_G16R16F:
	case D3DFMT_G32R32F:
	case D3DFMT_G8R8_G8B8:
	case D3DFMT_INDEX16:
	case D3DFMT_INDEX32:
	case D3DFMT_L16:
	case D3DFMT_L6V5U5:
	case D3DFMT_MULTI2_ARGB8:
	case D3DFMT_P8:
	case D3DFMT_Q16W16V16U16:
	case D3DFMT_Q8W8V8U8:
	case D3DFMT_R16F:
	case D3DFMT_R32F:
	case D3DFMT_R3G3B2:
	case D3DFMT_R5G6B5:
	case D3DFMT_R8G8_B8G8:
	case D3DFMT_S8_LOCKABLE:
	case D3DFMT_UNKNOWN:
	case D3DFMT_UYVY:
	case D3DFMT_V16U16:
	case D3DFMT_V8U8:
	case D3DFMT_VERTEXDATA:
	case D3DFMT_X1R5G5B5:
	case D3DFMT_X4R4G4B4:
	case D3DFMT_X8B8G8R8:
	case D3DFMT_X8L8V8U8:
	case D3DFMT_YUY2:
		break;
	}

	FCPPT_ASSERT_UNREACHABLE
}
