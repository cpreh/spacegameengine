//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/font/flags.hpp>
#include <sge/font/flags_field.hpp>
#include <sge/gdifont/include_windows.hpp>
#include <sge/gdifont/convert/flags.hpp>
#include <fcppt/container/bitfield/operators.hpp>

UINT sge::gdifont::convert::flags(sge::font::flags_field const &_flags)
{
  DWORD ret(0u);

  if (_flags & sge::font::flags::no_multi_line)
    ret |= DT_SINGLELINE;

  if (!(_flags & sge::font::flags::no_word_wrap))
    ret |= DT_WORDBREAK;

  return ret;
}
