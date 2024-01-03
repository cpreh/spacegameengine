//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_RENDERER_COLOR_BUFFER_SCOPED_SURFACE_LOCK_HPP_INCLUDED
#define SGE_RENDERER_COLOR_BUFFER_SCOPED_SURFACE_LOCK_HPP_INCLUDED

#include <sge/image2d/tag.hpp>
#include <sge/image2d/traits/dimension.hpp> // IWYU pragma: keep
#include <sge/image2d/view/object.hpp> // IWYU pragma: keep
#include <sge/renderer/buffer/detail/declare_scoped_lock.hpp>
#include <sge/renderer/color_buffer/scoped_surface_lock_fwd.hpp> // IWYU pragma: keep

SGE_RENDERER_BUFFER_DETAIL_DECLARE_SCOPED_LOCK(sge::image2d::tag);

#endif
