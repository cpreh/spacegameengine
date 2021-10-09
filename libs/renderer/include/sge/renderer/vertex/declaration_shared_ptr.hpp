//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_RENDERER_VERTEX_DECLARATION_SHARED_PTR_HPP_INCLUDED
#define SGE_RENDERER_VERTEX_DECLARATION_SHARED_PTR_HPP_INCLUDED

#include <sge/renderer/vertex/declaration_fwd.hpp>
#include <fcppt/shared_ptr_impl.hpp>

namespace sge
{
namespace renderer
{
namespace vertex
{

/**
\brief A shared pointer to an sge::renderer::vertex::declaration
*/
typedef fcppt::shared_ptr<sge::renderer::vertex::declaration> declaration_shared_ptr;

}
}
}

#endif
