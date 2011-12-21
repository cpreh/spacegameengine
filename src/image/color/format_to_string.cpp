/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2011 Carl Philipp Reh (sefi@s-e-f-i.de)

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
#include <fcppt/string.hpp>
#include <fcppt/assert/unreachable.hpp>
#include <fcppt/preprocessor/stringize.hpp>


fcppt::string const
sge::image::color::format_to_string(
	format::type const _format
)
{
#define SGE_IMAGE_COLOR_FORMAT_TO_STRING_CASE(\
	fmt \
) \
case format::fmt: \
	return FCPPT_PP_STRINGIZE(fmt)

	switch(
		_format
	)
	{
	SGE_IMAGE_COLOR_FORMAT_TO_STRING_CASE(a8);
	SGE_IMAGE_COLOR_FORMAT_TO_STRING_CASE(l8);
	SGE_IMAGE_COLOR_FORMAT_TO_STRING_CASE(r32f);
	SGE_IMAGE_COLOR_FORMAT_TO_STRING_CASE(la8);
	SGE_IMAGE_COLOR_FORMAT_TO_STRING_CASE(rgb8);
	SGE_IMAGE_COLOR_FORMAT_TO_STRING_CASE(bgr8);
	SGE_IMAGE_COLOR_FORMAT_TO_STRING_CASE(rgba8);
	SGE_IMAGE_COLOR_FORMAT_TO_STRING_CASE(rgbx8);
	SGE_IMAGE_COLOR_FORMAT_TO_STRING_CASE(bgra8);
	SGE_IMAGE_COLOR_FORMAT_TO_STRING_CASE(bgrx8);
	SGE_IMAGE_COLOR_FORMAT_TO_STRING_CASE(rgb32f);
	SGE_IMAGE_COLOR_FORMAT_TO_STRING_CASE(bgr32f);
	SGE_IMAGE_COLOR_FORMAT_TO_STRING_CASE(rgba32f);
	SGE_IMAGE_COLOR_FORMAT_TO_STRING_CASE(bgra32f);
	case format::size:
		break;
	}

	FCPPT_ASSERT_UNREACHABLE;
}
