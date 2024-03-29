//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/opengl/context/object_fwd.hpp>
#include <sge/opengl/context/use.hpp>
#include <sge/opengl/vertex/buffer.hpp>
#include <sge/opengl/vertex/context.hpp>
#include <sge/opengl/vertex/declaration.hpp> // NOLINT(misc-include-cleaner)
#include <sge/opengl/vertex/unset_buffer.hpp>
#include <sge/renderer/exception.hpp>
#include <sge/renderer/vertex/buffer.hpp>
#include <sge/renderer/vf/dynamic/part_index.hpp>
#include <fcppt/make_ref.hpp>
#include <fcppt/text.hpp>
#include <fcppt/cast/static_downcast.hpp>
#include <fcppt/optional/to_exception.hpp>

void sge::opengl::vertex::unset_buffer(
    sge::opengl::context::object &_context, sge::renderer::vertex::buffer const &_buffer)
{
  auto &context{
      sge::opengl::context::use<sge::opengl::vertex::context>(fcppt::make_ref(_context))};

  sge::renderer::vf::dynamic::part_index const index(_buffer.format_part_index());

  fcppt::cast::static_downcast<sge::opengl::vertex::buffer const &>(_buffer).unuse(
      fcppt::optional::to_exception(
          context.vertex_declaration(),
          []
          { return sge::renderer::exception{FCPPT_TEXT("Opengl vertex declaration not set!" }); })
          ->gl_format_part(index));

  context.vertex_buffer(index, sge::opengl::vertex::context::optional_buffer());
}
