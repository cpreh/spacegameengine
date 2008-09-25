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


/*#include "../error.hpp"
#include "../vbo.hpp"
#include "../vbo_base.hpp"
#include "../vertex_format.hpp"*/
#include "../format.hpp"
#include "../to_actor.hpp"
#include <boost/foreach.hpp>
/*#include <sge/exception.hpp>
#include <sge/text.hpp>
#include <boost/bind.hpp>
#include <boost/foreach.hpp>*/

/*
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
}*/

sge::ogl::vf::format::vf::format(
	renderer::vf::dynamic_format const &fmt)
: fmt(fmt)
{
	renderer::vf::dynamic_ordered_element_list const &elems(
		fmt.elements());
	
	BOOST_FOREACH(renderer::fv::dynamic_ordered_element const &e, elems)
		actors.push_back(
			to_actor(e));
	/*vertex_size offset = 0;
	const renderer::vertex_format::usage_list& l = f.elements();

	BOOST_FOREACH(renderer::vertex_format::usage_list::const_reference i, l)
	{
		for(vertex_size count = 0; count < i.count(); ++count)
		{
			const vertex_actor_info ai(offset + count * i.size(), f.stride(), count);
			switch(i.usage()) {
			case renderer::vertex_usage::pos:
				actors.push_back(boost::bind(pos_actor, ai));
				break;
			case renderer::vertex_usage::tex:
				actors.push_back(boost::bind(tex_actor, ai));
				break;
			case renderer::vertex_usage::normal:
				actors.push_back(boost::bind(normal_actor, ai));
				break;
			case renderer::vertex_usage::diffuse:
				actors.push_back(boost::bind(diffuse_actor, ai));
				break;
			default:
				throw exception(SGE_TEXT("Invalid vertex_usage!"));
			}
		}

		oi[i.usage()] = offset;
		offset += i.stride();
	}*/
}

sge::renderer::vf::dynamic_format const &
sge::ogl::vf::format::get() const
{
	return fmt;
}

void sge::ogl::vf::format::use_me() const
{
	glDisableClientState(GL_VERTEX_ARRAY);
        glDisableClientState(GL_NORMAL_ARRAY);
        glDisableClientState(GL_COLOR_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
        glDisableClientState(GL_SECONDARY_COLOR_ARRAY);

	BOOST_FOREACH(actor_array::const_reference c, actors)
		c();
}
