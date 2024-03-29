//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_OPENGL_XRANDR_GET_EXTENSION_HPP_INCLUDED
#define SGE_OPENGL_XRANDR_GET_EXTENSION_HPP_INCLUDED

#include <sge/opengl/xrandr/optional_extension_fwd.hpp>
#include <awl/backends/x11/display_ref.hpp>

namespace sge::opengl::xrandr
{

sge::opengl::xrandr::optional_extension get_extension(awl::backends::x11::display_ref);

}

#endif
