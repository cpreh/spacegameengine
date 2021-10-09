//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/wlinput/focus/get_keysym.hpp>
#include <sge/wlinput/focus/state.hpp>
#include <sge/wlinput/focus/xkb_keycode.hpp>
#include <sge/wlinput/focus/xkb_keysym.hpp>
#include <fcppt/config/external_begin.hpp>
#include <xkbcommon/xkbcommon.h>
#include <fcppt/config/external_end.hpp>

sge::wlinput::focus::xkb_keysym sge::wlinput::focus::get_keysym(
    sge::wlinput::focus::state const &_state, sge::wlinput::focus::xkb_keycode const _code)
{
  return sge::wlinput::focus::xkb_keysym{::xkb_state_key_get_one_sym(_state.get(), _code.get())};
}
