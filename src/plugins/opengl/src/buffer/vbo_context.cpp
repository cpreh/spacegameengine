/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2013 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include <sge/opengl/common.hpp>
#include <sge/opengl/buffer/base.hpp>
#include <sge/opengl/buffer/create.hpp>
#include <sge/opengl/buffer/make_type.hpp>
#include <sge/opengl/buffer/type.hpp>
#include <sge/opengl/buffer/vbo_context.hpp>
#include <sge/opengl/context/system/base.hpp>
#include <sge/opengl/context/system/id.hpp>
#include <sge/opengl/context/system/make_id.hpp>
#include <fcppt/preprocessor/disable_gcc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>


FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_GCC_WARNING(-Wold-style-cast)

sge::opengl::buffer::vbo_context::vbo_context()
:
	sge::opengl::context::system::base(),
	impl_(
		sge::opengl::buffer::create(
			GLEW_VERSION_1_5
			||
			GLEW_ARB_vertex_buffer_object
		)
	),
	index_buffer_type_(
		SGE_OPENGL_BUFFER_MAKE_TYPE(
			impl_->hardware_supported(),
			GLEW_VERSION_1_5,
			GL_ELEMENT_ARRAY_BUFFER,
			GLEW_ARB_vertex_buffer_object,
			GL_ELEMENT_ARRAY_BUFFER_ARB
		)
	),
	vertex_buffer_type_(
		SGE_OPENGL_BUFFER_MAKE_TYPE(
			impl_->hardware_supported(),
			GLEW_VERSION_1_5,
			GL_ARRAY_BUFFER,
			GLEW_ARB_vertex_buffer_object,
			GL_ARRAY_BUFFER_ARB
		)
	)
{
}

FCPPT_PP_POP_WARNING

sge::opengl::buffer::vbo_context::~vbo_context()
{
}

sge::opengl::buffer::base &
sge::opengl::buffer::vbo_context::impl()
{
	return *impl_;
}

sge::opengl::buffer::type const
sge::opengl::buffer::vbo_context::index_buffer_type() const
{
	return index_buffer_type_;
}

sge::opengl::buffer::type const
sge::opengl::buffer::vbo_context::vertex_buffer_type() const
{
	return vertex_buffer_type_;
}

sge::opengl::context::system::id const
sge::opengl::buffer::vbo_context::static_id(
	sge::opengl::context::system::make_id()
);
