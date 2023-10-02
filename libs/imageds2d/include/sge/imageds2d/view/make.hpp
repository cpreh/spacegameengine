//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_IMAGEDS2D_VIEW_MAKE_HPP_INCLUDED
#define SGE_IMAGEDS2D_VIEW_MAKE_HPP_INCLUDED

#include <sge/image/raw_pointer.hpp>
#include <sge/image/ds/format_fwd.hpp>
#include <sge/imageds2d/dim_fwd.hpp>
#include <sge/imageds2d/pitch_fwd.hpp>
#include <sge/imageds2d/detail/symbol.hpp>
#include <sge/imageds2d/view/object.hpp>

namespace sge::imageds2d::view
{

SGE_IMAGEDS2D_DETAIL_SYMBOL
sge::imageds2d::view::object make(
    sge::image::raw_pointer,
    sge::imageds2d::dim const &,
    sge::image::ds::format,
    sge::imageds2d::pitch const &);

}

#endif
