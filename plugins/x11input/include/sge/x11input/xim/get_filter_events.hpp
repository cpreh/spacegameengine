//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_X11INPUT_XIM_GET_FILTER_EVENTS_HPP_INCLUDED
#define SGE_X11INPUT_XIM_GET_FILTER_EVENTS_HPP_INCLUDED

#include <sge/x11input/xim/context_fwd.hpp>
#include <awl/backends/x11/window/event/mask.hpp>


namespace sge
{
namespace x11input
{
namespace xim
{

awl::backends::x11::window::event::mask
get_filter_events(
	sge::x11input::xim::context const &
);

}
}
}

#endif
