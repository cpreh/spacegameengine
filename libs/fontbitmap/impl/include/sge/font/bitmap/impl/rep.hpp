//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_FONT_BITMAP_IMPL_REP_HPP_INCLUDED
#define SGE_FONT_BITMAP_IMPL_REP_HPP_INCLUDED

#include <sge/font/rect.hpp>
#include <sge/font/bitmap/impl/line_vector.hpp>
#include <sge/font/bitmap/impl/rep_fwd.hpp> // IWYU pragma: keep

namespace sge::font::bitmap::impl
{

class rep
{
public:
  rep(sge::font::bitmap::impl::line_vector &&, sge::font::rect);

  [[nodiscard]] sge::font::bitmap::impl::line_vector const &lines() const;

  [[nodiscard]] sge::font::rect rect() const;

private:
  sge::font::bitmap::impl::line_vector lines_;

  sge::font::rect rect_;
};

}

#endif
