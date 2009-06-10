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


#include "../vertex_attrib.hpp"
#include "../../glew.hpp"
#include "../../version.hpp"
#include "../../check_state.hpp"
#include "../../common.hpp"
#include <sge/renderer/exception.hpp>
#include <sge/once.hpp>
#include <sge/text.hpp>

namespace
{

PFNGLVERTEXATTRIBPOINTERPROC gl_vertex_attrib_pointer;
PFNGLENABLEVERTEXATTRIBARRAYPROC gl_enable_vertex_attrib_array;
PFNGLDISABLEVERTEXATTRIBARRAYPROC gl_disable_vertex_attrib_array;

void initialize();

}

void sge::opengl::vf::vertex_attrib_pointer(
	GLuint const index,
	GLint const size,
	GLenum const type,
	GLboolean const normalized,
	GLsizei const stride,
	void const *const pointer)
{
	initialize();

	gl_vertex_attrib_pointer(
		index,
		size,
		type,
		normalized,
		stride,
		pointer
	);

	SGE_OPENGL_CHECK_STATE(
		SGE_TEXT("glVertexAttribPointer failed"),
		sge::renderer::exception
	)
}

void sge::opengl::vf::enable_vertex_attrib_array(
	GLuint const index)
{
	initialize();

	gl_enable_vertex_attrib_array(
		index
	);

	SGE_OPENGL_CHECK_STATE(
		SGE_TEXT("glEnableVertexAttribArray failed"),
		sge::renderer::exception
	)
}

void sge::opengl::vf::disable_vertex_attrib_array(
	GLuint const index)
{
	initialize();

	gl_disable_vertex_attrib_array(
		index
	);

	SGE_OPENGL_CHECK_STATE(
		SGE_TEXT("glDsiableVertexAttribArray failed"),
		sge::renderer::exception
	)
}

namespace
{

void initialize()
{
	SGE_FUNCTION_ONCE

	if(sge::opengl::glew_is_supported("GL_VERSION_2_0"))
	{
		gl_vertex_attrib_pointer = glVertexAttribPointer;
		gl_enable_vertex_attrib_array = glEnableVertexAttribArray;
		gl_disable_vertex_attrib_array = glDisableVertexAttribArray;
	
	}
	else if(sge::opengl::glew_is_supported("GL_ARB_vertex_shader"))
	{
		gl_vertex_attrib_pointer = glVertexAttribPointerARB;
		gl_enable_vertex_attrib_array = glEnableVertexAttribArrayARB;
		gl_disable_vertex_attrib_array = glDisableVertexAttribArrayARB;
	}
	else
		sge::opengl::on_not_supported(
			SGE_TEXT("vertex attributes"),
			SGE_TEXT("2.0"),
			SGE_TEXT("gl_arb_vertex_shader")
		);
}

}
