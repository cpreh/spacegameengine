//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/opengl/common.hpp>
#include <sge/opengl/disable.hpp>
#include <sge/opengl/enable.hpp>
#include <sge/opengl/context/object_ref.hpp>
#include <sge/opengl/state/actor.hpp>
#include <sge/opengl/state/actor_vector.hpp>
#include <sge/opengl/state/core/depth_stencil/stencil/enabled_variant.hpp>
#include <sge/opengl/state/core/depth_stencil/stencil/make_actors.hpp>
#include <sge/opengl/state/core/depth_stencil/stencil/write_mask.hpp>
#include <sge/renderer/state/core/depth_stencil/stencil/enabled.hpp>
#include <sge/renderer/state/core/depth_stencil/stencil/off_fwd.hpp>
#include <sge/renderer/state/core/depth_stencil/stencil/variant.hpp>
#include <sge/renderer/state/core/depth_stencil/stencil/write_mask_all.hpp>
#include <fcppt/container/join.hpp>
#include <fcppt/variant/match.hpp>


sge::opengl::state::actor_vector
sge::opengl::state::core::depth_stencil::stencil::make_actors(
	sge::opengl::context::object_ref const _context,
	sge::renderer::state::core::depth_stencil::stencil::variant const &_variant
)
{
	return
		fcppt::variant::match(
			_variant,
			[](
				sge::renderer::state::core::depth_stencil::stencil::off const &
			)
			{
				return
					sge::opengl::state::actor_vector{
						sge::opengl::state::actor{
							[]{
								sge::opengl::disable(
									GL_STENCIL_TEST
								);
							}
						},
						sge::opengl::state::core::depth_stencil::stencil::write_mask(
							sge::renderer::state::core::depth_stencil::stencil::write_mask_all()
						)
					};
			},
			[
				_context
			](
				sge::renderer::state::core::depth_stencil::stencil::enabled const &_enabled
			)
			{
				return
					fcppt::container::join(
						sge::opengl::state::actor_vector{
							sge::opengl::state::actor{
								[]{
									sge::opengl::enable(
										GL_STENCIL_TEST
									);
								}
							}
						},
						sge::opengl::state::core::depth_stencil::stencil::enabled_variant(
							_context,
							_enabled.ref(),
							_enabled.read_mask(),
							_enabled.write_mask(),
							_enabled.enabled_variant()
						)
					);
			}
		);
}
