//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_X11INPUT_EVENT_IS_DEVICE_HPP_INCLUDED
#define SGE_X11INPUT_EVENT_IS_DEVICE_HPP_INCLUDED

#include <sge/x11input/event/device_type_set.hpp>
#include <fcppt/config/external_begin.hpp>
#include <brigand/sequences/contains.hpp>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace x11input
{
namespace event
{

template<
	typename Value
>
using
is_device
=
brigand::contains<
	sge::x11input::event::device_type_set,
	Value
>;

}
}
}

#endif
