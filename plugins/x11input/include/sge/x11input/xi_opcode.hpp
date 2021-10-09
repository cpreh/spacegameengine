//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_X11INPUT_XI_OPCODE_HPP_INCLUDED
#define SGE_X11INPUT_XI_OPCODE_HPP_INCLUDED

#include <sge/x11input/optional_opcode.hpp>
#include <awl/backends/x11/display_fwd.hpp>

namespace sge::x11input
{

sge::x11input::optional_opcode
xi_opcode(awl::backends::x11::display & // NOLINT(google-runtime-references)
); // NOLINT(google-runtime-references)

}

#endif
