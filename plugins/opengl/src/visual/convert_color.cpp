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
