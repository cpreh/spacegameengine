//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/renderer/context/core.hpp> // NOLINT(misc-include-cleaner)
#include <sge/renderer/context/core_ref.hpp>
#include <sge/renderer/vertex/const_buffer_ref.hpp>
#include <sge/renderer/vertex/const_declaration_ref.hpp>
#include <sge/sprite/detail/render/scoped_vertex.hpp>
#include <sge/sprite/state/vertex_options.hpp>

sge::sprite::detail::render::scoped_vertex::scoped_vertex(
    sge::renderer::context::core_ref const _render_context,
    sge::renderer::vertex::const_declaration_ref const _vertex_declaration,
    sge::renderer::vertex::const_buffer_ref const _vertex_buffer,
    sge::sprite::state::vertex_options const &_options)
    : scoped_vertex_declaration_(_render_context, _vertex_declaration, _options),
      render_context_(_render_context),
      vertex_buffer_(_vertex_buffer),
      set_buffer_(
          _options == sge::sprite::state::vertex_options::buffer ||
          _options == sge::sprite::state::vertex_options::declaration_and_buffer)
{
  if (set_buffer_)
  {
    render_context_.get().activate_vertex_buffer(vertex_buffer_);
  }
}

sge::sprite::detail::render::scoped_vertex::~scoped_vertex()
{
  if (set_buffer_)
  {
    render_context_.get().deactivate_vertex_buffer(vertex_buffer_.get());
  }
}
