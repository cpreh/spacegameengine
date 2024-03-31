//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/dinput/di.hpp>
#include <sge/dinput/device/add_element.hpp>
#include <sge/dinput/device/enumerator.hpp>
#include <sge/dinput/device/get_property_dword.hpp>
#include <sge/dinput/joypad/absolute_axis_map.hpp>
#include <sge/dinput/joypad/button_map.hpp>
#include <sge/dinput/joypad/enumerator.hpp>
#include <sge/dinput/joypad/is_axis.hpp>
#include <sge/dinput/joypad/make_absolute_axis_info.hpp>
#include <sge/dinput/joypad/make_button_info.hpp>
#include <sge/dinput/joypad/make_relative_axis_info.hpp>
#include <sge/dinput/joypad/relative_axis_map.hpp>
#include <sge/input/exception.hpp>
#include <sge/input/joypad/absolute_axis_info.hpp>
#include <sge/input/joypad/absolute_axis_info_container.hpp>
#include <sge/input/joypad/button_info.hpp>
#include <sge/input/joypad/button_info_container.hpp>
#include <sge/input/joypad/relative_axis_info.hpp>
#include <sge/input/joypad/relative_axis_info_container.hpp>
#include <fcppt/text.hpp>
#include <fcppt/preprocessor/disable_gcc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>
#include <fcppt/config/external_begin.hpp>
#include <functional>
#include <fcppt/config/external_end.hpp>

sge::dinput::joypad::enumerator::enumerator(IDirectInputDevice8 &_device)
    : sge::dinput::device::enumerator(),
      device_(_device),
      absolute_axis_(),
      buttons_(),
      relative_axis_(),
      absolute_axis_map_(),
      button_map_(),
      relative_axis_map_()
{
}

sge::dinput::joypad::enumerator::~enumerator() {}

sge::input::joypad::absolute_axis_info_container::vector const &
sge::dinput::joypad::enumerator::absolute_axis() const
{
  return absolute_axis_;
}

sge::input::joypad::button_info_container::vector const &
sge::dinput::joypad::enumerator::buttons() const
{
  return buttons_;
}

sge::input::joypad::relative_axis_info_container::vector const &
sge::dinput::joypad::enumerator::relative_axis() const
{
  return relative_axis_;
}

sge::dinput::joypad::absolute_axis_map const &
sge::dinput::joypad::enumerator::absolute_axis_map() const
{
  return absolute_axis_map_;
}

sge::dinput::joypad::button_map const &sge::dinput::joypad::enumerator::button_map() const
{
  return button_map_;
}

sge::dinput::joypad::relative_axis_map const &
sge::dinput::joypad::enumerator::relative_axis_map() const
{
  return relative_axis_map_;
}

void sge::dinput::joypad::enumerator::dispatch(DIDEVICEOBJECTINSTANCE const &_data)
{
  if (sge::dinput::joypad::is_axis(_data.guidType))
  {
    FCPPT_PP_PUSH_WARNING
    FCPPT_PP_DISABLE_GCC_WARNING(-Wold-style-cast)
    switch (sge::dinput::device::get_property_dword(device_, _data, DIPROP_AXISMODE))
    {
    case DIPROPAXISMODE_ABS:
      sge::dinput::device::add_element(
          _data,
          absolute_axis_map_,
          absolute_axis_,
          std::bind(
              &sge::dinput::joypad::make_absolute_axis_info,
              std::ref(device_),
              std::placeholders::_1));
      break;
    case DIPROPAXISMODE_REL:
      sge::dinput::device::add_element(
          _data, relative_axis_map_, relative_axis_, &sge::dinput::joypad::make_relative_axis_info);
      break;
    default:
      throw sge::input::exception{FCPPT_TEXT("Invalid DIPROP_AXISMODE!")};
    }
    FCPPT_PP_POP_WARNING
  }
  else if (_data.guidType == GUID_Button)
    sge::dinput::device::add_element(
        _data, button_map_, buttons_, &sge::dinput::joypad::make_button_info);
}
