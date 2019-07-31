//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_RENDERER_INDEX_CONST_SCOPED_LOCK_HPP_INCLUDED
#define SGE_RENDERER_INDEX_CONST_SCOPED_LOCK_HPP_INCLUDED

#include <sge/renderer/buffer/detail/declare_const_scoped_lock.hpp>
#include <sge/renderer/index/const_scoped_lock_fwd.hpp>
#include <sge/renderer/index/tag.hpp>
#include <sge/renderer/index/dynamic/const_view.hpp>
#include <sge/renderer/index/traits/const_view_fwd.hpp>
#include <sge/renderer/index/traits/dimension.hpp>


SGE_RENDERER_BUFFER_DETAIL_DECLARE_CONST_SCOPED_LOCK(
	sge::renderer::index::tag
);

#endif
