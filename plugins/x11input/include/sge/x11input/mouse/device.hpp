//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_X11INPUT_MOUSE_DEVICE_HPP_INCLUDED
#define SGE_X11INPUT_MOUSE_DEVICE_HPP_INCLUDED

#include <sge/input/mouse/button_pressed.hpp>
#include <sge/input/mouse/device.hpp>
#include <sge/input/mouse/info.hpp>
#include <sge/window/object_fwd.hpp>
#include <sge/window/object_ref.hpp>
#include <sge/x11input/device/valuator/accu_map.hpp>
#include <sge/x11input/device/valuator/pair_fwd.hpp>
#include <sge/x11input/event/raw_demuxer_ref.hpp>
#include <sge/x11input/event/window_demuxer_ref.hpp>
#include <sge/x11input/mouse/device_fwd.hpp>
#include <awl/backends/x11/window/const_base_ref.hpp>
#include <awl/event/container.hpp>
#include <awl/event/optional_base_unique_ptr.hpp>
#include <fcppt/enable_shared_from_this_decl.hpp>
#include <fcppt/nonmovable.hpp>
#include <fcppt/log/object_reference.hpp>
#include <fcppt/signal/auto_connection.hpp>
#include <fcppt/config/external_begin.hpp>
#include <X11/extensions/XInput2.h>
#include <fcppt/config/external_end.hpp>

namespace sge::x11input::mouse
{

class device // NOLINT(fuchsia-multiple-inheritance)
    : public sge::input::mouse::device,
      public fcppt::enable_shared_from_this<sge::x11input::mouse::device>
{
  FCPPT_NONMOVABLE(device);

public:
  device(
      sge::window::object_ref,
      fcppt::log::object_reference,
      awl::backends::x11::window::const_base_ref,
      XIDeviceInfo const &,
      sge::x11input::event::window_demuxer_ref,
      sge::x11input::event::raw_demuxer_ref);

  ~device() override;

private:
  [[nodiscard]] sge::window::object &window() const override;

  [[nodiscard]] sge::input::mouse::info const &info() const override;

  [[nodiscard]] awl::event::container on_event(XIDeviceEvent const &);

  [[nodiscard]] awl::event::container on_raw_event(XIRawEvent const &);

  [[nodiscard]] awl::event::container on_motion(XIRawEvent const &);

  [[nodiscard]] awl::event::optional_base_unique_ptr
      process_valuator(sge::x11input::device::valuator::pair);

  [[nodiscard]] awl::event::optional_base_unique_ptr on_button_down(XIDeviceEvent const &);

  [[nodiscard]] awl::event::optional_base_unique_ptr on_button_up(XIDeviceEvent const &);

  [[nodiscard]] awl::event::optional_base_unique_ptr
  button_event(XIDeviceEvent const &, sge::input::mouse::button_pressed);

  sge::window::object_ref const sge_window_;

  fcppt::log::object_reference const log_;

  sge::x11input::device::valuator::accu_map accus_;

  sge::input::mouse::info const info_;

  fcppt::signal::auto_connection const event_connection_;

  fcppt::signal::auto_connection const raw_event_connection_;
};

}

#endif
