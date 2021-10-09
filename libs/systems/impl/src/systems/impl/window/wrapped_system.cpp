//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/systems/wrapped_window.hpp>
#include <sge/systems/impl/window/system_base.hpp>
#include <sge/systems/impl/window/wrapped_system.hpp>
#include <sge/window/system.hpp>

sge::systems::impl::window::wrapped_system::wrapped_system(
    sge::systems::wrapped_window const &_parameters)
    : sge::systems::impl::window::system_base(), system_(_parameters.awl_system())
{
}

sge::systems::impl::window::wrapped_system::~wrapped_system() = default;

sge::window::system &sge::systems::impl::window::wrapped_system::get() { return system_; }
