//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_IMAGE_COLOR_IMPL_DYNAMIC_FORMAT_EMPTY_C8_1_HPP_INCLUDED
#define SGE_IMAGE_COLOR_IMPL_DYNAMIC_FORMAT_EMPTY_C8_1_HPP_INCLUDED

#include <sge/image/channel8.hpp>
#include <sge/image/color/impl/dynamic/format/object_fwd.hpp>
#include <mizuiro/color/space/empty.hpp>


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
empty_c8_1
=
sge::image::color::impl::dynamic::format::object<
	mizuiro::color::space::empty,
	sge::image::channel8,
	1
>;

}
}
}
}
}
}

#endif
