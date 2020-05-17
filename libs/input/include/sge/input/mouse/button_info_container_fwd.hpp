//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_INPUT_MOUSE_BUTTON_INFO_CONTAINER_FWD_HPP_INCLUDED
#define SGE_INPUT_MOUSE_BUTTON_INFO_CONTAINER_FWD_HPP_INCLUDED

#include <sge/input/info/container_fwd.hpp>
#include <sge/input/mouse/button_id.hpp>
#include <sge/input/mouse/button_info_fwd.hpp>


namespace sge
{
namespace input
{
namespace mouse
{

using
button_info_container
=
input::info::container<
	sge::input::mouse::button_id,
	sge::input::mouse::button_info
>;

}
}
}

#endif
