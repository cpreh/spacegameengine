//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_RENDERER_INDEX_CONST_SCOPED_LOCK_FWD_HPP_INCLUDED
#define SGE_RENDERER_INDEX_CONST_SCOPED_LOCK_FWD_HPP_INCLUDED

#include <sge/renderer/buffer/const_scoped_lock_fwd.hpp>
#include <sge/renderer/index/tag.hpp>


namespace sge
{
namespace renderer
{
namespace index
{

/**
\brief A scoped lock that locks a renderer::index_buffer readonly

\see sge::renderer::const_linear_buffer_scoped_lock
*/
typedef
sge::renderer::buffer::const_scoped_lock<
	sge::renderer::index::tag
>
const_scoped_lock;

}
}
}

#endif
