//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/wlinput/xkb_context_ref.hpp>
#include <sge/wlinput/focus/data.hpp>
#include <sge/wlinput/focus/object_fwd.hpp>
#include <awl/backends/wayland/window/object_ref.hpp>
#include <awl/event/container_reference.hpp>
#include <awl/system/event/processor_ref.hpp>
#include <awl/timer/object.hpp>
#include <fcppt/reference_impl.hpp>
#include <fcppt/log/object_reference.hpp>
#include <fcppt/optional/object_impl.hpp>

sge::wlinput::focus::data::data(
    fcppt::log::object_reference const _log,
    fcppt::reference<sge::wlinput::focus::object> const _focus,
    sge::wlinput::xkb_context_ref const _xkb_context,
    awl::system::event::processor_ref const _processor,
    awl::backends::wayland::window::object_ref const _window,
    awl::event::container_reference const _events)
    : log_{_log},
      focus_{_focus},
      xkb_context_{_xkb_context},
      processor_{_processor},
      window_{_window},
      events_{_events},
      entered_{false},
      xkb_keymap_{},
      xkb_state_{},
      last_pressed_{},
      repeat_timer_{}
{
}

sge::wlinput::focus::data::~data() = default;
