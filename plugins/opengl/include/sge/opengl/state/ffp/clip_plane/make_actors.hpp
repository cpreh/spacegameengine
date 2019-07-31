//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_OPENGL_STATE_FFP_CLIP_PLANE_MAKE_ACTORS_HPP_INCLUDED
#define SGE_OPENGL_STATE_FFP_CLIP_PLANE_MAKE_ACTORS_HPP_INCLUDED

#include <sge/opengl/state/index_actor_vector.hpp>
#include <sge/renderer/state/ffp/clip_plane/parameters_fwd.hpp>


namespace sge
{
namespace opengl
{
namespace state
{
namespace ffp
{
namespace clip_plane
{

sge::opengl::state::index_actor_vector
make_actors(
	sge::renderer::state::ffp::clip_plane::parameters const &
);

}
}
}
}
}

#endif
