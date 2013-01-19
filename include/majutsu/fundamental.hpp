/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2013 Carl Philipp Reh (sefi@s-e-f-i.de)

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
#include <fcppt/preprocessor/disable_gcc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>
#include <fcppt/config/external_begin.hpp>
#include <type_traits>
#include <fcppt/config/external_end.hpp>


namespace majutsu
{

template<
	typename T
>
struct fundamental
{
	typedef T type;


	static_assert(
		std::is_fundamental<
			T
		>::value,
		"T must be fundamental"
	);
};

namespace concepts
{

FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_GCC_WARNING(-Weffc++)

template<
	typename T
>
struct static_size<
	majutsu::fundamental<
		T
	>
>
:
majutsu::integral_size<
	sizeof(T)
>
{
};

FCPPT_PP_POP_WARNING

}

template<
	typename Type
>
void
place(
	majutsu::concepts::static_memory::tag const *,
	majutsu::fundamental<
		Type
	> const *,
	Type const &_value,
	majutsu::raw_pointer const _memory
)
{
	majutsu::detail::copy_n(
		reinterpret_cast<
			majutsu::const_raw_pointer
		>(
			&_value
		),
		majutsu::concepts::static_size<
			majutsu::fundamental<
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
	majutsu::concepts::static_memory::tag const *,
	majutsu::fundamental<
		Type
	> const *,
	majutsu::const_raw_pointer const _memory
)
{
	Type ret;

	majutsu::detail::copy_n(
		_memory,
		majutsu::concepts::static_size<
			majutsu::fundamental<
				Type
			>
		>::value,
		reinterpret_cast<
			majutsu::raw_pointer
		>(
			&ret
		)
	);

	return ret;
}

}

#endif
