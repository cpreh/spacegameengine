//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/input/exception.hpp>
#include <sge/input/processor.hpp>
#include <sge/input/cursor/container.hpp>
#include <sge/input/cursor/shared_ptr.hpp>
#include <sge/input/cursor/event/discover.hpp>
#include <sge/input/cursor/event/remove.hpp>
#include <sge/input/focus/container.hpp>
#include <sge/input/focus/shared_ptr.hpp>
#include <sge/input/focus/event/discover.hpp>
#include <sge/input/focus/event/remove.hpp>
#include <sge/input/joypad/container.hpp>
#include <sge/input/keyboard/container.hpp>
#include <sge/input/mouse/container.hpp>
#include <sge/window/object.hpp>
#include <sge/window/object_ref.hpp>
#include <sge/window/system.hpp>
#include <sge/window/system_event_function.hpp>
#include <sge/wlinput/change_caps.hpp>
#include <sge/wlinput/initial_objects.hpp>
#include <sge/wlinput/processor.hpp>
#include <sge/wlinput/remove_seat.hpp>
#include <sge/wlinput/cursor/create.hpp>
#include <sge/wlinput/cursor/object.hpp>
#include <sge/wlinput/focus/create.hpp>
#include <sge/wlinput/focus/object.hpp>
#include <awl/backends/posix/event.hpp>
#include <awl/backends/posix/processor.hpp>
#include <awl/backends/wayland/display_comparison.hpp>
#include <awl/backends/wayland/display_fd.hpp>
#include <awl/backends/wayland/system/object.hpp>
#include <awl/backends/wayland/system/event/processor.hpp>
#include <awl/backends/wayland/system/event/seat_caps.hpp>
#include <awl/backends/wayland/system/event/seat_removed.hpp>
#include <awl/backends/wayland/system/seat/caps.hpp>
#include <awl/backends/wayland/system/seat/object.hpp>
#include <awl/backends/wayland/window/object.hpp>
#include <awl/event/base.hpp>
#include <awl/event/connection.hpp>
#include <awl/event/container.hpp>
#include <awl/system/object.hpp>
#include <awl/system/event/processor.hpp>
#include <fcppt/make_ref.hpp>
#include <fcppt/move_clear.hpp>
#include <fcppt/reference_impl.hpp>
#include <fcppt/text.hpp>
#include <fcppt/algorithm/map.hpp>
#include <fcppt/algorithm/map_optional.hpp>
#include <fcppt/cast/dynamic.hpp>
#include <fcppt/cast/dynamic_fun.hpp>
#include <fcppt/container/join.hpp>
#include <fcppt/log/object_reference.hpp>
#include <fcppt/mpl/list/object.hpp>
#include <fcppt/optional/maybe.hpp>
#include <fcppt/optional/to_container.hpp>
#include <fcppt/optional/to_exception.hpp>
#include <fcppt/variant/dynamic_cast.hpp>
#include <fcppt/variant/match.hpp>

sge::wlinput::processor::processor(
    fcppt::log::object_reference const _log, sge::window::object_ref const _window)
    : sge::input::processor{},
      log_{_log},
      system_processor_{
          fcppt::optional::to_exception(
              fcppt::cast::dynamic<awl::backends::wayland::system::event::processor>(
                  _window.get().system().awl_system().processor()),
              []
              {
                return sge::input::exception{FCPPT_TEXT(
                    "System processor passed to wlinput::processor is not a Wayland processor.")};
              })
              .get()},
      sge_window_{_window},
      window_{fcppt::optional::to_exception(
                  fcppt::cast::dynamic<awl::backends::wayland::window::object>(
                      _window.get().awl_object()),
                  []
                  {
                    return sge::input::exception{
                        FCPPT_TEXT("Window passed to wlinput::processor is not a Wayland window.")};
                  })
                  .get()},
      display_{fcppt::optional::to_exception(
                   fcppt::cast::dynamic<awl::backends::wayland::system::object>(
                       _window.get().system().awl_system()),
                   []
                   {
                     return sge::input::exception{FCPPT_TEXT(
                         "System passed to wlinput::processor is not a Wayland system.")};
                   })
                   ->display()},
      fd_{awl::backends::wayland::display_fd(display_.get())},
      xkb_context_{},
      last_events_{},
      cursors_(sge::wlinput::initial_objects<
               sge::wlinput::cursor::object,
               awl::backends::wayland::system::seat::caps::pointer>(
          sge::wlinput::cursor::create(sge_window_, window_, fcppt::make_ref(last_events_)),
          system_processor_.get().seats())),
      foci_(sge::wlinput::initial_objects<
            sge::wlinput::focus::object,
            awl::backends::wayland::system::seat::caps::keyboard>(
          sge::wlinput::focus::create(
              _log,
              sge_window_,
              fcppt::make_ref(xkb_context_),
              window_,
              fcppt::make_ref(last_events_)),
          system_processor_.get().seats())),
      fd_connection_{system_processor_.get().fd_processor().register_fd(this->fd_)},
      event_connection_{_window.get().system().event_handler(sge::window::system_event_function{
          [this](awl::event::base const &_event) { return this->on_event(_event); }})}
{
}

