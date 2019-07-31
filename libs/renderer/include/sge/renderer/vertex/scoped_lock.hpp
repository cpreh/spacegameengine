//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_RENDERER_VERTEX_SCOPED_LOCK_HPP_INCLUDED
#define SGE_RENDERER_VERTEX_SCOPED_LOCK_HPP_INCLUDED

#include <sge/renderer/buffer/detail/declare_scoped_lock.hpp>
#include <sge/renderer/vertex/scoped_lock_fwd.hpp>
#include <sge/renderer/vertex/tag.hpp>
#include <sge/renderer/vertex/traits/dimension.hpp>
#include <sge/renderer/vertex/traits/view_fwd.hpp>
#include <sge/renderer/vf/dynamic/view.hpp>


SGE_RENDERER_BUFFER_DETAIL_DECLARE_SCOPED_LOCK(
	sge::renderer::vertex::tag
);

#endif
