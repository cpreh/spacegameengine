//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/opengl/cg/texture/enable.hpp>
#include <sge/opengl/cg/texture/loaded_object.hpp>
#include <sge/renderer/cg/loaded_texture.hpp>
#include <sge/renderer/texture/stage.hpp>

sge::renderer::texture::stage
sge::opengl::cg::texture::enable(sge::renderer::cg::loaded_texture const &_texture)
{
  return dynamic_cast<sge::opengl::cg::texture::loaded_object const &>(_texture).enable();
}
