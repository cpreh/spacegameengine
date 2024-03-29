//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_X11INPUT_MOUSE_INFO_HPP_INCLUDED
#define SGE_X11INPUT_MOUSE_INFO_HPP_INCLUDED

#include <sge/input/mouse/info.hpp>
#include <awl/backends/x11/display_fwd.hpp>
#include <fcppt/config/external_begin.hpp>
#include <X11/extensions/XInput2.h>
#include <fcppt/config/external_end.hpp>

namespace sge::x11input::mouse
{

sge::input::mouse::info info(
    awl::backends::x11::display &, // NOLINT(google-runtime-references)
    XIDeviceInfo const &);

}

#endif
