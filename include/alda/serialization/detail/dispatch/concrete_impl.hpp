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


#ifndef ALDA_SERIALIZATION_DETAIL_DISPATCH_CONCRETE_IMPL_HPP_INCLUDED
#define ALDA_SERIALIZATION_DETAIL_DISPATCH_CONCRETE_IMPL_HPP_INCLUDED

#include <alda/serialization/detail/dispatch/concrete_decl.hpp>
#include <alda/serialization/detail/read/object_decl.hpp>


template<
	typename TypeEnum,
	typename Message
>
alda::serialization::detail::dispatch::concrete<
	TypeEnum,
	Message
>::concrete()
{
}

template<
	typename TypeEnum,
	typename Message
>
alda::serialization::detail::dispatch::concrete<
	TypeEnum,
	Message
>::~concrete()
{
}

template<
	typename TypeEnum,
	typename Message
>
typename alda::serialization::detail::dispatch::concrete<
	TypeEnum,
	Message
>::message_unique_ptr
alda::serialization::detail::dispatch::concrete<
	TypeEnum,
	Message
>::on_dispatch(
	reader const &_reader
) const
{
	return
		_reader. template operator()<
			Message
		>();
}

#endif
