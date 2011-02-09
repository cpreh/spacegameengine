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


#include "../color_to_internal_format.hpp"
#include <sge/renderer/exception.hpp>
#include <fcppt/text.hpp>

sge::opengl::internal_color_format const
sge::opengl::convert::color_to_internal_format(
	image::color::format::type const _fmt
)
{
	switch(
		_fmt
	)
	{
	case image::color::format::gray8:
		return
			opengl::internal_color_format(
				GL_LUMINANCE8
			);
	case image::color::format::alpha8:
		return
			opengl::internal_color_format(
				GL_ALPHA
			);
	case image::color::format::rgba8:
		return
			opengl::internal_color_format(
				GL_RGBA8
			);
	case image::color::format::rgba32f:
		return
			opengl::internal_color_format(
				4
			);
	case image::color::format::rgb8:
		return
			opengl::internal_color_format(
				GL_RGB8
			);
	case image::color::format::argb8:
	case image::color::format::bgra8:
	case image::color::format::argb32f:
	case image::color::format::bgra32f:
		return
			opengl::internal_color_format(
				4
			);
	case image::color::format::rgb32f:
		return
			opengl::internal_color_format(
				GL_RGB32F
			);
	case image::color::format::size:
		break;
	}

	throw renderer::exception(
		FCPPT_TEXT("Invalid color_format in color_to_internal_format()!")
	);
}
