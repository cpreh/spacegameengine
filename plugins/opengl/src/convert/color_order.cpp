//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


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
