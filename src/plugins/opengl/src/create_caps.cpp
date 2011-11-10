/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2011 Carl Philipp Reh (sefi@s-e-f-i.de)

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
#include <sge/opengl/create_caps.hpp>
#include <sge/opengl/get_int.hpp>
#include <sge/opengl/get_string.hpp>
#include <sge/opengl/context/object_fwd.hpp>
#include <sge/opengl/context/use.hpp>
#include <sge/opengl/fbo/context.hpp>
#include <sge/opengl/glsl/context.hpp>
#include <sge/opengl/texture/context.hpp>
#include <sge/opengl/texture/volume_context.hpp>
#include <sge/renderer/adapter.hpp>
#include <sge/renderer/size_type.hpp>
#include <sge/renderer/caps/clip_plane_indices.hpp>
#include <sge/renderer/caps/description.hpp>
#include <sge/renderer/caps/driver_name.hpp>
#include <sge/renderer/caps/glsl_supported.hpp>
#include <sge/renderer/caps/light_indices.hpp>
#include <sge/renderer/caps/max_anisotropy.hpp>
#include <sge/renderer/caps/max_texture_size.hpp>
#include <sge/renderer/caps/max_volume_texture_extent.hpp>
#include <sge/renderer/caps/object.hpp>
#include <sge/renderer/caps/object_unique_ptr.hpp>
#include <sge/renderer/caps/preferred_texture_format.hpp>
#include <sge/renderer/caps/render_target_supported.hpp>
#include <sge/renderer/caps/texture_stages.hpp>
#include <sge/renderer/texture/filter/anisotropic/level.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/text.hpp>
#include <fcppt/math/dim/basic_impl.hpp>


sge::renderer::caps::object_unique_ptr
sge::opengl::create_caps(
	context::object &_context
)
{
	renderer::size_type const max_texture_size(
		static_cast<
			renderer::size_type
		>(
			opengl::get_int(
				GL_MAX_TEXTURE_SIZE
			)
		)
	);

	opengl::texture::context const &texture_context(
		context::use<
			texture::context
		>(
			_context
		)
	);

	opengl::texture::volume_context const &volume_texture_context(
		context::use<
			texture::volume_context
		>(
			_context
		)
	);

	return
		fcppt::make_unique_ptr<
			renderer::caps::object
		>(
			sge::renderer::adapter(
				0
			),
			sge::renderer::caps::driver_name(
				opengl::get_string(
					GL_VENDOR
				)
			),
			sge::renderer::caps::description(
				opengl::get_string(
					GL_RENDERER
				)
				+ FCPPT_TEXT(' ')
				+ opengl::get_string(
					GL_VERSION
				)
			),
			sge::renderer::caps::max_texture_size(
				renderer::dim2(
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
						opengl::get_int(
							volume_texture_context.max_extent_flag()
						)
					:
						0
				)
			),
			sge::renderer::caps::max_anisotropy(
				sge::renderer::texture::filter::anisotropic::level(
					texture_context.anisotropic_filter_supported()
					?
						opengl::get_int(
							texture_context.max_anisotropy_flag()
						)
					:
						0
				)
			),
			sge::renderer::caps::render_target_supported(
				context::use<
					fbo::context
				>(
					_context
				).is_supported()
			),
			sge::renderer::caps::glsl_supported(
				context::use<
					glsl::context
				>(
					_context
				).is_supported()
			),
			sge::renderer::caps::preferred_texture_format(
				sge::image::color::format::bgra8
			),
			sge::renderer::caps::clip_plane_indices(
				opengl::get_int(
					GL_MAX_CLIP_PLANES
				)
			),
			sge::renderer::caps::light_indices(
				opengl::get_int(
					GL_MAX_LIGHTS
				)
			),
			sge::renderer::caps::texture_stages(
				opengl::get_int(
					GL_MAX_TEXTURE_UNITS
				)
			)
		);
}
