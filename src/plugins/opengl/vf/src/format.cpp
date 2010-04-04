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


#include "../../common.hpp"
#include "../format.hpp"
#include "../to_actor.hpp"
#include "../client_state_combiner.hpp"
#include "../global_client_state.hpp"
#include <fcppt/container/linear_set_impl.hpp>
#include <boost/foreach.hpp>

sge::opengl::vf::format::format(
	renderer::vf::dynamic::format const &fmt
)
:
	fmt(fmt)
{
	renderer::vf::dynamic::ordered_element_list const &elems(
		fmt.elements()
	);

	BOOST_FOREACH(
		renderer::vf::dynamic::ordered_element const &e,
		elems
	)
		actors.push_back(
			to_actor(
				e,
				fmt.stride()
			)
		);
}

sge::renderer::vf::dynamic::format const &
sge::opengl::vf::format::get() const
{
	return fmt;
}

void
sge::opengl::vf::format::use_me(
	pointer const src
) const
{
	client_state_combiner states_(
		global_client_state()
	);

	BOOST_FOREACH(
		actor_array::reference c,
		actors
	)
	{
		c.source(
			src
		);

		c(
			states_
		);
	}
}

void
sge::opengl::vf::format::unuse_me() const
{
	client_state_combiner states_(
		global_client_state()
	);

	BOOST_FOREACH(
		actor_array::reference c,
		actors
	)
	{
		c.unuse(
			states_
		);
	}
}
