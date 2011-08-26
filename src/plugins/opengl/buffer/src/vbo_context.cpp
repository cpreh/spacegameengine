/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2011 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include "../vbo_context.hpp"
#include "../base.hpp"
#include "../create.hpp"
#include "../make_type.hpp"
#include "../../common.hpp"
#include "../../context/make_id.hpp"
#include "../../glew/is_supported.hpp"

sge::opengl::buffer::vbo_context::vbo_context()
:
	impl_(
		opengl::buffer::create(
			glew::is_supported("GL_VERSION_1_5")
			|| glew::is_supported("GL_ARB_vertex_buffer_object")
		)
	),
	index_buffer_type_(
		opengl::buffer::make_type(
			impl_->hardware_supported(),
			"GL_VERSION_1_5",
			GL_ELEMENT_ARRAY_BUFFER,
			"GL_ARB_vertex_buffer_object",
			GL_ELEMENT_ARRAY_BUFFER_ARB
		)
	),
	vertex_buffer_type_(
		opengl::buffer::make_type(
			impl_->hardware_supported(),
			"GL_VERSION_1_5",
			GL_ARRAY_BUFFER,
			"GL_ARB_vertex_buffer_object",
			GL_ARRAY_BUFFER_ARB
		)
	)
{
}

sge::opengl::buffer::vbo_context::~vbo_context()
{
}

sge::opengl::buffer::base &
sge::opengl::buffer::vbo_context::impl()
{
	return *impl_;
}

GLenum
sge::opengl::buffer::vbo_context::index_buffer_type() const
{
	return index_buffer_type_;
}

GLenum
sge::opengl::buffer::vbo_context::vertex_buffer_type() const
{
	return vertex_buffer_type_;
}

sge::opengl::context::id const
sge::opengl::buffer::vbo_context::static_id(
	sge::opengl::context::make_id()
);
