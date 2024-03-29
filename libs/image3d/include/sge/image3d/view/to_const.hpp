//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_IMAGE3D_VIEW_TO_CONST_HPP_INCLUDED
#define SGE_IMAGE3D_VIEW_TO_CONST_HPP_INCLUDED

#include <sge/image/view/declare_to_const.hpp>
#include <sge/image3d/tag.hpp> // IWYU pragma: keep
#include <sge/image3d/detail/symbol.hpp>
#include <sge/image3d/view/const_object.hpp>
#include <sge/image3d/view/object_fwd.hpp>

namespace sge::image3d::view
{

SGE_IMAGE3D_DETAIL_SYMBOL
sge::image3d::view::const_object to_const(sge::image3d::view::object const &);

}

SGE_IMAGE_VIEW_DECLARE_TO_CONST(sge::image3d::tag);

#endif
