//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/systems/window_fwd.hpp>
#include <sge/systems/impl/window/make_system_base.hpp>
#include <sge/systems/impl/window/system.hpp>
#include <sge/systems/impl/window/system_base.hpp>
#include <sge/window/system_fwd.hpp>
#include <fcppt/log/context_reference.hpp>

sge::systems::impl::window::system::system(
    fcppt::log::context_reference const _log_context, sge::systems::window const &_parameters)
    : base_{sge::systems::impl::window::make_system_base(_log_context, _parameters)}
{
}

sge::systems::impl::window::system::~system() = default;

sge::window::system &sge::systems::impl::window::system::get() const { return base_->get(); }
