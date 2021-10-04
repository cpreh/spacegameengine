//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_RENDERER_VERTEX_CONST_BUFFER_REF_CONTAINER_HPP_INCLUDED
#define SGE_RENDERER_VERTEX_CONST_BUFFER_REF_CONTAINER_HPP_INCLUDED

#include <sge/renderer/vertex/const_buffer_ref.hpp>
#include <fcppt/config/external_begin.hpp>
#include <vector>
#include <fcppt/config/external_end.hpp>


namespace sge::renderer::vertex
{

/**
\brief A container of const vertex buffer references
*/
using
const_buffer_ref_container
=
std::vector<
	sge::renderer::vertex::const_buffer_ref
>;

}

#endif
