//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/opengl/common.hpp>
#include <sge/opengl/context/object_fwd.hpp>
#include <sge/opengl/context/use.hpp>
#include <sge/opengl/state/convert/anisotropic_mip_filter.hpp>
#include <sge/opengl/state/core/sampler/actor.hpp>
#include <sge/opengl/state/core/sampler/actor_vector.hpp>
#include <sge/opengl/state/core/sampler/filter/anisotropic.hpp>
#include <sge/opengl/state/core/sampler/filter/anisotropy_context.hpp>
#include <sge/opengl/texture/funcs/parameter_int.hpp>
#include <sge/renderer/unsupported.hpp>
#include <sge/renderer/state/core/sampler/filter/anisotropic/parameters.hpp>
#include <fcppt/text.hpp>
#include <fcppt/cast/to_signed.hpp>
#include <fcppt/optional/to_exception.hpp>
#include <fcppt/config/external_begin.hpp>
#include <functional>
#include <fcppt/config/external_end.hpp>


sge::opengl::state::core::sampler::actor_vector
sge::opengl::state::core::sampler::filter::anisotropic(
	sge::opengl::context::object &_context,
	sge::renderer::state::core::sampler::filter::anisotropic::parameters const &_filter
)
{
	return
		sge::opengl::state::core::sampler::actor_vector{
			sge::opengl::state::core::sampler::actor{
				std::bind(
					sge::opengl::texture::funcs::parameter_int,
					std::placeholders::_1,
					GL_TEXTURE_MAG_FILTER,
					GL_NEAREST
				)
			},
			sge::opengl::state::core::sampler::actor{
				std::bind(
					sge::opengl::texture::funcs::parameter_int,
					std::placeholders::_1,
					GL_TEXTURE_MIN_FILTER,
					fcppt::cast::to_signed(
						sge::opengl::state::convert::anisotropic_mip_filter(
							_filter.mip()
						)
					)
				)
			},
			sge::opengl::state::core::sampler::actor{
				std::bind(
					sge::opengl::texture::funcs::parameter_int,
					std::placeholders::_1,
					fcppt::optional::to_exception(
						sge::opengl::context::use<
							sge::opengl::state::core::sampler::filter::anisotropy_context
						>(
							_context,
							_context.info()
						).config(),
						[]{
							return
								sge::renderer::unsupported{
									FCPPT_TEXT("anisotropic filtering"),
									FCPPT_TEXT(""),
									FCPPT_TEXT("GL_EXT_texture_filter_anisotropic")
								};
						}
					).anisotropy_flag(),
					fcppt::cast::to_signed(
						_filter.level().get()
					)
				)
			}
		};
}
