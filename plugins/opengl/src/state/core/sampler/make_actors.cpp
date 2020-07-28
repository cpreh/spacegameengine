//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/opengl/context/object_ref.hpp>
#include <sge/opengl/state/core/sampler/actor_vector.hpp>
#include <sge/opengl/state/core/sampler/make_actors.hpp>
#include <sge/opengl/state/core/sampler/address/make_actors.hpp>
#include <sge/opengl/state/core/sampler/filter/make_actors.hpp>
#include <sge/renderer/state/core/sampler/parameters.hpp>
#include <fcppt/container/join.hpp>


sge::opengl::state::core::sampler::actor_vector
sge::opengl::state::core::sampler::make_actors(
	sge::opengl::context::object_ref const _context,
	sge::renderer::state::core::sampler::parameters const &_parameters
)
{
	return
		fcppt::container::join(
			sge::opengl::state::core::sampler::address::make_actors(
				_parameters.address()
			),
			sge::opengl::state::core::sampler::filter::make_actors(
				_context,
				_parameters.filter()
			)
		);
}
