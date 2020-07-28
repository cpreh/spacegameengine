//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/opengl/common.hpp>
#include <sge/opengl/context/object_ref.hpp>
#include <sge/opengl/context/use.hpp>
#include <sge/opengl/state/convert/mag_filter.hpp>
#include <sge/opengl/state/convert/min_filter.hpp>
#include <sge/opengl/state/core/sampler/actor.hpp>
#include <sge/opengl/state/core/sampler/actor_vector.hpp>
#include <sge/opengl/state/core/sampler/filter/anisotropy_config.hpp>
#include <sge/opengl/state/core/sampler/filter/anisotropy_context.hpp>
#include <sge/opengl/state/core/sampler/filter/normal.hpp>
#include <sge/opengl/texture/binding_fwd.hpp>
#include <sge/opengl/texture/funcs/parameter_int.hpp>
#include <sge/renderer/state/core/sampler/filter/normal/parameters.hpp>
#include <fcppt/cast/to_signed.hpp>
#include <fcppt/optional/maybe_void.hpp>


sge::opengl::state::core::sampler::actor_vector
sge::opengl::state::core::sampler::filter::normal(
	sge::opengl::context::object_ref const _context,
	sge::renderer::state::core::sampler::filter::normal::parameters const &_filter
)
{
	sge::opengl::state::core::sampler::actor_vector result(
		sge::opengl::state::core::sampler::actor_vector{
			sge::opengl::state::core::sampler::actor{
				[
					mag =
						_filter.mag()
				](
					sge::opengl::texture::binding const &_binding
				)
				{
					sge::opengl::texture::funcs::parameter_int(
						_binding,
						GL_TEXTURE_MAG_FILTER,
						fcppt::cast::to_signed(
							sge::opengl::state::convert::mag_filter(
								mag
							)
						)
					);
				}
			},
			sge::opengl::state::core::sampler::actor{
				[
					min =
						_filter.min(),
					mip =
						_filter.mip()
				](
					sge::opengl::texture::binding const &_binding
				)
				{
					sge::opengl::texture::funcs::parameter_int(
						_binding,
						GL_TEXTURE_MIN_FILTER,
						fcppt::cast::to_signed(
							sge::opengl::state::convert::min_filter(
								min,
								mip
							)
						)
					);
				}
			}
		}
	);

	fcppt::optional::maybe_void(
		sge::opengl::context::use<
			sge::opengl::state::core::sampler::filter::anisotropy_context
		>(
			_context,
			_context.get().info()
		).config(),
		[
			&result
		](
			sge::opengl::state::core::sampler::filter::anisotropy_config const &_config
		)
		{
			result.push_back(
				sge::opengl::state::core::sampler::actor{
					[
						flag =
							_config.anisotropy_flag()
					](
						sge::opengl::texture::binding const &_binding
					)
					{
						sge::opengl::texture::funcs::parameter_int(
							_binding,
							flag,
							1
						);
					}
				}
			);
		}
	);

	return
		result;
}
