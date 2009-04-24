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



#include "../basic_buffer_impl.hpp"
#include "../pbo.hpp"
#include "../software_vbo.hpp"
#include "../vbo_util.hpp"
#include "../glew.hpp"
#include <sge/scoped_ptr.hpp>

namespace
{

sge::scoped_ptr<sge::ogl::vbo_base> impl;

}

void sge::ogl::initialize_pbo()
{
	impl.reset(
		create_vbo_impl(
			sge::ogl::pbo_in_hardware()));
}

GLenum sge::ogl::pixel_pack_buffer_type()
{
	static GLenum const type(
		glew_is_supported(
			"GL_VERSION_2_1")
			? GL_PIXEL_PACK_BUFFER
			: glew_is_supported(
				"GL_ARB_pixel_buffer_object")
				? GL_PIXEL_PACK_BUFFER_ARB
				: software_vbo::unique_id());

	return type;
}

GLenum sge::ogl::pixel_unpack_buffer_type()
{
	static GLenum const type(
		glew_is_supported(
			"GL_VERSION_2_1")
			? GL_PIXEL_UNPACK_BUFFER
			: glew_is_supported(
				"GL_ARB_pixel_buffer_object")
				? GL_PIXEL_UNPACK_BUFFER_ARB
				: software_vbo::unique_id());

	return type;
}

sge::ogl::vbo_base& sge::ogl::pbo_impl()
{
	return *impl;
}

bool sge::ogl::pbo_in_hardware()
{
	return glew_is_supported("GL_VERSION_2_1")
		|| glew_is_supported("GL_ARB_pixel_buffer_object");
}
