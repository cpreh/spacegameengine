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


#include "../color_actor.hpp"
#include "../client_state_combiner.hpp"
#include "../../error.hpp"
#include <sge/exception.hpp>
#include <sge/text.hpp>

sge::ogl::vf::color_actor::color_actor(
	renderer::vf::dynamic_ordered_element const &e,
	renderer::vf::vertex_size const stride)
:
	pointer_actor(
		e,
		stride),
	elements(4) // TODO: maybe allow colors without alpha?
{
	if(index() > 0)
		throw exception(
			SGE_TEXT("opengl does not support more than one color type in the vertex format!")
			SGE_TEXT(" glSecondaryColor is currently not supported."));
}

void sge::ogl::vf::color_actor::operator()(
	client_state_combiner &c) const
{
	SGE_OPENGL_SENTRY

	glColorPointer(
		elements,
		format(),
		stride(),
		pointer());
	
	c.enable(GL_COLOR_ARRAY);
}
