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
#include <sge/opengl/state/ffp/transform/context.hpp>
#include <fcppt/preprocessor/disable_clang_warning.hpp>
#include <fcppt/preprocessor/disable_gcc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>

FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_GCC_WARNING(-Wold-style-cast)

sge::opengl::state::ffp::transform::context::context(sge::opengl::info::context const &_info)
    : sge::opengl::context::base(),
      load_transpose_matrix_f_(
          sge::opengl::info::version_at_least(
              _info.version(),
              sge::opengl::info::major_version{1U},
              sge::opengl::info::minor_version{0U})
              ? optional_load_transpose_matrix_f(sge::opengl::deref_fun_ptr(
                    sge::opengl::info::cast_function<gl_load_transpose_matrix_proc>(
                        _info.load_function("glLoadTransposeMatrixf"))))
              : optional_load_transpose_matrix_f())
{
}

FCPPT_PP_POP_WARNING

sge::opengl::state::ffp::transform::context::~context() = default;

sge::opengl::state::ffp::transform::context::optional_load_transpose_matrix_f
sge::opengl::state::ffp::transform::context::load_transpose_matrix_f() const
{
  return load_transpose_matrix_f_;
}

bool sge::opengl::state::ffp::transform::context::have_transpose() const
{
  return load_transpose_matrix_f_.has_value();
}

FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_CLANG_WARNING(-Wglobal-constructors)

sge::opengl::context::id const
    sge::opengl::state::ffp::transform::context::static_id(sge::opengl::context::make_id());

FCPPT_PP_POP_WARNING
