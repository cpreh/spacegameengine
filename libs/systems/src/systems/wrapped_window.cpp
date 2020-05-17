//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/systems/wrapped_window.hpp>
#include <awl/system/reference.hpp>
#include <awl/window/reference.hpp>


sge::systems::wrapped_window::wrapped_window(
	awl::system::reference const _awl_system,
	awl::window::reference const _awl_window
)
:
	awl_system_{
		_awl_system
	},
	awl_window_{
		_awl_window
	}
{
}

awl::system::reference
sge::systems::wrapped_window::awl_system() const
{
	return
		awl_system_;
}

awl::window::reference
sge::systems::wrapped_window::awl_window() const
{
	return
		awl_window_;
}
