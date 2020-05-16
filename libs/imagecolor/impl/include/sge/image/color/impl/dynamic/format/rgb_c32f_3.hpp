//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_IMAGE_COLOR_IMPL_DYNAMIC_FORMAT_RGB_C32F_3_HPP_INCLUDED
#define SGE_IMAGE_COLOR_IMPL_DYNAMIC_FORMAT_RGB_C32F_3_HPP_INCLUDED

#include <sge/image/channel32f.hpp>
#include <sge/image/color/impl/dynamic/format/object_fwd.hpp>
#include <mizuiro/color/space/rgb.hpp>


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
namespace format
{

using
rgb_c32f_3
=
sge::image::color::impl::dynamic::format::object<
	mizuiro::color::space::rgb,
	sge::image::channel32f,
	3
>;

}
}
}
}
}
}

#endif
