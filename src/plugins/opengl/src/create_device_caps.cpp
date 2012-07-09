/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2012 Carl Philipp Reh (sefi@s-e-f-i.de)

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
#include <sge/opengl/create_device_caps.hpp>
#include <sge/opengl/get_int.hpp>
#include <sge/opengl/get_string.hpp>
#include <sge/opengl/context/use.hpp>
#include <sge/opengl/context/system/object_fwd.hpp>
#include <sge/opengl/device_state/dummy.hpp>
#include <sge/opengl/fbo/context.hpp>
#include <sge/opengl/texture/context.hpp>
#include <sge/opengl/texture/multi_context.hpp>
#include <sge/opengl/texture/volume_context.hpp>
#include <sge/renderer/adapter.hpp>
#include <sge/renderer/size_type.hpp>
#include <sge/renderer/caps/clip_plane_indices.hpp>
#include <sge/renderer/caps/description.hpp>
#include <sge/renderer/caps/device.hpp>
#include <sge/renderer/caps/device_unique_ptr.hpp>
#include <sge/renderer/caps/driver_name.hpp>
#include <sge/renderer/caps/light_indices.hpp>
#include <sge/renderer/caps/max_anisotropy.hpp>
#include <sge/renderer/caps/max_texture_size.hpp>
#include <sge/renderer/caps/max_volume_texture_extent.hpp>
#include <sge/renderer/caps/preferred_texture_format.hpp>
#include <sge/renderer/caps/render_target_inverted.hpp>
#include <sge/renderer/caps/render_target_supported.hpp>
#include <sge/renderer/caps/target_surface_indices.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/strong_typedef_construct_cast.hpp>
#include <fcppt/text.hpp>


sge::renderer::caps::device_unique_ptr
sge::opengl::create_device_caps(
	sge::opengl::context::system::object &_context
)
{
	sge::opengl::device_state::dummy dummy_state;

	sge::renderer::size_type const max_texture_size(
		static_cast<
			sge::renderer::size_type
		>(
			sge::opengl::get_int(
				GL_MAX_TEXTURE_SIZE
			)
		)
	);

	sge::opengl::texture::context const &texture_context(
		sge::opengl::context::use<
			sge::opengl::texture::context
		>(
			_context
		)
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
			fbo::context
		>(
			_context
		).is_supported()
	);

	return
		fcppt::make_unique_ptr<
			sge::renderer::caps::device
		>(
			sge::renderer::adapter(
				0u
			),
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
			sge::renderer::caps::max_texture_size(
				sge::renderer::dim2(
					max_texture_size,
					max_texture_size
				)
			),
			sge::renderer::caps::max_volume_texture_extent(
				static_cast<
					sge::renderer::size_type
				>(
					volume_texture_context.have_volume_texture()
					?
						sge::opengl::get_int(
							volume_texture_context.max_extent_flag()
						)
					:
						0
				)
			),
			fcppt::strong_typedef_construct_cast<
				sge::renderer::caps::max_anisotropy
			>(
				texture_context.anisotropic_filter_supported()
				?
					sge::opengl::get_int(
						texture_context.max_anisotropy_flag()
					)
				:
					0
			),
			render_target_supported,
			sge::renderer::caps::render_target_inverted(
				true
			),
			sge::renderer::caps::preferred_texture_format(
				sge::image::color::format::bgra8
			),
			fcppt::strong_typedef_construct_cast<
				sge::renderer::caps::clip_plane_indices
			>(
				sge::opengl::get_int(
					GL_MAX_CLIP_PLANES
				)
			),
			fcppt::strong_typedef_construct_cast<
				sge::renderer::caps::light_indices
			>(
				sge::opengl::get_int(
					GL_MAX_LIGHTS
				)
			),
			texture_multi_context.max_level(),
			fcppt::strong_typedef_construct_cast<
				sge::renderer::caps::target_surface_indices
			>(
				render_target_supported.get()
				?
					sge::opengl::get_int(
						GL_MAX_COLOR_ATTACHMENTS
					)
				:
					0
			)
		);
}
