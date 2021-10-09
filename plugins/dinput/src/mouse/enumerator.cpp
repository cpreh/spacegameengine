//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/dinput/di.hpp>
#include <sge/dinput/device/add_element.hpp>
#include <sge/dinput/device/enumerator.hpp>
#include <sge/dinput/mouse/axis_map.hpp>
#include <sge/dinput/mouse/button_map.hpp>
#include <sge/dinput/mouse/enumerator.hpp>
#include <sge/dinput/mouse/is_axis.hpp>
#include <sge/dinput/mouse/make_axis_info.hpp>
#include <sge/dinput/mouse/make_button_info.hpp>
#include <sge/input/mouse/axis_info.hpp>
#include <sge/input/mouse/axis_info_container.hpp>
#include <sge/input/mouse/button_info.hpp>
#include <sge/input/mouse/button_info_container.hpp>

sge::dinput::mouse::enumerator::enumerator()
    : sge::dinput::device::enumerator(), axis_(), buttons_(), axis_map_(), button_map_()
{
}

sge::dinput::mouse::enumerator::~enumerator() {}

sge::input::mouse::axis_info_container::vector const &sge::dinput::mouse::enumerator::axis() const
{
  return axis_;
}

sge::input::mouse::button_info_container::vector const &
sge::dinput::mouse::enumerator::buttons() const
{
  return buttons_;
}

sge::dinput::mouse::axis_map const &sge::dinput::mouse::enumerator::axis_map() const
{
  return axis_map_;
}

sge::dinput::mouse::button_map const &sge::dinput::mouse::enumerator::button_map() const
{
  return button_map_;
}

void sge::dinput::mouse::enumerator::dispatch(DIDEVICEOBJECTINSTANCE const &_data)
{
  if (sge::dinput::mouse::is_axis(_data.guidType))
    sge::dinput::device::add_element(_data, axis_map_, axis_, &sge::dinput::mouse::make_axis_info);
  else if (_data.guidType == GUID_Button)
    sge::dinput::device::add_element(
        _data, button_map_, buttons_, &sge::dinput::mouse::make_button_info);
}
