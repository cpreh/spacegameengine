//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_INPUT_CURSOR_SCROLL_CODE_TO_STRING_HPP_INCLUDED
#define SGE_INPUT_CURSOR_SCROLL_CODE_TO_STRING_HPP_INCLUDED

#include <sge/input/cursor/scroll_code_fwd.hpp>
#include <sge/input/detail/symbol.hpp>
#include <fcppt/string.hpp>

namespace sge::input::cursor
{

SGE_INPUT_DETAIL_SYMBOL
fcppt::string scroll_code_to_string(sge::input::cursor::scroll_code);

}

#endif
