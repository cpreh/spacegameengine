//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_IMAGE3D_RGBA8_FORMAT_HPP_INCLUDED
#define SGE_IMAGE3D_RGBA8_FORMAT_HPP_INCLUDED

#include <sge/image/color/rgba8_format.hpp>
#include <sge/image/view/basic_format.hpp>

namespace sge::image3d
{

using rgba8_format = sge::image::view::basic_format<3, sge::image::color::rgba8_format>;

}

#endif
