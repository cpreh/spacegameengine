//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_IMAGE3D_ALGORITHM_COPY_AND_CONVERT_HPP_INCLUDED
#define SGE_IMAGE3D_ALGORITHM_COPY_AND_CONVERT_HPP_INCLUDED

#include <sge/image/algorithm/may_overlap_fwd.hpp>
#include <sge/image/algorithm/uninitialized_fwd.hpp>
#include <sge/image3d/detail/symbol.hpp>
#include <sge/image3d/view/const_object_fwd.hpp>
#include <sge/image3d/view/object_fwd.hpp>


namespace sge
{
namespace image3d
{
namespace algorithm
{

SGE_IMAGE3D_DETAIL_SYMBOL
void
copy_and_convert(
	sge::image3d::view::const_object const &src,
	sge::image3d::view::object const &dest,
	sge::image::algorithm::may_overlap,
	sge::image::algorithm::uninitialized
);

}
}
}

#endif
