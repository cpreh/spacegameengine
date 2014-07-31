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
#include <sge/opengl/context/device/object_fwd.hpp>
#include <sge/opengl/context/system/object_fwd.hpp>
#include <sge/opengl/vf/actor.hpp>
#include <sge/opengl/vf/client_state_combiner.hpp>
#include <sge/opengl/vf/part.hpp>
#include <sge/opengl/vf/pointer.hpp>
#include <sge/opengl/vf/to_actor.hpp>
#include <sge/renderer/vf/dynamic/ordered_element_fwd.hpp>
#include <sge/renderer/vf/dynamic/part.hpp>
#include <fcppt/algorithm/map.hpp>


sge::opengl::vf::part::part(
	sge::opengl::context::system::object &_system_context,
	sge::opengl::context::device::object &_device_context,
	sge::renderer::vf::dynamic::part const &_part
)
:
	system_context_(
		_system_context
	),
	device_context_(
		_device_context
	),
	part_(
		_part
	),
	actors_(
		fcppt::algorithm::map<
			actor_container
		>(
			_part.elements(),
			[
				&_part,
				&_system_context
			](
				sge::renderer::vf::dynamic::ordered_element const &_elem
			)
			{
				return
					sge::opengl::vf::to_actor(
						_elem,
						_part.stride(),
						_system_context
					);
			}
		)
	)
{
}

sge::opengl::vf::part::~part()
{
}

sge::renderer::vf::dynamic::part const &
sge::opengl::vf::part::get() const
{
	return
		part_;
}

void
sge::opengl::vf::part::use_me(
	sge::opengl::vf::pointer const _src
) const
{
	sge::opengl::vf::client_state_combiner states(
		system_context_,
		device_context_
	);

	for(
		auto const &actor
		:
		actors_
	)
		(*actor)(
			states,
			static_cast<
				unsigned char const *
			>(
				_src
			)
			+
			actor->offset().get()
		);
}

void
sge::opengl::vf::part::unuse_me() const
{
	sge::opengl::vf::client_state_combiner states(
		system_context_,
		device_context_
	);

	for(
		auto &actor
		:
		actors_
	)
		actor->unuse(
			states
		);
}
