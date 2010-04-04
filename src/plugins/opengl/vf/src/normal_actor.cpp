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


#include "../normal_actor.hpp"
#include "../client_state_combiner.hpp"
#include "../../check_state.hpp"
#include <sge/renderer/vf/dynamic/ordered_element.hpp>
#include <sge/renderer/exception.hpp>
#include <fcppt/text.hpp>

sge::opengl::vf::normal_actor::normal_actor(
	renderer::vf::dynamic::ordered_element const &e,
	renderer::vf::vertex_size const stride
)
:
	pointer_actor(
		e,
		stride
	)
{
	if(index() > 0)
		throw renderer::exception(
			FCPPT_TEXT("opengl does not support more than one normal type in the vertex format!")
		);
}

void
sge::opengl::vf::normal_actor::operator()(
	client_state_combiner &c
) const
{
	glNormalPointer(
		format(),
		stride(),
		pointer()
	);

	SGE_OPENGL_CHECK_STATE(
		FCPPT_TEXT("glNormalPointer failed"),
		sge::renderer::exception
	)

	c.enable(GL_NORMAL_ARRAY);
}
