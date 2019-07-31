//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/opengl/visual/convert_color.hpp>
#include <sge/opengl/visual/rgb_triple.hpp>
#include <sge/renderer/pixel_format/color.hpp>
#include <fcppt/assert/unreachable.hpp>


sge::opengl::visual::rgb_triple
sge::opengl::visual::convert_color(
	sge::renderer::pixel_format::color const _format
)
{
	switch(
		_format
	)
	{
	case sge::renderer::pixel_format::color::depth16:
		return
			sge::opengl::visual::rgb_triple(
				sge::opengl::visual::rgb_triple::red_bits(
					5
				),
				sge::opengl::visual::rgb_triple::green_bits(
					6 // TODO: is this ok?
				),
				sge::opengl::visual::rgb_triple::blue_bits(
					5
				)
			);
	case sge::renderer::pixel_format::color::depth32:
		return
			sge::opengl::visual::rgb_triple(
				sge::opengl::visual::rgb_triple::red_bits(
					8
				),
				sge::opengl::visual::rgb_triple::green_bits(
					8
				),
				sge::opengl::visual::rgb_triple::blue_bits(
					8
				)
			);
	}

	FCPPT_ASSERT_UNREACHABLE;
}
