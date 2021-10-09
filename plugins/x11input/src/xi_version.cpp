//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/x11input/xi_version.hpp>
#include <awl/backends/x11/display.hpp>
#include <fcppt/config/external_begin.hpp>
#include <X11/extensions/XInput2.h>
#include <fcppt/config/external_end.hpp>

bool sge::x11input::xi_version(
    awl::backends::x11::display &_display, int const _major, int const _minor)
{
  // BadRequest will be generated if the
  // server doesn't support XI2 at all.
  // Otherwise the version the server actually supports is returned.

  int major_ret{_major};

  int minor_ret{_minor};

  return ::XIQueryVersion(_display.get(), &major_ret, &minor_ret) != BadRequest &&
         (major_ret > _major || (_major == major_ret && minor_ret >= _minor));
}
