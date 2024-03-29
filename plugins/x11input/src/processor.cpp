//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/input/exception.hpp>
#include <sge/input/processor.hpp>
#include <sge/input/cursor/container.hpp>
#include <sge/input/cursor/object.hpp>
#include <sge/input/cursor/shared_ptr.hpp>
#include <sge/input/cursor/event/discover.hpp>
#include <sge/input/cursor/event/remove.hpp>
#include <sge/input/focus/container.hpp>
#include <sge/input/focus/object.hpp>
#include <sge/input/focus/shared_ptr.hpp>
#include <sge/input/focus/event/discover.hpp>
#include <sge/input/focus/event/remove.hpp>
#include <sge/input/joypad/container.hpp>
#include <sge/input/keyboard/container.hpp>
#include <sge/input/keyboard/device.hpp>
#include <sge/input/keyboard/shared_ptr.hpp>
#include <sge/input/keyboard/event/discover.hpp>
#include <sge/input/keyboard/event/remove.hpp>
#include <sge/input/mouse/container.hpp>
#include <sge/input/mouse/device.hpp>
#include <sge/input/mouse/shared_ptr.hpp>
#include <sge/input/mouse/event/discover.hpp>
#include <sge/input/mouse/event/remove.hpp>
#include <sge/window/object.hpp>
#include <sge/window/object_ref.hpp>
#include <sge/window/system.hpp>
#include <sge/window/system_event_function.hpp>
#include <sge/x11input/opcode.hpp>
#include <sge/x11input/processor.hpp>
#include <sge/x11input/cursor/object.hpp>
#include <sge/x11input/device/id.hpp>
#include <sge/x11input/device/insert.hpp>
#include <sge/x11input/device/remove.hpp>
#include <sge/x11input/device/info/multi.hpp>
#include <sge/x11input/device/info/single.hpp>
#include <sge/x11input/event/base.hpp>
#include <sge/x11input/event/concrete_handler.hpp>
#include <sge/x11input/event/device_type_set.hpp>
#include <sge/x11input/event/handler.hpp>
#include <sge/x11input/event/make_handler.hpp>
#include <sge/x11input/event/type.hpp>
#include <sge/x11input/event/type_c.hpp>
#include <sge/x11input/focus/object.hpp>
#include <sge/x11input/keyboard/device.hpp>
#include <sge/x11input/mouse/device.hpp>
#include <sge/x11input/xim/create_method_opt.hpp>
#include <sge/x11input/xim/method.hpp>
#include <awl/backends/x11/cursor/create_invisible.hpp>
#include <awl/backends/x11/cursor/object.hpp> // NOLINT(misc-include-cleaner)
#include <awl/backends/x11/system/event/generic.hpp>
#include <awl/backends/x11/window/base.hpp>
#include <awl/backends/x11/window/object.hpp>
#include <awl/backends/x11/window/root.hpp>
#include <awl/event/base.hpp>
#include <awl/event/container.hpp>
#include <awl/event/optional_base_unique_ptr.hpp>
#include <awl/window/object.hpp> // NOLINT(misc-include-cleaner)
#include <fcppt/make_cref.hpp>
#include <fcppt/make_int_range_count.hpp>
#include <fcppt/make_ref.hpp>
#include <fcppt/make_shared_ptr.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/reference_impl.hpp>
#include <fcppt/reference_to_base.hpp>
#include <fcppt/reference_to_const.hpp>
#include <fcppt/shared_ptr_impl.hpp>
#include <fcppt/tag_type.hpp>
#include <fcppt/text.hpp>
#include <fcppt/unique_ptr_to_base.hpp>
#include <fcppt/use.hpp>
#include <fcppt/algorithm/loop_break_mpl.hpp> // NOLINT(misc-include-cleaner)
#include <fcppt/algorithm/map.hpp>
#include <fcppt/cast/dynamic.hpp>
#include <fcppt/container/find_opt_mapped.hpp>
#include <fcppt/container/join.hpp>
#include <fcppt/container/map_values_copy.hpp>
#include <fcppt/log/object_reference.hpp>
#include <fcppt/mpl/set/to_list.hpp>
#include <fcppt/optional/bind.hpp>
#include <fcppt/optional/cat.hpp>
#include <fcppt/optional/deref.hpp>
#include <fcppt/optional/from.hpp>
#include <fcppt/optional/join.hpp>
#include <fcppt/optional/make_if.hpp>
#include <fcppt/optional/map.hpp>
#include <fcppt/optional/object_impl.hpp> // NOLINT(misc-include-cleaner)
#include <fcppt/optional/to_exception.hpp>
#include <fcppt/preprocessor/ignore_unsafe_buffer_usage.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>
#include <fcppt/config/external_begin.hpp>
#include <X11/extensions/XI2.h>
#include <X11/extensions/XInput2.h>
#include <vector>
#include <fcppt/config/external_end.hpp>

