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


#include <boost/bind.hpp>
#include "../../../exception.hpp"
#include "../error.hpp"
#include "../vbo.hpp"
#include "../vbo_base.hpp"
#include "../vertex_format.hpp"

namespace {

using sge::vertex_size;

struct vertex_actor_info {
	vertex_actor_info(vertex_size offset,
	                  vertex_size stride,
	                  vertex_size index);
	void*       offset;
	vertex_size stride;
	vertex_size index;
};

vertex_actor_info::vertex_actor_info(const vertex_size offset_,
                                     const vertex_size stride,
                                     const vertex_size index)
:	offset(
		sge::ogl::vb_ib_vbo_impl().buffer_offset(
			sge::ogl::vertex_buffer_type(),
			offset_)),
	stride(stride),
	index(index)
{}

void pos_actor(const vertex_actor_info& ai)
{
	SGE_OPENGL_SENTRY

	glVertexPointer(3, GL_FLOAT, static_cast<GLsizei>(ai.stride), ai.offset);
	glEnableClientState(GL_VERTEX_ARRAY);
}

void normal_actor(const vertex_actor_info& ai)
{
	SGE_OPENGL_SENTRY

	glNormalPointer(GL_FLOAT, static_cast<GLsizei>(ai.stride), ai.offset);
	glEnableClientState(GL_NORMAL_ARRAY);
}

void tex_actor(const vertex_actor_info& ai)
{
	SGE_OPENGL_SENTRY

	glClientActiveTexture(static_cast<GLenum>(GL_TEXTURE0 + ai.index));
	glTexCoordPointer(2, GL_FLOAT, static_cast<GLsizei>(ai.stride), ai.offset);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
}

void diffuse_actor(const vertex_actor_info& ai)
{
	SGE_OPENGL_SENTRY

  	glColorPointer(4, GL_UNSIGNED_BYTE, static_cast<GLsizei>(ai.stride), ai.offset);
	glEnableClientState(GL_COLOR_ARRAY);
}

}

sge::ogl::vertex_format::vertex_format(const sge::vertex_format& f)
{
	vertex_size offset = 0;
	const sge::vertex_format::usage_list& l = f.elements();

	for(sge::vertex_format::usage_list::const_iterator it = l.begin(); it != l.end(); ++it)
	{
		for(vertex_size count = 0; count < it->count(); ++count)
		{
			const vertex_actor_info ai(offset + count*it->size(), f.stride(), count);
			switch(it->usage()) {
			case vertex_usage::pos:
				actors.push_back(boost::bind(pos_actor, ai));
				break;
			case vertex_usage::tex:
				actors.push_back(boost::bind(tex_actor, ai));
				break;
			case vertex_usage::normal:
				actors.push_back(boost::bind(normal_actor, ai));
				break;
			case vertex_usage::diffuse:
				actors.push_back(boost::bind(diffuse_actor, ai));
				break;
			default:
				throw exception(SGE_TEXT("Invalid vertex_usage!"));
			}
		}

		oi[it->usage()] = offset;
		offset += it->stride();
	}
}

const sge::offset_info& sge::ogl::vertex_format::offsets() const
{
	return oi;
}

void sge::ogl::vertex_format::use_me() const
{
	glDisableClientState(GL_VERTEX_ARRAY);
        glDisableClientState(GL_NORMAL_ARRAY);
        glDisableClientState(GL_COLOR_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
        glDisableClientState(GL_SECONDARY_COLOR_ARRAY);
	for(actor_array::const_iterator it = actors.begin(); it != actors.end(); ++it)
		(*it)();
}
