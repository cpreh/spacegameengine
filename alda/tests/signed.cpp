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


#include <alda/exception.hpp>
#include <alda/bindings/fundamental.hpp>
#include <alda/message/make_class.hpp>
#include <majutsu/composite.hpp>
#include <majutsu/role.hpp>
#include <fcppt/preprocessor/disable_gcc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/cstdint.hpp>
#include <boost/mpl/vector/vector10.hpp>
#include <boost/test/unit_test.hpp>
#include <limits>
#include <fcppt/config/external_end.hpp>


namespace
{

typedef boost::uint16_t int_type;

typedef alda::bindings::fundamental<
	int_type
> int_alda_type;

typedef alda::message::make_class<
	majutsu::composite<
		boost::mpl::vector1<
			majutsu::role<
				int_alda_type
			>
		>
	>
>::type message;

bool
check_exception(
	alda::exception const &
)
{
	return true;
}

void
test_conversion(
	int_type const _value
)
{
	message const msg(
		_value
	);

	BOOST_CHECK(
		msg.get<
			int_alda_type
		>()
		==
		_value
	);
}

}

FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_GCC_WARNING(-Weffc++)

BOOST_AUTO_TEST_CASE(
	alda_signed
)
{
FCPPT_PP_POP_WARNING

	test_conversion(
		static_cast<
			int_type
		>(
			0
		)
	);

	test_conversion(
		static_cast<
			int_type
		>(
			1337
		)
	);

	test_conversion(
		static_cast<
			int_type
		>(
			-1337
		)
	);

	int_type const max(
		std::numeric_limits<
			int_type
		>::max()
	);

	int_type const min(
		std::numeric_limits<
			int_type
		>::min()
	);

	test_conversion(
		max
	);

	test_conversion(
		static_cast<
			int_type
		>(
			-max
		)
	);

	if(
		min
		+
		max
		<
		0
	)
		BOOST_CHECK_EXCEPTION(
			test_conversion(
				min
			),
			alda::exception,
			::check_exception
		);
}
