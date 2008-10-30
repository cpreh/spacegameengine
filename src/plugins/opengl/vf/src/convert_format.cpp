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


#include "../convert_format.hpp"
#include <sge/renderer/vf/dynamic_vector.hpp>
#include <sge/renderer/vf/dynamic_color.hpp>
#include <sge/exception.hpp>
#include <sge/text.hpp>

GLenum sge::ogl::vf::convert_format::operator()(
	renderer::vf::dynamic_vector const &v) const
{
	switch(v.element_type()) {
	case renderer::vf::element_type::float_:
		return GL_FLOAT;
	case renderer::vf::element_type::double_:
		return GL_DOUBLE;
	case renderer::vf::element_type::byte:
		return GL_UNSIGNED_BYTE;
	default:
		throw exception(
			SGE_TEXT("Invalid format in ogl::vf::convert_format!"));
	}
}

GLenum sge::ogl::vf::convert_format::operator()(
	renderer::vf::dynamic_color const &c) const
{
	switch(c.color_format()) {
	case renderer::color_format::rgba8:
	case renderer::color_format::bgra8:
	case renderer::color_format::argb8:
		return GL_UNSIGNED_BYTE;
	case renderer::color_format::rgbaf32:
		return GL_FLOAT;
	default:
		throw exception(
			SGE_TEXT("Invalid color_format in ogl::vf::convert_format!"));
	}
}
