/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2014 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#include <sge/opengl/common.hpp>
#include <sge/opengl/context/use.hpp>
#include <sge/opengl/vf/actor_parameters.hpp>
#include <sge/opengl/vf/attribute_actor.hpp>
#include <sge/opengl/vf/attribute_context.hpp>
#include <sge/opengl/vf/client_state_combiner.hpp>
#include <sge/opengl/vf/extra_elements.hpp>
#include <sge/opengl/vf/extra_format.hpp>
#include <sge/opengl/vf/extra_index.hpp>
#include <sge/opengl/vf/pointer.hpp>
#include <sge/opengl/vf/pointer_actor.hpp>
#include <sge/renderer/unsupported.hpp>
#include <sge/renderer/vf/dynamic/extra.hpp>
#include <sge/renderer/vf/dynamic/ordered_element.hpp>


sge::opengl::vf::attribute_actor::attribute_actor(
	sge::opengl::vf::actor_parameters const &_param,
	sge::renderer::vf::dynamic::extra const &_extra
)
:
	sge::opengl::vf::pointer_actor(
		_param
	),
	attribute_context_(
		sge::opengl::context::use<
			sge::opengl::vf::attribute_context
		>(
			_param.system_context()
		)
	),
	elements_(
		sge::opengl::vf::extra_elements(
			_extra.type()
		)
	),
	format_(
		sge::opengl::vf::extra_format(
			_extra.type()
		)
	),
	location_(
		static_cast<
			GLuint
		>(
			sge::opengl::vf::extra_index(
				_extra.index()
			)
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
}

sge::opengl::vf::attribute_actor::~attribute_actor()
{
}

void
sge::opengl::vf::attribute_actor::operator()(
	sge::opengl::vf::client_state_combiner &_combiner,
	sge::opengl::vf::pointer const _src
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
			this->stride().get()
		),
		_src
	);
}

void
sge::opengl::vf::attribute_actor::unuse(
	sge::opengl::vf::client_state_combiner &_combiner
) const
{
	_combiner.disable_attribute(
		location_
	);
}
