//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/charconv/convert.hpp>
#include <sge/charconv/encoding.hpp>
#include <sge/input/focus/key.hpp>
#include <sge/input/focus/object.hpp>
#include <sge/input/focus/shared_ptr.hpp>
#include <sge/input/focus/event/in.hpp>
#include <sge/input/focus/event/key.hpp>
#include <sge/input/focus/event/key_repeat.hpp>
#include <sge/input/focus/event/out.hpp>
#include <sge/input/focus/event/text.hpp>
#include <sge/input/key/code.hpp>
#include <sge/input/key/optional_code.hpp>
#include <sge/input/key/pressed.hpp>
#include <sge/window/object.hpp> // NOLINT(misc-include-cleaner)
#include <sge/window/object_ref.hpp>
#include <sge/window/system.hpp>
#include <sge/window/system_event_function.hpp>
#include <sge/wlinput/xkb_context_ref.hpp>
#include <sge/wlinput/focus/data.hpp>
#include <sge/wlinput/focus/get_keysym.hpp>
#include <sge/wlinput/focus/get_utf8_string.hpp>
#include <sge/wlinput/focus/key_pressed.hpp>
#include <sge/wlinput/focus/keymap.hpp>
#include <sge/wlinput/focus/mmap.hpp>
#include <sge/wlinput/focus/object.hpp>
#include <sge/wlinput/focus/optional_keymap.hpp>
#include <sge/wlinput/focus/optional_state.hpp>
#include <sge/wlinput/focus/scoped_fd.hpp>
#include <sge/wlinput/focus/state.hpp>
#include <sge/wlinput/focus/translate_keysym.hpp>
#include <sge/wlinput/focus/wl_to_xkb_keycode.hpp>
#include <sge/wlinput/focus/xkb_keycode.hpp>
#include <awl/backends/posix/fd.hpp>
#include <awl/backends/wayland/seat_ref.hpp>
#include <awl/backends/wayland/window/object.hpp> // NOLINT(misc-include-cleaner)
#include <awl/backends/wayland/window/object_ref.hpp>
#include <awl/event/base.hpp>
#include <awl/event/container.hpp>
#include <awl/event/container_reference.hpp>
#include <awl/system/object.hpp>
#include <awl/system/event/processor.hpp> // NOLINT(misc-include-cleaner)
#include <awl/timer/delay.hpp>
#include <awl/timer/duration.hpp>
#include <awl/timer/match.hpp>
#include <awl/timer/object.hpp> // NOLINT(misc-include-cleaner)
#include <awl/timer/period.hpp>
#include <awl/timer/setting.hpp>
#include <awl/timer/unique_ptr.hpp>
#include <fcppt/enable_shared_from_this_impl.hpp>
#include <fcppt/exception.hpp>
#include <fcppt/make_ref.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/unique_ptr_to_base.hpp>
#include <fcppt/cast/from_void_ptr.hpp>
#include <fcppt/log/error.hpp>
#include <fcppt/log/object_reference.hpp>
#include <fcppt/log/out.hpp>
#include <fcppt/optional/assign.hpp>
#include <fcppt/optional/comparison.hpp>
#include <fcppt/optional/make.hpp>
#include <fcppt/optional/map.hpp>
#include <fcppt/optional/maybe.hpp>
#include <fcppt/optional/maybe_void.hpp>
#include <fcppt/optional/to_container.hpp>
#include <fcppt/signal/object_impl.hpp> // NOLINT(misc-include-cleaner)
#include <fcppt/config/external_begin.hpp>
#include <wayland-client-protocol.h>
#include <wayland-util.h>
#include <xkbcommon/xkbcommon.h>
#include <cstdint>
#include <fcppt/config/external_end.hpp>

