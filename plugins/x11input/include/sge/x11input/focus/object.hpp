//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_X11INPUT_FOCUS_OBJECT_HPP_INCLUDED
#define SGE_X11INPUT_FOCUS_OBJECT_HPP_INCLUDED

#include <sge/input/focus/object.hpp>
#include <sge/input/key/code_fwd.hpp>
#include <sge/window/object_fwd.hpp>
#include <sge/window/object_ref.hpp>
#include <sge/x11input/device/id.hpp>
#include <sge/x11input/event/window_demuxer_ref.hpp>
#include <sge/x11input/focus/object_fwd.hpp>
#include <sge/x11input/key/repeated.hpp>
#include <sge/x11input/xim/const_optional_method_ref_fwd.hpp>
#include <sge/x11input/xim/context_fwd.hpp>
#include <awl/backends/x11/window/const_base_ref.hpp>
#include <awl/backends/x11/window/object_ref.hpp>
#include <awl/event/base_unique_ptr.hpp>
#include <awl/event/connection_unique_ptr.hpp>
#include <awl/event/container.hpp>
#include <fcppt/enable_shared_from_this_decl.hpp>
#include <fcppt/nonmovable.hpp>
#include <fcppt/unique_ptr_decl.hpp>
#include <fcppt/log/object_reference.hpp>
#include <fcppt/optional/object_decl.hpp>
#include <fcppt/signal/auto_connection.hpp>
#include <fcppt/config/external_begin.hpp>
#include <X11/extensions/XInput2.h>
#include <fcppt/config/external_end.hpp>

namespace sge::x11input::focus
{

class object // NOLINT(fuchsia-multiple-inheritance)
    : public sge::input::focus::object,
      public fcppt::enable_shared_from_this<sge::x11input::focus::object>
{
  FCPPT_NONMOVABLE(object);

public:
  object(
      sge::window::object_ref,
      fcppt::log::object_reference,
      awl::backends::x11::window::object_ref,
      sge::x11input::device::id,
      sge::x11input::event::window_demuxer_ref,
      sge::x11input::xim::const_optional_method_ref const &);

  ~object() override;

private:
  [[nodiscard]] sge::window::object &window() const override;

  [[nodiscard]] awl::event::container on_event(XIDeviceEvent const &);

  [[nodiscard]] awl::event::container on_key_press(XIDeviceEvent const &);

  [[nodiscard]] awl::event::base_unique_ptr on_key_release(XIDeviceEvent const &);

  [[nodiscard]] awl::event::base_unique_ptr on_focus_in();

  [[nodiscard]] awl::event::base_unique_ptr on_focus_out();

  [[nodiscard]] awl::event::base_unique_ptr
      process_key_down(sge::x11input::key::repeated, sge::input::key::code);

  sge::window::object_ref const sge_window_;

  fcppt::log::object_reference const log_;

  awl::backends::x11::window::const_base_ref const window_;

  using xim_context_unique_ptr = fcppt::unique_ptr<sge::x11input::xim::context>;

  using optional_xim_context_unique_ptr = fcppt::optional::object<xim_context_unique_ptr>;

  optional_xim_context_unique_ptr const xim_context_;

  using optional_connection_unique_ptr = fcppt::optional::object<awl::event::connection_unique_ptr>;

  optional_connection_unique_ptr const mask_connection_;

  fcppt::signal::auto_connection const event_connection_;
};

}

#endif
