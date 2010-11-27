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


#include <sge/iconv/convert.hpp>
#include <sge/iconv/encoding.hpp>
#include <sge/iconv/string_type.hpp>
#include <boost/test/unit_test.hpp>
#include <string>
#include <iostream>
#include <ostream>

BOOST_AUTO_TEST_CASE(iconv_main)
{
	// TODO: adapt this to different platforms
	std::string const test(
		"馬鹿"
	);

	typedef sge::iconv::string_type<
		sge::iconv::encoding::utf8
	>::type utf8_string;

	utf8_string const utf8_test(
		test.begin(),
		test.end()
	);

	typedef sge::iconv::string_type<
		sge::iconv::encoding::utf32
	>::type utf32_string;

	utf32_string const utf32_test(
		sge::iconv::convert<
			sge::iconv::encoding::utf32,
			sge::iconv::encoding::utf8
		>(
			utf8_test
		)
	);

	std::wstring const out(
		utf32_test.begin(),
		utf32_test.end()
	);

	// TODO: what to do about the BOM?
	BOOST_REQUIRE(
		out == L"馬鹿"
	);
}
