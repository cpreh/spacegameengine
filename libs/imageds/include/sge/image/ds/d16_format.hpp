//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_IMAGE_DS_D16_FORMAT_HPP_INCLUDED
#define SGE_IMAGE_DS_D16_FORMAT_HPP_INCLUDED

#include <sge/image/channel16.hpp>
#include <sge/image/homogenous_format.hpp>
#include <sge/image/ds/layout/depth.hpp>


namespace sge
{
namespace image
{
namespace ds
{

using
d16_format
=
sge::image::homogenous_format<
	sge::image::channel16,
	sge::image::ds::layout::depth
>;

}
}
}

#endif
