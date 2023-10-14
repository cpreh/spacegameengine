//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_WLINPUT_FOCUS_DATA_HPP_INCLUDED
#define SGE_WLINPUT_FOCUS_DATA_HPP_INCLUDED

#include <sge/input/key/optional_code.hpp>
#include <sge/wlinput/xkb_context_ref.hpp>
#include <sge/wlinput/focus/object_fwd.hpp>
#include <sge/wlinput/focus/optional_keymap.hpp>
#include <sge/wlinput/focus/optional_state.hpp>
#include <awl/backends/wayland/window/object_ref.hpp>
#include <awl/event/container_reference.hpp>
#include <awl/system/event/processor_ref.hpp>
#include <awl/timer/unique_ptr.hpp>
#include <fcppt/nonmovable.hpp>
#include <fcppt/reference_impl.hpp>
#include <fcppt/log/object_reference.hpp>
#include <fcppt/optional/object_decl.hpp>

namespace sge::wlinput::focus
{

struct data
{
  FCPPT_NONMOVABLE(data);

  data(
      fcppt::log::object_reference,
      fcppt::reference<sge::wlinput::focus::object>,
      sge::wlinput::xkb_context_ref,
      awl::system::event::processor_ref,
      awl::backends::wayland::window::object_ref,
      awl::event::container_reference);

  ~data();

  fcppt::log::object_reference const log_; // NOLINT(misc-non-private-member-variables-in-classes)

  fcppt::reference<sge::wlinput::focus::object> const
      focus_; // NOLINT(misc-non-private-member-variables-in-classes)

  sge::wlinput::xkb_context_ref const
      xkb_context_; // NOLINT(misc-non-private-member-variables-in-classes)

  awl::system::event::processor_ref const
      processor_; // NOLINT(misc-non-private-member-variables-in-classes)

  awl::backends::wayland::window::object_ref const
      window_; // NOLINT(misc-non-private-member-variables-in-classes)

  awl::event::container_reference const
      events_; // NOLINT(misc-non-private-member-variables-in-classes)

  // NOLINTNEXTLINE(cppcoreguidelines-use-default-member-init,modernize-use-default-member-init)
  bool entered_; // NOLINT(misc-non-private-member-variables-in-classes)

  sge::wlinput::focus::optional_keymap
      xkb_keymap_; // NOLINT(misc-non-private-member-variables-in-classes)

  sge::wlinput::focus::optional_state
      xkb_state_; // NOLINT(misc-non-private-member-variables-in-classes)

  sge::input::key::optional_code
      last_pressed_; // NOLINT(misc-non-private-member-variables-in-classes)

  fcppt::optional::object<awl::timer::unique_ptr>
      repeat_timer_; // NOLINT(misc-non-private-member-variables-in-classes)
};

}

#endif
