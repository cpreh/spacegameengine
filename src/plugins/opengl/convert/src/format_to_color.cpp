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


#include "../format_to_color.hpp"
#include <sge/renderer/exception.hpp>
#include <fcppt/text.hpp>

sge::image::color::format::type
sge::opengl::convert::format_to_color(
	GLenum const _format,
	GLenum const _format_type
)
{
	switch(_format)
	{
	case GL_RGBA:
		switch(_format_type)
		{
		case GL_UNSIGNED_BYTE:
			return image::color::format::rgba8;
		case GL_FLOAT:
			return image::color::format::rgba32f;
		}
		break;
	case GL_BGRA:
		switch(_format_type)
		{
		case GL_UNSIGNED_BYTE:
			return image::color::format::bgra8;
		case GL_FLOAT:
			return image::color::format::bgra32f;
		}
		break;
	case GL_RGB:
		return image::color::format::rgb8;
	}

	throw renderer::exception(
		FCPPT_TEXT("ogl::color_convert: No matching color_format!")
	);
}
