/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2015 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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
#include <sge/opengl/buffer/base.hpp>
#include <sge/opengl/buffer/hardware.hpp>
#include <sge/opengl/buffer/hardware_config.hpp>
#include <sge/opengl/buffer/id.hpp>
#include <sge/opengl/buffer/optional_id.hpp>
#include <sge/opengl/buffer/type.hpp>
#include <sge/renderer/exception.hpp>
#include <fcppt/const.hpp>
#include <fcppt/text.hpp>
#include <fcppt/assert/optional_error.hpp>
#include <fcppt/cast/to_void_ptr.hpp>
#include <fcppt/optional/comparison.hpp>
#include <fcppt/optional/from.hpp>


sge::opengl::buffer::hardware::hardware(
	sge::opengl::buffer::type const _type,
	sge::opengl::buffer::hardware_config const &_config
)
:
	sge::opengl::buffer::base(),
	type_(
		_type
	),
	config_(
		_config
	),
	bound_buffer_()
{
}

sge::opengl::buffer::hardware::~hardware()
{
}

sge::opengl::buffer::id
sge::opengl::buffer::hardware::gen_buffer()
{
	GLuint new_id;

	config_.gen_buffers()(
		1,
		&new_id
	);

	SGE_OPENGL_CHECK_STATE(
		FCPPT_TEXT("glGenBuffers failed"),
		sge::renderer::exception
	)

	return
		sge::opengl::buffer::id(
			new_id
		);
}

void
sge::opengl::buffer::hardware::delete_buffer(
	sge::opengl::buffer::id const _id
)
{
	config_.delete_buffers()(
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
	sge::opengl::buffer::optional_id const &_id
)
{
	if(
		_id
		==
		bound_buffer_
	)
		return;

	bound_buffer_ =
		_id;

	sge::opengl::buffer::id const id(
		fcppt::optional::from(
			_id,
			fcppt::const_(
				sge::opengl::buffer::id(
					0u
				)
			)
		)
	);

	config_.bind_buffer()(
		type_.get(),
		id.get()
	);

	SGE_OPENGL_CHECK_STATE(
		FCPPT_TEXT("glBindBuffer failed"),
		sge::renderer::exception
	)
}

GLvoid *
sge::opengl::buffer::hardware::map_buffer(
	GLenum const _flags
)
{
	GLvoid *const ret(
		fcppt::cast::to_void_ptr(
			config_.map_buffer()(
				type_.get(),
				_flags
			)
		)
	);

	SGE_OPENGL_CHECK_STATE(
		FCPPT_TEXT("glMapBuffer failed"),
		sge::renderer::exception
	)

	return
		ret;
}

GLvoid *
sge::opengl::buffer::hardware::map_buffer_range(
	GLenum const _flags,
	GLsizei const _first,
	GLsizei const _size
)
{
	GLvoid *const ret(
		FCPPT_ASSERT_OPTIONAL_ERROR(
			config_.map_buffer_range()
		).get()(
			type_.get(),
			_first,
			_size,
			_flags
		)
	);

	SGE_OPENGL_CHECK_STATE(
		FCPPT_TEXT("glMapBufferRange failed"),
		sge::renderer::exception
	)

	return
		ret;
}

bool
sge::opengl::buffer::hardware::map_buffer_range_supported() const
{
	return
		config_.map_buffer_range().has_value();
}

void
sge::opengl::buffer::hardware::unmap_buffer()
{
	config_.unmap_buffer()(
		type_.get()
	);

	SGE_OPENGL_CHECK_STATE(
		FCPPT_TEXT("glUnmapBuffer failed"),
		sge::renderer::exception
	)
}

void
sge::opengl::buffer::hardware::buffer_data(
	GLsizei const _size,
	GLvoid const *const _data,
	GLenum const _flags
)
{
	config_.buffer_data()(
		type_.get(),
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
	GLsizei const _first,
	GLsizei const _size,
	GLvoid const *const _data
)
{
	config_.buffer_sub_data()(
		type_.get(),
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
sge::opengl::buffer::hardware::native() const
{
	return
		true;
}
