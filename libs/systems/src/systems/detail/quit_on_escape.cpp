//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/input/key/code.hpp>
#include <sge/input/keyboard/event/key.hpp>
#include <sge/systems/detail/quit_on_escape.hpp>
#include <sge/window/system.hpp>
#include <awl/event/base.hpp>
#include <awl/main/exit_success.hpp>
#include <fcppt/reference_impl.hpp>
#include <fcppt/cast/dynamic.hpp>
#include <fcppt/optional/maybe_void.hpp>

void sge::systems::detail::quit_on_escape(
    sge::window::system &_window_system, awl::event::base const &_event)
{
  fcppt::optional::maybe_void(
      fcppt::cast::dynamic<sge::input::keyboard::event::key const>(_event),
      [&_window_system](fcppt::reference<sge::input::keyboard::event::key const> const _key_event)
      {
        if (!_key_event.get().pressed() &&
            _key_event.get().get().code() == sge::input::key::code::escape)
        {
          _window_system.quit(awl::main::exit_success());
        }
      });
}
