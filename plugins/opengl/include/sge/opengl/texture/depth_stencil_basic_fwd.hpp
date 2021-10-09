//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_OPENGL_TEXTURE_DEPTH_STENCIL_BASIC_FWD_HPP_INCLUDED
#define SGE_OPENGL_TEXTURE_DEPTH_STENCIL_BASIC_FWD_HPP_INCLUDED

#include <sge/opengl/texture/basic_box_fwd.hpp>
#include <sge/opengl/texture/depth_stencil_types_fwd.hpp>

namespace sge::opengl::texture
{

using depth_stencil_basic =
    sge::opengl::texture::basic_box<sge::opengl::texture::depth_stencil_types>;

}

#endif
