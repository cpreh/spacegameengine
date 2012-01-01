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


#ifndef MAJUTSU_CONSTANT_HPP_INCLUDED
#define MAJUTSU_CONSTANT_HPP_INCLUDED

#include <majutsu/concepts/static_size.hpp>

namespace majutsu
{

template<
	typename T,
	typename T::type Value
>
struct constant
:
T
{
	static typename T::type const value = Value;
};

template<
	typename T,
	typename T::type Value
>
typename T::type const
constant<T, Value>::value;


namespace concepts
{

template<
	typename T,
	typename T::type Value
>
struct static_size<
	majutsu::constant<
		T,
		Value
	>
>
:
static_size<
	T
>
{};

}
}

#endif
