//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_OPENGL_STATE_CONVERT_SOURCE_BLEND_FUNC_HPP_INCLUDED
#define SGE_OPENGL_STATE_CONVERT_SOURCE_BLEND_FUNC_HPP_INCLUDED

#include <sge/opengl/common.hpp>
#include <sge/renderer/state/core/blend/source_fwd.hpp>

namespace sge::opengl::state::convert
{

GLenum source_blend_func(sge::renderer::state::core::blend::source);

}

#endif
