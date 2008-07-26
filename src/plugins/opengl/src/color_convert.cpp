/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2007  Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include "../color_convert.hpp"
#include <sge/exception.hpp>
#include <sge/text.hpp>

sge::renderer::color_format::type
sge::ogl::color_convert(
	GLenum const format,
	GLenum const format_type)
{
	// TODO: make this prettier
	if(format == GL_RGBA && format_type == GL_UNSIGNED_BYTE)
		return renderer::color_format::rgba8;
	//if(format == GL_RGBA && format_type == GL_UNSIGNED_BYTE_REVERSED)
	//	return renderer::color_format::argb8;
	throw exception(
		SGE_TEXT("ogl::color_convert: No matching color_format!"));
}

GLenum sge::ogl::to_format(
	renderer::color_format::type const fmt)
{
	switch(fmt) {
	case renderer::color_format::argb8:
	case renderer::color_format::rgba8:
		return GL_RGBA; // TODO: is this right?
	default:
		throw exception(
			SGE_TEXT("Invalid color_format in to_format()!"));
	}
}

GLenum sge::ogl::to_format_type(
	renderer::color_format::type const fmt)
{
	switch(fmt) {
	case renderer::color_format::argb8:
	case renderer::color_format::rgba8:
		return GL_UNSIGNED_BYTE; // TODO: is this right?
	default:
		throw exception(
			SGE_TEXT("Invalid color_format in to_format_type()!"));
	}
}
