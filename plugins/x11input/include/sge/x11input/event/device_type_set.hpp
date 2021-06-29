//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_X11INPUT_EVENT_DEVICE_TYPE_SET_HPP_INCLUDED
#define SGE_X11INPUT_EVENT_DEVICE_TYPE_SET_HPP_INCLUDED

#include <sge/x11input/event/type_c.hpp>
#include <fcppt/mpl/set/object.hpp>
#include <fcppt/config/external_begin.hpp>
#include <X11/extensions/XI2.h>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace x11input
{
namespace event
{

using
device_type_set
=
fcppt::mpl::set::object<
	sge::x11input::event::type_c<
		XI_ButtonPress
	>,
	sge::x11input::event::type_c<
		XI_ButtonRelease
	>,
	sge::x11input::event::type_c<
		XI_Motion
	>,
	sge::x11input::event::type_c<
		XI_KeyPress
	>,
	sge::x11input::event::type_c<
		XI_KeyRelease
	>,
	sge::x11input::event::type_c<
		XI_Enter
	>,
	sge::x11input::event::type_c<
		XI_Leave
	>,
	sge::x11input::event::type_c<
		XI_FocusIn
	>,
	sge::x11input::event::type_c<
		XI_FocusOut
	>
>;

}
}
}

#endif
