//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_CAMERA_IMPL_SET_PRESSED_IF_APPROPRIATE_HPP_INCLUDED
#define SGE_CAMERA_IMPL_SET_PRESSED_IF_APPROPRIATE_HPP_INCLUDED

#include <sge/input/key/optional_code_fwd.hpp>
#include <sge/input/keyboard/event/key_fwd.hpp>


namespace sge
{
namespace camera
{
namespace impl
{

void
set_pressed_if_appropriate(
	bool &,
	sge::input::key::optional_code const &,
	sge::input::keyboard::event::key const &
);

}
}
}

#endif
