//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/opengl/call_fun_ref.hpp>
#include <sge/opengl/check_state.hpp>
#include <sge/opengl/occlusion_query/config.hpp>
#include <sge/opengl/occlusion_query/end.hpp>
#include <sge/renderer/exception.hpp>
#include <fcppt/text.hpp>

void sge::opengl::occlusion_query::end(sge::opengl::occlusion_query::config const &_config)
{
  sge::opengl::call_fun_ref(_config.end_query(), _config.samples_target());

  SGE_OPENGL_CHECK_STATE(FCPPT_TEXT("Ending an occlusion query failed"), sge::renderer::exception)
}
