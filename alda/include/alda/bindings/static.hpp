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


#ifndef ALDA_BINDINGS_STATIC_HPP_INCLUDED
#define ALDA_BINDINGS_STATIC_HPP_INCLUDED

#include <majutsu/const_raw_pointer.hpp>
#include <majutsu/integral_size.hpp>
#include <majutsu/raw_pointer.hpp>
#include <majutsu/size_type.hpp>
#include <majutsu/concepts/static_size.hpp>
#include <majutsu/concepts/dynamic_memory/tag.hpp>
#include <fcppt/preprocessor/disable_gcc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>


namespace alda
{
namespace bindings
{

template<
	typename Type,
	typename Adapted
>
struct static_
{
	typedef Type type;
};

template<
	typename Type,
	typename Adapted
>
void
place(
	majutsu::concepts::dynamic_memory::tag const *const _tag,
	alda::bindings::static_<
		Type,
		Adapted
	> const *,
	Type const &_value,
	majutsu::raw_pointer _mem
)
{
	for(
		typename Type::const_iterator it(
			_value.begin()
		);
		it != _value.end();
		_mem +=
			needed_size(
				_tag,
				static_cast<
					Adapted const *
				>(0),
				*it
			),
		++it
	)
		place(
			_tag,
			static_cast<
				Adapted const *
			>(0),
			*it,
			_mem
		);
}

template<
	typename Type,
	typename Adapted
>
Type
make(
	majutsu::concepts::dynamic_memory::tag const *const _tag,
	alda::bindings::static_<
		Type,
		Adapted
	> const *,
	majutsu::const_raw_pointer _mem
)
{
	Type ret;

	for(
		typename Type::iterator it(
			ret.begin()
		);
		it != ret.end();
		_mem +=
			needed_size(
				_tag,
				static_cast<
					Adapted const *
				>(0),
				*it
			),
		++it
	)
		*it =
			make(
				_tag,
				static_cast<
					Adapted const *
				>(0),
				_mem
			);

	return ret;
}

}
}

namespace majutsu
{
namespace concepts
{

FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_GCC_WARNING(-Weffc++)

template<
	typename Type,
	typename Adapted
>
struct static_size<
	alda::bindings::static_<
		Type,
		Adapted
	>
>
:
majutsu::integral_size<
	Type::dim_wrapper::value
	* sizeof(typename Type::value_type)
>
{
};

FCPPT_PP_POP_WARNING

}
}

#endif
