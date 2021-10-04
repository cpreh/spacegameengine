//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_SYSTEMS_QUIT_ON_ESCAPE_HPP_INCLUDED
#define SGE_SYSTEMS_QUIT_ON_ESCAPE_HPP_INCLUDED

#include <sge/systems/instance_impl.hpp>
#include <sge/systems/detail/quit_on_escape.hpp>
#include <awl/event/base_fwd.hpp>


namespace sge::systems
{

template<
	typename... Choices
>
void
quit_on_escape(
	sge::systems::instance<
		Choices...
	> const &_instance,
	awl::event::base const &_event
)
{
	return
		sge::systems::detail::quit_on_escape(
			_instance.window_system(),
			_event
		);
}

}

#endif
