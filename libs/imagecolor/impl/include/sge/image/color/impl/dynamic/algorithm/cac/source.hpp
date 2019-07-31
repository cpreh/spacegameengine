//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_IMAGE_COLOR_IMPL_DYNAMIC_ALGORITHM_CAC_SOURCE_HPP_INCLUDED
#define SGE_IMAGE_COLOR_IMPL_DYNAMIC_ALGORITHM_CAC_SOURCE_HPP_INCLUDED

#include <sge/image/view/mizuiro_access.hpp>
#include <mizuiro/const_tag.hpp>
#include <mizuiro/image/types/reference.hpp>


namespace sge
{
namespace image
{
namespace color
{
namespace impl
{
namespace dynamic
{
namespace algorithm
{
namespace cac
{

template<
	typename ImageFormat
>
using source
=
mizuiro::image::types::reference<
	sge::image::view::mizuiro_access,
	ImageFormat,
	mizuiro::const_tag
>;

}
}
}
}
}
}
}

#endif
