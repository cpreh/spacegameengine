//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_IMAGE_IMPL_ALGORITHM_CONVERT_MAY_OVERLAP_HPP_INCLUDED
#define SGE_IMAGE_IMPL_ALGORITHM_CONVERT_MAY_OVERLAP_HPP_INCLUDED

#include <sge/image/algorithm/may_overlap_fwd.hpp>
#include <sge/image/detail/symbol.hpp>
#include <mizuiro/image/algorithm/may_overlap.hpp>


namespace sge
{
namespace image
{
namespace impl
{
namespace algorithm
{

SGE_IMAGE_DETAIL_SYMBOL
mizuiro::image::algorithm::may_overlap
convert_may_overlap(
	sge::image::algorithm::may_overlap
);

}
}
}
}

#endif
