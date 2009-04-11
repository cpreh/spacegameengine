/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2007  Carl Philipp Reh (sefi@s-e-f-i.de)

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
	unsigned char*
> buffer_map;
buffer_map buffers;

GLuint &bound_buffer(GLenum type);
buffer_map::iterator buffer_object(GLuint id);
void check_bound(GLenum type);

}

GLuint sge::ogl::software_vbo::gen_buffer()
{
	buffers.insert(
		buffer_map::value_type(
			nextid,
			static_cast<buffer_map::mapped_type>(
				0))); // make gcc-4.3 -std=c++0x happy
	return nextid++;
}

void sge::ogl::software_vbo::delete_buffer(
	GLuint const id)
{
	buffer_map::iterator const it = buffer_object(id);
	delete[] it->second;
	buffers.erase(it);
}

void sge::ogl::software_vbo::bind_buffer(
	GLenum const type,
	GLuint const id)
{
	bound_buffer(type) = id;
}

void *sge::ogl::software_vbo::map_buffer(
	GLenum const type,
	GLenum)
{
	check_bound(type);
	return buffer_object(bound_buffer(type))->second;
}

void sge::ogl::software_vbo::unmap_buffer(
	GLenum const type)
{
	check_bound(type);
}

void sge::ogl::software_vbo::buffer_data(
	GLenum const type,
	GLsizei const size,
	void const *const data,
	GLenum)
{
	buffer_map::iterator const it = buffer_object(bound_buffer(type));
	delete[] it->second;
	it->second = new unsigned char[size];
	if(data)
		buffer_sub_data(type, 0, size, data);
}

void sge::ogl::software_vbo::buffer_sub_data(
	GLenum const type,
	GLsizei const first,
	GLsizei const size,
	void const *const data)
{
	if(!data)
		throw exception(
			SGE_TEXT("buffer_sub_data(): data may not be 0!"));

	algorithm::copy_n(
		static_cast<const unsigned char*>(data) + first,
		size,
		buffer_object(bound_buffer(type))->second);
}

void *sge::ogl::software_vbo::buffer_offset(
	GLenum const type,
	GLsizei const offset) const
{
	return buffer_object(bound_buffer(type))->second + offset;
}

GLenum sge::ogl::software_vbo::unique_id()
{
	static GLenum id = 0;
	return id++;
}

namespace
{
	
GLuint &bound_buffer(
	GLenum const type)
{
	if(type == sge::ogl::vertex_buffer_type())
		return bound_vb;
	if(type == sge::ogl::index_buffer_type())
		return bound_ib;
	if(type == sge::ogl::pixel_pack_buffer_type())
		return bound_pack;
	if(type == sge::ogl::pixel_unpack_buffer_type())
		return bound_unpack;
	throw sge::exception(SGE_TEXT("bound_buffer(): invalid type!"));
}

buffer_map::iterator
buffer_object(
	GLuint const id)
{
	buffer_map::iterator const it = buffers.find(id);
	if(it == buffers.end())
		throw sge::exception(
			SGE_TEXT("buffer_object(): invalid id!"));
	return it;
}

void check_bound(
	GLenum const type)
{
	if(bound_buffer(type) == 0)
		throw sge::exception(
			SGE_TEXT("ogl soft buffer: no buffer bound!"));
}

}
