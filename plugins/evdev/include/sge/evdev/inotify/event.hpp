//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_EVDEV_INOTIFY_EVENT_HPP_INCLUDED
#define SGE_EVDEV_INOTIFY_EVENT_HPP_INCLUDED

#include <sge/evdev/inotify/event_fwd.hpp> // IWYU pragma: keep
#include <sge/evdev/inotify/event_type.hpp>
#include <fcppt/config/external_begin.hpp>
#include <filesystem>
#include <fcppt/config/external_end.hpp>

namespace sge::evdev::inotify
{

class event
{
public:
  event(std::filesystem::path &&, sge::evdev::inotify::event_type);

  [[nodiscard]] std::filesystem::path const &filename() const;

  [[nodiscard]] sge::evdev::inotify::event_type event_type() const;

private:
  std::filesystem::path filename_;

  sge::evdev::inotify::event_type event_type_;
};

}

#endif
