//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_OPENGL_XRANDR_SET_RESOLUTION_HPP_INCLUDED
#define SGE_OPENGL_XRANDR_SET_RESOLUTION_HPP_INCLUDED

#include <sge/opengl/xrandr/configuration_fwd.hpp>
#include <sge/opengl/xrandr/mode_index.hpp>
#include <sge/opengl/xrandr/optional_refresh_rate_fwd.hpp>
#include <sge/opengl/xrandr/rotation.hpp>
#include <awl/backends/x11/window/base_fwd.hpp>


namespace sge
{
namespace opengl
{
namespace xrandr
{

void
set_resolution(
	awl::backends::x11::window::base const &,
	sge::opengl::xrandr::configuration const &,
	sge::opengl::xrandr::mode_index,
	sge::opengl::xrandr::rotation,
	sge::opengl::xrandr::optional_refresh_rate const &
);

}
}
}

#endif
