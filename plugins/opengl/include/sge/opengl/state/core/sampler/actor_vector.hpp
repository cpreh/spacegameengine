//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_OPENGL_STATE_CORE_SAMPLER_ACTOR_VECTOR_HPP_INCLUDED
#define SGE_OPENGL_STATE_CORE_SAMPLER_ACTOR_VECTOR_HPP_INCLUDED

#include <sge/opengl/state/core/sampler/actor.hpp>
#include <fcppt/config/external_begin.hpp>
#include <vector>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace opengl
{
namespace state
{
namespace core
{
namespace sampler
{

typedef std::vector<
	sge::opengl::state::core::sampler::actor
> actor_vector;

}
}
}
}
}

#endif
