//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/input/exception.hpp>
#include <sge/x11input/xim/get_im_values.hpp>
#include <sge/x11input/xim/get_supported_styles.hpp>
#include <sge/x11input/xim/method_fwd.hpp>
#include <sge/x11input/xim/supported_styles_unique_ptr.hpp>
#include <fcppt/text.hpp>
#include <fcppt/config/external_begin.hpp>
#include <X11/X.h>
#include <fcppt/config/external_end.hpp>

sge::x11input::xim::supported_styles_unique_ptr
sge::x11input::xim::get_supported_styles(sge::x11input::xim::method const &_method)
{
  XIMStyles *result{nullptr};

  sge::x11input::xim::get_im_values(_method, XNQueryInputStyle, &result);

  if(result == nullptr)
  {
    throw sge::input::exception{FCPPT_TEXT("x11input supported styles returned null!")};
  }

  return sge::x11input::xim::supported_styles_unique_ptr{result};
}
