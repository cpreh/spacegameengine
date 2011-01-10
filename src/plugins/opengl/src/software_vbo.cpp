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


#include "../software_vbo.hpp"
#include <sge/renderer/const_raw_pointer.hpp>
#include <sge/renderer/raw_value.hpp>
#include <sge/renderer/exception.hpp>
#include <fcppt/algorithm/copy_n.hpp>
#include <fcppt/text.hpp>
#include <cstddef>

sge::opengl::software_vbo::software_vbo()
:
	bound_buffers_(),
	nextid_(1),
	buffers_()
{}

sge::opengl::software_vbo::~software_vbo()
{}

GLuint
sge::opengl::software_vbo::gen_buffer()
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
sge::opengl::software_vbo::delete_buffer(
	GLuint const _id
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
sge::opengl::software_vbo::bind_buffer(
	GLenum const _type,
	GLuint const _id
)
{
	bound_buffers_[
		_type
	] = _id;
}

GLvoid *
sge::opengl::software_vbo::map_buffer(
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
sge::opengl::software_vbo::map_buffer_range(
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
sge::opengl::software_vbo::map_buffer_range_supported() const
{
	return true;
}

void
sge::opengl::software_vbo::unmap_buffer(
	GLenum const _type
)
{
	this->check_bound(
		_type
	);
}

void
sge::opengl::software_vbo::buffer_data(
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
sge::opengl::software_vbo::buffer_sub_data(
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
sge::opengl::software_vbo::buffer_offset(
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
sge::opengl::software_vbo::hardware_supported() const
{
	return false;
}

GLuint
sge::opengl::software_vbo::bound_buffer(
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
			0
		:
			it->second;
}

sge::opengl::software_vbo::buffer_map::iterator
sge::opengl::software_vbo::buffer_object(
	GLuint const _id
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

sge::opengl::software_vbo::buffer_map::const_iterator
sge::opengl::software_vbo::buffer_object(
	GLuint const _id
) const
{
	return
		const_cast<
			software_vbo &
		>(
			*this
		).buffer_object(
			_id
		);
}

void
sge::opengl::software_vbo::check_bound(
	GLenum const _type
)
{
	if(
		this->bound_buffer(
			_type
		)
		== 0
	)
		throw sge::renderer::exception(
			FCPPT_TEXT("ogl soft buffer: no buffer bound!")
		);
}
