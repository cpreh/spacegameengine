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


#include "../hardware_vbo.hpp"
#include "../check_state.hpp"
#include "../glew.hpp"
#include <sge/renderer/exception.hpp>
#include <sge/exception.hpp>
#include <sge/text.hpp>
#include <sge/once.hpp>

namespace
{

PFNGLGENBUFFERSPROC gl_gen_buffers;
PFNGLDELETEBUFFERSPROC gl_delete_buffers;
PFNGLBINDBUFFERPROC gl_bind_buffer;
PFNGLMAPBUFFERPROC gl_map_buffer;
PFNGLUNMAPBUFFERPROC gl_unmap_buffer;
PFNGLBUFFERDATAPROC gl_buffer_data;
PFNGLBUFFERSUBDATAPROC gl_buffer_sub_data;
PFNGLMAPBUFFERRANGEPROC gl_map_buffer_range;

void initialize_hardware_vbo();

}

GLuint sge::opengl::hardware_vbo::gen_buffer()
{
	initialize_hardware_vbo();

	GLuint id;
	gl_gen_buffers(1, &id);

	SGE_OPENGL_CHECK_STATE(
		SGE_TEXT("glGenBuffers failed"),
		sge::renderer::exception
	)

	return id;
}

void sge::opengl::hardware_vbo::delete_buffer(
	GLuint const id)
{
	gl_delete_buffers(1, &id);

	SGE_OPENGL_CHECK_STATE(
		SGE_TEXT("glDeleteBuffers failed"),
		sge::renderer::exception
	)
}

void sge::opengl::hardware_vbo::bind_buffer(
	GLenum const type,
	GLuint const id)
{
	gl_bind_buffer(type, id);

	SGE_OPENGL_CHECK_STATE(
		SGE_TEXT("glBindBuffer failed"),
		sge::renderer::exception
	)
}

GLvoid *
sge::opengl::hardware_vbo::map_buffer(
	GLenum const type,
	GLenum const flags
)
{
	GLvoid *const ret(
		static_cast<GLvoid *>(
			gl_map_buffer(
				type,
				flags
			)
		)
	);

	SGE_OPENGL_CHECK_STATE(
		SGE_TEXT("glMapBuffer failed"),
		sge::renderer::exception
	)

	return ret;
}

GLvoid *
sge::opengl::hardware_vbo::map_buffer_range(
	GLenum const type,
	GLenum const flags,
	GLsizei const first,
	GLsizei const size
)
{
	GLvoid *const ret(
		gl_map_buffer_range(
			type,
			first,
			size,
			flags
		)
	);

	SGE_OPENGL_CHECK_STATE(
		SGE_TEXT("glMapBufferRange failed"),
		sge::renderer::exception
	)

	return ret;
}

bool
sge::opengl::hardware_vbo::map_buffer_range_supported() const
{
	return gl_map_buffer_range;
}

void sge::opengl::hardware_vbo::unmap_buffer(
	GLenum const type)
{
	gl_unmap_buffer(type);

	SGE_OPENGL_CHECK_STATE(
		SGE_TEXT("glUnmapBuffer failed"),
		sge::renderer::exception
	)
}

void
sge::opengl::hardware_vbo::buffer_data(
	GLenum const type,
	GLsizei const size,
	GLvoid const *const data,
	GLenum const flags
)
{
	gl_buffer_data(
		type,
		size,
		data,
		flags
	);

	SGE_OPENGL_CHECK_STATE(
		SGE_TEXT("glBufferData failed"),
		sge::renderer::exception
	)
}

void
sge::opengl::hardware_vbo::buffer_sub_data(
	GLenum const type,
	GLsizei const first,
	GLsizei const size,
	GLvoid const *const data
)
{
	gl_buffer_sub_data(
		type,
		first,
		size,
		data
	);

	SGE_OPENGL_CHECK_STATE(
		SGE_TEXT("glBufferSubData failed"),
		sge::renderer::exception
	)
}

void *
sge::opengl::hardware_vbo::buffer_offset(
	GLenum,
	GLsizei const offset
) const
{
	return reinterpret_cast<void *>(offset);
}

namespace
{

void initialize_hardware_vbo()
{
	SGE_FUNCTION_ONCE

	if(sge::opengl::glew_is_supported("GL_VERSION_1_5"))
	{
		gl_gen_buffers = glGenBuffers;
		gl_delete_buffers = glDeleteBuffers;
		gl_bind_buffer = glBindBuffer;
		gl_map_buffer = glMapBuffer;
		gl_unmap_buffer = glUnmapBuffer;
		gl_buffer_data = glBufferData;
		gl_buffer_sub_data = glBufferSubData;
	}
	else if(sge::opengl::glew_is_supported("GL_ARB_vertex_buffer_object"))
	{
		gl_gen_buffers = glGenBuffersARB;
		gl_delete_buffers = glDeleteBuffersARB;
		gl_bind_buffer = glBindBufferARB;
		gl_map_buffer = glMapBufferARB;
		gl_unmap_buffer = glUnmapBufferARB;
		gl_buffer_data = glBufferDataARB;
		gl_buffer_sub_data = glBufferSubDataARB;
	}
	else
		throw sge::exception(
			SGE_TEXT("Invalid initialization of hardware_vbo!")
		);
	
	gl_map_buffer_range = glMapBufferRange;
}

}
