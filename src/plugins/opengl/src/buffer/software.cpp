/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2012 Carl Philipp Reh (sefi@s-e-f-i.de)

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
#include <sge/opengl/buffer/software.hpp>
#include <sge/renderer/const_raw_pointer.hpp>
#include <sge/renderer/exception.hpp>
#include <sge/renderer/raw_value.hpp>
#include <fcppt/text.hpp>
#include <fcppt/algorithm/copy_n.hpp>
#include <fcppt/config/external_begin.hpp>
#include <cstddef>
#include <fcppt/config/external_end.hpp>


sge::opengl::buffer::software::software()
:
	buffer::base(),
	bound_buffers_(),
	nextid_(1u),
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
		buffer_map::value_type(
			nextid_,
			static_cast<
				buffer_map::mapped_type
			>(
				0
			)
		)
	);

	return nextid_++;
}

void
sge::opengl::buffer::software::delete_buffer(
	buffer::id const _id
)
{
	buffer_map::iterator const it(
		this->buffer_object(
			_id
		)
	);

	delete[] it->second;

	buffers_.erase(
		it
	);
}

void
sge::opengl::buffer::software::bind_buffer(
	GLenum const _type,
	buffer::id const _id
)
{
	bound_buffers_[
		_type
	] = _id;
}

GLvoid *
sge::opengl::buffer::software::map_buffer(
	GLenum const _type,
	GLenum
)
{
	this->check_bound(
		_type
	);

	return
		this->buffer_object(
			this->bound_buffer(
				_type
			)
		)->second;
}

GLvoid *
sge::opengl::buffer::software::map_buffer_range(
	GLenum const _type,
	GLenum const,
	GLsizei const _first,
	GLsizei const
)
{
	this->check_bound(
		_type
	);

	return
		this->buffer_object(
			this->bound_buffer(
				_type
			)
		)->second
		+ _first;
}

bool
sge::opengl::buffer::software::map_buffer_range_supported() const
{
	return true;
}

void
sge::opengl::buffer::software::unmap_buffer(
	GLenum const _type
)
{
	this->check_bound(
		_type
	);
}

void
sge::opengl::buffer::software::buffer_data(
	GLenum const _type,
	GLsizei const _size,
	void const *const _data,
	GLenum
)
{
	buffer_map::iterator const it(
		this->buffer_object(
			this->bound_buffer(
				_type
			)
		)
	);

	delete[] it->second;

	it->second =
		new renderer::raw_value[
			static_cast<
				std::size_t
			>(
				_size
			)
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
	GLenum const _type,
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

	fcppt::algorithm::copy_n(
		static_cast<
			renderer::const_raw_pointer
		>(
			_data
		)
		+ _first,
		_size,
		this->buffer_object(
			this->bound_buffer(
				_type
			)
		)->second
	);
}

void *
sge::opengl::buffer::software::buffer_offset(
	GLenum const _type,
	GLsizei const _offset
) const
{
	return
		this->buffer_object(
			this->bound_buffer(
				_type
			)
		)->second
		+ _offset;
}

bool
sge::opengl::buffer::software::hardware_supported() const
{
	return false;
}

sge::opengl::buffer::id const
sge::opengl::buffer::software::bound_buffer(
	GLenum const _type
) const
{
	bound_buffer_map::const_iterator const it(
		bound_buffers_.find(
			_type
		)
	);

	return
		it == bound_buffers_.end()
		?
			buffer::id(
				0
			)
		:
			it->second;
}

sge::opengl::buffer::software::buffer_map::iterator
sge::opengl::buffer::software::buffer_object(
	buffer::id const _id
)
{
	buffer_map::iterator const it(
		buffers_.find(
			_id
		)
	);

	if(
		it == buffers_.end()
	)
		throw sge::renderer::exception(
			FCPPT_TEXT("buffer_object(): invalid id!")
		);

	return it;
}

sge::opengl::buffer::software::buffer_map::const_iterator
sge::opengl::buffer::software::buffer_object(
	buffer::id const _id
) const
{
	return
		const_cast<
			buffer::software &
		>(
			*this
		).buffer_object(
			_id
		);
}

void
sge::opengl::buffer::software::check_bound(
	GLenum const _type
)
{
	if(
		this->bound_buffer(
			_type
		)
		==
		buffer::id(
			0
		)
	)
		throw sge::renderer::exception(
			FCPPT_TEXT("ogl soft buffer: no buffer bound!")
		);
}
