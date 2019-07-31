//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/opengl/context/object.hpp>
#include <sge/opengl/context/use.hpp>
#include <sge/opengl/texture/basic_parameters.hpp>
#include <sge/opengl/texture/create_volume.hpp>
#include <sge/opengl/texture/volume.hpp>
#include <sge/opengl/texture/volume_context.hpp>
#include <sge/renderer/unsupported.hpp>
#include <sge/renderer/texture/volume.hpp>
#include <sge/renderer/texture/volume_parameters_fwd.hpp>
#include <sge/renderer/texture/volume_unique_ptr.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/text.hpp>
#include <fcppt/unique_ptr_to_base.hpp>
#include <fcppt/optional/to_exception.hpp>


sge::renderer::texture::volume_unique_ptr
sge::opengl::texture::create_volume(
	sge::opengl::texture::basic_parameters const &_basic_parameters,
	sge::renderer::texture::volume_parameters const &_parameters
)
{
	return
		fcppt::unique_ptr_to_base<
			sge::renderer::texture::volume
		>(
			fcppt::make_unique_ptr<
				sge::opengl::texture::volume
			>(
				fcppt::optional::to_exception(
					sge::opengl::context::use<
						sge::opengl::texture::volume_context
					>(
						_basic_parameters.context(),
						_basic_parameters.context().info()
					).config(),
					[]{
						return
							sge::renderer::unsupported{
								FCPPT_TEXT("volume texture"),
								FCPPT_TEXT("1.2"),
								FCPPT_TEXT("")
							};
					}
				),
				_basic_parameters,
				_parameters
			)
		);
}
