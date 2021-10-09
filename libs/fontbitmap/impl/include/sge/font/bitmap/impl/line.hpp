//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_FONT_BITMAP_IMPL_LINE_HPP_INCLUDED
#define SGE_FONT_BITMAP_IMPL_LINE_HPP_INCLUDED

#include <sge/font/unit.hpp>
#include <sge/font/bitmap/impl/char_metric_ref_vector.hpp>
#include <sge/font/bitmap/impl/line_fwd.hpp>
#include <fcppt/noncopyable.hpp>

namespace sge::font::bitmap::impl
{

class line
{
  FCPPT_NONCOPYABLE(line);

public:
  line(sge::font::bitmap::impl::char_metric_ref_vector &&, sge::font::unit width);

  line(line &&) noexcept;

  line &operator=(line &&) noexcept;

  ~line();

  [[nodiscard]] sge::font::bitmap::impl::char_metric_ref_vector const &char_metrics() const;

  [[nodiscard]] sge::font::unit width() const;

private:
  sge::font::bitmap::impl::char_metric_ref_vector char_metrics_;

  sge::font::unit width_;
};

}

#endif
