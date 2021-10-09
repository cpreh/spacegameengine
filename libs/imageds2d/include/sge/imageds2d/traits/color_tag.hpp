//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_IMAGEDS2D_TRAITS_COLOR_TAG_HPP_INCLUDED
#define SGE_IMAGEDS2D_TRAITS_COLOR_TAG_HPP_INCLUDED

#include <sge/image/ds/tag.hpp>
#include <sge/image/traits/image/color_tag_tpl_fwd.hpp>
#include <sge/imageds2d/tag.hpp>

namespace sge::image::traits::image
{

template <>
struct color_tag_tpl<sge::imageds2d::tag>
{
  using type = sge::image::ds::tag;
};

}

#endif
