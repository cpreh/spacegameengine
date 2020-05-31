//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_RENDERER_VERTEX_CONST_BUFFER_REF_HPP_INCLUDED
#define SGE_RENDERER_VERTEX_CONST_BUFFER_REF_HPP_INCLUDED

#include <sge/renderer/vertex/buffer_fwd.hpp>
#include <fcppt/reference_impl.hpp>


namespace sge
{
namespace renderer
{
namespace vertex
{

/**
\brief A reference wrapper to const vertex buffers
*/
using
const_buffer_ref
=
fcppt::reference<
	sge::renderer::vertex::buffer const
>;

}
}
}

#endif
