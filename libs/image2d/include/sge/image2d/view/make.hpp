//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_IMAGE2D_VIEW_MAKE_HPP_INCLUDED
#define SGE_IMAGE2D_VIEW_MAKE_HPP_INCLUDED

#include <sge/image/raw_pointer.hpp>
#include <sge/image/color/format_fwd.hpp>
#include <sge/image/color/traits/format_fwd.hpp>
#include <sge/image/view/declare_make.hpp>
#include <sge/image2d/dim_fwd.hpp>
#include <sge/image2d/pitch_fwd.hpp>
#include <sge/image2d/tag.hpp>
#include <sge/image2d/detail/symbol.hpp>
#include <sge/image2d/traits/color_tag.hpp>
#include <sge/image2d/traits/dimension.hpp>
#include <sge/image2d/view/object.hpp>

namespace sge::image2d::view
{

SGE_IMAGE2D_DETAIL_SYMBOL
sge::image2d::view::object make(
    sge::image::raw_pointer,
    sge::image2d::dim const &,
    sge::image::color::format,
    sge::image2d::pitch const &);

}

SGE_IMAGE_VIEW_DECLARE_MAKE(sge::image2d::tag);

#endif
