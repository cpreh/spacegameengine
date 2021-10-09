//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_RENDERER_VERTEX_DECLARATION_HPP_INCLUDED
#define SGE_RENDERER_VERTEX_DECLARATION_HPP_INCLUDED

#include <sge/core/detail/class_symbol.hpp>
#include <sge/renderer/detail/symbol.hpp>
#include <sge/renderer/vertex/declaration_fwd.hpp>
#include <fcppt/nonmovable.hpp>

namespace sge::renderer::vertex
{

/**
\brief A dynamic representation of a vertex format

In order to activate vertex buffers, the corresponding vertex declaration needs
to be set first.

\see sge::renderer::device::create_vertex_declaration

\see sge::renderer::device::vertex_declaration
*/
class SGE_CORE_DETAIL_CLASS_SYMBOL declaration
{
  FCPPT_NONMOVABLE(declaration);

protected:
  SGE_RENDERER_DETAIL_SYMBOL
  declaration();

public:
  SGE_RENDERER_DETAIL_SYMBOL
  virtual ~declaration();
};

}

#endif
