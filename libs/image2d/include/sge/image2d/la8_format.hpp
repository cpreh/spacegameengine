//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_IMAGE2D_LA8_FORMAT_HPP_INCLUDED
#define SGE_IMAGE2D_LA8_FORMAT_HPP_INCLUDED

#include <sge/image/color/la8_format.hpp>
#include <sge/image/view/basic_format.hpp>

namespace sge::image2d
{

using la8_format = sge::image::view::basic_format<2, sge::image::color::la8_format>;

}

#endif
