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


#include <map>
#include <utility>
#include "../../../algorithm_impl.hpp"
#include "../../../exception.hpp"
#include "../software_vbo.hpp"
#include "../vbo.hpp"
#include "../pbo.hpp"

namespace
{

GLuint nextid = 1,
       bound_vb = 0,
       bound_ib = 0,
       bound_pack = 0,
       bound_unpack = 0;

typedef std::map<GLuint, unsigned char*> buffer_map;
buffer_map buffers;

GLuint& get_bound_buffer(GLenum type);
buffer_map::iterator get_buffer_object(GLuint id);
void check_bound(GLenum type);

}

GLuint sge::ogl::software_vbo::gen_buffer()
{
	buffers.insert(buffer_map::value_type(nextid, 0));
	return nextid++;
}

void sge::ogl::software_vbo::delete_buffer(const GLuint id)
{
	const buffer_map::iterator it = get_buffer_object(id);
	delete[] it->second;
	buffers.erase(it);
}

void sge::ogl::software_vbo::bind_buffer(const GLenum type, const GLuint id)
{
	get_bound_buffer(type) = id;
}

void* sge::ogl::software_vbo::map_buffer(const GLenum type, const GLenum)
{
	check_bound(type);
	return get_buffer_object(get_bound_buffer(type))->second;
}

void sge::ogl::software_vbo::unmap_buffer(const GLenum type)
{
	check_bound(type);
}

void sge::ogl::software_vbo::buffer_data(const GLenum type,
                                         const GLsizei size,
                                         const void *const data,
                                         const GLenum)
{
	const buffer_map::iterator it = get_buffer_object(get_bound_buffer(type));
	delete[] it->second;
	it->second = new unsigned char[size];
	if(data)
		buffer_sub_data(type, 0, size, data);
}

void sge::ogl::software_vbo::buffer_sub_data(const GLenum type,
                                             const GLsizei first,
                                             const GLsizei size,
                                             const void *const data)
{
	if(!data)
		throw exception(SGE_TEXT("buffer_sub_data(): data may not be 0!"));

	copy_n(static_cast<const unsigned char*>(data) + first,
	       size,
	       get_buffer_object(get_bound_buffer(type))->second);
}

void* sge::ogl::software_vbo::buffer_offset(const GLenum type,
                                            const GLsizei offset)
{
	return get_buffer_object(get_bound_buffer(type))->second + offset;
}

GLenum sge::ogl::software_vbo::unique_id()
{
	static GLenum id = 0;
	return id++;
}

namespace
{
	
GLuint& get_bound_buffer(const GLenum type)
{
	if(type == sge::ogl::vertex_buffer_type())
		return bound_vb;
	if(type == sge::ogl::index_buffer_type())
		return bound_ib;
	if(type == sge::ogl::pixel_pack_buffer_type())
		return bound_pack;
	if(type == sge::ogl::pixel_unpack_buffer_type())
		return bound_unpack;
	throw sge::exception(SGE_TEXT("get_bound_buffer(): invalid type!"));
}

buffer_map::iterator get_buffer_object(const GLuint id)
{
	const buffer_map::iterator it = buffers.find(id);
	if(it == buffers.end())
		throw sge::exception(SGE_TEXT("get_buffer_object(): invalid id!"));
	return it;
}

void check_bound(const GLenum type)
{
	if(get_bound_buffer(type) == 0)
		throw sge::exception(SGE_TEXT("ogl soft buffer: no buffer bound!"));
}

}
