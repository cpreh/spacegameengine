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


#include <alda/bindings/float.hpp>
#include <alda/message/make_class.hpp>
#include <majutsu/composite.hpp>
#include <majutsu/role.hpp>
#include <fcppt/preprocessor/disable_gcc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/mpl/vector/vector10.hpp>
#include <boost/test/unit_test.hpp>
#include <algorithm>
#include <cmath>
#include <iostream>
#include <ostream>
#include <fcppt/config/external_end.hpp>


namespace
{

typedef alda::message::make_class<
	majutsu::composite<
		boost::mpl::vector1<
			majutsu::role<
				alda::bindings::float_
			>
		>
	>
>::type message;

void
fuzzy_equal(
	alda::bindings::float_::type const _val1,
	alda::bindings::float_::type const _val2
)
{
	BOOST_CHECK(
		(_val1 < 0)
		==
		(_val2 < 0)
	);

	BOOST_CHECK((
		(
			std::abs(
				_val1
				-
				_val2
			)
			/
			std::max(
				std::abs(
					_val1
				),
				std::abs(
					_val2
				)
			)
		)
		< 0.0001f
	));
}

void
test_conversion(
	alda::bindings::float_::type const _value
)
{
	std::cout
		<< "Testing: "
		<< _value
		<< '\n';

	message const msg(
		_value
	);

	fuzzy_equal(
		msg.get<
			alda::bindings::float_
		>(),
		_value
	);
}

}

FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_GCC_WARNING(-Weffc++)

BOOST_AUTO_TEST_CASE(
	alda_float
)
{
FCPPT_PP_POP_WARNING

	test_conversion(
		-1.f
	);

	test_conversion(
		1.f
	);
}
