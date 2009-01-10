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


#include "../convert_texture_filter.hpp"
#include <sge/exception.hpp>
#include <sge/text.hpp>

GLenum sge::ogl::convert_texture_filter(
	renderer::min_filter::type const arg)
{
	switch(arg) {
	case renderer::min_filter::point:
		return GL_NEAREST;
	case renderer::min_filter::linear:
		return GL_LINEAR;
	case renderer::min_filter::mipmap:
		return GL_LINEAR_MIPMAP_NEAREST;
	case renderer::min_filter::trilinear:
		return GL_LINEAR_MIPMAP_LINEAR;
	default:
		throw exception(
			SGE_TEXT("Invalid min_filter!"));
	}
}

GLenum sge::ogl::convert_texture_filter(
	renderer::mag_filter::type const arg)
{
	switch(arg) {
	case renderer::mag_filter::point:
		return GL_NEAREST;
	case renderer::mag_filter::linear:
		return GL_LINEAR;
	default:
		throw exception(
			SGE_TEXT("Invalid mag_filter!"));
	}
}


