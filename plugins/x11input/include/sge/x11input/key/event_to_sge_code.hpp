//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_X11INPUT_KEY_EVENT_TO_SGE_CODE_HPP_INCLUDED
#define SGE_X11INPUT_KEY_EVENT_TO_SGE_CODE_HPP_INCLUDED

#include <sge/input/key/code.hpp>
#include <awl/backends/x11/display_fwd.hpp>
#include <fcppt/config/external_begin.hpp>
#include <X11/extensions/XInput2.h>
#include <fcppt/config/external_end.hpp>

namespace sge::x11input::key
{

sge::input::key::code event_to_sge_code(awl::backends::x11::display const &, XIDeviceEvent const &);

}

#endif
