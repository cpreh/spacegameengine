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


#ifndef SGE_SPRITE_INTRUSIVE_PROCESS_ORDERED_HPP_INCLUDED
#define SGE_SPRITE_INTRUSIVE_PROCESS_ORDERED_HPP_INCLUDED

#include <sge/sprite/intrusive/ordered/collection_fwd.hpp>
#include <sge/sprite/intrusive/process/ordered_with_options.hpp>
#include <sge/sprite/process/default_geometry_options.hpp>
#include <sge/sprite/process/options.hpp>
#include <sge/sprite/state/object_fwd.hpp>
#include <sge/sprite/state/options_impl.hpp>
#include <sge/sprite/state/vertex_options.hpp>


namespace sge
{
namespace sprite
{
namespace intrusive
{
namespace process
{

template<
	typename Choices,
	typename Order,
	typename Buffers,
	typename StateChoices,
	typename Compare
>
void
ordered(
	sge::sprite::intrusive::ordered::collection<
		Choices,
		Order
	> &_collection,
	Buffers &_buffers,
	sge::sprite::state::object<
		StateChoices
	> const &_states,
	Compare const &_compare
)
{
	sge::sprite::intrusive::process::ordered_with_options<
		sge::sprite::process::options<
			sge::sprite::process::default_geometry_options<
				Choices,
				Compare
			>::value
		>
	>(
		_collection,
		_buffers,
		_states,
		_compare,
		sge::sprite::state::options<
			StateChoices
		>(
			sge::sprite::state::vertex_options::declaration
		)
	);
}

}
}
}
}

#endif
