//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/opengl/common.hpp>
#include <sge/opengl/deref_fun_ptr.hpp>
#include <sge/opengl/context/base.hpp>
#include <sge/opengl/context/id.hpp>
#include <sge/opengl/context/make_id.hpp>
#include <sge/opengl/convert/to_gl_enum.hpp>
#include <sge/opengl/info/cast_function.hpp>
#include <sge/opengl/info/context.hpp>
#include <sge/opengl/info/major_version.hpp>
#include <sge/opengl/info/minor_version.hpp>
#include <sge/opengl/info/version_at_least.hpp>
#include <sge/opengl/texture/optional_volume_config.hpp>
#include <sge/opengl/texture/volume_config.hpp>
#include <sge/opengl/texture/volume_context.hpp>
#include <sge/opengl/texture/convert/make_type.hpp>
#include <fcppt/preprocessor/disable_clang_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>

sge::opengl::texture::volume_context::volume_context(sge::opengl::info::context const &_info)
    : sge::opengl::context::base(),
      config_(
          sge::opengl::info::version_at_least(
              _info.version(),
              sge::opengl::info::major_version{1U},
              sge::opengl::info::minor_version{3U})
              ? sge::opengl::texture::optional_volume_config(sge::opengl::texture::volume_config(
                    sge::opengl::texture::convert::make_type(GL_TEXTURE_3D),
                    sge::opengl::deref_fun_ptr(
                        sge::opengl::info::cast_function<PFNGLTEXIMAGE3DPROC>(
                            _info.load_function("glTexImage3D"))),
                    sge::opengl::deref_fun_ptr(
                        sge::opengl::info::cast_function<PFNGLTEXSUBIMAGE3DPROC>(
                            _info.load_function("glTexSubImage3D"))),
                    sge::opengl::convert::to_gl_enum<GL_MAX_3D_TEXTURE_SIZE>()))
              : sge::opengl::texture::optional_volume_config())
{
}

sge::opengl::texture::volume_context::~volume_context() = default;

sge::opengl::texture::optional_volume_config const &
sge::opengl::texture::volume_context::config() const
{
  return config_;
}

FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_CLANG_WARNING(-Wglobal-constructors)

sge::opengl::context::id const
    sge::opengl::texture::volume_context::static_id(sge::opengl::context::make_id());

FCPPT_PP_POP_WARNING
