/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2010 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#ifndef MAJUTSU_FUNDAMENTAL_HPP_INCLUDED
#define MAJUTSU_FUNDAMENTAL_HPP_INCLUDED

#include <majutsu/detail/copy_n.hpp>
#include <majutsu/concepts/static_memory/tag.hpp>
#include <majutsu/concepts/static_size.hpp>
#include <majutsu/size_type.hpp>
#include <majutsu/raw_pointer.hpp>
#include <majutsu/integral_size.hpp>
#include <boost/type_traits/is_fundamental.hpp>
#include <boost/static_assert.hpp>

namespace majutsu
{

template<
	typename T
>
struct fundamental {
	typedef T type;

	BOOST_STATIC_ASSERT(
		boost::is_fundamental<T>::value
	);
};

namespace concepts
{

template<
	typename T
>
struct static_size<
	majutsu::fundamental<
		T
	>
>
:
integral_size<
	sizeof(T)
>
{};

}

template<
	typename Type
>
void
place(
	concepts::static_memory::tag const *,
	fundamental<
		Type
	> const *,
	Type const &value_,
	raw_pointer const memory_
)
{
	detail::copy_n(
		reinterpret_cast<
			const_raw_pointer
		>(
			&value_
		),
		concepts::static_size<
			fundamental<
				Type
			>
		>::value,
		memory_
	);
}

template<
	typename Type
>
Type
make(
	concepts::static_memory::tag const *,
	fundamental<
		Type
	> const *,
	const_raw_pointer const memory_
)
{
	Type ret;

	detail::copy_n(
		memory_,
		concepts::static_size<
			fundamental<
				Type
			>
		>::value,
		reinterpret_cast<
			raw_pointer
		>(
			&ret
		)
	);

	return ret;
}

}

#endif
