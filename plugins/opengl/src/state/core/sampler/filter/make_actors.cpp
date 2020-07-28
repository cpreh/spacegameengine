//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/opengl/context/object_fwd.hpp>
#include <sge/opengl/state/core/sampler/actor_vector.hpp>
#include <sge/opengl/state/core/sampler/filter/anisotropic.hpp>
#include <sge/opengl/state/core/sampler/filter/make_actors.hpp>
#include <sge/opengl/state/core/sampler/filter/normal.hpp>
#include <sge/renderer/state/core/sampler/filter/parameters.hpp>
#include <sge/renderer/state/core/sampler/filter/anisotropic/parameters_fwd.hpp>
#include <sge/renderer/state/core/sampler/filter/normal/parameters_fwd.hpp>
#include <fcppt/variant/match.hpp>


sge::opengl::state::core::sampler::actor_vector
sge::opengl::state::core::sampler::filter::make_actors(
	sge::opengl::context::object_ref const _context,
	sge::renderer::state::core::sampler::filter::parameters const &_parameters
)
{
	return
		fcppt::variant::match(
			_parameters.variant(),
			[
				_context
			](
				sge::renderer::state::core::sampler::filter::anisotropic::parameters const &_filter
			)
			{
				return
					sge::opengl::state::core::sampler::filter::anisotropic(
						_context,
						_filter
					);
			},
			[
				_context
			](
				sge::renderer::state::core::sampler::filter::normal::parameters const &_filter
			)
			{
				return
					sge::opengl::state::core::sampler::filter::normal(
						_context,
						_filter
					);
			}
		);
}
