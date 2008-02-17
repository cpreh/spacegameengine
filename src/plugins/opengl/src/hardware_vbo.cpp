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


#include "../../../exception.hpp"
#include "../hardware_vbo.hpp"
#include "../error.hpp"

namespace
{

void (*gl_gen_buffers)(GLsizei, GLuint*);
void (*gl_delete_buffers)(GLsizei, const GLuint*);
void (*gl_bind_buffer)(GLenum, GLuint);
void* (*gl_map_buffer)(GLenum, GLenum);
GLboolean (*gl_unmap_buffer)(GLenum);
void (*gl_buffer_data)(GLenum, GLsizeiptr, const GLvoid*, GLenum);
void (*gl_buffer_sub_data)(GLenum, GLintptr, GLsizeiptr, const GLvoid*);

void initialize_hardware_vbo()
{
	static bool initialized = false;
	if(initialized)
		return;
	initialized = true;

	if(GLEW_VERSION_1_5)
	{
		gl_gen_buffers = glGenBuffers;
		gl_delete_buffers = glDeleteBuffers;
		gl_bind_buffer = glBindBuffer;
		gl_map_buffer = glMapBuffer;
		gl_unmap_buffer = glUnmapBuffer;
		gl_buffer_data = glBufferData;
		gl_buffer_sub_data = glBufferSubData;
	}
	else if(GL_ARB_vertex_buffer_object)
	{
		gl_gen_buffers = glGenBuffersARB;
		gl_delete_buffers = glDeleteBuffersARB;
		gl_bind_buffer = glBindBufferARB;
		gl_map_buffer = glMapBufferARB;
		gl_unmap_buffer = glUnmapBufferARB;
		gl_buffer_data = glBufferDataARB;
		gl_buffer_sub_data = glBufferSubDataARB;
	}	
}

}

GLuint sge::ogl::hardware_vbo::gen_buffer()
{
	initialize_hardware_vbo();

	SGE_OPENGL_SENTRY

	GLuint id;
	gl_gen_buffers(1, &id);

	return id;
}

void sge::ogl::hardware_vbo::delete_buffer(const GLuint id)
{
	SGE_OPENGL_SENTRY

	gl_delete_buffers(1, &id);
}

void sge::ogl::hardware_vbo::bind_buffer(const GLenum type, const GLuint id)
{
	SGE_OPENGL_SENTRY

	gl_bind_buffer(type, id);
}

void* sge::ogl::hardware_vbo::map_buffer(const GLenum type, const GLenum flags)
{
	SGE_OPENGL_SENTRY
	
	void *const ret = gl_map_buffer(type, flags);
	
	if(ret == 0)
		throw exception(SGE_TEXT("glMapBuffer() returned 0!"));
	return ret;
}

void sge::ogl::hardware_vbo::unmap_buffer(const GLenum type)
{
	SGE_OPENGL_SENTRY
	
	if(gl_unmap_buffer(type) == GL_FALSE)
		throw exception("gl_unmap_buffer() returned false. The buffer corrupted during the lock time.");
}

void sge::ogl::hardware_vbo::buffer_data(const GLenum type,
                                         const GLsizei size,
                                         const void *const data,
                                         const GLenum flags)
{
	SGE_OPENGL_SENTRY
	
	gl_buffer_data(type, size, data, flags);
}

void sge::ogl::hardware_vbo::buffer_sub_data(const GLenum type,
                                             const GLsizei first,
                                             const GLsizei size,
                                             const void *const data)
{
	SGE_OPENGL_SENTRY
	
	gl_buffer_sub_data(type, first, size, data);
}

void* sge::ogl::hardware_vbo::buffer_offset(const GLenum, const GLsizei offset)
{
	return reinterpret_cast<void*>(offset);
}
