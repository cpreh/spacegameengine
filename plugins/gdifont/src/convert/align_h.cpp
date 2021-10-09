//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/font/align_h/center_fwd.hpp>
#include <sge/font/align_h/left_fwd.hpp>
#include <sge/font/align_h/right_fwd.hpp>
#include <sge/font/align_h/variant.hpp>
#include <sge/gdifont/include_windows.hpp>
#include <sge/gdifont/convert/align_h.hpp>
#include <fcppt/literal.hpp>
#include <fcppt/variant/match.hpp>

UINT sge::gdifont::convert::align_h(sge::font::align_h::variant const &_align_h)
{
  return fcppt::variant::match(
      _align_h,
      [](sge::font::align_h::left const &) { return fcppt::literal<UINT>(DT_LEFT); },
      [](sge::font::align_h::center const &) { return fcppt::literal<UINT>(DT_CENTER); },
      [](sge::font::align_h::right const &) { return fcppt::literal<UINT>(DT_RIGHT); });
}
