//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/x11input/opcode.hpp>
#include <sge/x11input/optional_opcode.hpp>
#include <sge/x11input/xi_opcode.hpp>
#include <awl/backends/x11/display.hpp>
#include <fcppt/optional/make_if.hpp>
#include <fcppt/config/external_begin.hpp>
#include <X11/Xlib.h>
#include <fcppt/config/external_end.hpp>

sge::x11input::optional_opcode sge::x11input::xi_opcode(awl::backends::x11::display &_display)
{
  int opcode{};
  int event{};
  int error{};

  return fcppt::optional::make_if(
      ::XQueryExtension(_display.get(), "XInputExtension", &opcode, &event, &error) == True,
      [&opcode] { return sge::x11input::opcode{opcode}; });
}
