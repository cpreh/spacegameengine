//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/evdev/device/event.hpp>
#include <sge/evdev/joypad/absolute_axis/make_event.hpp>
#include <sge/input/joypad/absolute_axis.hpp>
#include <sge/input/joypad/absolute_axis_id.hpp>
#include <sge/input/joypad/absolute_axis_info.hpp>
#include <sge/input/joypad/absolute_axis_info_container.hpp>
#include <sge/input/joypad/shared_ptr.hpp>
#include <sge/input/joypad/event/absolute_axis.hpp>
#include <awl/event/base.hpp>
#include <awl/event/optional_base_unique_ptr.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/reference_impl.hpp>
#include <fcppt/unique_ptr_to_base.hpp>
#include <fcppt/optional/map.hpp>

awl::event::optional_base_unique_ptr sge::evdev::joypad::absolute_axis::make_event(
    sge::input::joypad::shared_ptr const &_joypad,
    sge::input::joypad::absolute_axis_id const _id,
    sge::input::joypad::absolute_axis_info_container const &_info,
    sge::evdev::device::event const _event)
{
  return fcppt::optional::map(
      _info[_id],
      [&_joypad, _id, &_event](
          fcppt::reference<sge::input::joypad::absolute_axis_info const> const &_axis_info)
      {
        return fcppt::unique_ptr_to_base<awl::event::base>(
            fcppt::make_unique_ptr<sge::input::joypad::event::absolute_axis>(
                _joypad,
                sge::input::joypad::absolute_axis{_axis_info->code(), _id},
                _event.get().value));
      });
}
