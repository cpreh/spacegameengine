//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/input/mouse/axis_code.hpp>
#include <sge/input/mouse/shared_ptr.hpp>
#include <sge/input/mouse/event/axis.hpp>
#include <sge/sdlinput/mouse/make_axis.hpp>
#include <sge/sdlinput/mouse/translate_motion_event.hpp>
#include <awl/event/base.hpp>
#include <awl/event/container.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/unique_ptr_to_base.hpp>
#include <fcppt/config/external_begin.hpp>
#include <SDL_events.h>
#include <cstdint>
#include <fcppt/config/external_end.hpp>

awl::event::container sge::sdlinput::mouse::translate_motion_event(
    sge::input::mouse::shared_ptr const &_mouse, SDL_MouseMotionEvent const &_event)
{
  awl::event::container result{};

  auto const add_event(
      [&result, &_mouse](std::int32_t const _value, sge::input::mouse::axis_code const _code)
      {
        if (_value != 0)
        {
          result.push_back(fcppt::unique_ptr_to_base<awl::event::base>(
              fcppt::make_unique_ptr<sge::input::mouse::event::axis>(
                  _mouse, sge::sdlinput::mouse::make_axis(_code), _value)));
        }
      });

  add_event(_event.xrel, sge::input::mouse::axis_code::x);

  add_event(_event.yrel, sge::input::mouse::axis_code::y);

  return result;
}
