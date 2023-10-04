//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/window/loop.hpp>
#include <sge/window/loop_function.hpp>
#include <sge/window/system.hpp>
#include <awl/event/base.hpp> // NOLINT(misc-include-cleaner)
#include <awl/event/base_unique_ptr.hpp>
#include <awl/event/container.hpp>
#include <awl/main/exit_code.hpp>
#include <fcppt/either/loop.hpp>

awl::main::exit_code
sge::window::loop(sge::window::system &_system, sge::window::loop_function const &_function)
{
  return fcppt::either::loop(
      [&_system] { return _system.next(); },
      [&_function](awl::event::container const &_events)
      {
        for (awl::event::base_unique_ptr const &event : _events)
        {
          _function(*event);
        }
      });
}
