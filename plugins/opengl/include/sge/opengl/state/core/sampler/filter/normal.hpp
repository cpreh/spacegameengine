//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_OPENGL_STATE_CORE_SAMPLER_FILTER_NORMAL_HPP_INCLUDED
#define SGE_OPENGL_STATE_CORE_SAMPLER_FILTER_NORMAL_HPP_INCLUDED

#include <sge/opengl/context/object_ref.hpp>
#include <sge/opengl/state/core/sampler/actor_vector.hpp>
#include <sge/renderer/state/core/sampler/filter/normal/parameters_fwd.hpp>


namespace sge::opengl::state::core::sampler::filter
{

sge::opengl::state::core::sampler::actor_vector
normal(
	sge::opengl::context::object_ref,
	sge::renderer::state::core::sampler::filter::normal::parameters const &
);

}

#endif
