//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_X11INPUT_EVENT_HANDLER_HPP_INCLUDED
#define SGE_X11INPUT_EVENT_HANDLER_HPP_INCLUDED

#include <awl/backends/x11/system/event/generic_fwd.hpp>
#include <awl/event/container.hpp>
#include <fcppt/function_impl.hpp>


namespace sge::x11input::event
{

using
handler
=
fcppt::function<
	awl::event::container (
		awl::backends::x11::system::event::generic const &
	)
>;

}

#endif
