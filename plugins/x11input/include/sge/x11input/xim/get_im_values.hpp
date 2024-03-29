//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_X11INPUT_XIM_GET_IM_VALUES_HPP_INCLUDED
#define SGE_X11INPUT_XIM_GET_IM_VALUES_HPP_INCLUDED

#include <sge/input/exception.hpp>
#include <sge/x11input/xim/method.hpp>
#include <fcppt/from_std_string.hpp>
#include <fcppt/text.hpp>
#include <fcppt/config/external_begin.hpp>
#include <X11/Xlib.h>
#include <cstddef>
#include <utility>
#include <fcppt/config/external_end.hpp>

namespace sge::x11input::xim
{

template <typename... Args>
void get_im_values(sge::x11input::xim::method const &_method, Args &&..._args)
{
  char const *const result{::XGetIMValues( // NOLINT(cppcoreguidelines-pro-type-vararg,hicpp-vararg)
      _method.get(),
      std::forward<Args>(_args)...,
      NULL)};

  if (result != nullptr)
  {
    throw sge::input::exception{
        FCPPT_TEXT("XGetIMValues failed with ") + fcppt::from_std_string(result)};
  }
}

}

#endif
