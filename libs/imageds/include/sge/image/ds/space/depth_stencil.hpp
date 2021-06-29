//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_IMAGE_DS_SPACE_DEPTH_STENCIL_HPP_INCLUDED
#define SGE_IMAGE_DS_SPACE_DEPTH_STENCIL_HPP_INCLUDED

#include <sge/image/ds/channel/depth_fwd.hpp>
#include <sge/image/ds/channel/stencil_fwd.hpp>
#include <sge/image/ds/space/depth_stencil_fwd.hpp>
#include <fcppt/mpl/set/object.hpp>


namespace sge
{
namespace image
{
namespace ds
{
namespace space
{

struct depth_stencil
{
	using
	required_channels
	=
	fcppt::mpl::set::object<
		sge::image::ds::channel::depth,
		sge::image::ds::channel::stencil
	>;
};

}
}
}
}

#endif
