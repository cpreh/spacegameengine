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


#include "../vbo.hpp"
#include "../vbo_util.hpp"
#include "../software_vbo.hpp"
#include "../glew.hpp"
#include <fcppt/scoped_ptr.hpp>

namespace
{

fcppt::scoped_ptr<sge::opengl::vbo_base> impl;

}

void sge::opengl::initialize_vbo()
{
	impl.reset(
		create_vbo_impl(
			glew_is_supported("GL_VERSION_1_5")
			|| glew_is_supported("GL_ARB_vertex_buffer_object")));
}

GLenum sge::opengl::index_buffer_type()
{
	static GLenum const type(
		glew_is_supported(
			"GL_VERSION_1_5")
			? GL_ELEMENT_ARRAY_BUFFER
			: glew_is_supported(
				"GL_ARB_vertex_buffer_object")
				? GL_ELEMENT_ARRAY_BUFFER_ARB
				: software_vbo::unique_id());
	return type;
}

GLenum sge::opengl::vertex_buffer_type()
{
	static GLenum const type(
		glew_is_supported(
			"GL_VERSION_1_5")
			? GL_ARRAY_BUFFER
			: glew_is_supported(
				"GL_ARB_vertex_buffer_object")
				? GL_ARRAY_BUFFER_ARB
				: software_vbo::unique_id());

	return type;
}

sge::opengl::vbo_base& sge::opengl::vb_ib_vbo_impl()
{
	return *impl;
}
