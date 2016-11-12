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


#include <sge/opengl/color_format.hpp>
#include <sge/opengl/color_order.hpp>
#include <sge/opengl/common.hpp>
#include <sge/opengl/convert/color_order.hpp>
#include <sge/opengl/convert/make_color_order.hpp>
#include <fcppt/assert/unreachable.hpp>


sge::opengl::color_order
sge::opengl::convert::color_order(
	sge::opengl::color_format const _format
)
{
	switch(
		_format
	)
	{
	case sge::opengl::color_format::a8:
		return
			sge::opengl::convert::make_color_order<
				GL_ALPHA
			>();
	case sge::opengl::color_format::l8:
		return
			sge::opengl::convert::make_color_order<
				GL_LUMINANCE
			>();
	case sge::opengl::color_format::r32f:
		return
			sge::opengl::convert::make_color_order<
				GL_RED
			>();
	case sge::opengl::color_format::la8:
		return
			sge::opengl::convert::make_color_order<
				GL_LUMINANCE_ALPHA
			>();
	case sge::opengl::color_format::srgb8:
	case sge::opengl::color_format::rgb8:
	case sge::opengl::color_format::rgb32f:
		return
			sge::opengl::convert::make_color_order<
				GL_RGB
			>();
	case sge::opengl::color_format::sbgr8:
	case sge::opengl::color_format::bgr8:
	case sge::opengl::color_format::bgr32f:
		return
			sge::opengl::convert::make_color_order<
				GL_BGR
			>();
	case sge::opengl::color_format::rgba8:
	case sge::opengl::color_format::srgba8:
	case sge::opengl::color_format::rgba32f:
		return
			sge::opengl::convert::make_color_order<
				GL_RGBA
			>();
	case sge::opengl::color_format::sbgra8:
	case sge::opengl::color_format::bgra8:
	case sge::opengl::color_format::bgra32f:
		return
			sge::opengl::convert::make_color_order<
				GL_BGRA
			>();
	}

	FCPPT_ASSERT_UNREACHABLE;
}
