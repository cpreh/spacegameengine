//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_RENDERER_INDEX_BUFFER_SHARED_PTR_HPP_INCLUDED
#define SGE_RENDERER_INDEX_BUFFER_SHARED_PTR_HPP_INCLUDED

#include <sge/renderer/index/buffer_fwd.hpp>
#include <fcppt/shared_ptr_impl.hpp>


namespace sge
{
namespace renderer
{
namespace index
{

/**
\brief A shared pointer to an sge::renderer::index::buffer
*/
typedef
fcppt::shared_ptr<
	sge::renderer::index::buffer
>
buffer_shared_ptr;

}
}
}

#endif
