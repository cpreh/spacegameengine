//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_WLINPUT_CURSOR_CREATE_HPP_INCLUDED
#define SGE_WLINPUT_CURSOR_CREATE_HPP_INCLUDED

#include <sge/window/object_ref.hpp>
#include <sge/wlinput/cursor/create_function.hpp>
#include <awl/backends/wayland/window/object_ref.hpp>
#include <awl/event/container_reference.hpp>


namespace sge::wlinput::cursor
{

sge::wlinput::cursor::create_function
create(
	sge::window::object_ref,
	awl::backends::wayland::window::object_ref,
	awl::event::container_reference
);

}

#endif
