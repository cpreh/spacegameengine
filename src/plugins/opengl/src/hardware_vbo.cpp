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

GLuint sge::ogl::vbo_impl<true>::gen_buffer()
{
	SGE_OPENGL_SENTRY

	GLuint id;
#ifdef SGE_OPENGL_VERTEX_BUFFER_OBJECT_ARB
	glGenBuffersARB(1, &id);
#else
	glGenBuffers(1, &id);
#endif
	return id;
}

void sge::ogl::vbo_impl<true>::delete_buffer(const GLuint id)
{
#ifdef SGE_OPENGL_VERTEX_BUFFER_OBJECT_ARB
	glDeleteBuffersARB(1, &id);
#else
	glDeleteBuffers(1, &id);
#endif
}

void sge::ogl::vbo_impl<true>::bind_buffer(const GLenum type, const GLuint id)
{
	SGE_OPENGL_SENTRY
	
#ifdef SGE_OPENGL_VERTEX_BUFFER_OBJECT_ARB
	glBindBufferARB(type, id);
#else
	glBindBuffer(type, id);
#endif
}

void* sge::ogl::vbo_impl<true>::map_buffer(const GLenum type, const GLenum flags)
{
	SGE_OPENGL_SENTRY
	
	void *const ret = 
#ifdef SGE_OPENGL_VERTEX_BUFFER_OBJECT_ARB
	glMapBufferARB(type, flags);
#else
	glMapBuffer(type, flags);
#endif
	if(ret == 0)
		throw exception(SGE_TEXT("glMapBuffer() returned 0!"));
	return ret;
}

void sge::ogl::vbo_impl<true>::unmap_buffer(const GLenum type)
{
	SGE_OPENGL_SENTRY
#ifdef SGE_OPENGL_VERTEX_BUFFER_OBJECT_ARB
	glUnmapBufferARB(type);
#else
	glUnmapBuffer(type);
#endif
}

void sge::ogl::vbo_impl<true>::buffer_data(const GLenum type,
                                           const GLsizei size,
                                           const void *const data,
                                           const GLenum flags)
{
	SGE_OPENGL_SENTRY
#ifdef SGE_OPENGL_VERTEX_BUFFER_OBJECT_ARB
	glBufferDataARB(type, size, data, flags);
#else
	glBufferData(type, size, data, flags);
#endif
}

void sge::ogl::vbo_impl<true>::buffer_sub_data(const GLenum type,
                                               const GLsizei first,
                                               const GLsizei size,
                                               const void *const data)
{
	SGE_OPENGL_SENTRY
#ifdef SGE_OPENGL_VERTEX_BUFFER_OBJECT_ARB
	glBufferSubDataARB(type, first, size, data);
#else
	glBufferSubData(type, first, size, data);
#endif
}

void* sge::ogl::vbo_impl<true>::buffer_offset(const GLenum, const GLsizei offset)
{
	return reinterpret_cast<void*>(offset);
}
