//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_FONT_BITMAP_IMPL_POSITION_HPP_INCLUDED
#define SGE_FONT_BITMAP_IMPL_POSITION_HPP_INCLUDED

#include <sge/font/vector.hpp>
#include <sge/font/bitmap/impl/char_metric_fwd.hpp>
#include <sge/font/bitmap/impl/position_fwd.hpp> // IWYU pragma: keep
#include <fcppt/reference_impl.hpp>

namespace sge::font::bitmap::impl
{

class position
{
public:
  position(sge::font::vector, fcppt::reference<sge::font::bitmap::impl::char_metric const>);

  [[nodiscard]] sge::font::vector pos() const;

  [[nodiscard]] sge::font::bitmap::impl::char_metric const &metric() const;

private:
  sge::font::vector pos_;

  fcppt::reference<sge::font::bitmap::impl::char_metric const> metric_;
};

}

#endif
