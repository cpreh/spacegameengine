//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/input/cursor/scroll_code.hpp>
#include <sge/input/cursor/scroll_code_to_string.hpp>
#include <fcppt/string.hpp>
#include <fcppt/assert/unreachable.hpp>

fcppt::string sge::input::cursor::scroll_code_to_string(sge::input::cursor::scroll_code const _code)
{
#define MAKE_CASE(name) \
  case sge::input::cursor::scroll_code::name: \
    return FCPPT_TEXT(#name);

  switch (_code)
  {
    MAKE_CASE(vertical)
    MAKE_CASE(horizontal)
  }

  FCPPT_ASSERT_UNREACHABLE;
}
