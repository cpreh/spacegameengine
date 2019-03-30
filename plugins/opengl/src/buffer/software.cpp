/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2016 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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
#include <sge/opengl/buffer/id.hpp>
#include <sge/opengl/buffer/optional_id.hpp>
#include <sge/opengl/buffer/software.hpp>
#include <sge/renderer/const_raw_pointer.hpp>
#include <sge/renderer/exception.hpp>
#include <sge/renderer/raw_pointer.hpp>
#include <sge/renderer/raw_value.hpp>
#include <fcppt/text.hpp>
#include <fcppt/cast/to_char_ptr.hpp>
#include <fcppt/cast/to_unsigned.hpp>
#include <fcppt/container/find_opt_iterator.hpp>
#include <fcppt/container/find_opt_mapped.hpp>
#include <fcppt/optional/to_exception.hpp>
#include <fcppt/config/external_begin.hpp>
#include <algorithm>
#include <utility>
#include <fcppt/config/external_end.hpp>


sge::opengl::buffer::software::software()
:
	sge::opengl::buffer::base(),
	bound_buffer_(),
	nextid_(
		0u
	),
	buffers_()
{
}

sge::opengl::buffer::software::~software()
{
}

sge::opengl::buffer::id
sge::opengl::buffer::software::gen_buffer()
{
	buffers_.insert(
		std::make_pair(
			nextid_,
			nullptr
		)
	);

	return
		nextid_++;
}

void
sge::opengl::buffer::software::delete_buffer(
	sge::opengl::buffer::id const _id
)
{
	buffer_map::iterator const it(
		fcppt::optional::to_exception(
			fcppt::container::find_opt_iterator(
				buffers_,
				_id
			),
			[]{
				return
					sge::renderer::exception{
						FCPPT_TEXT("delete_buffer(): Buffer not found!")
					};
			}
		)
	);

	delete[] it->second;

	buffers_.erase(
		it
	);
}

void
sge::opengl::buffer::software::bind_buffer(
	sge::opengl::buffer::optional_id const &_id
)
{
	bound_buffer_ =
		_id;
}

GLvoid *
sge::opengl::buffer::software::map_buffer(
	GLenum
)
{
	return
		this->buffer_object(
			this->bound_buffer()
		);
}

GLvoid *
sge::opengl::buffer::software::map_buffer_range(
	GLbitfield,
	GLintptr const _first,
	GLsizeiptr
)
{
	return
		this->buffer_object(
			this->bound_buffer()
		)
		+ _first;
}

bool
sge::opengl::buffer::software::map_buffer_range_supported() const
{
	return
		true;
}

void
sge::opengl::buffer::software::unmap_buffer()
{
	// For error checking only
	this->bound_buffer();
}

void
sge::opengl::buffer::software::buffer_data(
	GLsizeiptr const _size,
	void const *const _data,
	GLenum
)
{
	sge::renderer::raw_pointer &buffer(
		this->buffer_object(
			this->bound_buffer()
		)
	);

	delete[] buffer;

	buffer =
		new sge::renderer::raw_value[
			fcppt::cast::to_unsigned(
				_size
			)
		];

	if(
		_data
	)
		this->buffer_sub_data(
			0,
			_size,
			_data
		);
}

void
sge::opengl::buffer::software::buffer_sub_data(
	GLintptr const _first,
	GLsizeiptr const _size,
	void const *const _data
)
{
	if(
		!_data
	)
		throw
			sge::renderer::exception{
				FCPPT_TEXT("buffer_sub_data(): data may not be 0!")
			};

	std::copy_n(
		fcppt::cast::to_char_ptr<
			sge::renderer::const_raw_pointer
		>(
			_data
		)
		+
		_first,
		_size,
		this->buffer_object(
			this->bound_buffer()
		)
	);
}

void *
sge::opengl::buffer::software::buffer_offset(
	GLintptr const _offset
) const
{
	return
		// TODO: Why is this const?
		const_cast<
			sge::renderer::raw_pointer
		>(
			this->buffer_object(
				this->bound_buffer()
			)
			+
			_offset
		);
}

bool
sge::opengl::buffer::software::native() const
{
	return
		false;
}

sge::opengl::buffer::id
sge::opengl::buffer::software::bound_buffer() const
{
	return
		fcppt::optional::to_exception(
			bound_buffer_,
			[]{
				return
					sge::renderer::exception{
						FCPPT_TEXT("bound_buffer(): Buffer not bound!")
					};
			}
		);
}

sge::renderer::raw_pointer &
sge::opengl::buffer::software::buffer_object(
	sge::opengl::buffer::id const _id
)
{
	return
		fcppt::optional::to_exception(
			fcppt::container::find_opt_mapped(
				buffers_,
				_id
			),
			[]{
				return
					sge::renderer::exception{
						FCPPT_TEXT("buffer_object(): invalid id!")
					};
			}
		).get();
}

sge::renderer::const_raw_pointer
sge::opengl::buffer::software::buffer_object(
	sge::opengl::buffer::id const _id
) const
{
	return
		const_cast<
			sge::opengl::buffer::software &
		>(
			*this
		).buffer_object(
			_id
		);
}
