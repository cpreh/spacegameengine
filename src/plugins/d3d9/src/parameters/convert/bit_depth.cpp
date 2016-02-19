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


#include <sge/d3d9/d3dinclude.hpp>
#include <sge/d3d9/parameters/convert/bit_depth.hpp>
#include <sge/renderer/pixel_format/color.hpp>
#include <fcppt/assert/unreachable.hpp>


D3DFORMAT
sge::d3d9::parameters::convert::bit_depth(
	sge::renderer::pixel_format::color const _type
)
{
	switch(
		_type
	)
	{
		// FIXME! This currently doesn't work because the corresponding mizuiro image format is missing!
	//case sge::renderer::pixel_format::color::depth16:
//		break; //return D3DFMT_R5G6B5;
	case sge::renderer::pixel_format::color::depth32:
		return D3DFMT_X8R8G8B8;
	}

	FCPPT_ASSERT_UNREACHABLE;
}
