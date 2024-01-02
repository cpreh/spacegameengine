//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_IMAGE2D_VIEW_FORMAT_HPP_INCLUDED
#define SGE_IMAGE2D_VIEW_FORMAT_HPP_INCLUDED

#include <sge/image/color/format.hpp>
#include <sge/image/color/traits/format_fwd.hpp> // IWYU pragma: keep
#include <sge/image/view/declare_format.hpp>
#include <sge/image2d/tag.hpp> // IWYU pragma: keep
#include <sge/image2d/detail/symbol.hpp>
#include <sge/image2d/traits/color_tag.hpp> // IWYU pragma: keep
#include <sge/image2d/view/const_object_fwd.hpp>
#include <sge/image2d/view/object_fwd.hpp>

namespace sge::image2d::view
{

SGE_IMAGE2D_DETAIL_SYMBOL
sge::image::color::format format(sge::image2d::view::object const &);

SGE_IMAGE2D_DETAIL_SYMBOL
sge::image::color::format format(sge::image2d::view::const_object const &);

}

SGE_IMAGE_VIEW_DECLARE_FORMAT(sge::image2d::tag);

#endif
