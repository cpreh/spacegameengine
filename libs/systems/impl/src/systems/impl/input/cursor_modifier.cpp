//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/input/processor.hpp>
#include <sge/input/cursor/mode.hpp>
#include <sge/input/cursor/object.hpp> // NOLINT(misc-include-cleaner)
#include <sge/input/cursor/shared_ptr.hpp>
#include <sge/input/cursor/event/discover.hpp>
#include <sge/systems/cursor_option.hpp>
#include <sge/systems/cursor_option_field.hpp>
#include <sge/systems/impl/input/cursor_modifier.hpp>
#include <sge/window/event_function.hpp>
#include <sge/window/object.hpp> // NOLINT(misc-include-cleaner)
#include <sge/window/object_ref.hpp>
#include <awl/event/container.hpp>
#include <awl/window/event/base.hpp>
#include <fcppt/reference_impl.hpp>
#include <fcppt/cast/dynamic.hpp>
#include <fcppt/container/bitfield/operators.hpp>
#include <fcppt/optional/maybe_void.hpp>
#include <fcppt/preprocessor/disable_vc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>

FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_VC_WARNING(4355)
sge::systems::impl::input::cursor_modifier::cursor_modifier(
    sge::input::processor const &_processor,
    sge::window::object_ref const _window,
    sge::systems::cursor_option_field const &_options)
    : options_{_options},
      connection_{_window.get().event_handler(sge::window::event_function{
          [this](awl::window::event::base const &_event) { return this->on_event(_event); }})}
{
  if (this->options_ & sge::systems::cursor_option::exclusive)
  {
    for (sge::input::cursor::shared_ptr const &cursor : _processor.cursors())
    {
      cursor->mode(sge::input::cursor::mode::exclusive);
    }
  }
}
FCPPT_PP_POP_WARNING

sge::systems::impl::input::cursor_modifier::~cursor_modifier() = default;

awl::event::container
sge::systems::impl::input::cursor_modifier::on_event(awl::window::event::base const &_event) const
{
  if (this->options_ & sge::systems::cursor_option::exclusive)
  {
    fcppt::optional::maybe_void(
        fcppt::cast::dynamic<sge::input::cursor::event::discover const>(_event),
        [](fcppt::reference<sge::input::cursor::event::discover const> const _discover)
        { _discover.get().cursor()->mode(sge::input::cursor::mode::exclusive); });
  }

  return awl::event::container();
}
