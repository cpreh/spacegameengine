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
#include <sge/image/color/format_to_string.hpp>
#include <sge/image2d/unsupported_format.hpp>
#include <sge/libpng/format.hpp>
#include <sge/libpng/from_sge_format_exn.hpp>
#include <sge/media/optional_path.hpp>
#include <fcppt/text.hpp>
#include <fcppt/assert/unreachable.hpp>


sge::libpng::format
sge::libpng::from_sge_format_exn(
	sge::image::color::format const _format
)
{
#define SGE_LIBPNG_CONVERT_FORMAT(\
	cur_format\
)\
	case sge::image::color::format::cur_format: \
		return \
			sge::libpng::format::cur_format

	switch(
		_format
	)
	{
		SGE_LIBPNG_CONVERT_FORMAT(
			l8
		);
		SGE_LIBPNG_CONVERT_FORMAT(
			la8
		);
		SGE_LIBPNG_CONVERT_FORMAT(
			rgb8
		);
		SGE_LIBPNG_CONVERT_FORMAT(
			bgr8
		);
		SGE_LIBPNG_CONVERT_FORMAT(
			rgba8
		);
		SGE_LIBPNG_CONVERT_FORMAT(
			rgbx8
		);
		SGE_LIBPNG_CONVERT_FORMAT(
			bgra8
		);
		SGE_LIBPNG_CONVERT_FORMAT(
			bgrx8
		);
		SGE_LIBPNG_CONVERT_FORMAT(
			srgb8
		);
		SGE_LIBPNG_CONVERT_FORMAT(
			srgba8
		);
		SGE_LIBPNG_CONVERT_FORMAT(
			sbgr8
		);
		SGE_LIBPNG_CONVERT_FORMAT(
			sbgra8
		);
		case sge::image::color::format::a8:
		case sge::image::color::format::r32f:
		case sge::image::color::format::rgb32f:
		case sge::image::color::format::bgr32f:
		case sge::image::color::format::rgba32f:
		case sge::image::color::format::bgra32f:
			throw
				sge::image2d::unsupported_format(
					sge::media::optional_path(),
					FCPPT_TEXT("libpng doesn't support ")
					+
					sge::image::color::format_to_string(
						_format
					)
				);
	}

	FCPPT_ASSERT_UNREACHABLE;
}
