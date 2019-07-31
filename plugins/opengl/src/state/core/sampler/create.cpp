//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/opengl/context/object_fwd.hpp>
#include <sge/opengl/state/core/sampler/create.hpp>
#include <sge/opengl/state/core/sampler/make_actors.hpp>
#include <sge/opengl/state/core/sampler/object.hpp>
#include <sge/renderer/state/core/sampler/object.hpp>
#include <sge/renderer/state/core/sampler/object_unique_ptr.hpp>
#include <sge/renderer/state/core/sampler/parameters_fwd.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/unique_ptr_to_base.hpp>


sge::renderer::state::core::sampler::object_unique_ptr
sge::opengl::state::core::sampler::create(
	sge::opengl::context::object &_context,
	sge::renderer::state::core::sampler::parameters const &_parameters
)
{
	return
		fcppt::unique_ptr_to_base<
			sge::renderer::state::core::sampler::object
		>(
			fcppt::make_unique_ptr<
				sge::opengl::state::core::sampler::object
			>(
				sge::opengl::state::core::sampler::make_actors(
					_context,
					_parameters
				)
			)
		);
}
