//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/opengl/call_fun_ref.hpp>
#include <sge/opengl/check_state.hpp>
#include <sge/opengl/occlusion_query/config.hpp>
#include <sge/opengl/occlusion_query/delete_id.hpp>
#include <sge/opengl/occlusion_query/id.hpp>
#include <sge/renderer/exception.hpp>
#include <fcppt/text.hpp>

void sge::opengl::occlusion_query::delete_id(
    sge::opengl::occlusion_query::config const &_config, sge::opengl::occlusion_query::id const _id)
{
  sge::opengl::call_fun_ref(_config.delete_queries(), 1, &_id.get());

  SGE_OPENGL_CHECK_STATE(FCPPT_TEXT("Generating a query failed"), sge::renderer::exception)
}
