//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/input/cursor/button_pressed.hpp>
#include <sge/input/cursor/mode.hpp>
#include <sge/input/cursor/object.hpp>
#include <sge/input/cursor/optional_position.hpp>
#include <sge/input/cursor/shared_ptr.hpp>
#include <sge/input/cursor/event/button.hpp>
#include <sge/input/cursor/event/move.hpp>
#include <sge/input/cursor/event/scroll.hpp>
#include <sge/window/object_fwd.hpp>
#include <sge/window/object_ref.hpp>
#include <sge/x11input/cursor/button_code.hpp>
#include <sge/x11input/cursor/create_grab.hpp>
#include <sge/x11input/cursor/grab.hpp> // NOLINT(misc-include-cleaner)
#include <sge/x11input/cursor/make_scroll_valuators.hpp>
#include <sge/x11input/cursor/object.hpp>
#include <sge/x11input/cursor/optional_grab_unique_ptr.hpp>
#include <sge/x11input/cursor/position.hpp>
#include <sge/x11input/cursor/query_pointer.hpp>
#include <sge/x11input/cursor/scroll_valuator.hpp>
#include <sge/x11input/device/id.hpp>
#include <sge/x11input/device/valuator/pair.hpp>
#include <sge/x11input/device/valuator/range.hpp>
#include <sge/x11input/event/device_function.hpp>
#include <sge/x11input/event/select.hpp>
#include <sge/x11input/event/type_c.hpp>
#include <sge/x11input/event/window_demuxer.hpp> // NOLINT(misc-include-cleaner)
#include <sge/x11input/event/window_demuxer_ref.hpp>
#include <awl/backends/x11/cursor/object_ref.hpp>
#include <awl/backends/x11/window/const_base_ref.hpp>
#include <awl/event/base.hpp>
#include <awl/event/base_unique_ptr.hpp>
#include <awl/event/container.hpp>
#include <awl/event/optional_base_unique_ptr.hpp>
#include <fcppt/enable_shared_from_this_impl.hpp>
#include <fcppt/make_cref.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/reference_impl.hpp>
#include <fcppt/text.hpp>
#include <fcppt/unique_ptr_to_base.hpp>
#include <fcppt/algorithm/map_optional.hpp>
#include <fcppt/container/find_opt_mapped.hpp>
#include <fcppt/container/join.hpp>
#include <fcppt/container/make.hpp>
#include <fcppt/log/debug.hpp>
#include <fcppt/log/object_reference.hpp>
#include <fcppt/log/out.hpp>
#include <fcppt/mpl/list/object.hpp>
#include <fcppt/optional/make_if.hpp>
#include <fcppt/optional/map.hpp>
#include <fcppt/optional/to_container.hpp>
#include <fcppt/config/external_begin.hpp>
#include <X11/extensions/XI2.h>
#include <X11/extensions/XInput2.h>
#include <fcppt/config/external_end.hpp>

sge::x11input::cursor::object::object(
    sge::window::object_ref const _sge_window,
    fcppt::log::object_reference const _log,
    awl::backends::x11::window::const_base_ref const _window,
    XIDeviceInfo const &_info,
    sge::x11input::event::window_demuxer_ref const _window_demuxer,
    awl::backends::x11::cursor::object_ref const _cursor)
    : sge::input::cursor::object(),
      fcppt::enable_shared_from_this<sge::x11input::cursor::object>{},
      sge_window_{_sge_window},
      id_{sge::x11input::device::id{_info.deviceid}},
      log_{_log},
      window_{_window},
      cursor_{_cursor},
      position_{sge::x11input::cursor::query_pointer(_window.get(), this->id_)},
      first_enter_{true},
      event_connection_{_window_demuxer.get().on_event(
          this->id_, sge::x11input::event::device_function{[this](XIDeviceEvent const &_event) {
            return this->on_event(_event);
          }})},
      paired_event_connection_{_window_demuxer.get().on_event(
          sge::x11input::device::id{_info.attachment},
          sge::x11input::event::device_function{[this](XIDeviceEvent const &_event)
                                                { return this->on_paired_event(_event); }})},
      mode_{sge::input::cursor::mode::normal},
      scroll_valuators_{sge::x11input::cursor::make_scroll_valuators(_info)},
      cursor_grab_{}
{
  sge::x11input::event::select<fcppt::mpl::list::object<
      sge::x11input::event::type_c<XI_Motion>,
      sge::x11input::event::type_c<XI_ButtonPress>,
      sge::x11input::event::type_c<XI_ButtonRelease>,
      sge::x11input::event::type_c<XI_Enter>,
      sge::x11input::event::type_c<XI_Leave>>>(_window_demuxer.get(), this->id_);
}

sge::x11input::cursor::object::~object() = default;

sge::window::object &sge::x11input::cursor::object::window() const { return sge_window_.get(); }

sge::input::cursor::optional_position sge::x11input::cursor::object::position() const
{
  return position_;
}

void sge::x11input::cursor::object::mode(sge::input::cursor::mode const _mode)
{
  mode_ = _mode;

  if (mode_ == sge::input::cursor::mode::normal)
  {
    this->ungrab();
  }
}

