//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_EVDEV_PROCESSOR_HPP_INCLUDED
#define SGE_EVDEV_PROCESSOR_HPP_INCLUDED

#include <sge/evdev/inotify/event_fwd.hpp>
#include <sge/evdev/inotify/reader.hpp>
#include <sge/evdev/joypad/map.hpp>
#include <sge/input/processor.hpp>
#include <sge/input/cursor/container.hpp>
#include <sge/input/focus/container.hpp>
#include <sge/input/joypad/container.hpp>
#include <sge/input/keyboard/container.hpp>
#include <sge/input/mouse/container.hpp>
#include <sge/window/object_fwd.hpp>
#include <sge/window/object_ref.hpp>
#include <awl/backends/posix/event_fwd.hpp>
#include <awl/backends/posix/processor_ref.hpp>
#include <awl/event/connection_unique_ptr.hpp>
#include <awl/event/container.hpp>
#include <awl/event/optional_base_unique_ptr.hpp>
#include <fcppt/nonmovable.hpp>
#include <fcppt/log/object_reference.hpp>
#include <fcppt/signal/auto_connection.hpp>
#include <fcppt/config/external_begin.hpp>
#include <filesystem>
#include <fcppt/config/external_end.hpp>

namespace sge::evdev
{

class processor : public sge::input::processor
{
  FCPPT_NONMOVABLE(processor);

public:
  processor(fcppt::log::object_reference, sge::window::object_ref);

  ~processor() override;

private:
  [[nodiscard]] sge::window::object &window() const override;

  [[nodiscard]] sge::input::cursor::container cursors() const override;

  [[nodiscard]] sge::input::focus::container foci() const override;

  [[nodiscard]] sge::input::joypad::container joypads() const override;

  [[nodiscard]] sge::input::keyboard::container keyboards() const override;

  [[nodiscard]] sge::input::mouse::container mice() const override;

  [[nodiscard]] awl::event::container system_event(awl::event::base const &);

  [[nodiscard]] awl::event::container fd_event(awl::backends::posix::event const &);

  [[nodiscard]] awl::event::optional_base_unique_ptr
  inotify_event(sge::evdev::inotify::event const &);

  [[nodiscard]] awl::event::container device_event(awl::backends::posix::event const &);

  fcppt::log::object_reference const log_;

  std::filesystem::path const path_;

  sge::window::object_ref const window_;

  awl::backends::posix::processor_ref const processor_;

  sge::evdev::inotify::reader dev_watch_;

  awl::event::connection_unique_ptr const dev_watch_connection_;

  sge::evdev::joypad::map joypads_;

  fcppt::signal::auto_connection const event_connection_;
};

}

#endif
