//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/input/joypad/axis_value.hpp>
#include <sge/input/joypad/shared_ptr.hpp>
#include <sge/input/joypad/event/absolute_axis.hpp>
#include <sge/sdlinput/joypad/device.hpp>
#include <sge/sdlinput/joypad/from_event.hpp>
#include <sge/sdlinput/joypad/hat_direction.hpp>
#include <sge/sdlinput/joypad/map.hpp>
#include <sge/sdlinput/joypad/shared_ptr.hpp>
#include <sge/sdlinput/joypad/translate_hat_event.hpp>
#include <awl/event/base.hpp>
#include <awl/event/container.hpp>
#include <awl/event/optional_base_unique_ptr.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/unique_ptr_to_base.hpp>
#include <fcppt/container/make.hpp>
#include <fcppt/optional/cat.hpp>
#include <fcppt/optional/make.hpp>
#include <fcppt/optional/map.hpp>
#include <fcppt/optional/maybe_multi.hpp>
#include <fcppt/optional/object_impl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <SDL_events.h>
#include <SDL_joystick.h>
#include <cstdint>
#include <utility>
#include <vector>
#include <fcppt/config/external_end.hpp>

namespace
{

using axes_direction = std::pair<sge::input::joypad::axis_value, sge::input::joypad::axis_value>;

fcppt::optional::object<axes_direction> axes_values(std::uint8_t const _value)
{
  switch (_value)
  {
  case SDL_HAT_LEFTUP: // NOLINT(hicpp-signed-bitwise)
    return fcppt::optional::make(axes_direction{-1, -1});
  case SDL_HAT_UP:
    return fcppt::optional::make(axes_direction{0, -1});
  case SDL_HAT_RIGHTUP: // NOLINT(hicpp-signed-bitwise)
    return fcppt::optional::make(axes_direction{1, -1});
  case SDL_HAT_LEFT:
    return fcppt::optional::make(axes_direction{-1, 0});
  case SDL_HAT_CENTERED:
    return fcppt::optional::make(axes_direction{0, 0});
  case SDL_HAT_RIGHT:
    return fcppt::optional::make(axes_direction{1, 0});
  case SDL_HAT_LEFTDOWN: // NOLINT(hicpp-signed-bitwise)
    return fcppt::optional::make(axes_direction{-1, 1});
  case SDL_HAT_DOWN:
    return fcppt::optional::make(axes_direction{0, 1});
  case SDL_HAT_RIGHTDOWN: // NOLINT(hicpp-signed-bitwise)
    return fcppt::optional::make(axes_direction{1, 1});
  default:
    break;
  }

  return fcppt::optional::object<axes_direction>{};
}

}

awl::event::container sge::sdlinput::joypad::translate_hat_event(
    sge::sdlinput::joypad::map const &_joypads, SDL_JoyHatEvent const &_event)
{
  return fcppt::optional::maybe_multi(
      [] { return awl::event::container{}; },
      [&_event](axes_direction const _axes, sge::sdlinput::joypad::shared_ptr const _joypad)
      {
        auto const make_event{
            [&_joypad, &_event](
                sge::sdlinput::joypad::hat_direction const _direction,
                sge::input::joypad::axis_value const _value) -> awl::event::optional_base_unique_ptr
            {
              return fcppt::optional::map(
                  _joypad->hat_axis(_event.hat, _direction),
                  [&_joypad, _value](sge::input::joypad::absolute_axis const &_axis)
                  {
                    return fcppt::unique_ptr_to_base<awl::event::base>(
                        fcppt::make_unique_ptr<sge::input::joypad::event::absolute_axis>(
                            sge::input::joypad::shared_ptr{_joypad}, _axis, _value));
                  });
            }};

        return fcppt::optional::cat<awl::event::container>(
            fcppt::container::make<std::vector<awl::event::optional_base_unique_ptr>>(
                make_event(sge::sdlinput::joypad::hat_direction::x, _axes.first),
                make_event(sge::sdlinput::joypad::hat_direction::y, _axes.second)));
      },
      axes_values(_event.value),
      sge::sdlinput::joypad::from_event(_joypads, _event));
}
