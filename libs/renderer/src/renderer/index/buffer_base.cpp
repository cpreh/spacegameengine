//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/renderer/dim1.hpp> // NOLINT(misc-include-cleaner)
#include <sge/renderer/lock_segment.hpp> // NOLINT(misc-include-cleaner)
#include <sge/renderer/impl/buffer/instantiate_base.hpp>
#include <sge/renderer/impl/buffer/instantiate_readable.hpp>
#include <sge/renderer/impl/buffer/instantiate_writable.hpp>
#include <sge/renderer/index/buffer_base.hpp> // NOLINT(misc-include-cleaner)
#include <sge/renderer/index/tag.hpp>
#include <sge/renderer/index/dynamic/const_view.hpp> // NOLINT(misc-include-cleaner)
#include <sge/renderer/index/dynamic/view.hpp> // NOLINT(misc-include-cleaner)

SGE_RENDERER_IMPL_BUFFER_INSTANTIATE_BASE(sge::renderer::index::tag);

SGE_RENDERER_IMPL_BUFFER_INSTANTIATE_READABLE(sge::renderer::index::tag);

SGE_RENDERER_IMPL_BUFFER_INSTANTIATE_WRITABLE(sge::renderer::index::tag);
