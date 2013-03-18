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


#include <sge/image/optional_path.hpp>
#include <sge/image/unsupported_format.hpp>
#include <sge/image/color/format.hpp>
#include <sge/libpng/png.hpp>
#include <sge/libpng/transforms_from_format.hpp>
#include <fcppt/optional_impl.hpp>
#include <fcppt/text.hpp>
#include <fcppt/assert/unreachable.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/filesystem/path.hpp>
#include <fcppt/config/external_end.hpp>


int
sge::libpng::transforms_from_format(
	boost::filesystem::path const &_path,
	sge::image::color::format const _format
)
{
	switch(
		_format
	)
	{
	case sge::image::color::format::a8:
		throw
			sge::image::unsupported_format(
				sge::image::optional_path(
					_path
				),
				FCPPT_TEXT("alpha8")
			);
	case sge::image::color::format::l8:
	case sge::image::color::format::la8:
	case sge::image::color::format::rgba8:
	case sge::image::color::format::rgb8:
	case sge::image::color::format::srgb8:
	case sge::image::color::format::srgba8:
		return PNG_TRANSFORM_IDENTITY;
	case sge::image::color::format::bgr8:
	case sge::image::color::format::bgra8:
		return PNG_TRANSFORM_BGR;
	case sge::image::color::format::rgbx8:
		return PNG_TRANSFORM_STRIP_FILLER_AFTER;
	case sge::image::color::format::bgrx8:
		return
			PNG_TRANSFORM_STRIP_FILLER_AFTER
			| PNG_TRANSFORM_BGR;
	case sge::image::color::format::r32f:
	case sge::image::color::format::rgb32f:
	case sge::image::color::format::bgr32f:
	case sge::image::color::format::rgba32f:
	case sge::image::color::format::bgra32f:
		throw
			sge::image::unsupported_format(
				sge::image::optional_path(
					_path
				),
				FCPPT_TEXT("{r,g,b,a}32f")
			);
	}

	FCPPT_ASSERT_UNREACHABLE;
}
