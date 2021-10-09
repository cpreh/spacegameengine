//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/font/align_h/center.hpp>
#include <sge/font/align_h/extract_max_width.hpp>
#include <sge/font/align_h/left.hpp>
#include <sge/font/align_h/optional_max_width.hpp>
#include <sge/font/align_h/right.hpp>
#include <sge/font/align_h/variant.hpp>
#include <fcppt/variant/match.hpp>

sge::font::align_h::optional_max_width
sge::font::align_h::extract_max_width(sge::font::align_h::variant const &_variant)
{
  return fcppt::variant::match(
      _variant,
      [](sge::font::align_h::left const &_left) { return _left.max_width(); },
      [](sge::font::align_h::center const &_center)
      { return sge::font::align_h::optional_max_width(_center.max_width()); },
      [](sge::font::align_h::right const &_right)
      { return sge::font::align_h::optional_max_width(_right.max_width()); });
}
