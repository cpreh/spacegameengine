//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_X11INPUT_DEVICE_VALUATOR_MAKE_ANY_HPP_INCLUDED
#define SGE_X11INPUT_DEVICE_VALUATOR_MAKE_ANY_HPP_INCLUDED

#include <sge/x11input/device/valuator/any.hpp>
#include <fcppt/config/external_begin.hpp>
#include <X11/extensions/XInput2.h>
#include <fcppt/config/external_end.hpp>


namespace sge::x11input::device::valuator
{

sge::x11input::device::valuator::any
make_any(
	XIValuatorClassInfo const &
);

}

#endif
