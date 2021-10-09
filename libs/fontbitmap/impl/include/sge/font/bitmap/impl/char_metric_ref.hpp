//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_FONT_BITMAP_IMPL_CHAR_METRIC_REF_HPP_INCLUDED
#define SGE_FONT_BITMAP_IMPL_CHAR_METRIC_REF_HPP_INCLUDED

#include <sge/font/bitmap/impl/char_metric_fwd.hpp>
#include <fcppt/reference.hpp>

namespace sge::font::bitmap::impl
{

using char_metric_ref = fcppt::reference<sge::font::bitmap::impl::char_metric const>;

}

#endif
