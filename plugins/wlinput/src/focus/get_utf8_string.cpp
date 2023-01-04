//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/charconv/utf8_string.hpp>
#include <sge/input/exception.hpp>
#include <sge/wlinput/focus/get_utf8_string.hpp>
#include <sge/wlinput/focus/state.hpp>
#include <sge/wlinput/focus/xkb_keycode.hpp>
#include <fcppt/text.hpp>
#include <fcppt/cast/to_unsigned.hpp>
#include <fcppt/container/dynamic_array_impl.hpp>

sge::charconv::utf8_string sge::wlinput::focus::get_utf8_string(
    sge::wlinput::focus::state const &_state, sge::wlinput::focus::xkb_keycode const _keycode)
{
  int const size{::xkb_state_key_get_utf8(_state.get(), _keycode.get(), nullptr, 0)};

  if(size < 0)
  {
    throw sge::input::exception{FCPPT_TEXT("wlinput xkb utf8 size < 0!")};
  }

  fcppt::container::dynamic_array<char> buffer(fcppt::cast::to_unsigned(size) + 1U);

  if (::xkb_state_key_get_utf8(_state.get(), _keycode.get(), buffer.data(), buffer.size()) != size)
  {
    throw sge::input::exception{FCPPT_TEXT("wlinput xkf utf8 size inconsistent!")};
  }

  return sge::charconv::utf8_string{buffer.data()};
}
