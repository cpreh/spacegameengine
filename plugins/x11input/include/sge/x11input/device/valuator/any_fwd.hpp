//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_X11INPUT_DEVICE_VALUATOR_ANY_FWD_HPP_INCLUDED
#define SGE_X11INPUT_DEVICE_VALUATOR_ANY_FWD_HPP_INCLUDED

#include <sge/x11input/device/valuator/absolute_fwd.hpp>
#include <sge/x11input/device/valuator/relative_fwd.hpp>
#include <fcppt/variant/object_fwd.hpp>

namespace sge::x11input::device::valuator
{

using any = fcppt::variant::
    object<sge::x11input::device::valuator::absolute, sge::x11input::device::valuator::relative>;

}

#endif
