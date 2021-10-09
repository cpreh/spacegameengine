//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/input/exception.hpp>
#include <sge/x11input/xim/setlocale.hpp>
#include <fcppt/from_std_string.hpp>
#include <fcppt/text.hpp>
#include <fcppt/config/external_begin.hpp>
#include <clocale>
#include <string>
#include <fcppt/config/external_end.hpp>

std::string sge::x11input::xim::setlocale(std::string const &_what)
{
  char const *const ret(::setlocale(LC_ALL, _what.c_str()));

  if (ret == nullptr)
  {
    throw sge::input::exception{FCPPT_TEXT("Can't set LC_ALL to ") + fcppt::from_std_string(_what)};
  }

  return ret;
}
