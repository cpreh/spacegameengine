//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/opengl/deref_fun_ptr.hpp>
#include <sge/opengl/ext.hpp>
#include <sge/opengl/get_int.hpp>
#include <sge/opengl/context/base.hpp>
#include <sge/opengl/context/id.hpp>
#include <sge/opengl/context/make_id.hpp>
#include <sge/opengl/info/cast_function.hpp>
#include <sge/opengl/info/context.hpp>
#include <sge/opengl/info/extension.hpp>
#include <sge/opengl/info/extension_supported.hpp>
#include <sge/opengl/info/major_version.hpp>
#include <sge/opengl/info/minor_version.hpp>
#include <sge/opengl/info/version_at_least.hpp>
#include <sge/opengl/texture/multi_config.hpp>
#include <sge/opengl/texture/multi_context.hpp>
#include <sge/opengl/texture/optional_multi_config.hpp>
#include <sge/renderer/caps/texture_stages.hpp>
#include <sge/renderer/opengl/glinclude.hpp>
#include <fcppt/strong_typedef_construct_cast.hpp>
#include <fcppt/cast/static_cast_fun.hpp>
#include <fcppt/optional/make_if.hpp>
#include <fcppt/preprocessor/disable_clang_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>
#include <fcppt/config/external_begin.hpp>
#include <algorithm>
#include <fcppt/config/external_end.hpp>

sge::opengl::texture::multi_context::multi_context(sge::opengl::info::context const &_info)
    : sge::opengl::context::base(),
      config_{
          sge::opengl::info::version_at_least(
              _info.version(),
              sge::opengl::info::major_version{1U},
              sge::opengl::info::minor_version{3U})
              ? sge::opengl::texture::optional_multi_config(sge::opengl::texture::multi_config(
                    sge::opengl::texture::multi_config::active_texture_type{
                        sge::opengl::deref_fun_ptr(
                            sge::opengl::info::cast_function<PFNGLACTIVETEXTUREPROC>(
                                _info.load_function("glActiveTexture")))},
                    sge::opengl::texture::multi_config::client_active_texture_type{
                        sge::opengl::deref_fun_ptr(
                            sge::opengl::info::cast_function<
                                sge::opengl::texture::multi_config::gl_client_active_texture_proc>(
                                _info.load_function("glClientActiveTexture")))},
                    fcppt::strong_typedef_construct_cast<
                        sge::renderer::caps::texture_stages,
                        fcppt::cast::static_cast_fun>(std::min(
                        sge::opengl::get_int(GL_MAX_TEXTURE_COORDS),
                        sge::opengl::get_int(GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS)))))
              : fcppt::optional::make_if(
                    sge::opengl::info::extension_supported(
                        _info.extensions(), sge::opengl::info::extension{"GL_ARB_multitexture"}),
                    [&_info]
                    {
                      return sge::opengl::texture::multi_config{
                          sge::opengl::texture::multi_config::active_texture_type{
                              sge::opengl::deref_fun_ptr(
                                  sge::opengl::info::cast_function<PFNGLACTIVETEXTUREPROC>(
                                      _info.load_function("glActiveTextureARB")))},
                          sge::opengl::texture::multi_config::client_active_texture_type{
                              sge::opengl::deref_fun_ptr(sge::opengl::info::cast_function<
                                                         sge::opengl::texture::multi_config::
                                                             gl_client_active_texture_proc>(
                                  _info.load_function("glClientActiveTextureARB")))},
                          fcppt::strong_typedef_construct_cast<
                              sge::renderer::caps::texture_stages,
                              fcppt::cast::static_cast_fun>(std::min(
                              sge::opengl::get_int(GL_MAX_TEXTURE_COORDS_ARB),
                              sge::opengl::get_int(GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS_ARB)))};
                    })}
{
}

sge::opengl::texture::multi_context::~multi_context() = default;

sge::opengl::texture::optional_multi_config const &
sge::opengl::texture::multi_context::config() const
{
  return config_;
}

FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_CLANG_WARNING(-Wglobal-constructors)

sge::opengl::context::id const
    sge::opengl::texture::multi_context::static_id(sge::opengl::context::make_id());

FCPPT_PP_POP_WARNING