sge::x11input::processor::processor(
    fcppt::log::object_reference const _log,
    sge::window::object_ref const _window,
    sge::x11input::opcode const _opcode)
    : sge::input::processor{},
      log_{_log},
      opcode_{_opcode},
      window_{_window},
      x11_window_{fcppt::optional::to_exception(
          fcppt::cast::dynamic<awl::backends::x11::window::object>(_window.get().awl_object()),
          []
          {
            return sge::input::exception{
                FCPPT_TEXT("Window passed to x11input::processor is not an X11 window.")};
          })},
      root_window_{awl::backends::x11::window::root(
          x11_window_.get().display(), x11_window_.get().screen())},
      invisible_cursor_{awl::backends::x11::cursor::create_invisible(x11_window_.get().display())},
      xim_method_{sge::x11input::xim::create_method_opt(_log.get(), x11_window_.get().display())},
      window_demuxer_{fcppt::reference_to_const(
          fcppt::reference_to_base<awl::backends::x11::window::base>(x11_window_))},
      raw_demuxer_{fcppt::make_cref(*root_window_)},
      foci_{},
      keyboards_{},
      cursors_{},
      mice_{},
      handlers_(fcppt::container::join(
          fcppt::algorithm::map<handler_map>(
              fcppt::mpl::set::to_list<sge::x11input::event::device_type_set>{},
              [this](auto const _value)
              {
                FCPPT_USE(_value);

                return sge::x11input::event::make_handler<fcppt::tag_type<decltype(_value)>>(
                    sge::x11input::event::concrete_handler<XIDeviceEvent>{
                        [this](XIDeviceEvent const &_event)
                        { return this->window_demuxer_.call(_event); }});
              }),
          handler_map{
              sge::x11input::event::make_handler<sge::x11input::event::type_c<XI_HierarchyChanged>>(
                  sge::x11input::event::concrete_handler<XIHierarchyEvent>{
                      [this](XIHierarchyEvent const &_event)
                      { return this->hierarchy_event(_event); }}),
              sge::x11input::event::make_handler<sge::x11input::event::type_c<XI_RawMotion>>(
                  sge::x11input::event::concrete_handler<XIRawEvent>{
                      [this](XIRawEvent const &_event)
                      { return this->raw_demuxer_.call(_event); }})})),
      event_connection_{_window.get().system().event_handler(sge::window::system_event_function{
          [this](awl::event::base const &_event) { return this->system_event(_event); }})}
{
  sge::x11input::device::info::multi const current_devices(x11_window_.get().display());

  for (auto const &device : current_devices)
  {
    FCPPT_USE(this->add_device(device));
  }
}

sge::x11input::processor::~processor() = default;

sge::window::object &sge::x11input::processor::window() const { return window_.get(); }

sge::input::cursor::container sge::x11input::processor::cursors() const
{
  return fcppt::container::map_values_copy<sge::input::cursor::container>(cursors_);
}

sge::input::focus::container sge::x11input::processor::foci() const
{
  return fcppt::container::map_values_copy<sge::input::focus::container>(foci_);
}

sge::input::joypad::container sge::x11input::processor::joypads() const
{
  return sge::input::joypad::container{};
}

sge::input::keyboard::container sge::x11input::processor::keyboards() const
{
  return fcppt::container::map_values_copy<sge::input::keyboard::container>(keyboards_);
}

