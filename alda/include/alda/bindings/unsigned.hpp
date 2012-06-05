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


#ifndef ALDA_BINDINGS_UNSIGNED_HPP_INCLUDED
#define ALDA_BINDINGS_UNSIGNED_HPP_INCLUDED

#include <alda/endianness.hpp>
#include <majutsu/const_raw_pointer.hpp>
#include <majutsu/fundamental.hpp>
#include <majutsu/raw_pointer.hpp>
#include <majutsu/concepts/static_size.hpp>
#include <majutsu/concepts/dynamic_memory/tag.hpp>
#include <fcppt/null_ptr.hpp>
#include <fcppt/static_assert_statement.hpp>
#include <fcppt/endianness/convert.hpp>
#include <fcppt/preprocessor/disable_gcc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/type_traits/is_unsigned.hpp>
#include <fcppt/config/external_end.hpp>


namespace alda
{
namespace bindings
{

FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_GCC_WARNING(-Weffc++)

template<
	typename Type
>
struct unsigned_
:
majutsu::fundamental<
	Type
>
{
	FCPPT_STATIC_ASSERT_STATEMENT(
		boost::is_unsigned<
			Type
		>::value
	);
};

FCPPT_PP_POP_WARNING

template<
	typename Type
>
void
place(
	majutsu::concepts::dynamic_memory::tag const *const _tag,
	alda::bindings::unsigned_<
		Type
	> const *,
	Type const &_type,
	majutsu::raw_pointer const _mem
)
{
	place(
		_tag,
		static_cast<
			majutsu::fundamental<
				Type
			> const *
		>(
			fcppt::null_ptr()
		),
		fcppt::endianness::convert(
			_type,
			alda::endianness()
		),
		_mem
	);
}

template<
	typename Type
>
Type
make(
	majutsu::concepts::dynamic_memory::tag const *const _tag,
	alda::bindings::unsigned_<
		Type
	> const *,
	majutsu::const_raw_pointer const _beg
)
{
	return
		fcppt::endianness::convert(
			make(
				_tag,
				static_cast<
					majutsu::fundamental<
						Type
					> const *
				>(
					fcppt::null_ptr()
				),
				_beg
			),
			alda::endianness()
		);
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
	typename Type
>
struct static_size<
	alda::bindings::unsigned_<
		Type
	>
>
:
majutsu::concepts::static_size<
	majutsu::fundamental<
		Type
	>
>
{
};

FCPPT_PP_POP_WARNING

}
}

#endif
