//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_OPENGL_TEXTURE_DEPTH_STENCIL_SURFACE_FWD_HPP_INCLUDED
#define SGE_OPENGL_TEXTURE_DEPTH_STENCIL_SURFACE_FWD_HPP_INCLUDED

#include <sge/opengl/texture/basic_buffer_fwd.hpp>
#include <sge/opengl/texture/depth_stencil_surface_types_fwd.hpp>


namespace sge
{
namespace opengl
{
namespace texture
{

typedef
sge::opengl::texture::basic_buffer<
	sge::opengl::texture::depth_stencil_surface_types
>
depth_stencil_surface;

}
}
}

#endif
