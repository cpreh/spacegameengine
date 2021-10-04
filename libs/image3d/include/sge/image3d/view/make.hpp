//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_IMAGE3D_VIEW_MAKE_HPP_INCLUDED
#define SGE_IMAGE3D_VIEW_MAKE_HPP_INCLUDED

#include <sge/image/raw_pointer.hpp>
#include <sge/image/color/format_fwd.hpp>
#include <sge/image/color/traits/format_fwd.hpp>
#include <sge/image/view/declare_make.hpp>
#include <sge/image3d/dim_fwd.hpp>
#include <sge/image3d/pitch_fwd.hpp>
#include <sge/image3d/tag.hpp>
#include <sge/image3d/detail/symbol.hpp>
#include <sge/image3d/traits/color_tag.hpp>
#include <sge/image3d/traits/dimension.hpp>
#include <sge/image3d/view/object_fwd.hpp>


namespace sge::image3d::view
{

SGE_IMAGE3D_DETAIL_SYMBOL
sge::image3d::view::object
make(
	sge::image::raw_pointer,
	sge::image3d::dim const &,
	sge::image::color::format,
	sge::image3d::pitch const &
);

}

SGE_IMAGE_VIEW_DECLARE_MAKE(
	sge::image3d::tag
);

#endif
