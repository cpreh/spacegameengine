/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2015 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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

#include <sge/sprite/optional_projection_dim.hpp>
#include <sge/sprite/projection_dim.hpp>
#include <sge/sprite/state/options_decl.hpp>
#include <sge/sprite/state/vertex_options.hpp>
#include <sge/sprite/state/detail/init_options.hpp>
#include <sge/sprite/state/roles/blend.hpp>
#include <sge/sprite/state/roles/projection_dim.hpp>
#include <sge/sprite/state/roles/rasterizer.hpp>
#include <sge/sprite/state/roles/transform.hpp>
#include <majutsu/role_return_type.hpp>
#include <majutsu/set.hpp>


template<
	typename StateChoices
>
sge::sprite::state::options<
	StateChoices
>::options(
	sge::sprite::state::vertex_options const _vertex_options
)
:
	vertex_options_(
		_vertex_options
	),
	elements_(
		sge::sprite::state::detail::init_options<
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
	return
		this->set<
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
	return
		this->set<
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
	return
		this->set<
			sge::sprite::state::roles::transform
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
>::fixed_projection(
	sge::sprite::projection_dim const _projection
)
{
	return
		this->set<
			sge::sprite::state::roles::projection_dim
		>(
			sge::sprite::optional_projection_dim(
				_projection
			)
		);
}

template<
	typename StateChoices
>
sge::sprite::state::vertex_options
sge::sprite::state::options<
	StateChoices
>::vertex_options() const
{
	return
		vertex_options_;
}

template<
	typename StateChoices
>
template<
	typename Role
>
sge::sprite::state::options<
	StateChoices
> &
sge::sprite::state::options<
	StateChoices
>::set(
	majutsu::role_return_type<
		elements_type,
		Role
	> _state
)
{
	majutsu::set<
		Role
	>(
		elements_,
		_state
	);

	return
		*this;
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
	return
		elements_;
}

#endif
