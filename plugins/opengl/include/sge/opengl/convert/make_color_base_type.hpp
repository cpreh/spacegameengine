//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_OPENGL_CONVERT_MAKE_COLOR_BASE_TYPE_HPP_INCLUDED
#define SGE_OPENGL_CONVERT_MAKE_COLOR_BASE_TYPE_HPP_INCLUDED

#include <sge/opengl/color_base_type.hpp>
#include <fcppt/cast/to_unsigned.hpp>

namespace sge::opengl::convert
{

template <int Format>
sge::opengl::color_base_type make_color_base_type()
{
  return sge::opengl::color_base_type{fcppt::cast::to_unsigned(Format)};
}

}

#endif
