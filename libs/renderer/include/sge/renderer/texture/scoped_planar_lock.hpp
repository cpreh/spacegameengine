//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_RENDERER_TEXTURE_SCOPED_PLANAR_LOCK_HPP_INCLUDED
#define SGE_RENDERER_TEXTURE_SCOPED_PLANAR_LOCK_HPP_INCLUDED

#include <sge/image2d/tag.hpp>
#include <sge/renderer/color_buffer/scoped_surface_lock.hpp> // IWYU pragma: keep
#include <sge/renderer/texture/scoped_planar_lock_fwd.hpp> // IWYU pragma: export
#include <sge/renderer/texture/detail/declare_basic_scoped_lock.hpp>

SGE_RENDERER_TEXTURE_DETAIL_DECLARE_BASIC_SCOPED_LOCK(sge::image2d::tag);

#endif
