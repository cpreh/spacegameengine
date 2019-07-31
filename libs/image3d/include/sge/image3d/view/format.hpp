//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_IMAGE3D_VIEW_FORMAT_HPP_INCLUDED
#define SGE_IMAGE3D_VIEW_FORMAT_HPP_INCLUDED

#include <sge/image/color/format_fwd.hpp>
#include <sge/image/color/traits/format_fwd.hpp>
#include <sge/image/view/declare_format.hpp>
#include <sge/image3d/tag.hpp>
#include <sge/image3d/detail/symbol.hpp>
#include <sge/image3d/traits/color_tag.hpp>
#include <sge/image3d/view/const_object_fwd.hpp>
#include <sge/image3d/view/object_fwd.hpp>


namespace sge
{
namespace image3d
{
namespace view
{

SGE_IMAGE3D_DETAIL_SYMBOL
sge::image::color::format
format(
	sge::image3d::view::object const &
);

SGE_IMAGE3D_DETAIL_SYMBOL
sge::image::color::format
format(
	sge::image3d::view::const_object const &
);

}
}
}

SGE_IMAGE_VIEW_DECLARE_FORMAT(
	sge::image3d::tag
);

#endif
