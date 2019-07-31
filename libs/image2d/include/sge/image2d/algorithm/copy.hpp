//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_IMAGE2D_ALGORITHM_COPY_HPP_INCLUDED
#define SGE_IMAGE2D_ALGORITHM_COPY_HPP_INCLUDED

#include <sge/image/algorithm/declare_copy.hpp>
#include <sge/image/algorithm/may_overlap_fwd.hpp>
#include <sge/image/algorithm/uninitialized_fwd.hpp>
#include <sge/image2d/tag.hpp>
#include <sge/image2d/detail/symbol.hpp>
#include <sge/image2d/view/const_object_fwd.hpp>
#include <sge/image2d/view/object_fwd.hpp>


namespace sge
{
namespace image2d
{
namespace algorithm
{

SGE_IMAGE2D_DETAIL_SYMBOL
void
copy(
	sge::image2d::view::const_object const &src,
	sge::image2d::view::object const &dest,
	sge::image::algorithm::may_overlap,
	sge::image::algorithm::uninitialized
);

}
}
}

SGE_IMAGE_ALGORITHM_DECLARE_COPY(
	sge::image2d::tag
);

#endif
