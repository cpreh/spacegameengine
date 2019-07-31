//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_IMAGE_DS_SPACE_DEPTH_HPP_INCLUDED
#define SGE_IMAGE_DS_SPACE_DEPTH_HPP_INCLUDED

#include <sge/image/ds/channel/depth_fwd.hpp>
#include <sge/image/ds/space/depth_fwd.hpp>
#include <fcppt/config/external_begin.hpp>
#include <brigand/sequences/list.hpp>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace image
{
namespace ds
{
namespace space
{

struct depth
{
	typedef
	brigand::list<
		sge::image::ds::channel::depth
	>
	required_channels;
};

}
}
}
}

#endif
