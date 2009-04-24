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



#include "../framebuffer_functions.hpp"
#include "../error.hpp"

void sge::ogl::read_pixels(
	renderer::target::size_type const x,
	renderer::target::size_type const y,
	renderer::target::size_type const width,
	renderer::target::size_type const height,
	GLenum const format,
	GLenum const type,
	unsigned char *const dest)
{
	SGE_OPENGL_SENTRY

	glReadPixels(
		static_cast<GLint>(x),
		static_cast<GLint>(y),
		static_cast<GLsizei>(width),
		static_cast<GLsizei>(height),
		format,
		type,
		dest);
}
