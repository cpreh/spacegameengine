//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_FONT_DRAW_COLOR_FORMAT_HPP_INCLUDED
#define SGE_FONT_DRAW_COLOR_FORMAT_HPP_INCLUDED

#include <sge/font/draw/detail/symbol.hpp>
#include <sge/image/color/format_fwd.hpp>
#include <sge/image/color/optional_format_fwd.hpp>

namespace sge::font::draw
{

SGE_FONT_DRAW_DETAIL_SYMBOL
sge::image::color::format color_format(sge::image::color::optional_format const &);

}

#endif
