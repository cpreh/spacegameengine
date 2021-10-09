//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_IMAGE3D_ALGORITHM_CLONE_HPP_INCLUDED
#define SGE_IMAGE3D_ALGORITHM_CLONE_HPP_INCLUDED

#include <sge/image3d/detail/symbol.hpp>
#include <sge/image3d/store/object_fwd.hpp>
#include <sge/image3d/view/const_object_fwd.hpp>

namespace sge::image3d::algorithm
{

SGE_IMAGE3D_DETAIL_SYMBOL
sge::image3d::store::object clone(sge::image3d::view::const_object const &);

}

#endif
