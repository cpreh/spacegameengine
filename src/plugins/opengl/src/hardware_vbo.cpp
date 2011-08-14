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


#include "../hardware_vbo.hpp"
#include "../check_state.hpp"
#include "../glew/is_supported.hpp"
#include <sge/renderer/exception.hpp>
#include <fcppt/assert/error.hpp>
#include <fcppt/text.hpp>

sge::opengl::hardware_vbo::hardware_vbo()
:
	have_version_1_5_(
		sge::opengl::glew::is_supported(
			"GL_VERSION_1_5"
		)
	),
	have_arb_(
		sge::opengl::glew::is_supported(
			"GL_ARB_vertex_buffer_object"
		)
	),
	gl_gen_buffers_(
		have_version_1_5_
		?
			glGenBuffers
		:
			glGenBuffersARB
	),
	gl_delete_buffers_(
		have_version_1_5_
		?
			glDeleteBuffers
		:
			glDeleteBuffersARB
	),
	gl_bind_buffer_(
		have_version_1_5_
		?
			glBindBuffer
		:
			glBindBufferARB
	),
	gl_map_buffer_(
		have_version_1_5_
		?
			glMapBuffer
		:
			glMapBufferARB
	),
	gl_unmap_buffer_(
		have_version_1_5_
		?
			glUnmapBuffer
		:
			glUnmapBufferARB
	),
	gl_buffer_data_(
		have_version_1_5_
		?
			glBufferData
		:
			glBufferDataARB
	),
	gl_buffer_sub_data_(
		have_version_1_5_
		?
			glBufferSubData
		:
			glBufferSubDataARB
	),
	gl_map_buffer_range_(
		glMapBufferRange
	)
{
	if(
		!have_version_1_5_
		&& !have_arb_
	)
		throw sge::renderer::exception(
			FCPPT_TEXT("Invalid initialization of hardware_vbo!")
		);
}

sge::opengl::hardware_vbo::~hardware_vbo()
{
}

GLuint
sge::opengl::hardware_vbo::gen_buffer()
{
	GLuint id;

	gl_gen_buffers_(
		1,
		&id
	);

	SGE_OPENGL_CHECK_STATE(
		FCPPT_TEXT("glGenBuffers failed"),
		sge::renderer::exception
	)

	return id;
}

void
sge::opengl::hardware_vbo::delete_buffer(
	GLuint const _id
)
{
	gl_delete_buffers_(
		1,
		&_id
	);

	SGE_OPENGL_CHECK_STATE(
		FCPPT_TEXT("glDeleteBuffers failed"),
		sge::renderer::exception
	)
}

void
sge::opengl::hardware_vbo::bind_buffer(
	GLenum const _type,
	GLuint const _id
)
{
	gl_bind_buffer_(
		_type,
		_id
	);

	SGE_OPENGL_CHECK_STATE(
		FCPPT_TEXT("glBindBuffer failed"),
		sge::renderer::exception
	)
}

GLvoid *
sge::opengl::hardware_vbo::map_buffer(
	GLenum const _type,
	GLenum const _flags
)
{
	GLvoid *const ret(
		static_cast<
			GLvoid *
		>(
			gl_map_buffer_(
				_type,
				_flags
			)
		)
	);

	SGE_OPENGL_CHECK_STATE(
		FCPPT_TEXT("glMapBuffer failed"),
		sge::renderer::exception
	)

	return ret;
}

GLvoid *
sge::opengl::hardware_vbo::map_buffer_range(
	GLenum const _type,
	GLenum const _flags,
	GLsizei const _first,
	GLsizei const _size
)
{
	FCPPT_ASSERT_ERROR(
		gl_map_buffer_range_
	);

	GLvoid *const ret(
		gl_map_buffer_range_(
			_type,
			_first,
			_size,
			_flags
		)
	);

	SGE_OPENGL_CHECK_STATE(
		FCPPT_TEXT("glMapBufferRange failed"),
		sge::renderer::exception
	)

	return ret;
}

bool
sge::opengl::hardware_vbo::map_buffer_range_supported() const
{
	return gl_map_buffer_range_ != 0;
}

void
sge::opengl::hardware_vbo::unmap_buffer(
	GLenum const _type
)
{
	gl_unmap_buffer_(
		_type
	);

	SGE_OPENGL_CHECK_STATE(
		FCPPT_TEXT("glUnmapBuffer failed"),
		sge::renderer::exception
	)
}

void
sge::opengl::hardware_vbo::buffer_data(
	GLenum const _type,
	GLsizei const _size,
	GLvoid const *const _data,
	GLenum const _flags
)
{
	gl_buffer_data_(
		_type,
		_size,
		_data,
		_flags
	);

	SGE_OPENGL_CHECK_STATE(
		FCPPT_TEXT("glBufferData failed"),
		sge::renderer::exception
	)
}

void
sge::opengl::hardware_vbo::buffer_sub_data(
	GLenum const _type,
	GLsizei const _first,
	GLsizei const _size,
	GLvoid const *const _data
)
{
	gl_buffer_sub_data_(
		_type,
		_first,
		_size,
		_data
	);

	SGE_OPENGL_CHECK_STATE(
		FCPPT_TEXT("glBufferSubData failed"),
		sge::renderer::exception
	)
}

void *
sge::opengl::hardware_vbo::buffer_offset(
	GLenum,
	GLsizei const _offset
) const
{
	return
		reinterpret_cast<
			void *
		>(
			_offset
		);
}

bool
sge::opengl::hardware_vbo::hardware_supported() const
{
	return true;
}
