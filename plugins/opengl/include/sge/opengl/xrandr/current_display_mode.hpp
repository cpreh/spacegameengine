//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_OPENGL_XRANDR_CURRENT_DISPLAY_MODE_HPP_INCLUDED
#define SGE_OPENGL_XRANDR_CURRENT_DISPLAY_MODE_HPP_INCLUDED

#include <sge/renderer/display_mode/optional_object.hpp>
#include <awl/backends/x11/window/base_fwd.hpp>


namespace sge::opengl::xrandr
{

sge::renderer::display_mode::optional_object
current_display_mode(
	awl::backends::x11::window::base const &
);

}

#endif
