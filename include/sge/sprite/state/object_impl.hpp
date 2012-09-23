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


#ifndef SGE_SPRITE_STATE_OBJECT_IMPL_HPP_INCLUDED
#define SGE_SPRITE_STATE_OBJECT_IMPL_HPP_INCLUDED

#include <sge/sprite/state/object_decl.hpp>
#include <sge/sprite/state/parameters_impl.hpp>
#include <sge/sprite/state/detail/make_objects.hpp>
#include <sge/sprite/state/detail/make_viewport_manager.hpp>
#include <sge/sprite/state/detail/viewport_manager_impl.hpp>


template<
	typename StateChoices
>
sge::sprite::state::object<
	StateChoices
>::object(
	render_device &_device,
	parameters_type const &_parameters
)
:
	elements_(
		sge::sprite::state::detail::make_objects<
			StateChoices
		>(
			_device,
			_parameters.elements()
		)
	),
	viewport_manager_(
		sge::sprite::state::detail::make_viewport_manager<
			StateChoices
		>(
			elements_,
			_device,
			_parameters
		)
	)
{
}

template<
	typename StateChoices
>
sge::sprite::state::object<
	StateChoices
>::~object()
{
}

template<
	typename StateChoices
>
typename
sge::sprite::state::object<
	StateChoices
>::elements_type const &
sge::sprite::state::object<
	StateChoices
>::elements() const
{
	return elements_;
}

#endif
