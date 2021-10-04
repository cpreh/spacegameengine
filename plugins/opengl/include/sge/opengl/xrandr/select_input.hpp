//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_OPENGL_XRANDR_SELECT_INPUT_HPP_INCLUDED
#define SGE_OPENGL_XRANDR_SELECT_INPUT_HPP_INCLUDED

#include <sge/opengl/xrandr/input_mask.hpp>
#include <awl/backends/x11/window/base_fwd.hpp>


namespace sge::opengl::xrandr
{

void
select_input(
	awl::backends::x11::window::base const &,
	sge::opengl::xrandr::input_mask
);

}

#endif