awl::event::container sge::x11input::cursor::object::on_event(XIDeviceEvent const &_event)
{
  switch (_event.evtype)
  {
  case XI_Motion:
    return this->on_motion(_event);
  case XI_ButtonPress:
    return fcppt::optional::to_container<awl::event::container>(this->on_button_down(_event));
  case XI_ButtonRelease:
    return fcppt::optional::to_container<awl::event::container>(this->on_button_up(_event));
  case XI_Enter:
    return fcppt::container::make<awl::event::container>(this->on_enter(_event));
  case XI_Leave:
    return fcppt::container::make<awl::event::container>(this->on_leave(_event));
  default: break;
  }

  return awl::event::container{};
}

awl::event::container sge::x11input::cursor::object::on_paired_event(XIDeviceEvent const &_event)
{
  if (_event.evtype == XI_FocusOut)
  {
    this->on_focus_out();
  }

  return awl::event::container{};
}

awl::event::container sge::x11input::cursor::object::on_motion(XIDeviceEvent const &_event)
{
  return fcppt::container::join(
      fcppt::algorithm::map_optional<awl::event::container>(
          sge::x11input::device::valuator::range(fcppt::make_cref(_event.valuators)),
          [this](sge::x11input::device::valuator::pair const _element)
          {
            return fcppt::optional::map(
                fcppt::container::find_opt_mapped(scroll_valuators_, _element.index()),
                [_element,
                 this](fcppt::reference<sge::x11input::cursor::scroll_valuator> const _valuator)
                {
                  return fcppt::unique_ptr_to_base<awl::event::base>(
                      fcppt::make_unique_ptr<sge::input::cursor::event::scroll>(
                          sge::input::cursor::shared_ptr{this->fcppt_shared_from_this()},
                          _valuator.get().code(),
                          _valuator.get().update(_element.value())));
                });
          }),
      // TODO(philipp): Check if this is necessary!
      fcppt::container::make<awl::event::container>(this->update_position(_event)));
}

awl::event::base_unique_ptr sge::x11input::cursor::object::on_enter(XIDeviceEvent const &_event)
{
  FCPPT_LOG_DEBUG(
      log_.get(),
      fcppt::log::out << FCPPT_TEXT("XIEnter: ") << _event.event_x << FCPPT_TEXT(",")
                      << _event.event_y)

  if (first_enter_)
  {
    first_enter_ = false;

    this->grab();
  }

  return this->update_position(_event);
}

awl::event::base_unique_ptr sge::x11input::cursor::object::on_leave(XIDeviceEvent const &)
{
  FCPPT_LOG_DEBUG(log_.get(), fcppt::log::out << FCPPT_TEXT("XILeave"))

  position_ = sge::input::cursor::optional_position{};

  this->ungrab();

  return this->make_position_event();
}

void sge::x11input::cursor::object::on_focus_out()
{
  FCPPT_LOG_DEBUG(log_.get(), fcppt::log::out << FCPPT_TEXT("XIFocusOut"))

  this->ungrab();
}

awl::event::base_unique_ptr
sge::x11input::cursor::object::update_position(XIDeviceEvent const &_event)
{
  position_ = sge::input::cursor::optional_position{sge::x11input::cursor::position(_event)};

  return this->make_position_event();
}

awl::event::base_unique_ptr sge::x11input::cursor::object::make_position_event()
{
  return fcppt::unique_ptr_to_base<awl::event::base>(
      fcppt::make_unique_ptr<sge::input::cursor::event::move>(
          sge::input::cursor::shared_ptr{this->fcppt_shared_from_this()}, position_));
}

awl::event::optional_base_unique_ptr
sge::x11input::cursor::object::on_button_down(XIDeviceEvent const &_event)
{
  this->grab();

  return this->button_event(_event, sge::input::cursor::button_pressed{true});
}

awl::event::optional_base_unique_ptr
sge::x11input::cursor::object::on_button_up(XIDeviceEvent const &_event)
{
  return this->button_event(_event, sge::input::cursor::button_pressed{false});
}

awl::event::optional_base_unique_ptr sge::x11input::cursor::object::button_event(
    XIDeviceEvent const &_event, sge::input::cursor::button_pressed const _pressed)
{
  return fcppt::optional::make_if(
      (_event.flags // NOLINT(hicpp-signed-bitwise)
       & XIPointerEmulated // NOLINT(hicpp-signed-bitwise)
       ) == 0,
      [this, &_event, _pressed]
      {
        return fcppt::unique_ptr_to_base<awl::event::base>(
            fcppt::make_unique_ptr<sge::input::cursor::event::button>(
                sge::input::cursor::shared_ptr{this->fcppt_shared_from_this()},
                sge::x11input::cursor::button_code(_event.detail),
                // FIXME
                sge::x11input::cursor::position(_event),
                _pressed));
      });
}

void sge::x11input::cursor::object::grab()
{
  if (mode_ == sge::input::cursor::mode::exclusive && !cursor_grab_.has_value())
  {
    cursor_grab_ = sge::x11input::cursor::create_grab(
        this->log_.get(), this->window_, this->id_, this->cursor_);
  }
}

void sge::x11input::cursor::object::ungrab()
{
  cursor_grab_ = sge::x11input::cursor::optional_grab_unique_ptr();
}
