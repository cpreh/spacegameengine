//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_FONT_STRING_VIEW_HPP_INCLUDED
#define SGE_FONT_STRING_VIEW_HPP_INCLUDED

#include <sge/font/char_type.hpp>
#include <fcppt/config/external_begin.hpp>
#include <string_view>
#include <fcppt/config/external_end.hpp>

namespace sge::font
{

using string_view = std::basic_string_view<sge::font::char_type>;

}

#endif
