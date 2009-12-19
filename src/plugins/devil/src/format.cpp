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
#include <sge/exception.hpp>
#include <sge/text.hpp>

sge::image::color::format::type
sge::devil::convert_format(
	ILint const bits_per_pixel,
	ILint const format)
{
	if(bits_per_pixel != 32)
		throw exception(
			FCPPT_TEXT("bits_per_pixel should be 32 for devil!"));
	switch(format) {
	case IL_RGBA:
		return image::color::format::rgba8;
	case IL_BGRA:
		return image::color::format::bgra8;
	default:
		throw exception(
			FCPPT_TEXT("Invalid il format in devil::convert_format!"));
	}
}

ILint sge::devil::to_il_format(
	image::color::format::type const fmt)
{
	switch(fmt) {
	case image::color::format::bgra8:
		return IL_BGRA;
	case image::color::format::rgba8:
		return IL_RGBA;
	default:
		throw exception(
			FCPPT_TEXT("Invalid color_format in to_il_format!"));
	}
}

ILint sge::devil::to_il_channel(
	image::color::format::type const fmt)
{
	switch(fmt) {
	case image::color::format::bgra8:
	case image::color::format::rgba8:
		return IL_UNSIGNED_BYTE;
	default:
		throw exception(
			FCPPT_TEXT("Invalid color_format in to_il_channel!"));
	}
}

sge::image::color::format::type
sge::devil::best_il_format(
	image::color::format::type const fmt)
{
	switch(fmt) {
	case image::color::format::bgra8:
	case image::color::format::rgba8:
		return fmt;
	case image::color::format::argb8:
	case image::color::format::rgba32f:
	case image::color::format::argb32f:
	case image::color::format::bgra32f:
		return image::color::format::rgba8;
	default:
		throw exception(
			FCPPT_TEXT("Invalid color_format in best_il_format!"));
	}
}
