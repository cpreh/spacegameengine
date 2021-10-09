//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_OPENGL_TEXTURE_CONVERT_BASE_TYPE_FUNCTION_HPP_INCLUDED
#define SGE_OPENGL_TEXTURE_CONVERT_BASE_TYPE_FUNCTION_HPP_INCLUDED

#include <sge/opengl/color_base_type.hpp>

namespace sge::opengl::texture
{

template <typename Format>
using convert_base_type_function = sge::opengl::color_base_type (&)(Format);

}

#endif
