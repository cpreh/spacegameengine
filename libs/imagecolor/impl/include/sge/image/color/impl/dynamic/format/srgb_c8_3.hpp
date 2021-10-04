//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_IMAGE_COLOR_IMPL_DYNAMIC_FORMAT_SRGB_C8_3_HPP_INCLUDED
#define SGE_IMAGE_COLOR_IMPL_DYNAMIC_FORMAT_SRGB_C8_3_HPP_INCLUDED

#include <sge/image/channel8.hpp>
#include <sge/image/color/impl/dynamic/format/object_fwd.hpp>
#include <mizuiro/color/space/srgb.hpp>


namespace sge::image::color::impl::dynamic::format
{

using
srgb_c8_3
=
sge::image::color::impl::dynamic::format::object<
	mizuiro::color::space::srgb,
	sge::image::channel8,
	3
>;

}

#endif
