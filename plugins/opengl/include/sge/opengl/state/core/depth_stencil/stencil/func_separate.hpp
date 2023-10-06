//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_OPENGL_STATE_CORE_DEPTH_STENCIL_STENCIL_FUNC_SEPARATE_HPP_INCLUDED
#define SGE_OPENGL_STATE_CORE_DEPTH_STENCIL_STENCIL_FUNC_SEPARATE_HPP_INCLUDED

#include <sge/opengl/state/actor.hpp>
#include <sge/opengl/state/core/depth_stencil/stencil/config_fwd.hpp>
#include <sge/renderer/opengl/glinclude.hpp>
#include <sge/renderer/state/core/depth_stencil/stencil/func_fwd.hpp>
#include <sge/renderer/state/core/depth_stencil/stencil/read_mask.hpp>
#include <sge/renderer/state/core/depth_stencil/stencil/ref.hpp>

namespace sge::opengl::state::core::depth_stencil::stencil
{

sge::opengl::state::actor func_separate(
    sge::opengl::state::core::depth_stencil::stencil::config const &,
    GLenum side,
    sge::renderer::state::core::depth_stencil::stencil::func,
    sge::renderer::state::core::depth_stencil::stencil::ref,
    sge::renderer::state::core::depth_stencil::stencil::read_mask);

}

#endif
