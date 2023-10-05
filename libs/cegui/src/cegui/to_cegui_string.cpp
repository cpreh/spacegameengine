//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/cegui/to_cegui_string.hpp>
#include <sge/charconv/convert.hpp>
#include <sge/charconv/encoding.hpp>
#include <fcppt/string.hpp>
#include <fcppt/to_std_wstring.hpp>
#include <fcppt/config/external_begin.hpp>
#include <CEGUI/String.h>
#include <fcppt/config/external_end.hpp>

CEGUI::String sge::cegui::to_cegui_string(fcppt::string const &_string)
{
  if (_string.empty())
  {
    return CEGUI::String();
  }

  return CEGUI::String(
      sge::charconv::convert<sge::charconv::encoding::utf8, sge::charconv::encoding::wchar>(
          fcppt::to_std_wstring(_string))
          .c_str());
}
