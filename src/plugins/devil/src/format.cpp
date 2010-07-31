/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2009 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include "../format.hpp"
#include <sge/image/exception.hpp>
#include <fcppt/format.hpp>
#include <fcppt/string.hpp>
#include <fcppt/text.hpp>

namespace
{

fcppt::string const
format_to_string(
	ILenum const format
)
{
	switch(
		format
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

	throw sge::image::exception(	
		FCPPT_TEXT("Unknown il format")
	);
}

}

sge::image::color::format::type
sge::devil::convert_format(
	ILint const bits_per_pixel,
	ILenum const format
)
{
	switch(
		format
	)
	{
	case IL_RGBA:
		switch(
			bits_per_pixel
		)
		{
		case 32:
			return image::color::format::rgba8;
		case 128:
			return image::color::format::rgba32f;
		}
		break;
	case IL_RGB:
		if(
			bits_per_pixel == 24
		)
			return image::color::format::rgb8;
		break;
	case IL_BGRA:
		switch(
			bits_per_pixel
		)
		{
		case 32:
			return image::color::format::bgra8;
		case 128:
			return image::color::format::bgra32f;
		}
		break;
	case IL_LUMINANCE:
	case IL_COLOR_INDEX:
		if(
			bits_per_pixel == 8
		)
			return image::color::format::gray8;
		break;
	case IL_ALPHA:
		if(
			bits_per_pixel == 8
		)
			return image::color::format::alpha8;
		break;
	}

	throw sge::image::exception(
		(
			fcppt::format(
				FCPPT_TEXT("Invalid il format in devil::convert_format ")
				FCPPT_TEXT(" with bits per pixel %1% and format %2%!")
			)
			% bits_per_pixel
			%
			::format_to_string(
				format
			)
		).str()
	);
}

ILint
sge::devil::to_il_format(
	image::color::format::type const fmt
)
{
	switch(fmt)
	{
	case image::color::format::bgra8:
		return IL_BGRA;
	case image::color::format::rgba8:
		return IL_RGBA;
	case image::color::format::rgb8:
		return IL_RGB;
	case image::color::format::alpha8:
		return IL_ALPHA;
	case image::color::format::argb8:
	case image::color::format::gray8:
	case image::color::format::argb32f:
	case image::color::format::bgra32f:
	case image::color::format::rgba32f:
	case image::color::format::size:
		break;
	}

	throw sge::image::exception(
		FCPPT_TEXT("Invalid color_format in to_il_format!")
	);
}

ILint
sge::devil::to_il_channel(
	image::color::format::type const fmt
)
{
	switch(fmt)
	{
	case image::color::format::bgra8:
	case image::color::format::rgba8:
	case image::color::format::rgb8:
	case image::color::format::alpha8:
	case image::color::format::gray8:
	case image::color::format::argb8:
		return IL_UNSIGNED_BYTE;
	case image::color::format::argb32f:
	case image::color::format::bgra32f:
	case image::color::format::rgba32f:
		return IL_FLOAT;
	case image::color::format::size:
		break;
	}

	throw sge::image::exception(
		FCPPT_TEXT("Invalid color_format in to_il_channel!")
	);
}

sge::image::color::format::type
sge::devil::best_il_format(
	image::color::format::type const fmt
)
{
	switch(fmt)
	{
	case image::color::format::bgra8:
	case image::color::format::rgba8:
	case image::color::format::rgb8:
	case image::color::format::gray8:
	case image::color::format::alpha8:
		return fmt;
	case image::color::format::argb8:
	case image::color::format::rgba32f:
	case image::color::format::argb32f:
	case image::color::format::bgra32f:
		return image::color::format::rgba8;
	case image::color::format::size:
		break;
	}

	throw sge::image::exception(
		FCPPT_TEXT("Invalid color_format in best_il_format!")
	);
}
