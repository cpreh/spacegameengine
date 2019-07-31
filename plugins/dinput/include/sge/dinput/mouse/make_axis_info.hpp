//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_DINPUT_MOUSE_MAKE_AXIS_INFO_HPP_INCLUDED
#define SGE_DINPUT_MOUSE_MAKE_AXIS_INFO_HPP_INCLUDED

#include <sge/dinput/di.hpp>
#include <sge/input/mouse/axis_info_fwd.hpp>


namespace sge
{
namespace dinput
{
namespace mouse
{

sge::input::mouse::axis_info const
make_axis_info(
	DIDEVICEOBJECTINSTANCE const &
);

}
}
}

#endif
