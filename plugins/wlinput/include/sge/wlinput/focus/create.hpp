//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_WLINPUT_FOCUS_CREATE_HPP_INCLUDED
#define SGE_WLINPUT_FOCUS_CREATE_HPP_INCLUDED

#include <sge/window/object_fwd.hpp>
#include <sge/wlinput/xkb_context_fwd.hpp>
#include <sge/wlinput/focus/create_function.hpp>
#include <awl/backends/wayland/window/object_fwd.hpp>
#include <awl/event/container_reference.hpp>
#include <fcppt/log/object_fwd.hpp>


namespace sge
{
namespace wlinput
{
namespace focus
{

sge::wlinput::focus::create_function
create(
	fcppt::log::object &,
	sge::window::object &,
	sge::wlinput::xkb_context const &,
	awl::backends::wayland::window::object const &,
	awl::event::container_reference
);

}
}
}

#endif
