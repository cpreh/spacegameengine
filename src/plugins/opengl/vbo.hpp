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


#ifndef SGE_OPENGL_VBO_HPP_INCLUDED
#define SGE_OPENGL_VBO_HPP_INCLUDED

#include "common.hpp"
#include "vbo_common.hpp"
#include "hardware_vbo.hpp"
#include "software_vbo.hpp"

#if defined(GLEW_VERSION_1_5)
#define SGE_OPENGL_VERTEX_BUFFER_OBJECT
#elif defined(GL_VERTEX_BUFFER_OBJECT_ARB)
#define SGE_OPENGL_VERTEX_BUFFER_OBJECT_ARB
#endif

#if defined(SGE_OPENGL_VERTEX_BUFFER_OBJECT) || defined(SGE_OPENGL_VERTEX_BUFFER_OBJECT_ARB)
#define SGE_OPENGL_HAVE_VBO
#endif

namespace sge
{
namespace ogl
{

#ifdef SGE_OPENGL_VERTEX_BUFFER_OBJECT_ARB
const GLenum index_buffer_type = GL_ELEMENT_ARRAY_BUFFER_ARB;
const GLenum vertex_buffer_type = GL_ARRAY_BUFFER_ARB;
#else
const GLenum index_buffer_type = GL_ELEMENT_ARRAY_BUFFER;
const GLenum vertex_buffer_type = GL_ARRAY_BUFFER;
#endif

namespace detail
{
const bool hw_vbo = 
#ifdef SGE_OPENGL_HAVE_VBO
	true
#else
	false
#endif
	;
}

template<>
struct select_vbo_impl<index_buffer_type> {
	typedef vbo_impl<detail::hw_vbo> type;
};

template<>
struct select_vbo_impl<vertex_buffer_type> {
	typedef vbo_impl<detail::hw_vbo> type;
};

template<GLenum Type>
void* buffer_offset(const GLsizei offset)
{
	return select_vbo_impl<Type>::type::buffer_offset(Type, offset);
}

}
}

#endif
