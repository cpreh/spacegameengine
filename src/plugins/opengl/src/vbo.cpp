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


#include "../vbo.hpp"
#include "../vbo_util.hpp"
#include "../software_vbo.hpp"
#include <boost/scoped_ptr.hpp>

namespace
{

boost::scoped_ptr<sge::ogl::vbo_base> impl;

}

void sge::ogl::initialize_vbo()
{
	impl.reset(create_vbo_impl(GLEW_VERSION_1_5 || GL_ARB_vertex_buffer_object));
}

GLenum sge::ogl::index_buffer_type()
{
	if(GLEW_VERSION_1_5)
		return GL_ELEMENT_ARRAY_BUFFER;
	if(GLEW_ARB_vertex_buffer_object)
		return GL_ELEMENT_ARRAY_BUFFER_ARB;
	static GLenum software_id = software_vbo::unique_id();
	return software_id;
}

GLenum sge::ogl::vertex_buffer_type()
{
	if(GLEW_VERSION_1_5)
		return GL_ARRAY_BUFFER;
	if(GLEW_ARB_vertex_buffer_object)
		return GL_ARRAY_BUFFER_ARB;
	static GLenum software_id = software_vbo::unique_id();
	return software_id;
}

sge::ogl::vbo_base& sge::ogl::vb_ib_vbo_impl()
{
	return *impl;
}