sge::input::mouse::container sge::x11input::processor::mice() const
{
  return fcppt::container::map_values_copy<sge::input::mouse::container>(mice_);
}

awl::event::container sge::x11input::processor::system_event(awl::event::base const &_event)
{
  return fcppt::optional::from(
      fcppt::optional::bind(
          fcppt::cast::dynamic<awl::backends::x11::system::event::generic const>(_event),
          [this](fcppt::reference<awl::backends::x11::system::event::generic const> const
                     _generic_event)
          {
            return fcppt::optional::join(fcppt::optional::make_if(
                _generic_event.get().get().extension == this->opcode_.get(),
                [&_generic_event, this] { return this->extension_event(_generic_event.get()); }));
          }),
      [] { return awl::event::container{}; });
}

sge::x11input::processor::optional_event_container
sge::x11input::processor::extension_event(awl::backends::x11::system::event::generic const &_event)
{
  XIEvent const generic_event{sge::x11input::event::base(_event)};

  return fcppt::optional::map(
      fcppt::container::find_opt_mapped(
          handlers_, sge::x11input::event::type{generic_event.evtype}),
      [&_event](fcppt::reference<sge::x11input::event::handler const> const _handler)
      { return _handler.get()(_event); });
}

awl::event::container sge::x11input::processor::hierarchy_event(XIHierarchyEvent const &_event)
{
FCPPT_PP_PUSH_WARNING
FCPPT_PP_IGNORE_UNSAFE_BUFFER_USAGE

  return fcppt::optional::cat<awl::event::container>(
      fcppt::algorithm::map<std::vector<awl::event::optional_base_unique_ptr>>(
          fcppt::make_int_range_count(_event.num_info),
          [&_event, this](int const _index)
          {
            return this->hierarchy_info(
                // NOLINTNEXTLINE(cppcoreguidelines-pro-bounds-pointer-arithmetic)
                _event.info[_index]);
          }));

FCPPT_PP_POP_WARNING
}

awl::event::optional_base_unique_ptr
sge::x11input::processor::hierarchy_info(XIHierarchyInfo const &_info)
{
  if ((_info.flags & XIMasterAdded) != 0 // NOLINT(hicpp-signed-bitwise)
      || (_info.flags & XISlaveAdded) != 0 // NOLINT(hicpp-signed-bitwise)
  )
  {
    sge::x11input::device::info::single const info{
        x11_window_.get().display(), sge::x11input::device::id{_info.deviceid}};

    return fcppt::optional::bind(
        info.get(),
        [this](fcppt::reference<XIDeviceInfo const> const _device_info)
        { return this->add_device(_device_info.get()); });
  }

  if ((_info.flags & XIMasterRemoved) != 0 // NOLINT(hicpp-signed-bitwise)
      || (_info.flags & XISlaveRemoved) != 0 // NOLINT(hicpp-signed-bitwise)
  )
  {
    return this->remove_device(_info);
  }

  return awl::event::optional_base_unique_ptr{};
}

awl::event::optional_base_unique_ptr sge::x11input::processor::add_device(XIDeviceInfo const &_info)
{
  switch (_info.use)
  {
  case XIMasterKeyboard:
    return awl::event::optional_base_unique_ptr{fcppt::unique_ptr_to_base<awl::event::base>(
        fcppt::make_unique_ptr<sge::input::focus::event::discover>(this->add_focus(_info)))};
  case XISlaveKeyboard:
    return awl::event::optional_base_unique_ptr{fcppt::unique_ptr_to_base<awl::event::base>(
        fcppt::make_unique_ptr<sge::input::keyboard::event::discover>(this->add_keyboard(_info)))};
  case XIMasterPointer:
    return awl::event::optional_base_unique_ptr{fcppt::unique_ptr_to_base<awl::event::base>(
        fcppt::make_unique_ptr<sge::input::cursor::event::discover>(this->add_cursor(_info)))};
  case XISlavePointer:
    return awl::event::optional_base_unique_ptr{fcppt::unique_ptr_to_base<awl::event::base>(
        fcppt::make_unique_ptr<sge::input::mouse::event::discover>(this->add_mouse(_info)))};
  default: break;
  }

  return awl::event::optional_base_unique_ptr{};
}

