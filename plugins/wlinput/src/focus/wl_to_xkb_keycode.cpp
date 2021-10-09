//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/wlinput/focus/wl_to_xkb_keycode.hpp>
#include <sge/wlinput/focus/xkb_keycode.hpp>
#include <fcppt/config/external_begin.hpp>
#include <cstdint>
#include <fcppt/config/external_end.hpp>

sge::wlinput::focus::xkb_keycode sge::wlinput::focus::wl_to_xkb_keycode(std::uint32_t const _key)
{
  return sge::wlinput::focus::xkb_keycode{
      _key + 8U // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
  };
}