namespace
{

void keyboard_keymap(
    void *const _data,
    wl_keyboard *,
    std::uint32_t const _format, // NOLINT(bugprone-easily-swappable-parameters)
    std::int32_t const _fd,
    std::uint32_t const _size)
{
  sge::wlinput::focus::data &data(*fcppt::cast::from_void_ptr<sge::wlinput::focus::data *>(_data));

  awl::backends::posix::fd const fd{_fd};

  sge::wlinput::focus::scoped_fd const scoped_fd{fd};

  auto const remove_xkb(
      [&data]
      {
        data.xkb_state_ = sge::wlinput::focus::optional_state();

        data.xkb_keymap_ = sge::wlinput::focus::optional_keymap();
      });

  if (_format != WL_KEYBOARD_KEYMAP_FORMAT_XKB_V1)
  {
    remove_xkb();

    return;
  }

  try
  {
    sge::wlinput::focus::mmap const mapped{fd, _size};

    sge::wlinput::focus::keymap &xkb_keymap{fcppt::optional::assign(
        data.xkb_keymap_, sge::wlinput::focus::keymap{data.xkb_context_, mapped.string()})};

    data.xkb_state_ = sge::wlinput::focus::optional_state{
        sge::wlinput::focus::state{fcppt::make_ref(xkb_keymap)}};
  }
  catch (fcppt::exception const &_error)
  {
    FCPPT_LOG_ERROR(data.log_.get(), fcppt::log::out << _error.string())

    remove_xkb();
  }
  catch (...)
  {
    remove_xkb();
  }
}

void keyboard_enter(
    void *const _data, wl_keyboard *, std::uint32_t, wl_surface *const _surface, wl_array *)
{
  sge::wlinput::focus::data &data(*fcppt::cast::from_void_ptr<sge::wlinput::focus::data *>(_data));

  if (_surface == data.window_.get().surface())
  {
    data.entered_ = true;

    data.last_pressed_ = sge::input::key::optional_code();

    data.events_.get().push_back(fcppt::unique_ptr_to_base<awl::event::base>(
        fcppt::make_unique_ptr<sge::input::focus::event::in>(data.focus_.get().get_shared_ptr())));
  }
}

void keyboard_leave(void *const _data, wl_keyboard *, std::uint32_t, wl_surface *const _surface)
{
  sge::wlinput::focus::data &data(*fcppt::cast::from_void_ptr<sge::wlinput::focus::data *>(_data));

  if (_surface == data.window_.get().surface())
  {
    data.entered_ = false;

    data.last_pressed_ = sge::input::key::optional_code();

    data.events_.get().push_back(fcppt::unique_ptr_to_base<awl::event::base>(
        fcppt::make_unique_ptr<sge::input::focus::event::out>(data.focus_.get().get_shared_ptr())));
  }
}

void keyboard_key(
    void *const _data,
    wl_keyboard *,
    std::uint32_t,
    std::uint32_t,
    std::uint32_t const _key,
    std::uint32_t const _state)
{
  sge::wlinput::focus::data &data(*fcppt::cast::from_void_ptr<sge::wlinput::focus::data *>(_data));

  fcppt::optional::maybe_void(
      data.xkb_state_,
      [&data, _key, _state](sge::wlinput::focus::state const &_xkb_state)
      {
        sge::wlinput::focus::xkb_keycode const xkb_keycode{
            sge::wlinput::focus::wl_to_xkb_keycode(_key)};

        sge::input::key::pressed const pressed{sge::wlinput::focus::key_pressed(_state)};

        sge::input::key::code const key_code{sge::wlinput::focus::translate_keysym(
            sge::wlinput::focus::get_keysym(_xkb_state, xkb_keycode))};

        if (pressed.get())
        {
          data.last_pressed_ = sge::input::key::optional_code{key_code};
        }
        else if (data.last_pressed_ == sge::input::key::optional_code{key_code})
        {
          // TODO(philipp): Reset key repeat timer here?
          data.last_pressed_ = sge::input::key::optional_code{};
        }

        data.events_.get().push_back(fcppt::unique_ptr_to_base<awl::event::base>(
            fcppt::make_unique_ptr<sge::input::focus::event::key>(
                data.focus_.get().get_shared_ptr(), sge::input::focus::key{key_code}, pressed)));

        data.events_.get().push_back(fcppt::unique_ptr_to_base<awl::event::base>(
            fcppt::make_unique_ptr<sge::input::focus::event::text>(
                data.focus_.get().get_shared_ptr(),
                sge::charconv::
                    convert<sge::charconv::encoding::wchar, sge::charconv::encoding::utf8>(
                        sge::wlinput::focus::get_utf8_string(_xkb_state, xkb_keycode)))));
      });
}

void keyboard_modifiers(
    void *const _data,
    wl_keyboard *,
    std::uint32_t,
    std::uint32_t const _mods_depressed,
    std::uint32_t const _mods_latched,
    std::uint32_t const _mods_locked,
    std::uint32_t const _group)
{
  sge::wlinput::focus::data &data(*fcppt::cast::from_void_ptr<sge::wlinput::focus::data *>(_data));

  fcppt::optional::maybe_void(
      data.xkb_state_,
      [_mods_depressed, _mods_latched, _mods_locked, _group](
          sge::wlinput::focus::state const &_state)
      {
        ::xkb_state_update_mask(
            _state.get(), _mods_depressed, _mods_latched, _mods_locked, 0, 0, _group);
      });
}

void keyboard_repeat_info(
    void *const _data, wl_keyboard *, std::int32_t const _rate, std::int32_t const _delay)
{
  sge::wlinput::focus::data &data(*fcppt::cast::from_void_ptr<sge::wlinput::focus::data *>(_data));

  auto const convert_duration([](std::int32_t const _duration)
                              { return awl::timer::duration{_duration}; });

  data.repeat_timer_ = fcppt::optional::make(data.processor_.get().create_timer(awl::timer::setting{
      awl::timer::delay{convert_duration(_delay)}, awl::timer::period{convert_duration(_rate)}}));
}

wl_keyboard_listener const keyboard_listener{
    .keymap = keyboard_keymap,
    .enter = keyboard_enter,
    .leave = keyboard_leave,
    .key = keyboard_key,
    .modifiers = keyboard_modifiers,
    .repeat_info = keyboard_repeat_info};

}

