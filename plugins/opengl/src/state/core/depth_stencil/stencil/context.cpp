//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/opengl/deref_fun_ptr.hpp>
#include <sge/opengl/ext.hpp>
#include <sge/opengl/context/base.hpp>
#include <sge/opengl/context/id.hpp>
#include <sge/opengl/context/make_id.hpp>
#include <sge/opengl/info/cast_function.hpp>
#include <sge/opengl/info/context.hpp>
#include <sge/opengl/info/major_version.hpp>
#include <sge/opengl/info/minor_version.hpp>
#include <sge/opengl/info/version_at_least.hpp>
#include <sge/opengl/state/core/depth_stencil/stencil/config.hpp>
#include <sge/opengl/state/core/depth_stencil/stencil/context.hpp>
#include <sge/opengl/state/core/depth_stencil/stencil/optional_config.hpp>
#include <fcppt/preprocessor/disable_clang_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>

sge::opengl::state::core::depth_stencil::stencil::context::context(
    sge::opengl::info::context const &_info)
    : sge::opengl::context::base(),
      config_(
          sge::opengl::info::version_at_least(
              _info.version(),
              sge::opengl::info::major_version{2U},
              sge::opengl::info::minor_version{0U})
              ? sge::opengl::state::core::depth_stencil::stencil::optional_config(
                    sge::opengl::state::core::depth_stencil::stencil::config(
                        sge::opengl::deref_fun_ptr(
                            sge::opengl::info::cast_function<PFNGLSTENCILFUNCSEPARATEPROC>(
                                _info.load_function("glStencilFuncSeparate"))),
                        sge::opengl::deref_fun_ptr(
                            sge::opengl::info::cast_function<PFNGLSTENCILOPSEPARATEPROC>(
                                _info.load_function("glStencilOpSeparate")))))
              : sge::opengl::state::core::depth_stencil::stencil::optional_config())
{
}

sge::opengl::state::core::depth_stencil::stencil::context::~context() = default;

sge::opengl::state::core::depth_stencil::stencil::optional_config const &
sge::opengl::state::core::depth_stencil::stencil::context::config() const
{
  return config_;
}

FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_CLANG_WARNING(-Wglobal-constructors)

sge::opengl::context::id const sge::opengl::state::core::depth_stencil::stencil::context::static_id(
    sge::opengl::context::make_id());

FCPPT_PP_POP_WARNING
