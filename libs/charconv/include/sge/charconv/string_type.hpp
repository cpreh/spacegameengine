//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_CHARCONV_STRING_TYPE_HPP_INCLUDED
#define SGE_CHARCONV_STRING_TYPE_HPP_INCLUDED

#include <sge/charconv/char_type.hpp>
#include <sge/charconv/encoding.hpp>
#include <fcppt/config/external_begin.hpp>
#include <string>
#include <fcppt/config/external_end.hpp>


namespace sge::charconv
{

template<
	sge::charconv::encoding Encoding
>
using
string_type
=
std::basic_string<
	sge::charconv::char_type<
		Encoding
	>
>;

}

#endif
