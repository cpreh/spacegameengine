//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_X11INPUT_MOUSE_BUTTON_INFOS_HPP_INCLUDED
#define SGE_X11INPUT_MOUSE_BUTTON_INFOS_HPP_INCLUDED

#include <sge/input/mouse/button_info_container.hpp>
#include <awl/backends/x11/display_fwd.hpp>
#include <fcppt/config/external_begin.hpp>
#include <X11/extensions/XInput2.h>
#include <fcppt/config/external_end.hpp>

namespace sge::x11input::mouse
{

sge::input::mouse::button_info_container::vector button_infos(
    XIButtonClassInfo const &,
    awl::backends::x11::display & // NOLINT(google-runtime-references)
); // NOLINT(google-runtime-references)

}

#endif
