//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/opengl/common.hpp>
#include <sge/opengl/deref_fun_ptr.hpp>
#include <sge/opengl/context/base.hpp>
#include <sge/opengl/context/id.hpp>
#include <sge/opengl/context/make_id.hpp>
#include <sge/opengl/info/cast_function.hpp>
#include <sge/opengl/info/context.hpp>
#include <sge/opengl/info/major_version.hpp>
#include <sge/opengl/info/minor_version.hpp>
#include <sge/opengl/info/version_at_least.hpp>
#include <sge/opengl/state/core/blend/config.hpp>
#include <sge/opengl/state/core/blend/context.hpp>
#include <sge/opengl/state/core/blend/optional_config.hpp>
#include <fcppt/preprocessor/disable_clang_warning.hpp>
#include <fcppt/preprocessor/disable_gcc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>

FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_GCC_WARNING(-Wold-style-cast)

sge::opengl::state::core::blend::context::context(sge::opengl::info::context const &_info)
    : sge::opengl::context::base(),
      config_(
          sge::opengl::info::version_at_least(
              _info.version(),
              sge::opengl::info::major_version{1U},
              sge::opengl::info::minor_version{4U})
              ? sge::opengl::state::core::blend::optional_config(
                    sge::opengl::state::core::blend::config(sge::opengl::deref_fun_ptr(
                        sge::opengl::info::cast_function<PFNGLBLENDFUNCSEPARATEPROC>(
                            _info.load_function("glBlendFuncSeparate")))))
              : sge::opengl::state::core::blend::optional_config())
{
}

FCPPT_PP_POP_WARNING

sge::opengl::state::core::blend::context::~context() = default;

sge::opengl::state::core::blend::optional_config const &
sge::opengl::state::core::blend::context::config() const
{
  return config_;
}

FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_CLANG_WARNING(-Wglobal-constructors)

sge::opengl::context::id const
    sge::opengl::state::core::blend::context::static_id(sge::opengl::context::make_id());

FCPPT_PP_POP_WARNING
