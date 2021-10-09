//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/opengl/call_fun_ref.hpp>
#include <sge/opengl/check_state.hpp>
#include <sge/opengl/common.hpp>
#include <sge/opengl/vf/attribute_config.hpp>
#include <sge/opengl/vf/attribute_context_fwd.hpp>
#include <sge/opengl/vf/enable_vertex_attrib_array.hpp>
#include <sge/opengl/vf/get_attribute_config.hpp>
#include <sge/renderer/exception.hpp>
#include <fcppt/text.hpp>

void sge::opengl::vf::enable_vertex_attrib_array(
    sge::opengl::vf::attribute_context const &_context, GLuint const _index)
{
  sge::opengl::call_fun_ref(
      sge::opengl::vf::get_attribute_config(_context).enable_vertex_attrib_array(), _index);

  SGE_OPENGL_CHECK_STATE(
      FCPPT_TEXT("Enabling a vertex attrib array failed"), sge::renderer::exception)
}
