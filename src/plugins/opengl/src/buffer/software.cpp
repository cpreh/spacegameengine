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


#include <sge/opengl/common.hpp>
#include <sge/opengl/buffer/base.hpp>
#include <sge/opengl/buffer/id.hpp>
#include <sge/opengl/buffer/optional_id.hpp>
#include <sge/opengl/buffer/software.hpp>
#include <sge/opengl/buffer/type.hpp>
#include <sge/renderer/const_raw_pointer.hpp>
#include <sge/renderer/exception.hpp>
#include <sge/renderer/raw_pointer.hpp>
#include <sge/renderer/raw_value.hpp>
#include <fcppt/optional_to_exception.hpp>
#include <fcppt/text.hpp>
#include <fcppt/container/find_opt.hpp>
#include <fcppt/container/find_opt_iterator.hpp>
#include <fcppt/config/external_begin.hpp>
#include <algorithm>
#include <cstddef>
#include <utility>
#include <fcppt/config/external_end.hpp>


sge::opengl::buffer::software::software()
:
	sge::opengl::buffer::base(),
	bound_buffers_(),
	nextid_(
		0u
	),
	buffers_()
{
}

sge::opengl::buffer::software::~software()
{
}

sge::opengl::buffer::id const
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
		fcppt::optional_to_exception(
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
	sge::opengl::buffer::type const _type,
	sge::opengl::buffer::optional_id const &_id
)
{
	bound_buffers_[
		_type
	] =
		_id;
}

GLvoid *
sge::opengl::buffer::software::map_buffer(
	sge::opengl::buffer::type const _type,
	GLenum
)
{
	return
		this->buffer_object(
			this->bound_buffer(
				_type
			)
		);
}

GLvoid *
sge::opengl::buffer::software::map_buffer_range(
	sge::opengl::buffer::type const _type,
	GLenum const,
	GLsizei const _first,
	GLsizei const
)
{
	return
		this->buffer_object(
			this->bound_buffer(
				_type
			)
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
sge::opengl::buffer::software::unmap_buffer(
	sge::opengl::buffer::type const _type
)
{
	// For error checking only
	this->bound_buffer(
		_type
	);
}

void
sge::opengl::buffer::software::buffer_data(
	sge::opengl::buffer::type const _type,
	GLsizei const _size,
	void const *const _data,
	GLenum
)
{
	sge::renderer::raw_pointer &buffer(
		this->buffer_object(
			this->bound_buffer(
				_type
			)
		)
	);

	delete[] buffer;

	std::size_t const alloc_size(
		static_cast<
			std::size_t
		>(
			_size
		)
	);

	buffer =
		new sge::renderer::raw_value[
			alloc_size
		];

	if(
		_data
	)
		this->buffer_sub_data(
			_type,
			0,
			_size,
			_data
		);
}

void
sge::opengl::buffer::software::buffer_sub_data(
	sge::opengl::buffer::type const _type,
	GLsizei const _first,
	GLsizei const _size,
	void const *const _data
)
{
	if(
		!_data
	)
		throw sge::renderer::exception(
			FCPPT_TEXT("buffer_sub_data(): data may not be 0!")
		);

	std::copy_n(
		static_cast<
			renderer::const_raw_pointer
		>(
			_data
		)
		+
		_first,
		_size,
		this->buffer_object(
			this->bound_buffer(
				_type
			)
		)
	);
}

void *
sge::opengl::buffer::software::buffer_offset(
	sge::opengl::buffer::type const _type,
	GLsizei const _offset
) const
{
	return
		// TODO: Why is this const?
		const_cast<
			sge::renderer::raw_pointer
		>(
			this->buffer_object(
				this->bound_buffer(
					_type
				)
			)
			+
			_offset
		);
}

bool
sge::opengl::buffer::software::hardware_supported() const
{
	return
		false;
}

sge::opengl::buffer::id const
sge::opengl::buffer::software::bound_buffer(
	sge::opengl::buffer::type const _type
) const
{
	return
		fcppt::optional_to_exception(
			fcppt::optional_to_exception(
				fcppt::container::find_opt(
					bound_buffers_,
					_type
				),
				[]{
					return
						sge::renderer::exception{
							FCPPT_TEXT("bound_buffer(): Buffer not found!")
						};
				}

			),
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
		fcppt::optional_to_exception(
			fcppt::container::find_opt(
				buffers_,
				_id
			),
			[]{
				return
					sge::renderer::exception{
						FCPPT_TEXT("buffer_object(): invalid id!")
					};
			}
		);
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
