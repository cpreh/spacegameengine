//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_OPENGL_FBO_ATTACH_TEXTURE_2D_HPP_INCLUDED
#define SGE_OPENGL_FBO_ATTACH_TEXTURE_2D_HPP_INCLUDED

#include <sge/opengl/fbo/attachment_type.hpp>
#include <sge/opengl/fbo/config_fwd.hpp>
#include <sge/opengl/texture/buffer_type.hpp>
#include <sge/opengl/texture/id.hpp>
#include <sge/renderer/texture/mipmap/level.hpp>


namespace sge::opengl::fbo
{

void
attach_texture_2d(
	sge::opengl::fbo::config const &,
	sge::opengl::fbo::attachment_type,
	sge::opengl::texture::buffer_type,
	sge::opengl::texture::id,
	sge::renderer::texture::mipmap::level
);

}

#endif
