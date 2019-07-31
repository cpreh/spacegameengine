//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/systems/impl/window/original_system.hpp>
#include <sge/systems/impl/window/system_base.hpp>
#include <sge/window/system.hpp>
#include <awl/system/create.hpp>
#include <awl/system/object.hpp>
#include <awl/system/event/processor.hpp>
#include <fcppt/log/context_fwd.hpp>


sge::systems::impl::window::original_system::original_system(
	fcppt::log::context &_log_context
)
:
	sge::systems::impl::window::system_base(),
	awl_system_{
		awl::system::create(
			_log_context
		)
	},
	system_{
		*awl_system_
	}
{
}

sge::systems::impl::window::original_system::~original_system()
{
}

sge::window::system &
sge::systems::impl::window::original_system::get()
{
	return
		system_;
}
