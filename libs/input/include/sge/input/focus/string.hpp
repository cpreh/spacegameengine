//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_INPUT_FOCUS_STRING_HPP_INCLUDED
#define SGE_INPUT_FOCUS_STRING_HPP_INCLUDED

#include <sge/input/focus/char_type.hpp>
#include <fcppt/config/external_begin.hpp>
#include <string>
#include <fcppt/config/external_end.hpp>

namespace sge::input::focus
{

using string = std::basic_string<sge::input::focus::char_type>;

}

#endif
