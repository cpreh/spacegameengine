/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2013 Carl Philipp Reh (sefi@s-e-f-i.de)

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
#include <sge/opengl/context/use.hpp>
#include <sge/opengl/context/system/object_fwd.hpp>
#include <sge/opengl/wgl/visual/attribute_container.hpp>
#include <sge/opengl/wgl/visual/context.hpp>
#include <sge/opengl/wgl/visual/make_attributes.hpp>
#include <sge/opengl/wgl/visual/optional_pixel_format_types.hpp>
#include <sge/renderer/unsupported.hpp>
#include <sge/renderer/pixel_format/color_bits.hpp>
#include <sge/renderer/pixel_format/depth_bits.hpp>
#include <sge/renderer/pixel_format/object.hpp>
#include <sge/renderer/pixel_format/optional_bit_count.hpp>
#include <sge/renderer/pixel_format/srgb.hpp>
#include <sge/renderer/pixel_format/stencil_bits.hpp>
#include <fcppt/text.hpp>
#include <fcppt/config/external_begin.hpp>
#include <GL/wglew.h>
#include <fcppt/config/external_end.hpp>


sge::opengl::wgl::visual::attribute_container
sge::opengl::wgl::visual::make_attributes(
	sge::opengl::context::system::object &_system_context,
	sge::renderer::pixel_format::object const &_format
)
{
	sge::opengl::wgl::visual::context &context(
		sge::opengl::context::use<
			sge::opengl::wgl::visual::context
		>(
			_system_context
		)
	);

	sge::opengl::wgl::visual::optional_pixel_format_types const pixel_format_types(
		context.pixel_format_types()
	);

	if(
		!pixel_format_types
	)
		throw sge::renderer::unsupported(
			FCPPT_TEXT("WGL pixel formats"),
			FCPPT_TEXT(""),
			FCPPT_TEXT("WGLEW_EXT_pixel_format, WGLEW_ARB_pixel_format")
		);

	sge::opengl::wgl::visual::attribute_container ret{
		pixel_format_types->draw_to_window().get(),
		GL_TRUE,
		pixel_format_types->support_opengl().get(),
		GL_TRUE,
		pixel_format_types->double_buffer().get(),
		GL_TRUE,
		pixel_format_types->pixel_type().get(),
		pixel_format_types->pixel_type_rgba().get()<
		pixel_format_types->color_bits().get(),
		static_cast<
			int
		>(
			sge::renderer::pixel_format::color_bits(
				_format.color()
			).get()
		)
	};

	{
		sge::renderer::pixel_format::optional_bit_count const depth_bits(
			sge::renderer::pixel_format::depth_bits(
				_format.depth_stencil()
			)
		);

		if(
			depth_bits
		)
		{
			ret.push_back(
				pixel_format_types->depth_bits().get()
			);

			ret.push_back(
				static_cast<
					int
				>(
					depth_bits->get()
				)
			);
		}
	}

	{
		sge::renderer::pixel_format::optional_bit_count const stencil_bits(
			sge::renderer::pixel_format::stencil_bits(
				_format.depth_stencil()
			)
		);

		if(
			stencil_bits
		)
		{
			ret.push_back(
				pixel_format_types->stencil_bits().get()
			);

			ret.push_back(
				static_cast<
					int
				>(
					stencil_bits->get()
				)
			);
		}
	}

	{
		sge::renderer::pixel_format::optional_multi_samples const multi_samples(
			_format.multi_samples()
		);

		if(
			multi_samples
		)
		{
			sge::opengl::optional_int const multi_sample_flag(
				context.multi_sample_flag()
			);

			if(
				!multi_sample_flag
			)
				throw sge::renderer::unsupported(
					FCPPT_TEXT("Multi sampling"),
					FCPPT_TEXT(""),
					FCPPT_TEXT("WGLEW_EXT_multisample, WGLEW_ARB_multisample")
				);

			ret.push_back(
				*multi_sample_flag
			);

			ret.push_back(
				static_cast<
					int
				>(
					multi_samples->get()
				)
			);
		}
	}

	if(
		_format.srgb()
		!=
		sge::renderer::pixel_format::srgb::no
	)
	{
		sge::opengl::optional_int const srgb_flag(
			context.srgb_flag()
		);

		if(
			!srgb_flag
		)
		{
			if(
				_format.srgb()
				==
				sge::renderer::pixel_format::srgb::yes
			)
				throw sge::renderer::unsupported(
					FCPPT_TEXT("SRGB framebuffer"),
					FCPPT_TEXT(""),
					FCPPT_TEXT("WGLEW_EXT_framebuffer_sRGB, WGLEW_ARB_framebuffer_sRGB")
				);
		}
		else
		{
			ret.push_back(
				*srgb_flag
			);

			ret.push_back(
				GL_TRUE
			);
		}
	}

	// End
	ret.push_back(
		0
	);

	return ret;
}
