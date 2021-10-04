//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_OPENGL_STATE_CORE_DEPTH_STENCIL_STENCIL_ENABLED_VARIANT_HPP_INCLUDED
#define SGE_OPENGL_STATE_CORE_DEPTH_STENCIL_STENCIL_ENABLED_VARIANT_HPP_INCLUDED

#include <sge/opengl/context/object_ref.hpp>
#include <sge/opengl/state/actor_vector.hpp>
#include <sge/renderer/state/core/depth_stencil/stencil/enabled_variant_fwd.hpp>
#include <sge/renderer/state/core/depth_stencil/stencil/read_mask.hpp>
#include <sge/renderer/state/core/depth_stencil/stencil/ref.hpp>
#include <sge/renderer/state/core/depth_stencil/stencil/write_mask.hpp>


namespace sge::opengl::state::core::depth_stencil::stencil
{

sge::opengl::state::actor_vector
enabled_variant(
	sge::opengl::context::object_ref,
	sge::renderer::state::core::depth_stencil::stencil::ref,
	sge::renderer::state::core::depth_stencil::stencil::read_mask,
	sge::renderer::state::core::depth_stencil::stencil::write_mask,
	sge::renderer::state::core::depth_stencil::stencil::enabled_variant const &
);

}

#endif
