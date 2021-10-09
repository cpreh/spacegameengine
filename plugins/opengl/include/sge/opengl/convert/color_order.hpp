//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_OPENGL_CONVERT_COLOR_ORDER_HPP_INCLUDED
#define SGE_OPENGL_CONVERT_COLOR_ORDER_HPP_INCLUDED

#include <sge/opengl/color_format.hpp>
#include <sge/opengl/color_order.hpp>

namespace sge::opengl::convert
{

sge::opengl::color_order color_order(sge::opengl::color_format);

}

#endif
