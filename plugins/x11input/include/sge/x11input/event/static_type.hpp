//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_X11INPUT_EVENT_STATIC_TYPE_HPP_INCLUDED
#define SGE_X11INPUT_EVENT_STATIC_TYPE_HPP_INCLUDED

#include <sge/x11input/event/is_device.hpp>
#include <sge/x11input/event/is_hierarchy.hpp>
#include <sge/x11input/event/is_raw.hpp>
#include <fcppt/unit.hpp>
#include <fcppt/config/external_begin.hpp>
#include <X11/extensions/XInput2.h>
#include <type_traits>
#include <fcppt/config/external_end.hpp>


namespace sge::x11input::event
{

template<
	typename Value
>
using
static_type
=
std::conditional_t<
	sge::x11input::event::is_raw<
		Value
	>::value,
	XIRawEvent,
	std::conditional_t<
		sge::x11input::event::is_device<
			Value
		>::value,
		XIDeviceEvent,
		std::conditional_t<
			sge::x11input::event::is_hierarchy<
				Value
			>::value,
			XIHierarchyEvent,
			fcppt::unit
		>
	>
>;

}

#endif
