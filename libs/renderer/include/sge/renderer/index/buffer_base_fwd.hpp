//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_RENDERER_INDEX_BUFFER_BASE_FWD_HPP_INCLUDED
#define SGE_RENDERER_INDEX_BUFFER_BASE_FWD_HPP_INCLUDED

#include <sge/renderer/buffer/writable_fwd.hpp>
#include <sge/renderer/index/tag.hpp>

namespace sge::renderer::index
{

using buffer_base = sge::renderer::buffer::writable<sge::renderer::index::tag>;

}

#endif
