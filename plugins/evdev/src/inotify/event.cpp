//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/evdev/inotify/event.hpp>
#include <sge/evdev/inotify/event_type.hpp>
#include <fcppt/config/external_begin.hpp>
#include <filesystem>
#include <utility>
#include <fcppt/config/external_end.hpp>

sge::evdev::inotify::event::event(
    std::filesystem::path &&_filename, sge::evdev::inotify::event_type const _event_type)
    : filename_{std::move(_filename)}, event_type_{_event_type}
{
}

std::filesystem::path const &sge::evdev::inotify::event::filename() const { return filename_; }

sge::evdev::inotify::event_type sge::evdev::inotify::event::event_type() const
{
  return event_type_;
}
