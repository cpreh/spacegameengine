//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/opengl/call.hpp>
#include <sge/opengl/check_state.hpp>
#include <sge/opengl/draw_arrays.hpp>
#include <sge/opengl/convert/primitive_type.hpp>
#include <sge/renderer/exception.hpp>
#include <sge/renderer/primitive_type.hpp>
#include <sge/renderer/opengl/glinclude.hpp>
#include <sge/renderer/vertex/count.hpp>
#include <sge/renderer/vertex/first.hpp>
#include <fcppt/text.hpp>
#include <fcppt/cast/size.hpp>
#include <fcppt/cast/to_signed.hpp>
#include <fcppt/log/object_fwd.hpp>
#include <fcppt/log/out.hpp>
#include <fcppt/log/warning.hpp>

void sge::opengl::draw_arrays(
    fcppt::log::object &_log,
    sge::renderer::vertex::first const _first_vertex,
    sge::renderer::vertex::count const _num_vertices,
    sge::renderer::primitive_type const _primitive_type)
{
  if (_num_vertices.get() == 0U)
  {
    FCPPT_LOG_WARNING(
        _log,
        fcppt::log::out << FCPPT_TEXT("Empty render() call. ") << FCPPT_TEXT("vertex_count was 0."))

    return;
  }

  sge::opengl::call(
      ::glDrawArrays,
      sge::opengl::convert::primitive_type(_primitive_type),
      fcppt::cast::size<GLsizei>(fcppt::cast::to_signed(_first_vertex.get())),
      fcppt::cast::size<GLint>(fcppt::cast::to_signed(_num_vertices.get())));

  SGE_OPENGL_CHECK_STATE(FCPPT_TEXT("glDrawArrays failed"), sge::renderer::exception)
}
