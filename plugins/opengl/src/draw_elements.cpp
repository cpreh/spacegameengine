//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/opengl/call.hpp>
#include <sge/opengl/check_state.hpp>
#include <sge/opengl/draw_context.hpp>
#include <sge/opengl/draw_elements.hpp>
#include <sge/opengl/context/object.hpp>
#include <sge/opengl/context/use.hpp>
#include <sge/opengl/convert/primitive_type.hpp>
#include <sge/opengl/index/buffer.hpp>
#include <sge/renderer/exception.hpp>
#include <sge/renderer/primitive_type.hpp>
#include <sge/renderer/index/buffer.hpp>
#include <sge/renderer/index/count.hpp>
#include <sge/renderer/index/first.hpp>
#include <sge/renderer/opengl/glinclude.hpp>
#include <sge/renderer/vertex/count.hpp>
#include <sge/renderer/vertex/first.hpp>
#include <fcppt/make_ref.hpp>
#include <fcppt/text.hpp>
#include <fcppt/cast/size.hpp>
#include <fcppt/cast/static_downcast.hpp>
#include <fcppt/cast/to_signed.hpp>
#include <fcppt/log/object_fwd.hpp>
#include <fcppt/log/out.hpp>
#include <fcppt/log/warning.hpp>
#include <fcppt/optional/maybe.hpp>

void sge::opengl::draw_elements(
    fcppt::log::object &_log,
    sge::opengl::context::object &_context,
    sge::renderer::index::buffer const &_index_buffer,
    sge::renderer::vertex::first const _first_vertex,
    sge::renderer::vertex::count const _num_vertices,
    sge::renderer::primitive_type const _primitive_type,
    sge::renderer::index::first const _first_index,
    sge::renderer::index::count const _num_indices)
{
  if (_primitive_type == sge::renderer::primitive_type::point_list)
  {
    FCPPT_LOG_WARNING(
        _log,
        fcppt::log::out << FCPPT_TEXT("Rendering point lists with index buffers is not portable!"))
  }

  if (_num_vertices.get() == 0U)
  {
    FCPPT_LOG_WARNING(
        _log,
        fcppt::log::out << FCPPT_TEXT("Empty render() call with index_buffer. ")
                        << FCPPT_TEXT("vertex_count was 0."))

    return;
  }

  sge::opengl::draw_context const &context(sge::opengl::context::use<sge::opengl::draw_context>(
      fcppt::make_ref(_context), _context.info()));

  auto const &gl_index_buffer{
      fcppt::cast::static_downcast<sge::opengl::index::buffer const &>(_index_buffer)};

  gl_index_buffer.bind();

  GLenum const primitive_type(sge::opengl::convert::primitive_type(_primitive_type));

  auto const element_count(fcppt::cast::size<GLsizei>(fcppt::cast::to_signed(_num_indices.get())));

  GLenum const format(gl_index_buffer.gl_format());

  GLvoid const *const offset(gl_index_buffer.buffer_offset(_first_index));

  fcppt::optional::maybe(
      context.draw_range_elements(),
      [primitive_type, element_count, format, offset]
      {
        sge::opengl::call(::glDrawElements, primitive_type, element_count, format, offset);

        SGE_OPENGL_CHECK_STATE(FCPPT_TEXT("glDrawElements failed"), sge::renderer::exception)
      },
      [primitive_type, element_count, format, offset, _first_vertex, _num_vertices](
          sge::opengl::draw_context::draw_range_elements_ref const _draw_elements)
      {
        _draw_elements.get()(
            primitive_type,
            fcppt::cast::size<GLuint>(_first_vertex.get()),
            fcppt::cast::size<GLuint>(_first_vertex.get() + _num_vertices.get() - 1U),
            element_count,
            format,
            offset);

        SGE_OPENGL_CHECK_STATE(FCPPT_TEXT("glDrawRangeElements failed"), sge::renderer::exception)
      });
}
