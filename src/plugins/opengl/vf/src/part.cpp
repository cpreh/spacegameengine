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


#include "../part.hpp"
#include "../to_actor.hpp"
#include "../actor.hpp"
#include "../client_state_combiner.hpp"
#include "../../common.hpp"
#include <sge/renderer/vf/dynamic/ordered_element_list.hpp>
#include <fcppt/container/ptr/push_back_unique_ptr.hpp>

sge::opengl::vf::part::part(
	sge::opengl::context::object &_context,
	renderer::vf::dynamic::part const &_part,
	opengl::vf::attribute_location_container &_attribute_locations
)
:
	context_(
		_context
	),
	part_(
		_part
	)
{
	renderer::vf::dynamic::ordered_element_list const &elems(
		part_.elements()
	);

	for(
		renderer::vf::dynamic::ordered_element_list::const_iterator elem_it(
			elems.begin()
		);
		elem_it != elems.end();
		++elem_it
	)
		fcppt::container::ptr::push_back_unique_ptr(
			actors_,
			vf::to_actor(
				*elem_it,
				part_.stride(),
				_context,
				_attribute_locations
			)
		);
}

sge::opengl::vf::part::~part()
{
}

sge::renderer::vf::dynamic::part const &
sge::opengl::vf::part::get() const
{
	return part_;
}

void
sge::opengl::vf::part::use_me(
	vf::pointer const _src
) const
{
	opengl::vf::client_state_combiner states(
		context_
	);

	for(
		actor_array::iterator actor_it(
			actors_.begin()
		);
		actor_it != actors_.end();
		++actor_it
	)
		(*actor_it)(
			states,
			static_cast<
				unsigned char const *
			>(
				_src
			)
			+ actor_it->offset()
		);
}

void
sge::opengl::vf::part::unuse_me() const
{
	opengl::vf::client_state_combiner states(
		context_
	);

	for(
		actor_array::iterator actor_it(
			actors_.begin()
		);
		actor_it != actors_.end();
		++actor_it
	)
		actor_it->unuse(
			states
		);
}
