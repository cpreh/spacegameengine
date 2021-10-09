//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/x11input/atom_name.hpp>
#include <sge/x11input/device/info/string_from_atom.hpp>
#include <awl/backends/x11/display_fwd.hpp>
#include <fcppt/from_std_string.hpp>
#include <fcppt/make_ref.hpp>
#include <fcppt/optional_string.hpp>
#include <fcppt/config/external_begin.hpp>
#include <X11/Xlib.h>
#include <fcppt/config/external_end.hpp>

fcppt::optional_string sge::x11input::device::info::string_from_atom(
    awl::backends::x11::display &_display, Atom const _atom)
{
  return _atom == None ? fcppt::optional_string()
                       : fcppt::optional_string(fcppt::from_std_string(
                             sge::x11input::atom_name(fcppt::make_ref(_display), _atom).get()));
}
