//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/opengl/context/base.hpp>
#include <sge/opengl/context/id.hpp>
#include <sge/opengl/context/make_id.hpp>
#include <sge/opengl/target/context.hpp>
#include <sge/opengl/target/optional_base_ref.hpp>
#include <fcppt/preprocessor/disable_clang_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>

sge::opengl::target::context::context() : sge::opengl::context::base(), last_target_() {}

sge::opengl::target::context::~context() = default;

sge::opengl::target::optional_base_ref const &sge::opengl::target::context::last_target()
{
  return last_target_;
}

void sge::opengl::target::context::last_target(
    sge::opengl::target::optional_base_ref const &_target)
{
  last_target_ = _target;
}

FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_CLANG_WARNING(-Wglobal-constructors)

sge::opengl::context::id const
    sge::opengl::target::context::static_id(sge::opengl::context::make_id());

FCPPT_PP_POP_WARNING
