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
#include <fcppt/config/external_begin.hpp>
#include <brigand/sequences/list.hpp>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace image
{
namespace ds
{
namespace layout
{

typedef
mizuiro::color::layout::make<
	sge::image::ds::space::depth_stencil,
	brigand::list<
		sge::image::ds::channel::depth,
		sge::image::ds::channel::stencil
	>
>
depth_stencil;

}
}
}
}

#endif
