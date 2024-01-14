//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_OPENGL_TEXTURE_MULTI_CONFIG_HPP_INCLUDED
#define SGE_OPENGL_TEXTURE_MULTI_CONFIG_HPP_INCLUDED

#include <sge/opengl/ext.hpp> // IWYU pragma: keep
#include <sge/opengl/fun_ref.hpp>
#include <sge/opengl/texture/multi_config_fwd.hpp> // IWYU pragma: keep
#include <sge/renderer/caps/texture_stages.hpp>
#include <sge/renderer/opengl/glinclude.hpp> // IWYU pragma: keep
#include <fcppt/declare_strong_typedef.hpp>
#include <fcppt/strong_typedef_impl.hpp> // IWYU pragma: keep

namespace sge::opengl::texture
{

class multi_config
{
public:
  using gl_active_texture = sge::opengl::fun_ref<PFNGLACTIVETEXTUREPROC>;

  // TODO(philipp): mesa headers are broken
  //PFNGLCLIENTACTIVETEXTUREPROC
  using gl_client_active_texture_proc = PFNGLACTIVETEXTUREPROC;

  using gl_client_active_texture = sge::opengl::fun_ref<gl_client_active_texture_proc>;

  FCPPT_DECLARE_STRONG_TYPEDEF(gl_active_texture, active_texture_type);
  FCPPT_DECLARE_STRONG_TYPEDEF(gl_client_active_texture, client_active_texture_type);

  multi_config(
      active_texture_type, client_active_texture_type, sge::renderer::caps::texture_stages);

  [[nodiscard]] gl_active_texture active_texture() const;

  [[nodiscard]] gl_client_active_texture client_active_texture() const;

  [[nodiscard]] sge::renderer::caps::texture_stages max_level() const;

private:
  gl_active_texture active_texture_;

  gl_client_active_texture client_active_texture_;

  sge::renderer::caps::texture_stages max_level_;
};

}

#endif
