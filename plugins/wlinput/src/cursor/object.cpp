//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/input/cursor/mode.hpp>
#include <sge/input/cursor/object.hpp>
#include <sge/input/cursor/optional_position.hpp>
#include <sge/input/cursor/position.hpp>
#include <sge/input/cursor/shared_ptr.hpp>
#include <sge/input/cursor/event/button.hpp>
#include <sge/input/cursor/event/move.hpp>
#include <sge/input/cursor/event/scroll.hpp>
#include <sge/window/object_fwd.hpp>
#include <sge/window/object_ref.hpp>
#include <sge/wlinput/cursor/button_code.hpp>
#include <sge/wlinput/cursor/button_state.hpp>
#include <sge/wlinput/cursor/data.hpp>
#include <sge/wlinput/cursor/object.hpp>
#include <sge/wlinput/cursor/position.hpp>
#include <sge/wlinput/cursor/scroll_code.hpp>
#include <sge/wlinput/cursor/scroll_value.hpp>
#include <awl/backends/wayland/seat_ref.hpp>
#include <awl/backends/wayland/window/object.hpp> // NOLINT(misc-include-cleaner)
#include <awl/backends/wayland/window/object_ref.hpp>
#include <awl/event/base.hpp>
#include <awl/event/container_reference.hpp>
#include <fcppt/enable_shared_from_this_impl.hpp>
#include <fcppt/make_ref.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/unique_ptr_to_base.hpp>
#include <fcppt/cast/from_void_ptr.hpp>
#include <fcppt/optional/maybe_void.hpp>
#include <fcppt/config/external_begin.hpp>
#include <wayland-client-protocol.h>
#include <wayland-util.h>
#include <cstdint>
#include <fcppt/config/external_end.hpp>

namespace
{

void pointer_enter(
    void *const _data,
    wl_pointer *,
    std::uint32_t,
    wl_surface *const _surface,
    wl_fixed_t const _surface_x,
    wl_fixed_t const _surface_y)
{
  sge::wlinput::cursor::data &data(
      *fcppt::cast::from_void_ptr<sge::wlinput::cursor::data *>(_data));

  if (data.window_.get().surface() == _surface)
  {
    data.position_ = sge::input::cursor::optional_position{
        sge::wlinput::cursor::position(_surface_x, _surface_y)};

    data.events_.get().push_back(fcppt::unique_ptr_to_base<awl::event::base>(
        fcppt::make_unique_ptr<sge::input::cursor::event::move>(
            data.cursor_.get().get_shared_ptr(), data.position_)));
  }
}

void pointer_leave(void *const _data, wl_pointer *, std::uint32_t, wl_surface *const _surface)
{
  sge::wlinput::cursor::data &data(
      *fcppt::cast::from_void_ptr<sge::wlinput::cursor::data *>(_data));

  if (data.window_.get().surface() == _surface)
  {
    data.position_ = sge::input::cursor::optional_position{};

    data.events_.get().push_back(fcppt::unique_ptr_to_base<awl::event::base>(
        fcppt::make_unique_ptr<sge::input::cursor::event::move>(
            data.cursor_.get().get_shared_ptr(), data.position_)));
  }
}

void pointer_motion(
    void *const _data,
    wl_pointer *,
    std::uint32_t,
    wl_fixed_t const _surface_x,
    wl_fixed_t const _surface_y)
{
  sge::wlinput::cursor::data &data(
      *fcppt::cast::from_void_ptr<sge::wlinput::cursor::data *>(_data));

  if (data.position_.has_value())
  {
    data.position_ = sge::input::cursor::optional_position{
        sge::wlinput::cursor::position(_surface_x, _surface_y)};

    data.events_.get().push_back(fcppt::unique_ptr_to_base<awl::event::base>(
        fcppt::make_unique_ptr<sge::input::cursor::event::move>(
            data.cursor_.get().get_shared_ptr(), data.position_)));
  }
}

void pointer_button(
    void *const _data,
    wl_pointer *,
    std::uint32_t,
    std::uint32_t,
    std::uint32_t const _button,
    std::uint32_t const _state)
{
  sge::wlinput::cursor::data &data(
      *fcppt::cast::from_void_ptr<sge::wlinput::cursor::data *>(_data));

  fcppt::optional::maybe_void(
      data.position_,
      [_button, _state, &data](sge::input::cursor::position const &_position)
      {
        data.events_.get().push_back(fcppt::unique_ptr_to_base<awl::event::base>(
            fcppt::make_unique_ptr<sge::input::cursor::event::button>(
                data.cursor_.get().get_shared_ptr(),
                sge::wlinput::cursor::button_code(_button),
                _position,
                sge::wlinput::cursor::button_state(_state))));
      });
}

void pointer_axis(void *, wl_pointer *, std::uint32_t, std::uint32_t, wl_fixed_t) {}

void pointer_frame(void *, wl_pointer *) {}

void pointer_axis_source(void *, wl_pointer *, std::uint32_t) {}

void pointer_axis_stop(void *, wl_pointer *, std::uint32_t, std::uint32_t) {}

void pointer_axis_discrete(
    void *const _data, wl_pointer *, std::uint32_t const _axis, std::int32_t const _discrete)
{
  sge::wlinput::cursor::data const &data{
      *fcppt::cast::from_void_ptr<sge::wlinput::cursor::data *>(_data)};

  if (data.position_.has_value())
  {
    data.events_.get().push_back(fcppt::unique_ptr_to_base<awl::event::base>(
        fcppt::make_unique_ptr<sge::input::cursor::event::scroll>(
            data.cursor_.get().get_shared_ptr(),
            sge::wlinput::cursor::scroll_code(_axis),
            sge::wlinput::cursor::scroll_value(_discrete))));
  }
}

wl_pointer_listener const pointer_listener{
    pointer_enter,
    pointer_leave,
    pointer_motion,
    pointer_button,
    pointer_axis,
    pointer_frame,
    pointer_axis_source,
    pointer_axis_stop,
    pointer_axis_discrete};

}

sge::wlinput::cursor::object::object(
    sge::window::object_ref const _sge_window,
    awl::backends::wayland::window::object_ref const _window,
    awl::event::container_reference const _events,
    awl::backends::wayland::seat_ref const _seat)
    : sge::input::cursor::object{},
      fcppt::enable_shared_from_this<sge::wlinput::cursor::object>{},
      window_{_sge_window},
      impl_{_seat},
      data_{fcppt::make_ref(*this), _window, _events}
{
  ::wl_pointer_add_listener(impl_.get(), &pointer_listener, &data_);
}

sge::window::object &sge::wlinput::cursor::object::window() const { return window_.get(); }

sge::wlinput::cursor::object::~object() = default;

sge::input::cursor::optional_position sge::wlinput::cursor::object::position() const
{
  return data_.position_;
}

void sge::wlinput::cursor::object::mode(sge::input::cursor::mode const _mode)
{
  // TODO(philipp): We need a different API here because this is not implementable in wayland
}

sge::input::cursor::shared_ptr sge::wlinput::cursor::object::get_shared_ptr()
{
  return sge::input::cursor::shared_ptr{this->fcppt_shared_from_this()};
}
