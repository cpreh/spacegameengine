//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_SPRITE_DETAIL_RENDER_SCOPED_VERTEX_DECLARATION_HPP_INCLUDED
#define SGE_SPRITE_DETAIL_RENDER_SCOPED_VERTEX_DECLARATION_HPP_INCLUDED

#include <sge/renderer/context/core_ref.hpp>
#include <sge/renderer/vertex/const_declaration_ref.hpp>
#include <sge/sprite/detail/symbol.hpp>
#include <sge/sprite/state/vertex_options.hpp>
#include <fcppt/nonmovable.hpp>

namespace sge::sprite::detail::render
{

class scoped_vertex_declaration
{
  FCPPT_NONMOVABLE(scoped_vertex_declaration);

public:
  SGE_SPRITE_DETAIL_SYMBOL
  scoped_vertex_declaration(
      sge::renderer::context::core_ref,
      sge::renderer::vertex::const_declaration_ref,
      sge::sprite::state::vertex_options const &);

  SGE_SPRITE_DETAIL_SYMBOL
  ~scoped_vertex_declaration();

private:
  sge::renderer::context::core_ref const render_context_;

  // NOLINTNEXTLINE(cppcoreguidelines-use-default-member-init,modernize-use-default-member-init)
  bool const set_declaration_;
};

}

#endif
