//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_OPENGL_STATE_CORE_DEPTH_STENCIL_STENCIL_MAKE_ACTORS_HPP_INCLUDED
#define SGE_OPENGL_STATE_CORE_DEPTH_STENCIL_STENCIL_MAKE_ACTORS_HPP_INCLUDED

#include <sge/opengl/context/object_ref.hpp>
#include <sge/opengl/state/actor_vector.hpp>
#include <sge/renderer/state/core/depth_stencil/stencil/variant_fwd.hpp>


namespace sge
{
namespace opengl
{
namespace state
{
namespace core
{
namespace depth_stencil
{
namespace stencil
{

sge::opengl::state::actor_vector
make_actors(
	sge::opengl::context::object_ref,
	sge::renderer::state::core::depth_stencil::stencil::variant const &
);

}
}
}
}
}
}

#endif
