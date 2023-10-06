//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/evdev/joypad/add.hpp>
#include <sge/evdev/joypad/attrib.hpp>
#include <sge/evdev/joypad/find_path.hpp>
#include <sge/evdev/joypad/map.hpp>
#include <sge/window/object_ref.hpp>
#include <awl/backends/posix/processor_ref.hpp>
#include <awl/event/base.hpp> // NOLINT(misc-include-cleaner)
#include <awl/event/optional_base_unique_ptr.hpp>
#include <fcppt/log/object_fwd.hpp>
#include <fcppt/optional/join.hpp>
#include <fcppt/optional/make_if.hpp>
#include <fcppt/config/external_begin.hpp>
#include <filesystem>
#include <fcppt/config/external_end.hpp>

awl::event::optional_base_unique_ptr sge::evdev::joypad::attrib(
    fcppt::log::object &_log,
    sge::window::object_ref const _window,
    awl::backends::posix::processor_ref const _processor,
    sge::evdev::joypad::map &_map,
    std::filesystem::path const &_path)
{
  return fcppt::optional::join(fcppt::optional::make_if(
      !sge::evdev::joypad::find_path(_map, _path).has_value(),
      [&_log, _window, &_processor, &_map, &_path]
      { return sge::evdev::joypad::add(_log, _window, _processor, _map, _path); }));
}
