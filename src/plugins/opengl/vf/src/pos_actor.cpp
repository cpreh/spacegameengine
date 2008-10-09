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


#include "../pos_actor.hpp"
#include "../../error.hpp"
#include <sge/renderer/vf/dynamic_ordered_element.hpp>
#include <sge/exception.hpp>
#include <sge/text.hpp>
#include <boost/variant/get.hpp>

sge::ogl::vf::pos_actor::pos_actor(
	renderer::vf::dynamic_ordered_element const &e,
	renderer::vf::vertex_size const stride)
:
	pointer_actor(
		e,
		stride),
	elements(
		static_cast<GLint>(
			boost::get<renderer::vf::dynamic_vector>(
				e.element().info())
			.elements()))
{
	if(index() > 0)
		throw exception(
			SGE_TEXT("opengl does not support more than one pos type in the vertex format!"));
}

void sge::ogl::vf::pos_actor::operator()() const
{
	SGE_OPENGL_SENTRY

	glVertexPointer(
		elements,
		format(),
		stride(),
		pointer());
	
	glEnableClientState(GL_VERTEX_ARRAY);
}
