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


#include "../software_vbo.hpp"
#include <sge/renderer/const_raw_pointer.hpp>
#include <sge/renderer/raw_value.hpp>
#include <sge/exception.hpp>
#include <fcppt/algorithm/copy_n.hpp>
#include <fcppt/text.hpp>

sge::opengl::software_vbo::software_vbo()
:
	bound_buffers(),
	nextid(1),
	buffers()
{}

sge::opengl::software_vbo::~software_vbo()
{}

GLuint
sge::opengl::software_vbo::gen_buffer()
{
	buffers.insert(
		buffer_map::value_type(
			nextid,
			static_cast<
				buffer_map::mapped_type
			>(
				0
			)
		)
	);

	return nextid++;
}

void
sge::opengl::software_vbo::delete_buffer(
	GLuint const id
)
{
	buffer_map::iterator const it = buffer_object(id);
	delete[] it->second;
	buffers.erase(it);
}

void
sge::opengl::software_vbo::bind_buffer(
	GLenum const type,
	GLuint const id
)
{
	bound_buffers[type] = id;
}

GLvoid *
sge::opengl::software_vbo::map_buffer(
	GLenum const type,
	GLenum
)
{
	check_bound(type);
	return buffer_object(bound_buffer(type))->second;
}

GLvoid *
sge::opengl::software_vbo::map_buffer_range(
	GLenum const type,
	GLenum const,
	GLsizei const first,
	GLsizei const
)
{
	check_bound(type);

	return
		buffer_object(
			bound_buffer(
				type
			)
		)->second + first;
}

bool
sge::opengl::software_vbo::map_buffer_range_supported() const
{
	return true;
}

void
sge::opengl::software_vbo::unmap_buffer(
	GLenum const type
)
{
	check_bound(type);
}

void
sge::opengl::software_vbo::buffer_data(
	GLenum const type,
	GLsizei const size,
	void const *const data,
	GLenum
)
{
	buffer_map::iterator const it = buffer_object(bound_buffer(type));

	delete[] it->second;

	it->second = new renderer::raw_value[size];

	if(data)
		buffer_sub_data(type, 0, size, data);
}

void
sge::opengl::software_vbo::buffer_sub_data(
	GLenum const type,
	GLsizei const first,
	GLsizei const size,
	void const *const data
)
{
	if(!data)
		throw exception(
			FCPPT_TEXT("buffer_sub_data(): data may not be 0!"));

	fcppt::algorithm::copy_n(
		static_cast<
			renderer::const_raw_pointer
		>(data) + first,
		size,
		buffer_object(
			bound_buffer(type)
		)->second
	);
}

void *
sge::opengl::software_vbo::buffer_offset(
	GLenum const type,
	GLsizei const offset
) const
{
	return
		buffer_object(
			bound_buffer(
				type
			)
		)->second
		+ offset;
}

bool
sge::opengl::software_vbo::hardware_supported() const
{
	return false;
}

GLuint
sge::opengl::software_vbo::bound_buffer(
	GLenum const type
) const
{
	bound_buffer_map::const_iterator const it(
		bound_buffers.find(
			type
		)
	);

	return
		it == bound_buffers.end()
		?
			0
		:
			it->second;
}

sge::opengl::software_vbo::buffer_map::iterator
sge::opengl::software_vbo::buffer_object(
	GLuint const id
)
{
	buffer_map::iterator const it = buffers.find(id);

	if(it == buffers.end())
		throw sge::exception(
			FCPPT_TEXT("buffer_object(): invalid id!")
		);

	return it;
}

sge::opengl::software_vbo::buffer_map::const_iterator
sge::opengl::software_vbo::buffer_object(
	GLuint const id
) const
{
	return
		const_cast<
			software_vbo &
		>(
			*this
		).buffer_object(
			id
		);
}

void
sge::opengl::software_vbo::check_bound(
	GLenum const type
)
{
	if(bound_buffer(type) == 0)
		throw sge::exception(
			FCPPT_TEXT("ogl soft buffer: no buffer bound!")
		);
}
