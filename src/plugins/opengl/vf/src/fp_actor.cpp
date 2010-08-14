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


#include "../fp_actor.hpp"
#include "../client_state_combiner.hpp"

sge::opengl::vf::fp_actor::fp_actor(
	vf::actor_parameters const &_param,
	GLenum const _client_state
)
:
	pointer_actor(
		_param
	),
	client_state_(
		_client_state
	)
{
}
		
void
sge::opengl::vf::fp_actor::operator()(
	client_state_combiner &_combiner,
	vf::pointer const _src
) const
{
	on_use(
		_src
	);

	_combiner.enable(
		client_state_
	);
}

void
sge::opengl::vf::fp_actor::unuse(
	client_state_combiner &_combiner
) const
{
	_combiner.disable(
		client_state_
	);
}
