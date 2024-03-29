//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_RENDERER_TEXTURE_CONST_SCOPED_VOLUME_LOCK_FWD_HPP_INCLUDED
#define SGE_RENDERER_TEXTURE_CONST_SCOPED_VOLUME_LOCK_FWD_HPP_INCLUDED

#include <sge/image3d/tag.hpp>
#include <sge/renderer/texture/const_basic_scoped_lock_fwd.hpp>

namespace sge::renderer::texture
{

using const_scoped_volume_lock = sge::renderer::texture::const_basic_scoped_lock<sge::image3d::tag>;

}

#endif
