//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_IMAGE_PIXEL_MIZUIRO_TYPE_FWD_HPP_INCLUDED
#define SGE_IMAGE_PIXEL_MIZUIRO_TYPE_FWD_HPP_INCLUDED

#include <mizuiro/color/object_fwd.hpp>

namespace sge::image::pixel
{

template <typename Format>
using mizuiro_type = mizuiro::color::object<Format>;

}

#endif
