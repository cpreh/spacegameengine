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
#include <sge/opengl/wgl/visual/attribute_container.hpp>
#include <sge/opengl/wgl/visual/config.hpp>
#include <sge/opengl/wgl/visual/make_attributes.hpp>
#include <sge/opengl/wgl/visual/pixel_format_types.hpp>
#include <sge/renderer/unsupported.hpp>
#include <sge/renderer/pixel_format/bit_count.hpp>
#include <sge/renderer/pixel_format/color_bits.hpp>
#include <sge/renderer/pixel_format/depth_bits.hpp>
#include <sge/renderer/pixel_format/multi_samples.hpp>
#include <sge/renderer/pixel_format/object.hpp>
#include <sge/renderer/pixel_format/srgb.hpp>
#include <sge/renderer/pixel_format/stencil_bits.hpp>
#include <fcppt/maybe_void.hpp>
#include <fcppt/optional_to_exception.hpp>
#include <fcppt/text.hpp>
#include <fcppt/cast/to_signed.hpp>


sge::opengl::wgl::visual::attribute_container
sge::opengl::wgl::visual::make_attributes(
	sge::opengl::wgl::visual::config const &_config,
	sge::renderer::pixel_format::object const &_format
)
{
	sge::opengl::wgl::visual::pixel_format_types const pixel_format_types(
		fcppt::optional_to_exception(
			_config.pixel_format_types(),
			[]{
				return
					sge::renderer::unsupported(
						FCPPT_TEXT("WGL pixel formats"),
						FCPPT_TEXT(""),
						FCPPT_TEXT("WGLEW_EXT_pixel_format, WGLEW_ARB_pixel_format")
					);
			}
		)
	);

	sge::opengl::wgl::visual::attribute_container ret{
		pixel_format_types.draw_to_window().get(),
		GL_TRUE,
		pixel_format_types.support_opengl().get(),
		GL_TRUE,
		pixel_format_types.double_buffer().get(),
		GL_TRUE,
		pixel_format_types.pixel_type().get(),
		pixel_format_types.pixel_type_rgba().get(),
		pixel_format_types.color_bits().get(),
		fcppt::cast::to_signed(
			sge::renderer::pixel_format::color_bits(
				_format.color()
			).get()
		)
	};

	fcppt::maybe_void(
		sge::renderer::pixel_format::depth_bits(
			_format.depth_stencil()
		),
		[
			&pixel_format_types,
			&ret
		](
			sge::renderer::pixel_format::bit_count const _depth_bits
		)
		{
			ret.push_back(
				pixel_format_types.depth_bits().get()
			);

			ret.push_back(
				fcppt::cast::to_signed(
					_depth_bits.get()
				)
			);
		}
	);

	fcppt::maybe_void(
		sge::renderer::pixel_format::stencil_bits(
			_format.depth_stencil()
		),
		[
			&pixel_format_types,
			&ret
		](
			sge::renderer::pixel_format::bit_count const _stencil_bits
		)
		{
			ret.push_back(
				pixel_format_types.stencil_bits().get()
			);

			ret.push_back(
				fcppt::cast::to_signed(
					_stencil_bits.get()
				)
			);
		}
	);

	fcppt::maybe_void(
		_format.multi_samples(),
		[
			&_config,
			&ret
		](
			sge::renderer::pixel_format::multi_samples const _multi_samples
		)
		{
			ret.push_back(
				fcppt::optional_to_exception(
					_config.multi_sample_flag(),
					[]{
						return
							sge::renderer::unsupported(
								FCPPT_TEXT("Multi sampling"),
								FCPPT_TEXT(""),
								FCPPT_TEXT("WGLEW_EXT_multisample, WGLEW_ARB_multisample")
							);
					}
				)
			);

			ret.push_back(
				fcppt::cast::to_signed(
					_multi_samples.get()
				)
			);
		}
	);

	if(
		_format.srgb()
		!=
		sge::renderer::pixel_format::srgb::no
	)
		fcppt::maybe(
			_config.srgb_flag(),
			[
				&_format
			]{
				if(
					_format.srgb()
					==
					sge::renderer::pixel_format::srgb::yes
				)
					throw
						sge::renderer::unsupported(
							FCPPT_TEXT("SRGB framebuffer"),
							FCPPT_TEXT(""),
							FCPPT_TEXT("WGLEW_EXT_framebuffer_sRGB, WGLEW_ARB_framebuffer_sRGB")
						);
			},
			[
				&ret
			](
				int const _srgb_flag
			)
			{
				ret.push_back(
					_srgb_flag
				);

				ret.push_back(
					GL_TRUE
				);
			}
		);

	// End
	ret.push_back(
		0
	);

	return
		ret;
}
