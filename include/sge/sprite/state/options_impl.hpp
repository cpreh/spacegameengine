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


#ifndef SGE_SPRITE_STATE_OPTIONS_IMPL_HPP_INCLUDED
#define SGE_SPRITE_STATE_OPTIONS_IMPL_HPP_INCLUDED

#include <sge/sprite/state/options_decl.hpp>
#include <sge/sprite/state/vertex_options.hpp>
#include <sge/sprite/state/detail/options_to_true.hpp>
#include <sge/sprite/state/roles/blend.hpp>
#include <sge/sprite/state/roles/rasterizer.hpp>
#include <sge/sprite/state/roles/transform.hpp>


template<
	typename StateChoices
>
sge::sprite::state::options<
	StateChoices
>::options(
	sge::sprite::state::vertex_options::type const _vertex_options
)
:
	vertex_options_(
		_vertex_options
	),
	elements_(
		sge::sprite::state::detail::options_to_true<
			StateChoices
		>()
	)
{
}

template<
	typename StateChoices
>
sge::sprite::state::options<
	StateChoices
> &
sge::sprite::state::options<
	StateChoices
>::no_blend_state()
{
	elements_. template set<
		sge::sprite::state::roles::blend
	>(
		false
	);
}

template<
	typename StateChoices
>
sge::sprite::state::options<
	StateChoices
> &
sge::sprite::state::options<
	StateChoices
>::no_rasterizer_state()
{
	elements_. template set<
		sge::sprite::state::roles::rasterizer
	>(
		false
	);
}

template<
	typename StateChoices
>
sge::sprite::state::options<
	StateChoices
> &
sge::sprite::state::options<
	StateChoices
>::no_transform_state()
{
	elements_. template set<
		sge::sprite::state::roles::transform
	>(
		false
	);
}

template<
	typename StateChoices
>
sge::sprite::state::vertex_options::type
sge::sprite::state::options<
	StateChoices
>::vertex_options() const
{
	return vertex_options_;
}

template<
	typename StateChoices
>
typename
sge::sprite::state::options<
	StateChoices
>::elements_type const &
sge::sprite::state::options<
	StateChoices
>::elements() const
{
	return elements_;
}

#endif
