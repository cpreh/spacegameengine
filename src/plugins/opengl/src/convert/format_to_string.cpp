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


#include <sge/opengl/convert/format_to_string.hpp>
#include <sge/opengl/color_format.hpp>
#include <sge/opengl/common.hpp>
#include <fcppt/string.hpp>
#include <fcppt/assert/unreachable.hpp>


fcppt::string const
sge::opengl::convert::format_to_string(
	opengl::color_format const _format
)
{
	switch(
		_format.get()
	)
	{
	case GL_COLOR_INDEX:
		return FCPPT_TEXT("COLOR_INDEX");
	case GL_RED:
		return FCPPT_TEXT("RED");
	case GL_GREEN:
		return FCPPT_TEXT("GREEN");
	case GL_BLUE:
		return FCPPT_TEXT("BLUE");
	case GL_ALPHA:
		return FCPPT_TEXT("ALPHA");
	case GL_RGB:
		return FCPPT_TEXT("RGB");
	case GL_BGR:
		return FCPPT_TEXT("BGR");
	case GL_RGBA:
		return FCPPT_TEXT("RGBA");
	case GL_BGRA:
		return FCPPT_TEXT("BGRA");
	case GL_LUMINANCE:
		return FCPPT_TEXT("LUMINANCE");
	case GL_LUMINANCE_ALPHA:
		return FCPPT_TEXT("LUMINANCE_ALPHA");
	}

	FCPPT_ASSERT_UNREACHABLE;
}
