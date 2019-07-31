//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_IMAGE_BOX_FWD_HPP_INCLUDED
#define SGE_IMAGE_BOX_FWD_HPP_INCLUDED

#include <sge/image/basic_box_fwd.hpp>
#include <sge/image/traits/image/dimension.hpp>


namespace sge
{
namespace image
{

template<
	typename Tag
>
using
box
=
sge::image::basic_box<
	sge::image::traits::image::dimension<
		Tag
	>::value
>;

}
}

#endif
