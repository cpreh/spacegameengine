//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/wininput/cursor/clip.hpp>
#include <sge/wininput/cursor/grab.hpp>
#include <sge/wininput/cursor/set_capture.hpp>
#include <sge/wininput/cursor/show.hpp>
#include <awl/backends/windows/optional_rect.hpp>
#include <awl/backends/windows/window/get_rect.hpp>
#include <awl/backends/windows/window/object_fwd.hpp>

bool sge::wininput::cursor::grab(awl::backends::windows::window::object &_window)
{
  sge::wininput::cursor::show(false);

  {
    // When can this fail?
    awl::backends::windows::optional_rect const window_rect(
        awl::backends::windows::window::get_rect(_window));

    if (!window_rect.has_value())
      return false;

    if (!sge::wininput::cursor::clip(window_rect))
      return false;
  }

  sge::wininput::cursor::set_capture(_window);

  return true;
}
