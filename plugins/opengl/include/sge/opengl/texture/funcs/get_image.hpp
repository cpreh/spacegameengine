//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_OPENGL_TEXTURE_FUNCS_GET_IMAGE_HPP_INCLUDED
#define SGE_OPENGL_TEXTURE_FUNCS_GET_IMAGE_HPP_INCLUDED

#include <sge/opengl/color_base_type.hpp>
#include <sge/opengl/color_order.hpp>
#include <sge/opengl/texture/binding_fwd.hpp>
#include <sge/opengl/texture/buffer_type.hpp>
#include <sge/renderer/raw_pointer.hpp>
#include <sge/renderer/texture/mipmap/level.hpp>


namespace sge
{
namespace opengl
{
namespace texture
{
namespace funcs
{

void
get_image(
	sge::opengl::texture::binding const &,
	sge::opengl::texture::buffer_type,
	sge::opengl::color_order,
	sge::opengl::color_base_type,
	sge::renderer::raw_pointer dest,
	sge::renderer::texture::mipmap::level
);

}
}
}
}

#endif
