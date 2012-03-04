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


#ifndef ALDA_MESSAGE_IMPL_CONCRETE_IMPL_HPP_INCLUDED
#define ALDA_MESSAGE_IMPL_CONCRETE_IMPL_HPP_INCLUDED

#include <alda/message/concrete_decl.hpp>
#include <alda/message/detail/extract_id.hpp>


template<
	typename TypeEnum,
	typename Type
>
alda::message::concrete<
	TypeEnum,
	Type
>::concrete(
	Type const &_value
)
:
	base_type(),
	value_(
		_value
	)
{
}

template<
	typename TypeEnum,
	typename Type
>
alda::message::concrete<
	TypeEnum,
	Type
>::~concrete()
{
}

template<
	typename TypeEnum,
	typename Type
>
Type const &
alda::message::concrete<
	TypeEnum,
	Type
>::value() const
{
	return value_;
}

template<
	typename TypeEnum,
	typename Type
>
typename alda::message::concrete<
	TypeEnum,
	Type
>::type_enum
alda::message::concrete<
	TypeEnum,
	Type
>::type() const
{
	return
		static_cast<
			type_enum
		>(
			alda::message::detail::extract_id<
				typename Type::types
			>::type::value
		);
}

template<
	typename TypeEnum,
	typename Type
>
typename alda::message::concrete<
	TypeEnum,
	Type
>::const_raw_pointer
alda::message::concrete<
	TypeEnum,
	Type
>::data() const
{
	return
		value_.memory().data();
}

template<
	typename TypeEnum,
	typename Type
>
typename alda::message::concrete<
	TypeEnum,
	Type
>::size_type
alda::message::concrete<
	TypeEnum,
	Type
>::size() const
{
	return
		value_.memory().size();
}

#endif
