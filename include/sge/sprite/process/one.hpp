/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2012 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#ifndef SGE_SPRITE_PROCESS_ONE_HPP_INCLUDED
#define SGE_SPRITE_PROCESS_ONE_HPP_INCLUDED

#include <sge/sprite/object_fwd.hpp>
#include <sge/sprite/process/geometry_options.hpp>
#include <sge/sprite/process/one_with_options.hpp>
#include <sge/sprite/process/options.hpp>
#include <sge/sprite/state/default_options.hpp>
#include <sge/sprite/state/object_fwd.hpp>
#include <sge/sprite/state/render_context.hpp>


namespace sge
{
namespace sprite
{
namespace process
{

template<
	typename RenderContext,
	typename Choices,
	typename StateChoices,
	typename Buffers
>
void
one(
	RenderContext &_render_context,
	sge::sprite::object<
		Choices
	> const &_sprite,
	Buffers &_buffers,
	sge::sprite::state::object<
		StateChoices
	> const &_sprite_state
)
{
	sge::sprite::process::one_with_options<
		sge::sprite::process::options<
			sge::sprite::process::geometry_options::update
		>
	>(
		_render_context,
		_sprite,
		_buffers,
		_sprite_state,
		sge::sprite::state::default_options<
			StateChoices
		>()
	);
}

}
}
}

#endif
