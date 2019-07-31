//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_X11INPUT_CURSOR_CREATE_GRAB_HPP_INCLUDED
#define SGE_X11INPUT_CURSOR_CREATE_GRAB_HPP_INCLUDED

#include <sge/x11input/cursor/optional_grab_unique_ptr.hpp>
#include <sge/x11input/device/id.hpp>
#include <awl/backends/x11/cursor/object_fwd.hpp>
#include <awl/backends/x11/window/base_fwd.hpp>
#include <fcppt/log/object_fwd.hpp>


namespace sge
{
namespace x11input
{
namespace cursor
{

sge::x11input::cursor::optional_grab_unique_ptr
create_grab(
	fcppt::log::object &,
	awl::backends::x11::window::base const &,
	sge::x11input::device::id,
	awl::backends::x11::cursor::object const &
);

}
}
}

#endif
