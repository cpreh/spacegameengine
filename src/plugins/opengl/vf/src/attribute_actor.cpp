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


#include "../attribute_actor.hpp"
#include "../convert_num_elements.hpp"
#include "../client_state_combiner.hpp"
#include "../vertex_attrib.hpp"
#include <sge/renderer/vf/dynamic/ordered_element.hpp>
#include <fcppt/variant/apply_unary.hpp>

sge::opengl::vf::attribute_actor::attribute_actor(
	renderer::vf::dynamic::ordered_element const &e,
	renderer::vf::vertex_size const stride
)
:
	pointer_actor(
		e,
		stride
	),
	elements(
		fcppt::variant::apply_unary(
			convert_num_elements(),
			e.element().info()
		)
	)
{}

void
sge::opengl::vf::attribute_actor::operator()(
	client_state_combiner &c
) const
{
	vertex_attrib_pointer(
		static_cast<GLuint>(index()),
		elements,
		format(),
		true, // normalized
		stride(),
		pointer()
	);

	c.enable_attribute(
		static_cast<GLuint>(
			index()
		)
	);
}