sge::wlinput::focus::object::object(
    fcppt::log::object_reference const _log,
    sge::window::object_ref const _sge_window,
    sge::wlinput::xkb_context_ref const _xkb_context,
    awl::backends::wayland::window::object_ref const _window,
    awl::event::container_reference const _events,
    awl::backends::wayland::seat_ref const _seat)
    : sge::input::focus::object{},
      fcppt::enable_shared_from_this<sge::wlinput::focus::object>{},
      impl_{_seat},
      data_{
          _log,
          fcppt::make_ref(*this),
          _xkb_context,
          fcppt::make_ref(_sge_window.get().system().awl_system().processor()),
          _window,
          _events},
      event_connection_{_sge_window.get().system().event_handler(sge::window::system_event_function{
          [this](awl::event::base const &_event)
          {
            return fcppt::optional::maybe(
                this->data_.repeat_timer_,
                [] { return awl::event::container{}; },
                [this, &_event](awl::timer::unique_ptr const &_timer) {
                  return awl::timer::match(_event, *_timer) ? this->on_key_repeat()
                                                            : awl::event::container{};
                });
          }})}
{
  ::wl_keyboard_add_listener(impl_.get(), &keyboard_listener, &data_);
}

sge::wlinput::focus::object::~object() = default;

sge::input::focus::shared_ptr sge::wlinput::focus::object::get_shared_ptr()
{
  return sge::input::focus::shared_ptr{this->fcppt_shared_from_this()};
}

awl::event::container sge::wlinput::focus::object::on_key_repeat()
{
  return fcppt::optional::to_container<awl::event::container>(fcppt::optional::map(
      data_.last_pressed_,
      [this](sge::input::key::code const _code)
      {
        return fcppt::unique_ptr_to_base<awl::event::base>(
            fcppt::make_unique_ptr<sge::input::focus::event::key_repeat>(
                this->get_shared_ptr(), sge::input::focus::key{_code}));
      }));
}
