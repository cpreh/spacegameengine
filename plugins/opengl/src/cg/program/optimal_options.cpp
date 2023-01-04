//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/cg/check_state.hpp>
#include <sge/cg/exception.hpp>
#include <sge/cg/context/object.hpp>
#include <sge/cg/profile/object.hpp>
#include <sge/cg/program/compile_options.hpp>
#include <sge/opengl/cg/program/optimal_options.hpp>
#include <sge/renderer/exception.hpp>
#include <fcppt/text.hpp>
#include <fcppt/config/external_begin.hpp>
#include <Cg/cg.h>
#include <Cg/cgGL.h>
#include <fcppt/config/external_end.hpp>

sge::cg::program::compile_options sge::opengl::cg::program::optimal_options(
    sge::cg::context::object const &_context, sge::cg::profile::object const &_profile)
{
  sge::cg::char_type const **const ret{
      ::cgGLGetContextOptimalOptions(_context.get(), _profile.get())};

  SGE_CG_CHECK_STATE(FCPPT_TEXT("cgGLGetContextOptimalOptions failed"), sge::renderer::exception)

  if(ret == nullptr)
  {
    throw sge::cg::exception{FCPPT_TEXT("Cg GL optimal options are null!")};
  }

  return sge::cg::program::compile_options(ret);
}
