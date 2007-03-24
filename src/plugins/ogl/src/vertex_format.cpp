/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006  Carl Philipp Reh (sefi@s-e-f-i.de)

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/


#include <stdexcept>
#include "../vertex_format.hpp"
#include "../error.hpp"

sge::ogl::actor_info::actor_info(const vertex_size _offset, const vertex_size stride, const vertex_size index)
: offset(vbo_offset(_offset)),
  stride(stride),
  index(index)
{}

namespace {
	using sge::ogl::is_error;
	typedef sge::ogl::actor_base actor_base;
	typedef sge::ogl::actor_info actor_info;
	
	class pos_actor : public actor_base {
	public:
		pos_actor(const actor_info& ai)
		 : actor_base(ai) {}
		void operator()() const
		{
			glVertexPointer(3, GL_FLOAT, static_cast<GLsizei>(ai.stride), ai.offset);
			glEnableClientState(GL_VERTEX_ARRAY);
			if(is_error())
				throw std::runtime_error("Enabling positions on ogl stream failed!");
		}
	};

	class normal_actor : public actor_base {
	public:
		normal_actor(const actor_info& ai)
		 : actor_base(ai) {}
		void operator()() const
		{
			glNormalPointer(GL_FLOAT, static_cast<GLsizei>(ai.stride), ai.offset);
			glEnableClientState(GL_NORMAL_ARRAY);
			if(is_error())
				throw std::runtime_error("Enabling normals on ogl stream failed!");
		}
	};

	class tex_actor : public actor_base {
	public:
		tex_actor(const actor_info& ai)
		 : actor_base(ai) {}
		void operator()() const
		{
			glClientActiveTextureARB(static_cast<GLenum>(GL_TEXTURE0 + ai.index));
			glTexCoordPointer(2, GL_FLOAT, static_cast<GLsizei>(ai.stride), ai.offset);
			glEnableClientState(GL_TEXTURE_COORD_ARRAY);
			if(is_error())
				throw std::runtime_error("Enabling texture coordinates on ogl stream failed!");
		}
	};

	class diffuse_actor : public actor_base {
	public:
		diffuse_actor(const actor_info& ai)
		 : actor_base(ai) {}
		void operator()() const
		{
  			glColorPointer(4, GL_UNSIGNED_BYTE, static_cast<GLsizei>(ai.stride), ai.offset);
			glEnableClientState(GL_COLOR_ARRAY);
			if(is_error())
				throw std::runtime_error("Enabling diffuse colors on ogl stream failed!");
		}
	};
}

sge::ogl::vertex_format::vertex_format(const sge::vertex_format& f)
{
	vertex_size offset = 0;
	const sge::vertex_format::usage_list& l = f.elements();

	for(sge::vertex_format::usage_list::const_iterator it = l.begin(); it != l.end(); ++it)
	{
		for(vertex_size count = 0; count < it->count(); ++count)
		{
			const actor_info ai(offset + count*it->size(), f.stride(), count);
			switch(it->usage()) {
			case VU_Pos:
				actors.push_back(new pos_actor(ai));
				break;
			case VU_Tex:
				actors.push_back(new tex_actor(ai));
				break;
			case VU_Normal:
				actors.push_back(new normal_actor(ai));
				break;
			case VU_Diffuse:
				actors.push_back(new diffuse_actor(ai));
				break;
			default:
				throw std::runtime_error("unsupported vertex_usage");
			}
		}
		
		oi[it->usage()] = offset;
		offset += it->stride();
	}
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
