//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/cg/check_state.hpp>
#include <sge/cg/profile/object.hpp>
#include <sge/cg/program/object.hpp>
#include <sge/cg/program/object_ref.hpp>
#include <sge/opengl/cg/program/loaded_object.hpp>
#include <sge/renderer/exception.hpp>
#include <fcppt/text.hpp>
#include <fcppt/config/external_begin.hpp>
#include <Cg/cgGL.h>
#include <fcppt/config/external_end.hpp>

sge::opengl::cg::program::loaded_object::loaded_object(sge::cg::program::object_ref const _program)
    : program_(_program)
{
  ::cgGLLoadProgram(program_.get().get());

  SGE_CG_CHECK_STATE(FCPPT_TEXT("cgGLLoadProgram failed"), sge::renderer::exception)
}

sge::opengl::cg::program::loaded_object::~loaded_object()
{
  ::cgGLUnloadProgram(program_.get().get());
}

void sge::opengl::cg::program::loaded_object::activate() const
{
  {
    ::cgGLBindProgram(program_.get().get());

    SGE_CG_CHECK_STATE(FCPPT_TEXT("cgGLBindProgram"), sge::renderer::exception)
  }

  {
    ::cgGLEnableProfile(program_.get().profile().get());

    SGE_CG_CHECK_STATE(FCPPT_TEXT("cgGLEnableProfile"), sge::renderer::exception)
  }
}

void sge::opengl::cg::program::loaded_object::deactivate() const
{
  {
    ::cgGLDisableProfile(program_.get().profile().get());

    SGE_CG_CHECK_STATE(FCPPT_TEXT("cgGLDisableProfile"), sge::renderer::exception)
  }

  {
    ::cgGLUnbindProgram(program_.get().profile().get());

    SGE_CG_CHECK_STATE(FCPPT_TEXT("cgGLUnbindProgram"), sge::renderer::exception)
  }
}
