//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/evdev/joypad/add.hpp>
#include <sge/evdev/joypad/create.hpp>
#include <sge/evdev/joypad/map.hpp>
#include <sge/evdev/joypad/object.hpp> // NOLINT(misc-include-cleaner)
#include <sge/evdev/joypad/shared_ptr.hpp>
#include <sge/input/exception.hpp>
#include <sge/input/joypad/shared_ptr.hpp>
#include <sge/input/joypad/event/discover.hpp>
#include <sge/window/object_ref.hpp>
#include <awl/backends/posix/processor_ref.hpp>
#include <awl/event/base.hpp>
#include <awl/event/optional_base_unique_ptr.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/not.hpp>
#include <fcppt/text.hpp>
#include <fcppt/unique_ptr_to_base.hpp>
#include <fcppt/log/object_fwd.hpp>
#include <fcppt/optional/map.hpp>
#include <fcppt/config/external_begin.hpp>
#include <filesystem>
#include <utility>
#include <fcppt/config/external_end.hpp>

awl::event::optional_base_unique_ptr sge::evdev::joypad::add(
    fcppt::log::object &_log,
    sge::window::object_ref const _window,
    awl::backends::posix::processor_ref const _processor,
    sge::evdev::joypad::map &_map,
    std::filesystem::path const &_path)
{
  return fcppt::optional::map(
      sge::evdev::joypad::create(_log, _window, _processor, _path),
      [&_map](sge::evdev::joypad::shared_ptr const &_ptr)
      {
        if(fcppt::not_(_map.insert(std::make_pair(_ptr->posix_fd(), _ptr)).second))
        {
          throw sge::input::exception{FCPPT_TEXT("Double insert in evdev!")};
        }

        return fcppt::unique_ptr_to_base<awl::event::base>(
            fcppt::make_unique_ptr<sge::input::joypad::event::discover>(
                sge::input::joypad::shared_ptr{_ptr}));
      });
}
