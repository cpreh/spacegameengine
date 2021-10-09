//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_FONT_BITMAP_IMPL_CHAR_METRIC_HPP_INCLUDED
#define SGE_FONT_BITMAP_IMPL_CHAR_METRIC_HPP_INCLUDED

#include <sge/font/unit.hpp>
#include <sge/font/vector.hpp>
#include <sge/font/bitmap/impl/char_metric_fwd.hpp>
#include <sge/font/bitmap/impl/const_view.hpp>

namespace sge::font::bitmap::impl
{

class char_metric
{
public:
  char_metric(
      sge::font::bitmap::impl::const_view, sge::font::vector offset, sge::font::unit x_advance);

  [[nodiscard]] sge::font::bitmap::impl::const_view view() const;

  [[nodiscard]] sge::font::vector offset() const;

  [[nodiscard]] sge::font::unit x_advance() const;

private:
  sge::font::bitmap::impl::const_view view_;

  sge::font::vector offset_;

  sge::font::unit x_advance_;
};

}

#endif
