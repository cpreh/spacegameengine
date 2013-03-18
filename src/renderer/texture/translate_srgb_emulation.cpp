/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2013 Carl Philipp Reh (sefi@s-e-f-i.de)

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
#include <sge/renderer/texture/color_format.hpp>
#include <sge/renderer/texture/emulate_srgb.hpp>
#include <sge/renderer/texture/translate_srgb_emulation.hpp>
#include <fcppt/assert/unreachable.hpp>


sge::image::color::format
sge::renderer::texture::translate_srgb_emulation(
	sge::renderer::texture::color_format const &_color_format
)
{
	sge::image::color::format const format(
		_color_format.format()
	);

	if(
		_color_format.emulate_srgb()
		==
		sge::renderer::texture::emulate_srgb::no
	)
		return
			format;

	switch(
		format
	)
	{
	case sge::image::color::format::a8:
	case sge::image::color::format::l8:
	case sge::image::color::format::la8:
	case sge::image::color::format::rgb8:
	case sge::image::color::format::bgr8:
	case sge::image::color::format::rgba8:
	case sge::image::color::format::rgbx8:
	case sge::image::color::format::bgra8:
	case sge::image::color::format::bgrx8:
	case sge::image::color::format::r32f:
	case sge::image::color::format::bgr32f:
	case sge::image::color::format::rgb32f:
	case sge::image::color::format::rgba32f:
	case sge::image::color::format::bgra32f:
		return
			format;
	case sge::image::color::format::srgb8:
		return
			sge::image::color::format::rgb8;
	case sge::image::color::format::srgba8:
		return
			sge::image::color::format::rgba8;
	}

	FCPPT_ASSERT_UNREACHABLE;
}
