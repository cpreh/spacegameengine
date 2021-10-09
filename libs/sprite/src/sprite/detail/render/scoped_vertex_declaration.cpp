//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/renderer/context/core.hpp>
#include <sge/renderer/context/core_ref.hpp>
#include <sge/renderer/vertex/const_declaration_ref.hpp>
#include <sge/renderer/vertex/const_optional_declaration_ref.hpp>
#include <sge/sprite/detail/render/scoped_vertex_declaration.hpp>
#include <sge/sprite/state/vertex_options.hpp>

sge::sprite::detail::render::scoped_vertex_declaration::scoped_vertex_declaration(
    sge::renderer::context::core_ref const _render_context,
    sge::renderer::vertex::const_declaration_ref const _vertex_declaration,
    sge::sprite::state::vertex_options const &_options)
    : render_context_(_render_context),
      set_declaration_(
          _options == sge::sprite::state::vertex_options::declaration ||
          _options == sge::sprite::state::vertex_options::declaration_and_buffer)
{
  if (set_declaration_)
  {
    render_context_.get().vertex_declaration(
        sge::renderer::vertex::const_optional_declaration_ref(_vertex_declaration));
  }
}

sge::sprite::detail::render::scoped_vertex_declaration::~scoped_vertex_declaration()
{
  if (set_declaration_)
  {
    render_context_.get().vertex_declaration(
        sge::renderer::vertex::const_optional_declaration_ref());
  }
}
