//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/dinput/di.hpp>
#include <sge/dinput/device/element_name.hpp>
#include <sge/dinput/mouse/axis_code.hpp>
#include <sge/dinput/mouse/make_axis_info.hpp>
#include <sge/input/mouse/axis_info.hpp>
#include <fcppt/optional_string.hpp>

sge::input::mouse::axis_info sge::dinput::mouse::make_axis_info(DIDEVICEOBJECTINSTANCE const &_data)
{
  return sge::input::mouse::axis_info(
      sge::dinput::mouse::axis_code(_data.dwOfs), sge::dinput::device::element_name(_data));
}
