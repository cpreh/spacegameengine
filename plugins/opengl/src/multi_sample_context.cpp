//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/opengl/ext.hpp>
#include <sge/opengl/multi_sample_context.hpp>
#include <sge/opengl/optional_enum.hpp>
#include <sge/opengl/context/base.hpp>
#include <sge/opengl/context/id.hpp>
#include <sge/opengl/context/make_id.hpp>
#include <sge/opengl/convert/to_gl_enum.hpp>
#include <sge/opengl/info/context.hpp>
#include <sge/opengl/info/extension.hpp>
#include <sge/opengl/info/extension_supported.hpp>
#include <sge/opengl/info/major_version.hpp>
#include <sge/opengl/info/minor_version.hpp>
#include <sge/opengl/info/version_at_least.hpp>
#include <sge/renderer/opengl/glinclude.hpp>
#include <fcppt/preprocessor/disable_clang_warning.hpp>
#include <fcppt/preprocessor/disable_gcc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>

FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_GCC_WARNING(-Wold-style-cast)

sge::opengl::multi_sample_context::multi_sample_context(sge::opengl::info::context const &_info)
    : sge::opengl::context::base(),
      flag_(
          sge::opengl::info::version_at_least(
              _info.version(),
              sge::opengl::info::major_version{1U},
              sge::opengl::info::minor_version{3U})
              ? sge::opengl::optional_enum(sge::opengl::convert::to_gl_enum<GL_MULTISAMPLE>())
          : sge::opengl::info::extension_supported(
                _info.extensions(), sge::opengl::info::extension{"GL_ARB_multisample"})
              ? sge::opengl::optional_enum(sge::opengl::convert::to_gl_enum<GL_MULTISAMPLE_ARB>())
              : sge::opengl::optional_enum())
{
}

FCPPT_PP_POP_WARNING

sge::opengl::multi_sample_context::~multi_sample_context() = default;

sge::opengl::optional_enum sge::opengl::multi_sample_context::flag() const { return flag_; }

FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_CLANG_WARNING(-Wglobal-constructors)

sge::opengl::context::id const
    sge::opengl::multi_sample_context::static_id(sge::opengl::context::make_id());

FCPPT_PP_POP_WARNING
