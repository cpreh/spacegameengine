//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/input/cursor/optional_position.hpp>
#include <sge/input/cursor/position.hpp>
#include <sge/input/cursor/position_unit.hpp>
#include <sge/x11input/cursor/query_pointer.hpp>
#include <sge/x11input/device/id.hpp>
#include <awl/backends/x11/deleter.hpp>
#include <awl/backends/x11/display.hpp> // NOLINT(misc-include-cleaner)
#include <awl/backends/x11/window/base.hpp>
#include <fcppt/unique_ptr_impl.hpp>
#include <fcppt/cast/float_to_int.hpp>
#include <fcppt/config/external_begin.hpp>
#include <X11/X.h>
#include <X11/Xlib.h>
#include <X11/extensions/XInput2.h>
#include <fcppt/config/external_end.hpp>

sge::input::cursor::optional_position sge::x11input::cursor::query_pointer(
    awl::backends::x11::window::base const &_window, sge::x11input::device::id const &_id)
{
  Window root_return{};
  Window child_return{};

  double root_x_return{};
  double root_y_return{};
  double win_x_return{};
  double win_y_return{};

  XIButtonState buttons_return{};

  XIModifierState modifiers_return{};

  XIGroupState group_return{};

  if (::XIQueryPointer(
          _window.display().get().get(),
          _id.get(),
          _window.get(),
          &root_return,
          &child_return,
          &root_x_return,
          &root_y_return,
          &win_x_return,
          &win_y_return,
          &buttons_return,
          &modifiers_return,
          &group_return) == False)
  {
    return sge::input::cursor::optional_position();
  }

  using scoped_mask = fcppt::unique_ptr<unsigned char, awl::backends::x11::deleter>;

  scoped_mask const scoped_buttons_mask(buttons_return.mask);

  return sge::input::cursor::optional_position(sge::input::cursor::position(
      fcppt::cast::float_to_int<sge::input::cursor::position_unit>(win_x_return),
      fcppt::cast::float_to_int<sge::input::cursor::position_unit>(win_y_return)));
}
