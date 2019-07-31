//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_OPENGL_XRANDR_CHOOSE_RESOLUTION_HPP_INCLUDED
#define SGE_OPENGL_XRANDR_CHOOSE_RESOLUTION_HPP_INCLUDED

#include <sge/opengl/xrandr/configuration_fwd.hpp>
#include <sge/opengl/xrandr/resolution_unique_ptr.hpp>
#include <sge/renderer/display_mode/object_fwd.hpp>
#include <awl/backends/x11/window/base_fwd.hpp>


namespace sge
{
namespace opengl
{
namespace xrandr
{

sge::opengl::xrandr::resolution_unique_ptr
choose_resolution(
	sge::opengl::xrandr::configuration const &,
	awl::backends::x11::window::base const &,
	sge::renderer::display_mode::object const &
);

}
}
}

#endif
