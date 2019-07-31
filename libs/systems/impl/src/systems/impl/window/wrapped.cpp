//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/systems/wrapped_window.hpp>
#include <sge/systems/impl/window/base.hpp>
#include <sge/systems/impl/window/wrapped.hpp>
#include <sge/window/object.hpp>
#include <sge/window/system_fwd.hpp>


sge::systems::impl::window::wrapped::wrapped(
	sge::systems::wrapped_window const &_parameters,
	sge::window::system &_system
)
:
	sge::systems::impl::window::base(),
	window_{
		_system,
		_parameters.awl_window()
	}
{
}

sge::systems::impl::window::wrapped::~wrapped()
{
}

sge::window::object &
sge::systems::impl::window::wrapped::get() const
{
	return
		window_;
}
