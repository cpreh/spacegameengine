//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_RENDERER_COLOR_BUFFER_SCOPED_VOLUME_LOCK_HPP_INCLUDED
#define SGE_RENDERER_COLOR_BUFFER_SCOPED_VOLUME_LOCK_HPP_INCLUDED

#include <sge/image3d/tag.hpp>
#include <sge/image3d/traits/dimension.hpp>
#include <sge/image3d/view/object.hpp>
#include <sge/renderer/buffer/scoped_lock.hpp>
#include <sge/renderer/buffer/detail/declare_scoped_lock.hpp>
#include <sge/renderer/color_buffer/scoped_volume_lock_fwd.hpp>

SGE_RENDERER_BUFFER_DETAIL_DECLARE_SCOPED_LOCK(sge::image3d::tag);

#endif
