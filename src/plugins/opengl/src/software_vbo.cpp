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
#include "../vbo.hpp"
#include "../pbo.hpp"
#include <sge/algorithm/copy_n.hpp>
#include <sge/renderer/raw_pointer.hpp>
#include <sge/renderer/raw_value.hpp>
#include <sge/exception.hpp>
#include <sge/text.hpp>
#include <utility>
#include <map>

namespace
{

GLuint
	nextid = 1,
	bound_vb = 0,
	bound_ib = 0,
	bound_pack = 0,
	bound_unpack = 0;

typedef std::map<
	GLuint,
	sge::renderer::raw_pointer
> buffer_map;
buffer_map buffers;

GLuint &bound_buffer(GLenum type);
buffer_map::iterator buffer_object(GLuint id);
void check_bound(GLenum type);

}

GLuint sge::opengl::software_vbo::gen_buffer()
{
	buffers.insert(
		buffer_map::value_type(
			nextid,
			static_cast<buffer_map::mapped_type>(
				0))); // make gcc-4.3 -std=c++0x happy
	return nextid++;
}

void sge::opengl::software_vbo::delete_buffer(
	GLuint const id)
{
	buffer_map::iterator const it = buffer_object(id);
	delete[] it->second;
	buffers.erase(it);
}

void sge::opengl::software_vbo::bind_buffer(
	GLenum const type,
	GLuint const id)
{
	bound_buffer(type) = id;
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

void sge::opengl::software_vbo::unmap_buffer(
	GLenum const type)
{
	check_bound(type);
}

void sge::opengl::software_vbo::buffer_data(
	GLenum const type,
	GLsizei const size,
	void const *const data,
	GLenum)
{
	buffer_map::iterator const it = buffer_object(bound_buffer(type));
	delete[] it->second;
	it->second = new renderer::raw_value[size];
	if(data)
		buffer_sub_data(type, 0, size, data);
}

void sge::opengl::software_vbo::buffer_sub_data(
	GLenum const type,
	GLsizei const first,
	GLsizei const size,
	void const *const data)
{
	if(!data)
		throw exception(
			FCPPT_TEXT("buffer_sub_data(): data may not be 0!"));

	algorithm::copy_n(
		static_cast<renderer::const_raw_pointer>(data) + first,
		size,
		buffer_object(bound_buffer(type))->second);
}

void *sge::opengl::software_vbo::buffer_offset(
	GLenum const type,
	GLsizei const offset) const
{
	return buffer_object(bound_buffer(type))->second + offset;
}

GLenum sge::opengl::software_vbo::unique_id()
{
	static GLenum id = 0;
	return id++;
}

namespace
{

GLuint &bound_buffer(
	GLenum const type)
{
	if(type == sge::opengl::vertex_buffer_type())
		return bound_vb;
	if(type == sge::opengl::index_buffer_type())
		return bound_ib;
	if(type == sge::opengl::pixel_pack_buffer_type())
		return bound_pack;
	if(type == sge::opengl::pixel_unpack_buffer_type())
		return bound_unpack;
	throw sge::exception(FCPPT_TEXT("bound_buffer(): invalid type!"));
}

buffer_map::iterator
buffer_object(
	GLuint const id)
{
	buffer_map::iterator const it = buffers.find(id);
	if(it == buffers.end())
		throw sge::exception(
			FCPPT_TEXT("buffer_object(): invalid id!"));
	return it;
}

void check_bound(
	GLenum const type)
{
	if(bound_buffer(type) == 0)
		throw sge::exception(
			FCPPT_TEXT("ogl soft buffer: no buffer bound!"));
}

}
