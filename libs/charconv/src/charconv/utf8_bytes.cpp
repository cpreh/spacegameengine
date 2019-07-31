//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/charconv/exception.hpp>
#include <sge/charconv/utf8_bytes.hpp>
#include <sge/charconv/utf8_char.hpp>
#include <fcppt/text.hpp>
#include <fcppt/assert/unreachable.hpp>


unsigned
sge::charconv::utf8_bytes(
	sge::charconv::utf8_char const _ch
)
{
	if(
		(_ch & 0x80)
		==
		0
	)
		return
			1u;

	if(
		(_ch & 0xE0)
		==
		0xC0
	)
		return
			2u;

	if(
		(_ch & 0xF0)
		==
		0xE0
	)
		return
			3u;

	if(
		(_ch & 0xF8)
		==
		0xF0
	)
		return
			4u;

	throw
		sge::charconv::exception{
			FCPPT_TEXT("Invalid UTF-8 byte")
		};
}
