//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_OPENGL_STATE_FFP_SAMPLER_MAKE_ACTORS_HPP_INCLUDED
#define SGE_OPENGL_STATE_FFP_SAMPLER_MAKE_ACTORS_HPP_INCLUDED

#include <sge/opengl/state/ffp/sampler/actor_vector.hpp>
#include <sge/renderer/state/ffp/sampler/parameters_fwd.hpp>

namespace sge::opengl::state::ffp::sampler
{

sge::opengl::state::ffp::sampler::actor_vector
make_actors(sge::renderer::state::ffp::sampler::parameters const &);

}

#endif
