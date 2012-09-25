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


#ifndef SGE_SPRITE_STATE_SCOPED_IMPL_HPP_INCLUDED
#define SGE_SPRITE_STATE_SCOPED_IMPL_HPP_INCLUDED

#include <sge/sprite/state/scoped_decl.hpp>
#include <sge/sprite/state/set.hpp>
#include <sge/sprite/state/unset.hpp>


template<
	typename StateChoices
>
sge::sprite::state::scoped<
	StateChoices
>::scoped(
	render_device &_render_device,
	render_context &_render_context,
	state_options const &_options,
	state_object &_object
)
:
	render_context_(
		_render_context
	),
	options_(
		_options
	)
{
	sge::sprite::state::set(
		_render_device,
		render_context_,
		options_,
		_object
	);
}

template<
	typename StateChoices
>
sge::sprite::state::scoped<
	StateChoices
>::~scoped()
{
	sge::sprite::state::unset(
		render_context_,
		options_
	);
}

#endif
