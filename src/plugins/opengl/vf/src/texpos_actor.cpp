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


#include "../texpos_actor.hpp"
#include "../client_state_combiner.hpp"
#include "../../check_state.hpp"
#include "../../multi_texture.hpp"
#include <sge/renderer/vf/dynamic_ordered_element.hpp>
#include <sge/renderer/exception.hpp>
#include <sge/exception.hpp>
#include <sge/format.hpp>
#include <fcppt/text.hpp>

sge::opengl::vf::texpos_actor::texpos_actor(
	renderer::vf::dynamic_ordered_element const &e,
	renderer::vf::vertex_size const stride)
:
	pointer_actor(
		e,
		stride),
	elements(
		static_cast<GLint>(
			e.element().info().get<
				renderer::vf::dynamic_vector
			>().elements()
		)
	)
{
	if(index() >= GL_MAX_TEXTURE_COORDS)
		throw renderer::exception((
			::sge::format(FCPPT_TEXT("opengl texture coordinates exceeded: Allowed are %1%."))
			% GL_MAX_TEXTURE_COORDS).str());
}

void sge::opengl::vf::texpos_actor::operator()(
	client_state_combiner &c) const
{
	client_texture_level(
		static_cast<
			renderer::stage_type
		>(index())
	);

	glTexCoordPointer(
		elements,
		format(),
		stride(),
		pointer()
	);

	SGE_OPENGL_CHECK_STATE(
		FCPPT_TEXT("glTexCoordPointer failed"),
		sge::renderer::exception
	)

	c.enable(GL_TEXTURE_COORD_ARRAY);
}
