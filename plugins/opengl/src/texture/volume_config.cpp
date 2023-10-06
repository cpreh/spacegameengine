//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/opengl/texture/type.hpp>
#include <sge/opengl/texture/volume_config.hpp>
#include <sge/renderer/opengl/glinclude.hpp>

sge::opengl::texture::volume_config::volume_config(
    sge::opengl::texture::type const _volume_texture_type,
    gl_tex_image_3d _tex_image_3d,
    gl_tex_sub_image_3d _tex_sub_image_3d,
    GLenum const _max_extent_flag)
    : volume_texture_type_(_volume_texture_type),
      tex_image_3d_(_tex_image_3d),
      tex_sub_image_3d_(_tex_sub_image_3d),
      max_extent_flag_(_max_extent_flag)
{
}

sge::opengl::texture::type sge::opengl::texture::volume_config::volume_texture_type() const
{
  return volume_texture_type_;
}

sge::opengl::texture::volume_config::gl_tex_image_3d
sge::opengl::texture::volume_config::tex_image_3d() const
{
  return tex_image_3d_;
}

sge::opengl::texture::volume_config::gl_tex_sub_image_3d
sge::opengl::texture::volume_config::tex_sub_image_3d() const
{
  return tex_sub_image_3d_;
}

GLenum sge::opengl::texture::volume_config::max_extent_flag() const { return max_extent_flag_; }
