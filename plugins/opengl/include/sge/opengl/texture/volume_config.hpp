//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_OPENGL_TEXTURE_VOLUME_CONFIG_HPP_INCLUDED
#define SGE_OPENGL_TEXTURE_VOLUME_CONFIG_HPP_INCLUDED

#include <sge/opengl/common.hpp>
#include <sge/opengl/fun_ref.hpp>
#include <sge/opengl/texture/type.hpp>
#include <sge/opengl/texture/volume_config_fwd.hpp>

namespace sge::opengl::texture
{

class volume_config
{
public:
  using gl_tex_image_3d = sge::opengl::fun_ref<PFNGLTEXIMAGE3DPROC>;

  using gl_tex_sub_image_3d = sge::opengl::fun_ref<PFNGLTEXSUBIMAGE3DPROC>;

  volume_config(
      sge::opengl::texture::type, gl_tex_image_3d, gl_tex_sub_image_3d, GLenum max_extent_flag);

  [[nodiscard]] sge::opengl::texture::type volume_texture_type() const;

  [[nodiscard]] gl_tex_image_3d tex_image_3d() const;

  [[nodiscard]] gl_tex_sub_image_3d tex_sub_image_3d() const;

  [[nodiscard]] GLenum max_extent_flag() const;

private:
  sge::opengl::texture::type volume_texture_type_;

  gl_tex_image_3d tex_image_3d_;

  gl_tex_sub_image_3d tex_sub_image_3d_;

  GLenum max_extent_flag_;
};

}

#endif
