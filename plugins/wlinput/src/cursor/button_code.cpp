//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/input/cursor/button_code.hpp>
#include <sge/wlinput/cursor/button_code.hpp>
#include <fcppt/config/external_begin.hpp>
#include <cstdint>
#include <fcppt/config/external_end.hpp>

sge::input::cursor::button_code sge::wlinput::cursor::button_code(std::uint32_t const /*_button*/
)
{
  // TODO(philipp): How does this work?
  return sge::input::cursor::button_code::unknown;
}
