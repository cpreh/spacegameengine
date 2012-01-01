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


#ifndef MAJUTSU_FUNDAMENTAL_HPP_INCLUDED
#define MAJUTSU_FUNDAMENTAL_HPP_INCLUDED

#include <majutsu/const_raw_pointer.hpp>
#include <majutsu/integral_size.hpp>
#include <majutsu/raw_pointer.hpp>
#include <majutsu/size_type.hpp>
#include <majutsu/concepts/static_size.hpp>
#include <majutsu/concepts/static_memory/tag.hpp>
#include <majutsu/detail/copy_n.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/static_assert.hpp>
#include <boost/type_traits/is_fundamental.hpp>
#include <fcppt/config/external_end.hpp>


namespace majutsu
{

template<
	typename T
>
struct fundamental
{
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
	Type const &_value,
	raw_pointer const _memory
)
{
	detail::copy_n(
		reinterpret_cast<
			const_raw_pointer
		>(
			&_value
		),
		concepts::static_size<
			fundamental<
				Type
			>
		>::value,
		_memory
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
	const_raw_pointer const _memory
)
{
	Type ret;

	detail::copy_n(
		_memory,
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
