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


#include "../format_to_color.hpp"
#include "../format_to_string.hpp"
#include "../format_type_to_string.hpp"
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
		if(
			_format_type == GL_UNSIGNED_BYTE
		)
			return image::color::format::rgb8;
	case GL_ALPHA:
		if(
			_format_type == GL_UNSIGNED_BYTE
		)
			return image::color::format::alpha8;
	case GL_LUMINANCE:
		if(
			_format_type == GL_UNSIGNED_BYTE
		)
			return image::color::format::gray8;
	}

	throw renderer::exception(
		FCPPT_TEXT("opengl::convert::format_to_color: No matching conversion for ")
		+ convert::format_to_string(
			_format
		)
		+ FCPPT_TEXT(" ")
		+ convert::format_type_to_string(
			_format_type
		)
	);
}