sge::wlinput::processor::~processor() = default;

sge::window::object &sge::wlinput::processor::window() const { return sge_window_.get(); }

sge::input::cursor::container sge::wlinput::processor::cursors() const
{
  return fcppt::algorithm::map<sge::input::cursor::container>(
      cursors_, [](auto const &_pair) { return sge::input::cursor::shared_ptr{_pair.second}; });
}

sge::input::focus::container sge::wlinput::processor::foci() const
{
  return fcppt::algorithm::map<sge::input::focus::container>(
      foci_, [](auto const &_pair) { return sge::input::focus::shared_ptr{_pair.second}; });
}

sge::input::joypad::container sge::wlinput::processor::joypads() const
{
  return sge::input::joypad::container{};
}

sge::input::keyboard::container sge::wlinput::processor::keyboards() const
{
  return sge::input::keyboard::container{};
}

sge::input::mouse::container sge::wlinput::processor::mice() const
{
  return sge::input::mouse::container{};
}

awl::event::container sge::wlinput::processor::on_event(awl::event::base const &_event)
{
  return fcppt::optional::maybe(
      fcppt::variant::dynamic_cast_<
          fcppt::mpl::list::object<
              awl::backends::wayland::system::event::seat_caps const,
              awl::backends::wayland::system::event::seat_removed const,
              awl::backends::posix::event const>,
          fcppt::cast::dynamic_fun>(_event),
      [] { return awl::event::container{}; },
      [this](auto const &_variant)
      {
        return fcppt::variant::match(
            _variant,
            [this](fcppt::reference<awl::backends::wayland::system::event::seat_caps const> const
                       _seat_caps)
            {
              return this->display_.get() == _seat_caps.get().display()
                         ? this->seat_caps(_seat_caps.get())
                         : awl::event::container();
            },
            [this](fcppt::reference<awl::backends::wayland::system::event::seat_removed const> const
                       _seat_removed)
            {
              return this->display_.get() == _seat_removed.get().display()
                         ? this->remove_seat(_seat_removed.get())
                         : awl::event::container{};
            },
            [this](fcppt::reference<awl::backends::posix::event const> const _fd_event) {
              return this->fd_ == _fd_event.get().fd() ? this->display_event()
                                                       : awl::event::container();
            });
      });
}

awl::event::container sge::wlinput::processor::display_event()
{
  return fcppt::move_clear(last_events_);
}

awl::event::container
sge::wlinput::processor::seat_caps(awl::backends::wayland::system::event::seat_caps const &_event)
{
  awl::backends::wayland::system::seat::object &seat{*_event.get()};

  return fcppt::container::join(
      fcppt::optional::to_container<awl::event::container>(
          sge::wlinput::change_caps<
              awl::backends::wayland::system::seat::caps::keyboard,
              sge::input::focus::shared_ptr,
              sge::input::focus::event::discover,
              sge::input::focus::event::remove>(
              sge::wlinput::focus::create(
                  log_,
                  sge_window_,
                  fcppt::make_ref(xkb_context_),
                  window_,
                  fcppt::make_ref(last_events_)),
              fcppt::make_ref(foci_),
              fcppt::make_ref(seat))),
      fcppt::optional::to_container<awl::event::container>(
          sge::wlinput::change_caps<
              awl::backends::wayland::system::seat::caps::pointer,
              sge::input::cursor::shared_ptr,
              sge::input::cursor::event::discover,
              sge::input::cursor::event::remove>(
              sge::wlinput::cursor::create(sge_window_, window_, fcppt::make_ref(last_events_)),
              fcppt::make_ref(cursors_),
              fcppt::make_ref(seat))));
}

awl::event::container sge::wlinput::processor::remove_seat(
    awl::backends::wayland::system::event::seat_removed const &_event)
{
  awl::backends::wayland::system::seat::object const &seat{*_event.get()};

  return fcppt::container::join(
      fcppt::optional::to_container<awl::event::container>(
          sge::wlinput::remove_seat<
              awl::backends::wayland::system::seat::caps::keyboard,
              sge::input::focus::shared_ptr,
              sge::input::focus::event::remove>(foci_, seat)),

      fcppt::optional::to_container<awl::event::container>(
          sge::wlinput::remove_seat<
              awl::backends::wayland::system::seat::caps::pointer,
              sge::input::cursor::shared_ptr,
              sge::input::cursor::event::remove>(cursors_, seat)));
}
