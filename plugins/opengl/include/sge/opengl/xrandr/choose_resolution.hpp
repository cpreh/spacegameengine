//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_OPENGL_XRANDR_CHOOSE_RESOLUTION_HPP_INCLUDED
#define SGE_OPENGL_XRANDR_CHOOSE_RESOLUTION_HPP_INCLUDED

#include <sge/opengl/xrandr/const_configuration_ref.hpp>
#include <sge/opengl/xrandr/resolution_unique_ptr.hpp>
#include <sge/renderer/display_mode/object_fwd.hpp>
#include <awl/backends/x11/window/const_base_ref.hpp>


namespace sge::opengl::xrandr
{

sge::opengl::xrandr::resolution_unique_ptr
choose_resolution(
	sge::opengl::xrandr::const_configuration_ref,
	awl::backends::x11::window::const_base_ref,
	sge::renderer::display_mode::object const &
);

}

#endif
