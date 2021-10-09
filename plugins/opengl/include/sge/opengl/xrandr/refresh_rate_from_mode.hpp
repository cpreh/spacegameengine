//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_OPENGL_XRANDR_REFRESH_RATE_FROM_MODE_HPP_INCLUDED
#define SGE_OPENGL_XRANDR_REFRESH_RATE_FROM_MODE_HPP_INCLUDED

#include <sge/renderer/display_mode/optional_refresh_rate_fwd.hpp>
#include <fcppt/config/external_begin.hpp>
#include <X11/extensions/Xrandr.h>
#include <fcppt/config/external_end.hpp>

namespace sge::opengl::xrandr
{

sge::renderer::display_mode::optional_refresh_rate refresh_rate_from_mode(XRRModeInfo const &);

}

#endif
