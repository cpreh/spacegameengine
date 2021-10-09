//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_X11INPUT_DEVICE_INFO_CLASS_MAP_HPP_INCLUDED
#define SGE_X11INPUT_DEVICE_INFO_CLASS_MAP_HPP_INCLUDED

#include <sge/x11input/device/info/make_class_pair.hpp>
#include <fcppt/mpl/map/object.hpp>
#include <fcppt/config/external_begin.hpp>
#include <X11/extensions/XI2.h>
#include <X11/extensions/XInput2.h>
#include <fcppt/config/external_end.hpp>

namespace sge::x11input::device::info
{

using class_map = fcppt::mpl::map::object<
    SGE_X11INPUT_DEVICE_INFO_MAKE_CLASS_PAIR(XIButtonClass),
    SGE_X11INPUT_DEVICE_INFO_MAKE_CLASS_PAIR(XIValuatorClass),
    SGE_X11INPUT_DEVICE_INFO_MAKE_CLASS_PAIR(XIKeyClass),
    SGE_X11INPUT_DEVICE_INFO_MAKE_CLASS_PAIR(XIScrollClass)>;

}

#endif
