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
#include <sge/renderer/exception.hpp>
#include <fcppt/text.hpp>

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
	}

	throw sge::renderer::exception(
		FCPPT_TEXT("Invalid format in to_color_format()!")
	);
}
