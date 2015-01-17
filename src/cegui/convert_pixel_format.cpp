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
#include <sge/image/color/optional_format.hpp>
#include <sge/src/cegui/convert_pixel_format.hpp>
#include <fcppt/assert/unreachable.hpp>
#include <fcppt/config/external_begin.hpp>
#include <CEGUI/Texture.h>
#include <fcppt/config/external_end.hpp>


sge::image::color::optional_format const
sge::cegui::convert_pixel_format(
	CEGUI::Texture::PixelFormat const _format
)
{
	switch(
		_format
	)
	{
	case CEGUI::Texture::PF_RGB:
		return
			sge::image::color::optional_format(
				sge::image::color::format::rgb8
			);
	case CEGUI::Texture::PF_RGBA:
		return
			sge::image::color::optional_format(
				sge::image::color::format::rgba8
			);
	case CEGUI::Texture::PF_RGBA_4444:
	case CEGUI::Texture::PF_RGB_565:
	case CEGUI::Texture::PF_PVRTC2:
	case CEGUI::Texture::PF_PVRTC4:
	case CEGUI::Texture::PF_RGB_DXT1:
	case CEGUI::Texture::PF_RGBA_DXT1:
	case CEGUI::Texture::PF_RGBA_DXT3:
	case CEGUI::Texture::PF_RGBA_DXT5:
		return
			sge::image::color::optional_format();
	}

	FCPPT_ASSERT_UNREACHABLE;
}
