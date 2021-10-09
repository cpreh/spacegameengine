//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_X11INPUT_EVENT_IS_DEVICE_HPP_INCLUDED
#define SGE_X11INPUT_EVENT_IS_DEVICE_HPP_INCLUDED

#include <sge/x11input/event/device_type_set.hpp>
#include <fcppt/mpl/set/contains.hpp>

namespace sge::x11input::event
{

template <typename Value>
using is_device = fcppt::mpl::set::contains<sge::x11input::event::device_type_set, Value>;

}

#endif
