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


#include <sge/opengl/check_state.hpp>
#include <sge/opengl/common.hpp>
#include <sge/opengl/buffer/hardware.hpp>
#include <sge/opengl/glew/is_supported.hpp>
#include <sge/renderer/exception.hpp>
#include <fcppt/text.hpp>
#include <fcppt/assert/error.hpp>


sge::opengl::buffer::hardware::hardware()
:
	buffer::base(),
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
	FCPPT_ASSERT_ERROR(
		have_version_1_5_
		|| have_arb_
	);
}

sge::opengl::buffer::hardware::~hardware()
{
}

sge::opengl::buffer::id const
sge::opengl::buffer::hardware::gen_buffer()
{
	GLuint new_id;

	gl_gen_buffers_(
		1,
		&new_id
	);

	SGE_OPENGL_CHECK_STATE(
		FCPPT_TEXT("glGenBuffers failed"),
		sge::renderer::exception
	)

	return
		opengl::buffer::id(
			new_id
		);
}

void
sge::opengl::buffer::hardware::delete_buffer(
	buffer::id const _id
)
{
	gl_delete_buffers_(
		1,
		&_id.get()
	);

	SGE_OPENGL_CHECK_STATE(
		FCPPT_TEXT("glDeleteBuffers failed"),
		sge::renderer::exception
	)
}

void
sge::opengl::buffer::hardware::bind_buffer(
	GLenum const _type,
	buffer::id const _id
)
{
	gl_bind_buffer_(
		_type,
		_id.get()
	);

	SGE_OPENGL_CHECK_STATE(
		FCPPT_TEXT("glBindBuffer failed"),
		sge::renderer::exception
	)
}

GLvoid *
sge::opengl::buffer::hardware::map_buffer(
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
sge::opengl::buffer::hardware::map_buffer_range(
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
sge::opengl::buffer::hardware::map_buffer_range_supported() const
{
	return gl_map_buffer_range_ != 0;
}

void
sge::opengl::buffer::hardware::unmap_buffer(
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
sge::opengl::buffer::hardware::buffer_data(
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
sge::opengl::buffer::hardware::buffer_sub_data(
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
sge::opengl::buffer::hardware::buffer_offset(
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
sge::opengl::buffer::hardware::hardware_supported() const
{
	return true;
}
