//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/evdev/device/fd.hpp>
#include <sge/evdev/joypad/absolute_axis/code.hpp>
#include <sge/evdev/joypad/absolute_axis/make_code.hpp>
#include <sge/evdev/joypad/absolute_axis/make_info.hpp>
#include <sge/evdev/joypad/absolute_axis/make_string.hpp>
#include <sge/input/exception.hpp>
#include <sge/input/joypad/absolute_axis_info.hpp>
#include <sge/input/joypad/axis_max.hpp>
#include <sge/input/joypad/axis_min.hpp>
#include <fcppt/optional_string.hpp>
#include <fcppt/text.hpp>
#include <fcppt/cast/enum_to_int.hpp>
#include <fcppt/config/external_begin.hpp>
#include <linux/input.h>
#include <sys/ioctl.h>
#include <fcppt/config/external_end.hpp>

sge::input::joypad::absolute_axis_info sge::evdev::joypad::absolute_axis::make_info(
    sge::evdev::device::fd &_fd, sge::evdev::joypad::absolute_axis::code const _event)
{
  input_absinfo ret{};

  if (::ioctl( // NOLINT(cppcoreguidelines-pro-type-vararg,hicpp-vararg)
          _fd.get().get(),
          EVIOCGABS( // NOLINT(hicpp-signed-bitwise)
              fcppt::cast::enum_to_int<unsigned>(_event)),
          &ret) == -1)
  {
    throw sge::input::exception(FCPPT_TEXT("ioctl for abs info failed!"));
  }

  return sge::input::joypad::absolute_axis_info(
      sge::evdev::joypad::absolute_axis::make_code(_event),
      sge::evdev::joypad::absolute_axis::make_string(_event),
      sge::input::joypad::axis_min(ret.minimum),
      sge::input::joypad::axis_max(ret.maximum));
}
