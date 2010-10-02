/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2010 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include <sge/image/color/format_to_string.hpp>
#include <sge/image/exception.hpp>
#include <fcppt/text.hpp>

fcppt::string const
sge::image::color::format_to_string(
	format::type const _format
)
{
	switch(
		_format
	)
	{
	case format::alpha8:
		return FCPPT_TEXT("alpha8");
	case format::gray8:
		return FCPPT_TEXT("gray8");
	case format::rgba8:
		return FCPPT_TEXT("rgba8");
	case format::argb8:
		return FCPPT_TEXT("argb8");
	case format::bgra8:
		return FCPPT_TEXT("bgra8");
	case format::rgb8:
		return FCPPT_TEXT("rgb8");
	case format::rgba32f:
		return FCPPT_TEXT("rgba32f");
	case format::argb32f:
		return FCPPT_TEXT("argb32f");
	case format::bgra32f:
		return FCPPT_TEXT("bgra32f");
	case format::rgb32f:
		return FCPPT_TEXT("rgb32f");
	case format::size:
		break;
	}

	throw sge::image::exception(
		FCPPT_TEXT("Invalid color format!")
	);
}
