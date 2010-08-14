/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2010 Carl Philipp Reh (sefi@s-e-f-i.de)

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
#include "../actor_parameters.hpp"
#include "../unspecified_elements.hpp"
#include "../unspecified_format.hpp"
#include "../unspecified_index.hpp"
#include "../client_state_combiner.hpp"
#include "../../glsl/context.hpp"
#include "../../context/use.hpp"
#include "../../on_not_supported.hpp"
#include <sge/renderer/vf/dynamic/ordered_element.hpp>
#include <fcppt/optional_impl.hpp>
#include <fcppt/assert.hpp>

sge::opengl::vf::attribute_actor::attribute_actor(
	actor_parameters const &_param,
	renderer::vf::dynamic::unspecified const &_unspec
)
:
	pointer_actor(
		_param
	),
	attribute_context_(
		opengl::context::use<
			attribute_context
		>(
			_param.context()
		)
	),
	glsl_context_(
		opengl::context::use<
			opengl::glsl::context
		>(
			_param.context()
		)
	),
	elements_(
		vf::unspecified_elements(
			_unspec.type()
		)
	),
	format_(
		vf::unspecified_format(
			_unspec.type()
		)
	),
	element_tag_(
		_unspec.tag()
	),
	index_()
{
	// This check is not really necessary because this format cannot
	// be used without an active program. But I'll leave it here.
	if(
		!attribute_context_.is_supported()
	)
		opengl::on_not_supported(
			FCPPT_TEXT("glVertexAttribPointer"),
			FCPPT_TEXT("GL_VERSION_2_0"),
			FCPPT_TEXT("GL_ARB_vertex_shader")
		);
}

void
sge::opengl::vf::attribute_actor::operator()(
	client_state_combiner &_combiner,
	vf::pointer const _src
) const
{
	// This function is called when the vertex format
	// is actually used.
	// It is important to postpone the glGetAttribLocation
	// until here.
	index_ =
		vf::unspecified_index(
			glsl_context_,
			element_tag_
		);

	_combiner.enable_attribute(
		*index_
	);

	attribute_context_.vertex_attrib_pointer()(
		*index_,
		elements_,
		format_,
		GL_TRUE, // normalized
		static_cast<
			GLsizei
		>(
			stride()
		),
		_src
	);
}

void
sge::opengl::vf::attribute_actor::unuse(
	client_state_combiner &_combiner
) const
{
	FCPPT_ASSERT(index_);

	_combiner.disable_attribute(
		*index_
	);

	index_.reset();
}
