//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_FONT_METRICS_HPP_INCLUDED
#define SGE_FONT_METRICS_HPP_INCLUDED

#include <sge/font/height.hpp>
#include <sge/font/metrics_fwd.hpp> // IWYU pragma: keep
#include <sge/font/detail/symbol.hpp>

namespace sge::font
{

class metrics
{
public:
  SGE_FONT_DETAIL_SYMBOL
  explicit metrics(sge::font::height);

  [[nodiscard]] SGE_FONT_DETAIL_SYMBOL sge::font::height height() const;

private:
  sge::font::height height_;
};

}

#endif
