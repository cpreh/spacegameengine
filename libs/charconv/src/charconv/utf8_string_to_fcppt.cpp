//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/charconv/utf8_string.hpp>
#include <sge/charconv/utf8_string_to_fcppt.hpp>
#include <sge/charconv/impl/fcppt_is_utf8.hpp>
#include <fcppt/optional_string.hpp>
#include <fcppt/string.hpp>
#ifndef SGE_CHARCONV_IMPL_FCPPT_IS_UTF8
#include <sge/charconv/convert.hpp>
#include <sge/charconv/encoding.hpp>
#include <fcppt/from_std_wstring.hpp>
#endif

fcppt::optional_string
sge::charconv::utf8_string_to_fcppt(sge::charconv::utf8_string const &_string)
{
#ifdef SGE_CHARCONV_IMPL_FCPPT_IS_UTF8
  return fcppt::optional_string{fcppt::string{_string.begin(), _string.end()}};
#else
  return fcppt::from_std_wstring(
      sge::charconv::convert<sge::charconv::encoding::wchar, sge::charconv::encoding::utf8>(
          _string));
#endif
}
