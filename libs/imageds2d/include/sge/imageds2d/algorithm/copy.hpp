//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_IMAGEDS2D_ALGORITHM_COPY_HPP_INCLUDED
#define SGE_IMAGEDS2D_ALGORITHM_COPY_HPP_INCLUDED

#include <sge/image/algorithm/may_overlap_fwd.hpp>
#include <sge/image/algorithm/uninitialized_fwd.hpp>
#include <sge/imageds2d/detail/symbol.hpp>
#include <sge/imageds2d/view/const_object_fwd.hpp>
#include <sge/imageds2d/view/object_fwd.hpp>

namespace sge::imageds2d::algorithm
{

SGE_IMAGEDS2D_DETAIL_SYMBOL
void copy(
    sge::imageds2d::view::const_object const &src,
    sge::imageds2d::view::object const &dest,
    sge::image::algorithm::may_overlap,
    sge::image::algorithm::uninitialized);

}

#endif
