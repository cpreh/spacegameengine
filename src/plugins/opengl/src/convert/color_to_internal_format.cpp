/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2015 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#include <sge/image/color/format.hpp>
#include <sge/opengl/common.hpp>
#include <sge/opengl/internal_color_format.hpp>
#include <sge/opengl/convert/color_to_internal_format.hpp>
#include <fcppt/assert/unreachable.hpp>


sge::opengl::internal_color_format const
sge::opengl::convert::color_to_internal_format(
	sge::image::color::format const _fmt
)
{
	switch(
		_fmt
	)
	{
	case sge::image::color::format::a8:
		return
			sge::opengl::internal_color_format(
				GL_ALPHA8
			);
	case sge::image::color::format::l8:
		return
			sge::opengl::internal_color_format(
				GL_LUMINANCE8
			);
	case sge::image::color::format::r32f:
		return
			sge::opengl::internal_color_format(
				1
			);
	case sge::image::color::format::la8:
		return
			sge::opengl::internal_color_format(
				GL_LUMINANCE_ALPHA
			);
	case sge::image::color::format::rgb8:
		return
			sge::opengl::internal_color_format(
				GL_RGB8
			);
	case sge::image::color::format::bgr8:
	case sge::image::color::format::bgr32f:
		return
			sge::opengl::internal_color_format(
				3
			);
	case sge::image::color::format::rgba8:
		return
			sge::opengl::internal_color_format(
				GL_RGBA8
			);
	case sge::image::color::format::bgra8:
	case sge::image::color::format::rgba32f:
	case sge::image::color::format::bgra32f:
		return
			sge::opengl::internal_color_format(
				4
			);
	case sge::image::color::format::rgb32f:
		return
			sge::opengl::internal_color_format(
				GL_RGB32F
			);
	case sge::image::color::format::srgb8:
	case sge::image::color::format::sbgr8:
		return
			sge::opengl::internal_color_format(
				GL_SRGB8
			);
	case sge::image::color::format::srgba8:
	case sge::image::color::format::sbgra8:
		return
			sge::opengl::internal_color_format(
				GL_SRGB8_ALPHA8
			);
	case sge::image::color::format::rgbx8:
	case sge::image::color::format::bgrx8:
		break;
	}

	FCPPT_ASSERT_UNREACHABLE;
}
