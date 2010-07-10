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


#include "../vbo_context.hpp"
#include "../context/make_id.hpp"
#include "../create_vbo_impl.hpp"
#include "../vbo_base.hpp"
#include "../software_vbo.hpp"
#include "../glew.hpp"
#include <sge/exception.hpp>
#include <fcppt/text.hpp>

sge::opengl::vbo_context::vbo_context()
:
	impl_(
		create_vbo_impl(
			glew_is_supported("GL_VERSION_1_5")
			|| glew_is_supported("GL_ARB_vertex_buffer_object")
		)
	),
	index_buffer_type_(
		impl_->hardware_supported()
		?
			glew_is_supported(
				"GL_VERSION_1_5"
			)
			?
				GL_ELEMENT_ARRAY_BUFFER
			:
				glew_is_supported(
					"GL_ARB_vertex_buffer_object"
				)
				?
					GL_ELEMENT_ARRAY_BUFFER_ARB
				:
					throw sge::exception(
						FCPPT_TEXT("Can't figure out what GL_ELEMENT_ARRAY_BUFFER should be")
					)
		:
			software_vbo::unique_id()
	),
	vertex_buffer_type_(
		impl_->hardware_supported()
		?
			glew_is_supported(
				"GL_VERSION_1_5"
			)
			?
				GL_ARRAY_BUFFER
			:
				glew_is_supported(
					"GL_ARB_vertex_buffer_object"
				)
				?
					GL_ARRAY_BUFFER_ARB
				:
					throw sge::exception(
						FCPPT_TEXT("Can't figure out what GL_ARRAY_BUFFER should be")
					)
		:
			software_vbo::unique_id()

	)
{
}

sge::opengl::vbo_context::~vbo_context()
{
}

sge::opengl::vbo_base &
sge::opengl::vbo_context::impl()
{
	return *impl_;
}

sge::opengl::context::id const
sge::opengl::vbo_context::static_id(
	sge::opengl::context::make_id()
);

