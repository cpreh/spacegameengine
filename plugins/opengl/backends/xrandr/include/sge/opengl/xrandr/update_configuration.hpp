//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_OPENGL_XRANDR_UPDATE_CONFIGURATION_HPP_INCLUDED
#define SGE_OPENGL_XRANDR_UPDATE_CONFIGURATION_HPP_INCLUDED

#include <awl/backends/x11/window/event/object_fwd.hpp>

namespace sge::opengl::xrandr
{

[[nodiscard]] bool update_configuration(awl::backends::x11::window::event::object const &);

}

#endif
