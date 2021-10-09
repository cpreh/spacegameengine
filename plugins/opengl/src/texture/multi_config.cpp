//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/opengl/texture/multi_config.hpp>
#include <sge/renderer/caps/texture_stages.hpp>

sge::opengl::texture::multi_config::multi_config(
    gl_active_texture _active_texture,
    gl_client_active_texture _client_active_texture,
    sge::renderer::caps::texture_stages const _max_level)
    : active_texture_(_active_texture),
      client_active_texture_(_client_active_texture),
      max_level_(_max_level)
{
}

sge::opengl::texture::multi_config::gl_active_texture
sge::opengl::texture::multi_config::active_texture() const
{
  return active_texture_;
}

sge::opengl::texture::multi_config::gl_client_active_texture
sge::opengl::texture::multi_config::client_active_texture() const
{
  return client_active_texture_;
}

sge::renderer::caps::texture_stages sge::opengl::texture::multi_config::max_level() const
{
  return max_level_;
}
