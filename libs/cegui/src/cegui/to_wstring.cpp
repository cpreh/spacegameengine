//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/cegui/to_wstring.hpp>
#include <sge/charconv/convert.hpp>
#include <sge/charconv/encoding.hpp>
#include <sge/charconv/string_type.hpp>
#include <fcppt/config/external_begin.hpp>
#include <CEGUI/Base.h>
#include <CEGUI/String.h>
#include <string>
#include <fcppt/config/external_end.hpp>


std::wstring
sge::cegui::to_wstring(
	CEGUI::String const &_string
)
{
	typedef
	sge::charconv::string_type<
		sge::charconv::encoding::utf32
	>
	source_string;

	static_assert(
		sizeof(
			source_string::value_type
		)
		==
		sizeof(
			CEGUI::utf32
		),
		"CEGUI's string must use utf32"
	);

	return
		sge::charconv::convert<
			sge::charconv::encoding::wchar,
			sge::charconv::encoding::utf32
		>(
			source_string(
				_string.begin(),
				_string.end()
			)
		);
}
