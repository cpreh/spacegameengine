//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_X11INPUT_MOUSE_AXIS_HPP_INCLUDED
#define SGE_X11INPUT_MOUSE_AXIS_HPP_INCLUDED

#include <sge/input/mouse/axis_fwd.hpp>
#include <sge/input/mouse/axis_info_container_fwd.hpp>
#include <sge/x11input/device/valuator/index.hpp>


namespace sge
{
namespace x11input
{
namespace mouse
{

sge::input::mouse::axis
axis(
	sge::x11input::device::valuator::index,
	sge::input::mouse::axis_info_container const &
);

}
}
}

#endif
