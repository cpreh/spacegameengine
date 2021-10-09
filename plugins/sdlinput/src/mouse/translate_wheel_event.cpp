//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/input/mouse/axis_code.hpp>
#include <sge/input/mouse/shared_ptr.hpp>
#include <sge/input/mouse/event/axis.hpp>
#include <sge/sdlinput/mouse/make_axis.hpp>
#include <sge/sdlinput/mouse/translate_wheel_event.hpp>
#include <awl/event/base.hpp>
#include <awl/event/container.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/unique_ptr_to_base.hpp>
#include <fcppt/config/external_begin.hpp>
#include <SDL_events.h>
#include <cstdint>
#include <fcppt/config/external_end.hpp>

awl::event::container sge::sdlinput::mouse::translate_wheel_event(
    sge::input::mouse::shared_ptr const &_mouse, SDL_MouseWheelEvent const &_event)
{
  awl::event::container result{};

  auto const make_event(
      [&result, &_mouse](sge::input::mouse::axis_code const _code, std::int32_t const _value)
      {
        if (_value != 0)
        {
          result.push_back(fcppt::unique_ptr_to_base<awl::event::base>(
              fcppt::make_unique_ptr<sge::input::mouse::event::axis>(
                  _mouse, sge::sdlinput::mouse::make_axis(_code), _value)));
        }
      });

  // TODO(philipp): Add horizontal wheel code!
  make_event(sge::input::mouse::axis_code::wheel, _event.y);

  return result;
}
