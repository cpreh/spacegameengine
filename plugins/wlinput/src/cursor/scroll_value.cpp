//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/input/cursor/scroll_value.hpp>
#include <sge/wlinput/cursor/scroll_value.hpp>
#include <fcppt/config/external_begin.hpp>
#include <cstdint>
#include <fcppt/config/external_end.hpp>

sge::input::cursor::scroll_value sge::wlinput::cursor::scroll_value(std::int32_t const _value)
{
  return sge::input::cursor::scroll_value{_value};
}
