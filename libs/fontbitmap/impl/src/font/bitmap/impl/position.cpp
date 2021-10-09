//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/font/vector.hpp>
#include <sge/font/bitmap/impl/char_metric_fwd.hpp>
#include <sge/font/bitmap/impl/position.hpp>
#include <fcppt/reference_impl.hpp>

sge::font::bitmap::impl::position::position(
    sge::font::vector const _pos,
    fcppt::reference<sge::font::bitmap::impl::char_metric const> const _metric)
    : pos_{_pos}, metric_{_metric}
{
}

sge::font::vector sge::font::bitmap::impl::position::pos() const { return pos_; }

sge::font::bitmap::impl::char_metric const &sge::font::bitmap::impl::position::metric() const
{
  return metric_.get();
}
