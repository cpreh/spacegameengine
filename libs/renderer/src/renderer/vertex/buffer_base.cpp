//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/renderer/dim1.hpp>
#include <sge/renderer/lock_segment.hpp>
#include <sge/renderer/impl/buffer/instantiate_base.hpp>
#include <sge/renderer/impl/buffer/instantiate_readable.hpp>
#include <sge/renderer/impl/buffer/instantiate_writable.hpp>
#include <sge/renderer/vertex/buffer_base.hpp>
#include <sge/renderer/vertex/tag.hpp>
#include <sge/renderer/vf/dynamic/const_view.hpp>
#include <sge/renderer/vf/dynamic/view.hpp>

SGE_RENDERER_IMPL_BUFFER_INSTANTIATE_BASE(sge::renderer::vertex::tag);

SGE_RENDERER_IMPL_BUFFER_INSTANTIATE_READABLE(sge::renderer::vertex::tag);

SGE_RENDERER_IMPL_BUFFER_INSTANTIATE_WRITABLE(sge::renderer::vertex::tag);
