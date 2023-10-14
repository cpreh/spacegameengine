//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/input/exception.hpp>
#include <sge/x11input/xim/method.hpp>
#include <awl/backends/x11/display.hpp> // NOLINT(misc-include-cleaner)
#include <awl/backends/x11/display_ref.hpp>
#include <fcppt/text.hpp>
#include <fcppt/config/external_begin.hpp>
#include <X11/Xlib.h>
#include <fcppt/config/external_end.hpp>

sge::x11input::xim::method::method(awl::backends::x11::display_ref const _display)
    : xim_(::XOpenIM(_display.get().get(), nullptr, nullptr, nullptr))
{
  if (xim_ == nullptr)
  {
    throw sge::input::exception{FCPPT_TEXT("XOpenIM() failed!")};
  }
}

sge::x11input::xim::method::~method() { ::XCloseIM(xim_); }

XIM sge::x11input::xim::method::get() const { return xim_; }
