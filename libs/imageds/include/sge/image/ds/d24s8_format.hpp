//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_IMAGE_DS_D24S8_FORMAT_HPP_INCLUDED
#define SGE_IMAGE_DS_D24S8_FORMAT_HPP_INCLUDED

#include <sge/image/heterogenous_format.hpp>
#include <sge/image/ds/layout/depth_stencil.hpp>
#include <mizuiro/size_list.hpp>


namespace sge
{
namespace image
{
namespace ds
{

typedef
sge::image::heterogenous_format<
	mizuiro::size_list<
		24u,
		8u
	>,
	sge::image::ds::layout::depth_stencil
>
d24s8_format;

}
}
}

#endif
