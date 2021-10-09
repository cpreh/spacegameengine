//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/font/from_fcppt_string.hpp>
#include <sge/font/from_std_wstring.hpp>
#include <sge/font/string.hpp>
#include <fcppt/string.hpp>
#include <fcppt/to_std_wstring.hpp>

sge::font::string sge::font::from_fcppt_string(fcppt::string const &_string)
{
  return sge::font::from_std_wstring(fcppt::to_std_wstring(_string));
}
