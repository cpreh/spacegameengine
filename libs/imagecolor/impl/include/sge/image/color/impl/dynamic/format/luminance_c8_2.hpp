//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_IMAGE_COLOR_IMPL_DYNAMIC_FORMAT_LUMINANCE_C8_2_HPP_INCLUDED
#define SGE_IMAGE_COLOR_IMPL_DYNAMIC_FORMAT_LUMINANCE_C8_2_HPP_INCLUDED

#include <sge/image/channel8.hpp>
#include <sge/image/color/impl/dynamic/format/object_fwd.hpp>
#include <mizuiro/color/space/luminance.hpp>

namespace sge::image::color::impl::dynamic::format
{

using luminance_c8_2 = sge::image::color::impl::dynamic::format::
    object<mizuiro::color::space::luminance, sge::image::channel8, 2>;

}

#endif
