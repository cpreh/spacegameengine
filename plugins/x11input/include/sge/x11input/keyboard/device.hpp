//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_X11INPUT_KEYBOARD_DEVICE_HPP_INCLUDED
#define SGE_X11INPUT_KEYBOARD_DEVICE_HPP_INCLUDED

#include <sge/input/key/pressed.hpp>
#include <sge/input/keyboard/device.hpp>
#include <sge/window/object_fwd.hpp>
#include <sge/window/object_ref.hpp>
#include <sge/x11input/device/id.hpp>
#include <sge/x11input/event/window_demuxer_ref.hpp>
#include <sge/x11input/keyboard/device_fwd.hpp>
#include <awl/backends/x11/window/const_base_ref.hpp>
#include <awl/event/base_unique_ptr.hpp>
#include <awl/event/container.hpp>
#include <awl/event/optional_base_unique_ptr.hpp>
#include <fcppt/enable_shared_from_this_decl.hpp>
#include <fcppt/nonmovable.hpp>
#include <fcppt/signal/auto_connection.hpp>
#include <fcppt/config/external_begin.hpp>
#include <X11/extensions/XI2.h>
#include <fcppt/config/external_end.hpp>

namespace sge::x11input::keyboard
{

class device // NOLINT(fuchsia-multiple-inheritance)
    : public sge::input::keyboard::device,
      public fcppt::enable_shared_from_this<sge::x11input::keyboard::device>
{
  FCPPT_NONMOVABLE(device);

public:
  device(
      sge::window::object_ref,
      sge::x11input::device::id,
      awl::backends::x11::window::const_base_ref,
      sge::x11input::event::window_demuxer_ref);

  ~device() override;

private:
  [[nodiscard]] sge::window::object &window() const override;

  [[nodiscard]] awl::event::container on_event(XIDeviceEvent const &);

  [[nodiscard]] awl::event::optional_base_unique_ptr on_key_press(XIDeviceEvent const &);

  [[nodiscard]] awl::event::base_unique_ptr on_key_release(XIDeviceEvent const &);

  [[nodiscard]] awl::event::base_unique_ptr
  make_key_event(XIDeviceEvent const &, sge::input::key::pressed);

  sge::window::object_ref const sge_window_;

  awl::backends::x11::window::const_base_ref const window_;

  fcppt::signal::auto_connection const event_connection_;
};

}

#endif
