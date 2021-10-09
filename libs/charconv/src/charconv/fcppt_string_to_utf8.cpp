//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/charconv/fcppt_string_to_utf8.hpp>
#include <sge/charconv/utf8_string.hpp>
#include <sge/charconv/impl/fcppt_is_utf8.hpp>
#include <fcppt/string.hpp>
#if !defined(SGE_CHARCONV_IMPL_FCPPT_IS_UTF8)
#include <sge/charconv/convert.hpp>
#include <sge/charconv/encoding.hpp>
#include <fcppt/to_std_wstring.hpp>
#endif

sge::charconv::utf8_string sge::charconv::fcppt_string_to_utf8(fcppt::string const &_string)
{
  return
#if defined(SGE_CHARCONV_IMPL_FCPPT_IS_UTF8)
      {_string.begin(), _string.end()};
#else
      sge::charconv::convert<sge::charconv::encoding::utf8, sge::charconv::encoding::wchar>(
          fcppt::to_std_wstring(_string));
#endif
}
