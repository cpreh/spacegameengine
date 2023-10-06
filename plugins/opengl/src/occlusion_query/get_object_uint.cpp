//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/opengl/call_fun_ref.hpp>
#include <sge/opengl/check_state.hpp>
#include <sge/opengl/occlusion_query/config.hpp>
#include <sge/opengl/occlusion_query/get_object_uint.hpp>
#include <sge/opengl/occlusion_query/id.hpp>
#include <sge/renderer/exception.hpp>
#include <sge/renderer/opengl/glinclude.hpp>
#include <fcppt/text.hpp>

GLuint sge::opengl::occlusion_query::get_object_uint(
    sge::opengl::occlusion_query::config const &_config,
    sge::opengl::occlusion_query::id const _id,
    GLenum const _what)
{
  GLuint result{};

  sge::opengl::call_fun_ref(_config.get_query_object_uiv(), _id.get(), _what, &result);

  SGE_OPENGL_CHECK_STATE(
      FCPPT_TEXT("Getting an unsigned int from an occlusion query failed"),
      sge::renderer::exception)

  return result;
}
