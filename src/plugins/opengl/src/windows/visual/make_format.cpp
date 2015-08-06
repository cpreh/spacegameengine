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


#include <sge/opengl/windows/visual/make_format.hpp>
#include <sge/renderer/pixel_format/bit_count.hpp>
#include <sge/renderer/pixel_format/color.hpp>
#include <sge/renderer/pixel_format/color_bits.hpp>
#include <sge/renderer/pixel_format/depth_bits.hpp>
#include <sge/renderer/pixel_format/depth_stencil.hpp>
#include <sge/renderer/pixel_format/optional_bit_count.hpp>
#include <sge/renderer/pixel_format/stencil_bits.hpp>
#include <awl/backends/windows/windows.hpp>
#include <fcppt/const.hpp>
#include <fcppt/from_optional.hpp>
#include <fcppt/cast/size.hpp>



PIXELFORMATDESCRIPTOR const
sge::opengl::windows::visual::make_format(
	sge::renderer::pixel_format::color const _color,
	sge::renderer::pixel_format::depth_stencil const _depth_stencil
)
{
	auto const convert_optional_bit_count(
		[](
			sge::renderer::pixel_format::optional_bit_count const _bit_count
		)
		-> BYTE
		{
			return
				fcppt::cast::size<
					BYTE
				>(
					fcppt::from_optional(
						_bit_count,
						fcppt::const_(
							sge::renderer::pixel_format::bit_count{
								0u
							}
						)
					).get()
				);
		}
	);


	PIXELFORMATDESCRIPTOR const ret = {
		sizeof(
			PIXELFORMATDESCRIPTOR
		),
		1,                      // Version Number
		PFD_DRAW_TO_WINDOW
		| PFD_SUPPORT_OPENGL
		| PFD_DOUBLEBUFFER,
		PFD_TYPE_RGBA,
		fcppt::cast::size<
			BYTE
		>(
			sge::renderer::pixel_format::color_bits(
				_color
			).get()
		),
		0, 0, 0, 0, 0, 0,       // Color Bits Ignored
		0,                      // No Alpha Buffer
		0,                      // Shift Bit Ignored
		0,                      // No Accumulation Buffer
		0, 0, 0, 0,             // Accumulation Bits Ignored
		convert_optional_bit_count(
			sge::renderer::pixel_format::depth_bits(
				_depth_stencil
			)
		),
		convert_optional_bit_count(
			sge::renderer::pixel_format::stencil_bits(
				_depth_stencil
			)
		),
		0,                      // No Auxiliary Buffer
		PFD_MAIN_PLANE,         // Main Drawing Layer
		0,                      // Reserved
		0, 0, 0                 // Layer Masks Ignored
	};

	return
		ret;
}
