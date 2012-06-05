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


#ifndef ALDA_BINDINGS_SIGNED_HPP_INCLUDED
#define ALDA_BINDINGS_SIGNED_HPP_INCLUDED

#include <alda/exception.hpp>
#include <alda/bindings/unsigned.hpp>
#include <majutsu/const_raw_pointer.hpp>
#include <majutsu/fundamental.hpp>
#include <majutsu/raw_pointer.hpp>
#include <majutsu/concepts/static_size.hpp>
#include <majutsu/concepts/dynamic_memory/tag.hpp>
#include <fcppt/null_ptr.hpp>
#include <fcppt/static_assert_statement.hpp>
#include <fcppt/text.hpp>
#include <fcppt/preprocessor/disable_gcc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>
#include <fcppt/config/external_begin.hpp>
#include <exception>
#include <limits>
#include <boost/type_traits/make_unsigned.hpp>
#include <boost/type_traits/is_signed.hpp>
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
struct signed_
:
majutsu::fundamental<
	Type
>
{
	FCPPT_STATIC_ASSERT_STATEMENT(
		boost::is_signed<
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
	alda::bindings::signed_<
		Type
	> const *,
	Type const &_value,
	majutsu::raw_pointer const _mem
)
{
	typedef typename boost::make_unsigned<
		Type
	>::type unsigned_type;

	Type const null(
		static_cast<
			Type
		>(
			0
		)
	);

	bool const is_negative(
		_value
		<
		null
	);

	Type const max(
		std::numeric_limits<
			Type
		>::max()
	);

	if(
		is_negative
		&&
		(
			_value + max
			<
			null
		)
	)
		throw alda::exception(
			FCPPT_TEXT("alda::bindings::signed has encountered a negative value")
			FCPPT_TEXT(" whose magnitude is larger than the largest positive value!")
		);

	unsigned_type const converted(
		is_negative
		?
			static_cast<
				unsigned_type
			>(
				-_value
			)
			+
			static_cast<
				unsigned_type
			>(
				max
			)
		:
			static_cast<
				unsigned_type
			>(
				_value
			)
	);

	place(
		_tag,
		static_cast<
			alda::bindings::unsigned_<
				unsigned_type
			> const *
		>(
			fcppt::null_ptr()
		),
		converted,
		_mem
	);
}

template<
	typename Type
>
Type
make(
	majutsu::concepts::dynamic_memory::tag const *const _tag,
	alda::bindings::signed_<
		Type
	> const *,
	majutsu::const_raw_pointer const _beg
)
{
	typedef typename boost::make_unsigned<
		Type
	>::type unsigned_type;


	unsigned_type const converted(
		make(
			_tag,
			static_cast<
				alda::bindings::unsigned_<
					unsigned_type
				> const *
			>(
				fcppt::null_ptr()
			),
			_beg
		)
	);

	Type const max(
		std::numeric_limits<
			Type
		>::max()
	);

	unsigned_type const converted_max(
		static_cast<
			unsigned_type
		>(
			max
		)
	);

	return
		converted
		>
		converted_max
		?
			-
			static_cast<
				Type
			>(
				converted - converted_max
			)
		:
			static_cast<
				Type
			>(
				converted
			)
		;
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
	alda::bindings::signed_<
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
