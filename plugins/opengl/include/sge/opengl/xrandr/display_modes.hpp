//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_OPENGL_XRANDR_DISPLAY_MODES_HPP_INCLUDED
#define SGE_OPENGL_XRANDR_DISPLAY_MODES_HPP_INCLUDED

#include <sge/opengl/xrandr/configuration_fwd.hpp>
#include <sge/renderer/display_mode/container.hpp>


namespace sge::opengl::xrandr
{

sge::renderer::display_mode::container
display_modes(
	sge::opengl::xrandr::configuration const &
);

}

#endif
