//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_OPENGL_CONVERT_DEPTH_STENCIL_ORDER_HPP_INCLUDED
#define SGE_OPENGL_CONVERT_DEPTH_STENCIL_ORDER_HPP_INCLUDED

#include <sge/image/ds/format_fwd.hpp>
#include <sge/opengl/color_order.hpp>

namespace sge::opengl::convert
{

sge::opengl::color_order depth_stencil_order(sge::image::ds::format);

}

#endif
