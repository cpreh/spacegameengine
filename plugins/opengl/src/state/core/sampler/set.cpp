//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/opengl/context/object_fwd.hpp>
#include <sge/opengl/context/use.hpp>
#include <sge/opengl/state/core/sampler/context.hpp>
#include <sge/opengl/state/core/sampler/object.hpp>
#include <sge/opengl/state/core/sampler/set.hpp>
#include <sge/opengl/texture/active_level.hpp>
#include <sge/opengl/texture/get_stage_type.hpp>
#include <sge/opengl/texture/render_binding.hpp>
#include <sge/opengl/texture/set_samplers.hpp>
#include <sge/opengl/texture/type.hpp>
#include <sge/renderer/state/core/sampler/const_optional_object_ref_map.hpp>
#include <sge/renderer/texture/stage.hpp>
#include <fcppt/log/object_fwd.hpp>
#include <fcppt/optional/maybe_void.hpp>


void
sge::opengl::state::core::sampler::set(
	fcppt::log::object &_log,
	sge::opengl::context::object &_context,
	sge::renderer::state::core::sampler::const_optional_object_ref_map const &_objects
)
{
	// Record this so we can update the samplers for textures when they are activated
	sge::opengl::context::use<
		sge::opengl::state::core::sampler::context
	>(
		_context,
		_context
	).set(
		_objects
	);

	// Update all samplers for currently bound textures
	for(
		auto const &sampler
		:
		_objects
	)
	{
		sge::renderer::texture::stage const stage(
			sampler.first
		);

		fcppt::optional::maybe_void(
			sge::opengl::texture::get_stage_type(
				_context,
				stage
			),
			[
				&_log,
				&_context,
				stage
			](
				sge::opengl::texture::type const _bound_type
			)
			{
				sge::opengl::texture::active_level const active_level(
					_log,
					_context,
					stage
				);

				sge::opengl::texture::render_binding const render_binding(
					active_level,
					_bound_type
				);

				sge::opengl::texture::set_samplers(
					render_binding,
					_context
				);
			}
		);
	}
}
