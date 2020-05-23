//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_RENDERER_INDEX_SCOPED_LOCK_FWD_HPP_INCLUDED
#define SGE_RENDERER_INDEX_SCOPED_LOCK_FWD_HPP_INCLUDED

#include <sge/renderer/buffer/scoped_lock_fwd.hpp>
#include <sge/renderer/index/tag.hpp>


namespace sge
{
namespace renderer
{
namespace index
{

/**
\brief A scoped lock that locks an sge::renderer::index::buffer
*/
using
scoped_lock
=
sge::renderer::buffer::scoped_lock<
	sge::renderer::index::tag
>;

}
}
}

#endif
