//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <sge/image3d/tag.hpp>
#include <sge/renderer/color_buffer/const_scoped_volume_lock.hpp> // NOLINT(misc-include-cleaner)
#include <sge/renderer/color_buffer/readable_volume.hpp> // NOLINT(misc-include-cleaner)
#include <sge/renderer/impl/buffer/instantiate_const_scoped_lock.hpp>

SGE_RENDERER_IMPL_BUFFER_INSTANTIATE_CONST_SCOPED_LOCK(sge::image3d::tag);
