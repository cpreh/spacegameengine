//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/systems/impl/window/quit.hpp>
#include <sge/window/event_function.hpp>
#include <sge/window/object.hpp> // NOLINT(misc-include-cleaner)
#include <sge/window/object_ref.hpp>
#include <sge/window/system.hpp> // NOLINT(misc-include-cleaner)
#include <sge/window/system_ref.hpp>
#include <awl/event/container.hpp>
#include <awl/main/exit_success.hpp>
#include <awl/window/event/base.hpp>
#include <awl/window/event/close.hpp>
#include <awl/window/event/destroy.hpp>
#include <fcppt/cast/dynamic_fun.hpp>
#include <fcppt/mpl/list/object.hpp>
#include <fcppt/optional/maybe_void.hpp>
#include <fcppt/preprocessor/disable_vc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>
#include <fcppt/variant/dynamic_cast.hpp>

FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_VC_WARNING(4355)
sge::systems::impl::window::quit::quit(
    sge::window::system_ref const _system, sge::window::object_ref const _window)
    : system_{_system},
      destroy_connection_{_window.get().event_handler(sge::window::event_function{
          [this](awl::window::event::base const &_event)
          {
            fcppt::optional::maybe_void(
                fcppt::variant::dynamic_cast_<
                    fcppt::mpl::list::
                        object<awl::window::event::destroy const, awl::window::event::close const>,
                    fcppt::cast::dynamic_fun>(_event),
                [this](auto const &) { this->system_.get().quit(awl::main::exit_success()); });

            return awl::event::container();
          }})}
{
}
FCPPT_PP_POP_WARNING

sge::systems::impl::window::quit::~quit() = default;
