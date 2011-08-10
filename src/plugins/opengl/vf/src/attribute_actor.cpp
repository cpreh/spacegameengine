/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2011 Carl Philipp Reh (sefi@s-e-f-i.de)

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
#include "../attribute_location.hpp"
#include "../actor_parameters.hpp"
#include "../unspecified_elements.hpp"
#include "../unspecified_format.hpp"
#include "../client_state_combiner.hpp"
#include "../../glsl/context.hpp"
#include "../../context/use.hpp"
#include <sge/renderer/vf/dynamic/ordered_element.hpp>
#include <sge/renderer/unsupported.hpp>
#include <fcppt/to_std_string.hpp>

sge::opengl::vf::attribute_actor::attribute_actor(
	opengl::vf::actor_parameters const &_param,
	renderer::vf::dynamic::unspecified const &_unspec,
	opengl::vf::attribute_location_container &_attribute_locations
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
	location_(
		static_cast<
			GLuint
		>(
			// don't use 0 as a location
			_attribute_locations.size() + 1u
		)
	)
{
	if(
		!attribute_context_.is_supported()
	)
		throw sge::renderer::unsupported(
			FCPPT_TEXT("glVertexAttribPointer"),
			FCPPT_TEXT("GL_VERSION_2_0"),
			FCPPT_TEXT("GL_ARB_vertex_shader")
		);

	_attribute_locations.push_back(
		vf::attribute_location(
			location_,
			fcppt::to_std_string(
				_unspec.tag()
			)
		)
	);
}

sge::opengl::vf::attribute_actor::~attribute_actor()
{
}

void
sge::opengl::vf::attribute_actor::operator()(
	client_state_combiner &_combiner,
	vf::pointer const _src
) const
{
	_combiner.enable_attribute(
		location_
	);

	attribute_context_.vertex_attrib_pointer()(
		location_,
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
	_combiner.disable_attribute(
		location_
	);
}
