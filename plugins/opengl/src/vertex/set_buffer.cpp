//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/opengl/context/object_fwd.hpp>
#include <sge/opengl/context/use.hpp>
#include <sge/opengl/vertex/buffer.hpp>
#include <sge/opengl/vertex/context.hpp>
#include <sge/opengl/vertex/declaration.hpp>
#include <sge/opengl/vertex/set_buffer.hpp>
#include <sge/opengl/vertex/unset_buffer.hpp>
#include <sge/renderer/exception.hpp>
#include <sge/renderer/vertex/buffer.hpp>
#include <sge/renderer/vertex/const_buffer_ref.hpp>
#include <sge/renderer/vf/dynamic/part_index.hpp>
#include <fcppt/make_cref.hpp>
#include <fcppt/make_ref.hpp>
#include <fcppt/reference_impl.hpp>
#include <fcppt/text.hpp>
#include <fcppt/cast/static_downcast.hpp>
#include <fcppt/optional/maybe_void.hpp>
#include <fcppt/optional/to_exception.hpp>
#include <fcppt/preprocessor/ignore_dangling_reference.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>

void sge::opengl::vertex::set_buffer(
    sge::opengl::context::object &_context, sge::renderer::vertex::const_buffer_ref const _buffer)
{
  sge::opengl::vertex::context &context{
      sge::opengl::context::use<sge::opengl::vertex::context>(fcppt::make_ref(_context))};

  sge::renderer::vf::dynamic::part_index const index{_buffer.get().format_part_index()};

  fcppt::optional::maybe_void(
      context.vertex_buffer(index),
      [&_context](fcppt::reference<sge::opengl::vertex::buffer const> const _old_buffer)
      { sge::opengl::vertex::unset_buffer(_context, _old_buffer.get()); });

  FCPPT_PP_PUSH_WARNING
  FCPPT_PP_IGNORE_DANGLING_REFERENCE
  sge::opengl::vertex::declaration const &vertex_declaration{fcppt::optional::to_exception(
      context.vertex_declaration(),
      [] { return sge::renderer::exception{FCPPT_TEXT("Opengl vertex declaration not set!" }); }).get()};
  FCPPT_PP_POP_WARNING

  sge::opengl::vertex::buffer const &gl_buffer{
      fcppt::cast::static_downcast<sge::opengl::vertex::buffer const &>(_buffer.get())};

  context.vertex_buffer(
      index, sge::opengl::vertex::context::optional_buffer(fcppt::make_cref(gl_buffer)));

  gl_buffer.use(vertex_declaration.gl_format_part(index));
}
