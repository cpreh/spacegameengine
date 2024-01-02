//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_IMAGE2D_VIEW_SUB_HPP_INCLUDED
#define SGE_IMAGE2D_VIEW_SUB_HPP_INCLUDED

#include <sge/image/view/declare_sub.hpp>
#include <sge/image2d/rect_fwd.hpp>
#include <sge/image2d/tag.hpp> // IWYU pragma: keep
#include <sge/image2d/detail/symbol.hpp>
#include <sge/image2d/traits/dimension.hpp> // IWYU pragma: keep
#include <sge/image2d/view/const_object_fwd.hpp>
#include <sge/image2d/view/object_fwd.hpp>

namespace sge::image2d::view
{

SGE_IMAGE2D_DETAIL_SYMBOL
sge::image2d::view::object sub(sge::image2d::view::object const &, sge::image2d::rect const &);

SGE_IMAGE2D_DETAIL_SYMBOL
sge::image2d::view::const_object
sub(sge::image2d::view::const_object const &, sge::image2d::rect const &);

}

SGE_IMAGE_VIEW_DECLARE_SUB(sge::image2d::tag);

#endif
