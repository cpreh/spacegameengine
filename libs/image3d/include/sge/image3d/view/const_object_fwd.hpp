//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_IMAGE3D_VIEW_CONST_OBJECT_FWD_HPP_INCLUDED
#define SGE_IMAGE3D_VIEW_CONST_OBJECT_FWD_HPP_INCLUDED

#include <sge/image/view/const_object_fwd.hpp>
#include <sge/image3d/tag.hpp>


namespace sge::image3d::view
{

using
const_object
=
sge::image::view::const_object<
	sge::image3d::tag
>;

}

#endif
