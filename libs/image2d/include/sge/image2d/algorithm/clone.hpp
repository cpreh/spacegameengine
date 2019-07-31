//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_IMAGE2D_ALGORITHM_CLONE_HPP_INCLUDED
#define SGE_IMAGE2D_ALGORITHM_CLONE_HPP_INCLUDED

#include <sge/image2d/detail/symbol.hpp>
#include <sge/image2d/store/object_fwd.hpp>
#include <sge/image2d/view/const_object_fwd.hpp>


namespace sge
{
namespace image2d
{
namespace algorithm
{

SGE_IMAGE2D_DETAIL_SYMBOL
sge::image2d::store::object
clone(
	sge::image2d::view::const_object const &
);

}
}
}

#endif
