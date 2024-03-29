//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_X11INPUT_MOUSE_AXIS_VALUE_HPP_INCLUDED
#define SGE_X11INPUT_MOUSE_AXIS_VALUE_HPP_INCLUDED

#include <sge/x11input/device/valuator/accu.hpp>
#include <sge/x11input/device/valuator/value.hpp>
#include <sge/x11input/mouse/axis_value_accu_pair.hpp>

namespace sge::x11input::mouse
{

sge::x11input::mouse::axis_value_accu_pair
    axis_value(sge::x11input::device::valuator::accu, sge::x11input::device::valuator::value);

}

#endif
