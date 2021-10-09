//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/systems/original_window_fwd.hpp>
#include <sge/systems/window.hpp>
#include <sge/systems/wrapped_window_fwd.hpp>
#include <sge/systems/impl/window/make_system_base.hpp>
#include <sge/systems/impl/window/original_system.hpp>
#include <sge/systems/impl/window/system_base.hpp>
#include <sge/systems/impl/window/system_base_unique_ptr.hpp>
#include <sge/systems/impl/window/wrapped_system.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/unique_ptr_to_base.hpp>
#include <fcppt/log/context_reference.hpp>
#include <fcppt/variant/match.hpp>

sge::systems::impl::window::system_base_unique_ptr sge::systems::impl::window::make_system_base(
    fcppt::log::context_reference const _log_context, sge::systems::window const &_parameters)
{
  return fcppt::variant::match(
      _parameters.source(),
      [&_log_context](sge::systems::original_window const &)
      {
        return fcppt::unique_ptr_to_base<sge::systems::impl::window::system_base>(
            fcppt::make_unique_ptr<sge::systems::impl::window::original_system>(_log_context));
      },
      [](sge::systems::wrapped_window const &_wrapped)
      {
        return fcppt::unique_ptr_to_base<sge::systems::impl::window::system_base>(
            fcppt::make_unique_ptr<sge::systems::impl::window::wrapped_system>(_wrapped));
      });
}
