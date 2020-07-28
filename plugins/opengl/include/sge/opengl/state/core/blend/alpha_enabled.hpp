//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_OPENGL_STATE_CORE_BLEND_ALPHA_ENABLED_HPP_INCLUDED
#define SGE_OPENGL_STATE_CORE_BLEND_ALPHA_ENABLED_HPP_INCLUDED

#include <sge/opengl/context/object_ref.hpp>
#include <sge/opengl/state/actor.hpp>
#include <sge/renderer/state/core/blend/alpha_enabled_fwd.hpp>


namespace sge
{
namespace opengl
{
namespace state
{
namespace core
{
namespace blend
{

sge::opengl::state::actor
alpha_enabled(
	sge::opengl::context::object_ref,
	sge::renderer::state::core::blend::alpha_enabled const &
);

}
}
}
}
}

#endif
