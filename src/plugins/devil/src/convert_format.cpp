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


#include <sge/devil/convert_format.hpp>
#include <sge/image/exception.hpp>
#include <sge/image/color/format.hpp>
#include <fcppt/format.hpp>
#include <fcppt/string.hpp>
#include <fcppt/text.hpp>
#include <fcppt/assert/unreachable.hpp>
#include <fcppt/config/external_begin.hpp>
#include <IL/il.h>
#include <fcppt/config/external_end.hpp>


namespace
{

fcppt::string const
format_to_string(
	ILenum
);

}

sge::image::color::format::type
sge::devil::convert_format(
	ILint const _bits_per_pixel,
	ILenum const _format
)
{
	switch(
		_format
	)
	{
	case IL_ALPHA:
		if(
			_bits_per_pixel == 8
		)
			return image::color::format::a8;
		break;
	case IL_LUMINANCE:
		if(
			_bits_per_pixel == 8
		)
			return image::color::format::l8;
		break;
	case IL_LUMINANCE_ALPHA:
		if(
			_bits_per_pixel == 16
		)
			return image::color::format::la8;
		break;
	case IL_RGB:
		switch(
			_bits_per_pixel
		)
		{
		case 24:
			return image::color::format::rgb8;
		case 96:
			return image::color::format::rgb32f;
		}
		break;
	case IL_BGR:
		switch(
			_bits_per_pixel
		)
		{
		case 24:
			return image::color::format::bgr8;
		case 96:
			return image::color::format::bgr32f;
		}
		break;
	case IL_RGBA:
		switch(
			_bits_per_pixel
		)
		{
		case 32:
			return image::color::format::rgba8;
		case 128:
			return image::color::format::rgba32f;
		}
		break;
	case IL_BGRA:
		switch(
			_bits_per_pixel
		)
		{
		case 32:
			return image::color::format::bgra8;
		case 128:
			return image::color::format::bgra32f;
		}
		break;
	}

	throw sge::image::exception(
		(
			fcppt::format(
				FCPPT_TEXT("Invalid il format in devil::convert_format ")
				FCPPT_TEXT("with bits per pixel %1% and format %2%!")
			)
			% _bits_per_pixel
			%
			::format_to_string(
				_format
			)
		).str()
	);
}

namespace
{

fcppt::string const
format_to_string(
	ILenum const _format
)
{
	switch(
		_format
	)
	{
	case IL_COLOR_INDEX:
		return FCPPT_TEXT("COLOR_INDEX");
	case IL_ALPHA:
		return FCPPT_TEXT("ALPHA");
	case IL_RGB:
		return FCPPT_TEXT("RGB");
	case IL_RGBA:
		return FCPPT_TEXT("RGBA");
	case IL_BGR:
		return FCPPT_TEXT("BGR");
	case IL_BGRA:
		return FCPPT_TEXT("BGRA");
	case IL_LUMINANCE:
		return FCPPT_TEXT("LUMINANCE");
	case IL_LUMINANCE_ALPHA:
		return FCPPT_TEXT("LUMINANCE_ALPHA");
	}

	FCPPT_ASSERT_UNREACHABLE;
}

}
