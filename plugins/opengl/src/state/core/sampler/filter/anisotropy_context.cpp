//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/opengl/ext.hpp>
#include <sge/opengl/context/base.hpp>
#include <sge/opengl/context/id.hpp>
#include <sge/opengl/context/make_id.hpp>
#include <sge/opengl/convert/to_gl_enum.hpp>
#include <sge/opengl/info/context.hpp>
#include <sge/opengl/info/extension.hpp>
#include <sge/opengl/info/extension_supported.hpp>
#include <sge/opengl/state/core/sampler/filter/anisotropy_config.hpp>
#include <sge/opengl/state/core/sampler/filter/anisotropy_context.hpp>
#include <sge/opengl/state/core/sampler/filter/optional_anisotropy_config.hpp>
#include <fcppt/preprocessor/disable_clang_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>

sge::opengl::state::core::sampler::filter::anisotropy_context::anisotropy_context(
    sge::opengl::info::context const &_info)
    : sge::opengl::context::base(),
      config_(
          sge::opengl::info::extension_supported(
              _info.extensions(), sge::opengl::info::extension{"GL_EXT_texture_filter_anisotropic"})
              ? sge::opengl::state::core::sampler::filter::optional_anisotropy_config(
                    sge::opengl::state::core::sampler::filter::anisotropy_config(
                        sge::opengl::convert::to_gl_enum<GL_TEXTURE_MAX_ANISOTROPY_EXT>(),
                        sge::opengl::convert::to_gl_enum<GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT>()))
              : sge::opengl::state::core::sampler::filter::optional_anisotropy_config())
{
}

sge::opengl::state::core::sampler::filter::anisotropy_context::~anisotropy_context() = default;

sge::opengl::state::core::sampler::filter::optional_anisotropy_config const &
sge::opengl::state::core::sampler::filter::anisotropy_context::config() const
{
  return config_;
}

FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_CLANG_WARNING(-Wglobal-constructors)

sge::opengl::context::id const
    sge::opengl::state::core::sampler::filter::anisotropy_context::static_id(
        sge::opengl::context::make_id());

FCPPT_PP_POP_WARNING
