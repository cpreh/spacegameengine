//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_IMAGEDS2D_VIEW_FORMAT_HPP_INCLUDED
#define SGE_IMAGEDS2D_VIEW_FORMAT_HPP_INCLUDED

#include <sge/image/ds/format_fwd.hpp>
#include <sge/image/ds/traits/format_fwd.hpp>
#include <sge/image/view/declare_format.hpp>
#include <sge/imageds2d/tag.hpp>
#include <sge/imageds2d/detail/symbol.hpp>
#include <sge/imageds2d/traits/color_tag.hpp>
#include <sge/imageds2d/view/const_object_fwd.hpp>
#include <sge/imageds2d/view/object_fwd.hpp>

namespace sge::imageds2d::view
{

SGE_IMAGEDS2D_DETAIL_SYMBOL
sge::image::ds::format format(sge::imageds2d::view::object const &);

SGE_IMAGEDS2D_DETAIL_SYMBOL
sge::image::ds::format format(sge::imageds2d::view::const_object const &);

}

SGE_IMAGE_VIEW_DECLARE_FORMAT(sge::imageds2d::tag);

#endif
