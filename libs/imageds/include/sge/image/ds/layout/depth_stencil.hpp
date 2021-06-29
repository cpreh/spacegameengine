//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_IMAGE_DS_LAYOUT_DEPTH_STENCIL_HPP_INCLUDED
#define SGE_IMAGE_DS_LAYOUT_DEPTH_STENCIL_HPP_INCLUDED

#include <sge/image/ds/channel/depth.hpp>
#include <sge/image/ds/channel/stencil.hpp>
#include <sge/image/ds/space/depth_stencil.hpp>
#include <mizuiro/color/layout/make.hpp>
#include <fcppt/mpl/list/object.hpp>


namespace sge
{
namespace image
{
namespace ds
{
namespace layout
{

using
depth_stencil
=
mizuiro::color::layout::make<
	sge::image::ds::space::depth_stencil,
	fcppt::mpl::list::object<
		sge::image::ds::channel::depth,
		sge::image::ds::channel::stencil
	>
>;

}
}
}
}

#endif
