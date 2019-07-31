//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_RENDERER_VERTEX_TO_PRIMITIVE_COUNT_HPP_INCLUDED
#define SGE_RENDERER_VERTEX_TO_PRIMITIVE_COUNT_HPP_INCLUDED

#include <sge/renderer/primitive_count.hpp>
#include <sge/renderer/primitive_type_fwd.hpp>
#include <sge/renderer/detail/symbol.hpp>
#include <sge/renderer/vertex/count.hpp>


namespace sge
{
namespace renderer
{
namespace vertex
{

/**
\brief Calculates how many primitives are described by a number of vertices

The number of vertices given by \a vertices (which could also be indirectly
given by a number of indices) combined with a certain primitive_type given by
\a type describe a certain number of primitives. For example, using the
sge::renderer::primitive_type::triangle_list

\param vertices The number of vertices (or a number of indices used to count
vertices)

\param type The primitive type
*/
SGE_RENDERER_DETAIL_SYMBOL
sge::renderer::primitive_count
to_primitive_count(
	sge::renderer::vertex::count vertices,
	sge::renderer::primitive_type type
);

}
}
}

#endif
