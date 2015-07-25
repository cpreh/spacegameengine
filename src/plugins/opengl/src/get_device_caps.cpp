/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2015 Carl Philipp Reh (carlphilippreh <at> gmail.com)

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/


#include <sge/opengl/common.hpp>
#include <sge/opengl/get_device_caps.hpp>
#include <sge/opengl/get_int.hpp>
#include <sge/opengl/get_string.hpp>
#include <sge/opengl/srgb_context.hpp>
#include <sge/opengl/backend/dummy.hpp>
#include <sge/opengl/backend/system_fwd.hpp>
#include <sge/opengl/context/use.hpp>
#include <sge/opengl/context/system/object_fwd.hpp>
#include <sge/opengl/fbo/context.hpp>
#include <sge/opengl/state/core/sampler/filter/anisotropy_config.hpp>
#include <sge/opengl/state/core/sampler/filter/anisotropy_context.hpp>
#include <sge/opengl/state/core/sampler/filter/optional_anisotropy_config.hpp>
#include <sge/opengl/texture/multi_context.hpp>
#include <sge/opengl/texture/npot_context.hpp>
#include <sge/opengl/texture/volume_context.hpp>
#include <sge/renderer/dim2.hpp>
#include <sge/renderer/size_type.hpp>
#include <sge/renderer/caps/clip_plane_indices.hpp>
#include <sge/renderer/caps/description.hpp>
#include <sge/renderer/caps/device.hpp>
#include <sge/renderer/caps/driver_name.hpp>
#include <sge/renderer/caps/light_indices.hpp>
#include <sge/renderer/caps/max_anisotropy.hpp>
#include <sge/renderer/caps/max_texture_size.hpp>
#include <sge/renderer/caps/max_volume_texture_extent.hpp>
#include <sge/renderer/caps/non_power_of_2_textures.hpp>
#include <sge/renderer/caps/normalized_cvv.hpp>
#include <sge/renderer/caps/render_target_inverted.hpp>
#include <sge/renderer/caps/render_target_supported.hpp>
#include <sge/renderer/caps/srgb_framebuffer.hpp>
#include <sge/renderer/caps/target_surface_indices.hpp>
#include <awl/system/object_fwd.hpp>
#include <fcppt/const.hpp>
#include <fcppt/maybe.hpp>
#include <fcppt/strong_typedef_construct_cast.hpp>
#include <fcppt/text.hpp>
#include <fcppt/cast/size.hpp>
#include <fcppt/cast/static_cast_fun.hpp>
#include <fcppt/cast/to_unsigned.hpp>
#include <fcppt/math/dim/fill.hpp>


sge::renderer::caps::device
sge::opengl::get_device_caps(
	awl::system::object &_awl_system,
	sge::opengl::context::system::object &_context,
	sge::opengl::backend::system &_device_system
)
{
	sge::opengl::backend::dummy dummy_state(
		_awl_system,
		_device_system
	);

	sge::opengl::state::core::sampler::filter::optional_anisotropy_config const &anisotropy_config(
		sge::opengl::context::use<
			sge::opengl::state::core::sampler::filter::anisotropy_context
		>(
			_context
		).config()
	);

	sge::opengl::texture::multi_context const &texture_multi_context(
		sge::opengl::context::use<
			sge::opengl::texture::multi_context
		>(
			_context
		)
	);

	sge::opengl::texture::volume_context const &volume_texture_context(
		sge::opengl::context::use<
			sge::opengl::texture::volume_context
		>(
			_context
		)
	);

	sge::renderer::caps::render_target_supported const render_target_supported(
		sge::opengl::context::use<
			sge::opengl::fbo::context
		>(
			_context
		).config().has_value()
	);

	return
		sge::renderer::caps::device(
			sge::renderer::caps::driver_name(
				sge::opengl::get_string(
					GL_VENDOR
				)
			),
			sge::renderer::caps::description(
				sge::opengl::get_string(
					GL_RENDERER
				)
				+ FCPPT_TEXT(' ')
				+ sge::opengl::get_string(
					GL_VERSION
				)
			),
			sge::renderer::caps::normalized_cvv(
				true
			),
			sge::renderer::caps::max_texture_size(
				fcppt::math::dim::fill<
					sge::renderer::dim2
				>(
					fcppt::cast::size<
						sge::renderer::size_type
					>(
						fcppt::cast::to_unsigned(
							sge::opengl::get_int(
								GL_MAX_TEXTURE_SIZE
							)
						)
					)
				)
			),
			sge::renderer::caps::max_volume_texture_extent(
				fcppt::cast::to_unsigned(
					fcppt::maybe(
						volume_texture_context.max_extent_flag(),
						fcppt::const_(
							0
						),
						[](
							GLenum const _flag
						)
						{
							return
								sge::opengl::get_int(
									_flag
								);
						}
					)
				)
			),
			sge::renderer::caps::non_power_of_2_textures(
				sge::opengl::context::use<
					sge::opengl::texture::npot_context
				>(
					_context
				).is_supported()
			),
			fcppt::strong_typedef_construct_cast<
				sge::renderer::caps::max_anisotropy,
				fcppt::cast::static_cast_fun
			>(
				fcppt::maybe(
					anisotropy_config,
					fcppt::const_(
						0
					),
					[](
						sge::opengl::state::core::sampler::filter::anisotropy_config const &_config
					)
					{
						return
							sge::opengl::get_int(
								_config.max_anisotropy_flag()
							);
					}
				)
			),
			render_target_supported,
			sge::renderer::caps::render_target_inverted(
				true
			),
			fcppt::strong_typedef_construct_cast<
				sge::renderer::caps::clip_plane_indices,
				fcppt::cast::static_cast_fun
			>(
				sge::opengl::get_int(
					GL_MAX_CLIP_PLANES
				)
			),
			fcppt::strong_typedef_construct_cast<
				sge::renderer::caps::light_indices,
				fcppt::cast::static_cast_fun
			>(
				sge::opengl::get_int(
					GL_MAX_LIGHTS
				)
			),
			texture_multi_context.max_level(),
			fcppt::strong_typedef_construct_cast<
				sge::renderer::caps::target_surface_indices,
				fcppt::cast::static_cast_fun
			>(
				render_target_supported.get()
				?
					sge::opengl::get_int(
						GL_MAX_COLOR_ATTACHMENTS
					)
				:
					0
			),
			sge::renderer::caps::srgb_framebuffer(
				sge::opengl::context::use<
					sge::opengl::srgb_context
				>(
					_context
				).flag().has_value()
			)
		);
}
