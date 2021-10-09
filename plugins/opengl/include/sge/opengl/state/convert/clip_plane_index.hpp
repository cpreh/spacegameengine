//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_OPENGL_STATE_CONVERT_CLIP_PLANE_INDEX_HPP_INCLUDED
#define SGE_OPENGL_STATE_CONVERT_CLIP_PLANE_INDEX_HPP_INCLUDED

#include <sge/opengl/common.hpp>
#include <sge/renderer/state/index_count.hpp>

namespace sge::opengl::state::convert
{

GLenum clip_plane_index(sge::renderer::state::index_count);

}

#endif
