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
#include "../attribute_context.hpp"
#include "../convert_num_elements.hpp"
#include "../client_state_combiner.hpp"
#include "../../context/use.hpp"
#include "../../on_not_supported.hpp"
#include <sge/renderer/vf/dynamic/ordered_element.hpp>
#include <fcppt/variant/apply_unary.hpp>

sge::opengl::vf::attribute_actor::attribute_actor(
	opengl::context::object &_context,
	renderer::vf::dynamic::ordered_element const &_element,
	renderer::vf::vertex_size const _stride
)
:
	pointer_actor(
		_element,
		_stride
	),
	context_(
		opengl::context::use<
			attribute_context
		>(
			_context
		)
	),
	elements_(
		fcppt::variant::apply_unary(
			convert_num_elements(),
			_element.element().info()
		)
	)
{
	if(
		!context_.is_supported()
	)
		opengl::on_not_supported(
			FCPPT_TEXT("glVertexAttribPointer"),
			FCPPT_TEXT("GL_VERSION_2_0"),
			FCPPT_TEXT("GL_ARB_vertex_shader")
		);
}

void
sge::opengl::vf::attribute_actor::operator()(
	client_state_combiner &c
) const
{
	context_.vertex_attrib_pointer()(
		gl_index(),
		elements_,
		format(),
		GL_TRUE, // normalized
		stride(),
		pointer()
	);

	c.enable_attribute(
		gl_index()
	);
}

void
sge::opengl::vf::attribute_actor::unuse(
	client_state_combiner &c
) const
{
	c.disable_attribute(
		gl_index()
	);
}

GLuint
sge::opengl::vf::attribute_actor::gl_index() const
{
	return
		static_cast<
			GLuint
		>(
			index() + 1u
		);
}
