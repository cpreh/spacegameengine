/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2016 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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
#include <sge/opengl/vf/attribute_config.hpp>
#include <sge/opengl/vf/attribute_context.hpp>
#include <sge/opengl/vf/client_state_combiner.hpp>
#include <sge/opengl/vf/extra_elements.hpp>
#include <sge/opengl/vf/extra_format.hpp>
#include <sge/opengl/vf/extra_index.hpp>
#include <sge/opengl/vf/get_attribute_config.hpp>
#include <sge/opengl/vf/pointer.hpp>
#include <sge/opengl/vf/pointer_actor.hpp>
#include <sge/opengl/vf/vertex_attrib_pointer.hpp>
#include <sge/renderer/vf/dynamic/extra.hpp>
#include <fcppt/cast/size.hpp>
#include <fcppt/cast/to_signed.hpp>


sge::opengl::vf::attribute_actor::attribute_actor(
	sge::opengl::vf::actor_parameters const &_param,
	sge::renderer::vf::dynamic::extra const &_extra
)
:
	sge::opengl::vf::pointer_actor(
		_param
	),
	attribute_config_(
		sge::opengl::vf::get_attribute_config(
			sge::opengl::context::use<
				sge::opengl::vf::attribute_context
			>(
				_param.context(),
				_param.context().info()
			)
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
		fcppt::cast::size<
			GLuint
		>(
			sge::opengl::vf::extra_index(
				_extra.index()
			)
		)
	)
{
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

	sge::opengl::vf::vertex_attrib_pointer(
		attribute_config_,
		location_,
		elements_,
		format_,
		GL_TRUE, // normalized
		fcppt::cast::size<
			GLsizei
		>(
			fcppt::cast::to_signed(
				this->stride().get()
			)
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