awl::event::optional_base_unique_ptr
sge::x11input::processor::remove_device(XIHierarchyInfo const &_info)
{
  sge::x11input::device::id const id{_info.deviceid};

  switch (_info.use)
  {
  case XIMasterKeyboard:
    return awl::event::optional_base_unique_ptr{fcppt::unique_ptr_to_base<awl::event::base>(
        fcppt::make_unique_ptr<sge::input::focus::event::remove>(
            sge::x11input::device::remove(fcppt::make_ref(foci_), id)))};
  case XISlaveKeyboard:
    return awl::event::optional_base_unique_ptr{fcppt::unique_ptr_to_base<awl::event::base>(
        fcppt::make_unique_ptr<sge::input::keyboard::event::remove>(
            sge::x11input::device::remove(fcppt::make_ref(keyboards_), id)))};
  case XIMasterPointer:
    return awl::event::optional_base_unique_ptr{fcppt::unique_ptr_to_base<awl::event::base>(
        fcppt::make_unique_ptr<sge::input::cursor::event::remove>(
            sge::x11input::device::remove(fcppt::make_ref(cursors_), id)))};
  case XISlavePointer:
    return awl::event::optional_base_unique_ptr{fcppt::unique_ptr_to_base<awl::event::base>(
        fcppt::make_unique_ptr<sge::input::mouse::event::remove>(
            sge::x11input::device::remove(fcppt::make_ref(mice_), id)))};
  default: break;
  }

  return awl::event::optional_base_unique_ptr{};
}

sge::input::focus::shared_ptr sge::x11input::processor::add_focus(XIDeviceInfo const &_info)
{
  return sge::x11input::device::insert(
      foci_,
      sge::x11input::device::id{_info.deviceid},
      fcppt::shared_ptr<sge::input::focus::object>{
          fcppt::make_shared_ptr<sge::x11input::focus::object>(
              window_,
              log_,
              x11_window_,
              sge::x11input::device::id{_info.deviceid},
              fcppt::make_ref(window_demuxer_),
              fcppt::optional::map(
                  fcppt::optional::deref(xim_method_),
                  [](fcppt::reference<sge::x11input::xim::method> const _method)
                  { return fcppt::make_cref(_method.get()); }))});
}

sge::input::keyboard::shared_ptr sge::x11input::processor::add_keyboard(XIDeviceInfo const &_info)
{
  return sge::x11input::device::insert(
      keyboards_,
      sge::x11input::device::id{_info.deviceid},
      fcppt::shared_ptr<sge::input::keyboard::device>{
          fcppt::make_shared_ptr<sge::x11input::keyboard::device>(
              window_,
              sge::x11input::device::id{_info.deviceid},
              fcppt::reference_to_const(
                  fcppt::reference_to_base<awl::backends::x11::window::base>(x11_window_)),
              fcppt::make_ref(window_demuxer_))});
}

sge::input::cursor::shared_ptr sge::x11input::processor::add_cursor(XIDeviceInfo const &_info)
{
  return sge::x11input::device::insert(
      cursors_,
      sge::x11input::device::id{_info.deviceid},
      fcppt::shared_ptr<sge::input::cursor::object>{
          fcppt::make_shared_ptr<sge::x11input::cursor::object>(
              window_,
              log_,
              fcppt::reference_to_const(
                  fcppt::reference_to_base<awl::backends::x11::window::base>(x11_window_)),
              _info,
              fcppt::make_ref(window_demuxer_),
              fcppt::make_ref(*invisible_cursor_))});
}

sge::input::mouse::shared_ptr sge::x11input::processor::add_mouse(XIDeviceInfo const &_info)
{
  return sge::x11input::device::insert(
      mice_,
      sge::x11input::device::id{_info.deviceid},
      fcppt::shared_ptr<sge::input::mouse::device>{
          fcppt::make_shared_ptr<sge::x11input::mouse::device>(
              window_,
              log_,
              fcppt::reference_to_const(
                  fcppt::reference_to_base<awl::backends::x11::window::base>(x11_window_)),
              _info,
              fcppt::make_ref(window_demuxer_),
              fcppt::make_ref(raw_demuxer_))});
}
