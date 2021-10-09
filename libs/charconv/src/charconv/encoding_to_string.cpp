//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/charconv/encoding.hpp>
#include <sge/charconv/encoding_to_string.hpp>
#include <fcppt/string.hpp>
#include <fcppt/text.hpp>
#include <fcppt/assert/unreachable.hpp>

fcppt::string sge::charconv::encoding_to_string(sge::charconv::encoding const _encoding)
{
#define SGE_CHARCONV_ENCODING_CASE(name) \
  case sge::charconv::encoding::name: \
    return FCPPT_TEXT(#name)

  switch (_encoding)
  {
    SGE_CHARCONV_ENCODING_CASE(utf8);
    SGE_CHARCONV_ENCODING_CASE(utf16);
    SGE_CHARCONV_ENCODING_CASE(utf32);
    SGE_CHARCONV_ENCODING_CASE(wchar);
  }

  FCPPT_ASSERT_UNREACHABLE;
}
