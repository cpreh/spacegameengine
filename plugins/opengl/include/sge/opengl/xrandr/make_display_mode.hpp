//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_OPENGL_XRANDR_MAKE_DISPLAY_MODE_HPP_INCLUDED
#define SGE_OPENGL_XRANDR_MAKE_DISPLAY_MODE_HPP_INCLUDED

#include <sge/opengl/xrandr/refresh_rate.hpp>
#include <sge/renderer/display_mode/object.hpp>
#include <fcppt/config/external_begin.hpp>
#include <X11/extensions/Xrandr.h>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace opengl
{
namespace xrandr
{

sge::renderer::display_mode::object
make_display_mode(
	XRRScreenSize const &,
	sge::opengl::xrandr::refresh_rate
);

}
}
}

#endif
