//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/input/mouse/axis.hpp>
#include <sge/input/mouse/button.hpp>
#include <sge/input/mouse/button_pressed.hpp>
#include <sge/input/mouse/device.hpp>
#include <sge/input/mouse/info.hpp>
#include <sge/input/mouse/shared_ptr.hpp>
#include <sge/input/mouse/event/axis.hpp>
#include <sge/input/mouse/event/button.hpp>
#include <sge/window/object_fwd.hpp>
#include <sge/window/object_ref.hpp>
#include <sge/x11input/device/id.hpp>
#include <sge/x11input/device/valuator/accu.hpp>
#include <sge/x11input/device/valuator/index.hpp>
#include <sge/x11input/device/valuator/pair.hpp>
#include <sge/x11input/device/valuator/range.hpp>
#include <sge/x11input/event/device_function.hpp>
#include <sge/x11input/event/raw_demuxer.hpp> // NOLINT(misc-include-cleaner)
#include <sge/x11input/event/raw_demuxer_ref.hpp>
#include <sge/x11input/event/raw_function.hpp>
#include <sge/x11input/event/select.hpp>
#include <sge/x11input/event/type_c.hpp>
#include <sge/x11input/event/window_demuxer.hpp> // NOLINT(misc-include-cleaner)
#include <sge/x11input/event/window_demuxer_ref.hpp>
#include <sge/x11input/mouse/axis.hpp>
#include <sge/x11input/mouse/axis_value.hpp>
#include <sge/x11input/mouse/axis_value_accu_pair.hpp>
#include <sge/x11input/mouse/button.hpp>
#include <sge/x11input/mouse/device.hpp>
#include <sge/x11input/mouse/info.hpp>
#include <awl/backends/x11/window/base.hpp> // NOLINT(misc-include-cleaner)
#include <awl/backends/x11/window/const_base_ref.hpp>
#include <awl/event/base.hpp>
#include <awl/event/container.hpp>
#include <awl/event/optional_base_unique_ptr.hpp>
#include <fcppt/enable_shared_from_this_impl.hpp>
#include <fcppt/make_cref.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/text.hpp>
#include <fcppt/unique_ptr_to_base.hpp>
#include <fcppt/algorithm/map.hpp>
#include <fcppt/container/get_or_insert.hpp>
#include <fcppt/log/object_reference.hpp>
#include <fcppt/log/out.hpp>
#include <fcppt/log/warning.hpp>
#include <fcppt/mpl/list/object.hpp>
#include <fcppt/optional/cat.hpp>
#include <fcppt/optional/join.hpp>
#include <fcppt/optional/make_if.hpp>
#include <fcppt/optional/map.hpp>
#include <fcppt/optional/object_impl.hpp>
#include <fcppt/optional/to_container.hpp>
#include <fcppt/config/external_begin.hpp>
#include <X11/extensions/XI2.h>
#include <X11/extensions/XInput2.h>
#include <vector>
#include <fcppt/config/external_end.hpp>

sge::x11input::mouse::device::device(
    sge::window::object_ref const _sge_window,
    fcppt::log::object_reference const _log,
    awl::backends::x11::window::const_base_ref const _window,
    XIDeviceInfo const &_info,
    sge::x11input::event::window_demuxer_ref const _window_demuxer,
    sge::x11input::event::raw_demuxer_ref const _raw_demuxer)
    : sge::input::mouse::device{},
      fcppt::enable_shared_from_this<sge::x11input::mouse::device>{},
      sge_window_{_sge_window},
      log_{_log},
      accus_{},
      info_{sge::x11input::mouse::info(_window.get().display().get(), _info)},
      event_connection_{_window_demuxer.get().on_event(
          sge::x11input::device::id{_info.deviceid},
          sge::x11input::event::device_function{[this](XIDeviceEvent const &_event)
                                                { return this->on_event(_event); }})},
      raw_event_connection_{_raw_demuxer.get().on_event(
          sge::x11input::device::id{_info.deviceid},
          sge::x11input::event::raw_function{[this](XIRawEvent const &_event)
                                             { return this->on_raw_event(_event); }})}
{
  sge::x11input::device::id const id{_info.deviceid};

  sge::x11input::event::select<fcppt::mpl::list::object<
      sge::x11input::event::type_c<XI_ButtonPress>,
      sge::x11input::event::type_c<XI_ButtonRelease>>>(_window_demuxer.get(), id);

  sge::x11input::event::select<
      fcppt::mpl::list::object<sge::x11input::event::type_c<XI_RawMotion>>>(_raw_demuxer.get(), id);
}

