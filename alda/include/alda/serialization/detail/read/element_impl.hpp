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


#ifndef ALDA_SERIALIZATION_DETAIL_READ_ELEMENT_IMPL_HPP_INCLUDED
#define ALDA_SERIALIZATION_DETAIL_READ_ELEMENT_IMPL_HPP_INCLUDED

#include <alda/serialization/istream.hpp>
#include <alda/serialization/detail/read/element_decl.hpp>
#include <alda/serialization/detail/read/load.hpp>
#include <majutsu/access_role.hpp>


template<
	typename Class
>
alda::serialization::detail::read::element<
	Class
>::element(
	alda::serialization::istream &_stream,
	Class &_object
)
:
	stream_(
		_stream
	),
	object_(
		_object
	)
{
}

template<
	typename Class
>
template<
	typename Role
>
void
alda::serialization::detail::read::element<
	Class
>::operator()(
	Role &
) const
{
	object_. template set<
		typename Role::alias
	>(
		alda::serialization::detail::read::load<
			typename majutsu::access_role<
				Role
			>::type
		>::get(
			stream_
		)
	);
}

#endif
