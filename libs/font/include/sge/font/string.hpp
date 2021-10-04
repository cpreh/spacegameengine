//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_FONT_STRING_HPP_INCLUDED
#define SGE_FONT_STRING_HPP_INCLUDED

#include <sge/font/char_type.hpp>
#include <fcppt/config/external_begin.hpp>
#include <string>
#include <fcppt/config/external_end.hpp>


namespace sge::font
{

using
string
=
std::basic_string<
	sge::font::char_type
>;

}

#endif