sge::x11input::mouse::device::~device() = default;

sge::window::object &sge::x11input::mouse::device::window() const { return sge_window_.get(); }

sge::input::mouse::info const &sge::x11input::mouse::device::info() const { return info_; }

awl::event::container sge::x11input::mouse::device::on_event(XIDeviceEvent const &_event)
{
  switch (_event.evtype)
  {
  case XI_ButtonPress:
    return fcppt::optional::to_container<awl::event::container>(this->on_button_down(_event));
  case XI_ButtonRelease:
    return fcppt::optional::to_container<awl::event::container>(this->on_button_up(_event));
  default: break;
  }

  return awl::event::container{};
}

awl::event::container sge::x11input::mouse::device::on_raw_event(XIRawEvent const &_event)
{
  return _event.evtype == XI_RawMotion ? this->on_motion(_event) : awl::event::container{};
}

awl::event::container sge::x11input::mouse::device::on_motion(XIRawEvent const &_event)
{
  return fcppt::optional::cat<awl::event::container>(
      fcppt::algorithm::map<std::vector<awl::event::optional_base_unique_ptr>>(
          sge::x11input::device::valuator::range(fcppt::make_cref(_event.valuators)),
          [this](sge::x11input::device::valuator::pair const _valuator)
          { return this->process_valuator(_valuator); }));
}

awl::event::optional_base_unique_ptr sge::x11input::mouse::device::process_valuator(
    sge::x11input::device::valuator::pair const _valuator)
{
  return fcppt::optional::map(
      sge::x11input::mouse::axis(_valuator.index(), this->info_.axes()),
      [this, &_valuator](sge::input::mouse::axis const _axis)
      {
        sge::x11input::device::valuator::accu &accu{fcppt::container::get_or_insert(
            this->accus_,
            _valuator.index(),
            [](sge::x11input::device::valuator::index)
            { return sge::x11input::device::valuator::accu{0.}; })};

        sge::x11input::mouse::axis_value_accu_pair const result{
            sge::x11input::mouse::axis_value(accu, _valuator.value())};

        accu = result.second;

        return fcppt::unique_ptr_to_base<awl::event::base>(
            fcppt::make_unique_ptr<sge::input::mouse::event::axis>(
                sge::input::mouse::shared_ptr{this->fcppt_shared_from_this()},
                _axis,
                result.first));
      });
}

awl::event::optional_base_unique_ptr
sge::x11input::mouse::device::on_button_down(XIDeviceEvent const &_event)
{
  return this->button_event(_event, sge::input::mouse::button_pressed{true});
}

awl::event::optional_base_unique_ptr
sge::x11input::mouse::device::on_button_up(XIDeviceEvent const &_event)
{
  return this->button_event(_event, sge::input::mouse::button_pressed{false});
}

awl::event::optional_base_unique_ptr sge::x11input::mouse::device::button_event(
    XIDeviceEvent const &_event, sge::input::mouse::button_pressed const _pressed)
{
  return fcppt::optional::join(fcppt::optional::make_if(
      (_event.flags // NOLINT(hicpp-signed-bitwise)
       & XIPointerEmulated // NOLINT(hicpp-signed-bitwise)
       ) == 0,
      [this, &_event, _pressed]
      {
        fcppt::optional::object<sge::input::mouse::button> const button(
            sge::x11input::mouse::button(_event, info_.buttons()));

        if (!button.has_value())
        {
          FCPPT_LOG_WARNING(
              this->log_.get(),
              fcppt::log::out << FCPPT_TEXT("Invalid mouse button id ") << _event.detail)
        }

        return fcppt::optional::map(
            button,
            [this, _pressed](sge::input::mouse::button const &_button)
            {
              return fcppt::unique_ptr_to_base<awl::event::base>(
                  fcppt::make_unique_ptr<sge::input::mouse::event::button>(
                      sge::input::mouse::shared_ptr{this->fcppt_shared_from_this()},
                      _button,
                      _pressed));
            });
      }));
}
