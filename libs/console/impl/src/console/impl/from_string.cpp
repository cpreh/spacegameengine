//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/console/impl/from_string.hpp>
#include <sge/font/from_std_wstring.hpp>
#include <sge/font/string.hpp>
#include <fcppt/widen.hpp>
#include <fcppt/config/external_begin.hpp>
#include <string>
#include <fcppt/config/external_end.hpp>

sge::font::string sge::console::impl::from_string(std::string const &_string)
{
  return sge::console::impl::from_string(fcppt::widen(_string));
}

sge::font::string sge::console::impl::from_string(std::wstring const &_string)
{
  return sge::font::from_std_wstring(_string);
}
