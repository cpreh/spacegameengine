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


#ifndef SGE_SPRITE_STATE_PARAMETERS_IMPL_HPP_INCLUDED
#define SGE_SPRITE_STATE_PARAMETERS_IMPL_HPP_INCLUDED

#include <sge/sprite/state/parameters_decl.hpp>
#include <sge/sprite/state/roles/blend_write_mask.hpp>
#include <sge/sprite/state/roles/enable_scissor_test.hpp>
#include <majutsu/role_return_type.hpp>
#include <fcppt/no_init.hpp>
#include <fcppt/optional_impl.hpp>


template<
	typename StateChoices
>
sge::sprite::state::parameters<
	StateChoices
>::parameters()
:
	elements_(
		fcppt::no_init()
	)
{
}

template<
	typename StateChoices
>
sge::sprite::state::parameters<
	StateChoices
> &
sge::sprite::state::parameters<
	StateChoices
>::blend_write_mask(
	typename majutsu::role_return_type<
		flattened_types,
		sge::sprite::state::roles::blend_write_mask
	>::type const &_blend_write_mask
)
{
	return
		this->set<
			sge::sprite::state::roles::blend_write_mask
		>(
			_blend_write_mask
		);
}

template<
	typename StateChoices
>
sge::sprite::state::parameters<
	StateChoices
> &
sge::sprite::state::parameters<
	StateChoices
>::enable_scissor_test(
	typename majutsu::role_return_type<
		flattened_types,
		sge::sprite::state::roles::enable_scissor_test
	>::type const &_enable_scissor_test
)
{
	return
		this->set<
			sge::sprite::state::roles::enable_scissor_test
		>(
			_enable_scissor_test
		);
}

template<
	typename StateChoices
>
template<
	typename Role
>
sge::sprite::state::parameters<
	StateChoices
> &
sge::sprite::state::parameters<
	StateChoices
>::set(
	typename majutsu::role_return_type<
		flattened_types,
		Role
	>::type const &_value
)
{
	return
		elements_. template set<
			Role
		>(
			fcppt::optional<
				typename majutsu::role_return_type<
					flattened_types,
					Role
				>::type
			>(
				_value
			)
		);
}

template<
	typename StateChoices
>
typename
sge::sprite::state::parameters<
	StateChoices
>::elements_type const &
sge::sprite::state::parameters<
	StateChoices
>::elements() const
{
	return elements_;
}

#endif
