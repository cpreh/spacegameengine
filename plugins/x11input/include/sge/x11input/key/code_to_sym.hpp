//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_X11INPUT_KEY_CODE_TO_SYM_HPP_INCLUDED
#define SGE_X11INPUT_KEY_CODE_TO_SYM_HPP_INCLUDED

#include <sge/x11input/key/code.hpp>
#include <awl/backends/x11/display_fwd.hpp>
#include <fcppt/config/external_begin.hpp>
#include <X11/Xlib.h>
#include <fcppt/config/external_end.hpp>

namespace sge::x11input::key
{

KeySym code_to_sym(awl::backends::x11::display const &, sge::x11input::key::code);

}

#endif
