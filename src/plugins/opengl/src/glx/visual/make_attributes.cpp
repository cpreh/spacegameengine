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


#include <sge/opengl/context/use.hpp>
#include <sge/opengl/context/system/object_fwd.hpp>
#include <sge/opengl/glx/visual/attribute_container.hpp>
#include <sge/opengl/glx/visual/context.hpp>
#include <sge/opengl/glx/visual/convert_color.hpp>
#include <sge/opengl/glx/visual/make_attributes.hpp>
#include <sge/opengl/glx/visual/rgb_triple.hpp>
#include <sge/renderer/unsupported.hpp>
#include <sge/renderer/pixel_format/bit_count.hpp>
#include <sge/renderer/pixel_format/depth_bits.hpp>
#include <sge/renderer/pixel_format/multi_samples.hpp>
#include <sge/renderer/pixel_format/object.hpp>
#include <sge/renderer/pixel_format/srgb.hpp>
#include <sge/renderer/pixel_format/stencil_bits.hpp>
#include <fcppt/maybe_void.hpp>
#include <fcppt/text.hpp>
#include <fcppt/cast/to_signed.hpp>
#include <fcppt/config/external_begin.hpp>
#include <GL/glx.h>
#include <fcppt/config/external_end.hpp>


sge::opengl::glx::visual::attribute_container
sge::opengl::glx::visual::make_attributes(
	sge::opengl::context::system::object &_system_context,
	sge::renderer::pixel_format::object const &_format
)
{
	sge::opengl::glx::visual::attribute_container ret;

	ret.push_back(
		GLX_RGBA
	);

	ret.push_back(
		GLX_DOUBLEBUFFER
	);

	{
		sge::opengl::glx::visual::rgb_triple const rgb(
			sge::opengl::glx::visual::convert_color(
				_format.color()
			)
		);

		ret.push_back(
			GLX_RED_SIZE
		);

		ret.push_back(
			rgb.red().get()
		);

		ret.push_back(
			GLX_BLUE_SIZE
		);

		ret.push_back(
			rgb.blue().get()
		);

		ret.push_back(
			GLX_GREEN_SIZE
		);

		ret.push_back(
			rgb.green().get()
		);
	}

	fcppt::maybe_void(
		sge::renderer::pixel_format::depth_bits(
			_format.depth_stencil()
		),
		[
			&ret
		](
			sge::renderer::pixel_format::bit_count const _depth_bits
		)
		{
			ret.push_back(
				GLX_DEPTH_SIZE
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
			&ret
		](
			sge::renderer::pixel_format::bit_count const _stencil_bits
		)
		{
			ret.push_back(
				GLX_STENCIL_SIZE
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
			&ret
		](
			sge::renderer::pixel_format::multi_samples const _samples
		)
		{
			ret.push_back(
				GLX_SAMPLE_BUFFERS
			);

			ret.push_back(
				GL_TRUE
			);

			ret.push_back(
				GLX_SAMPLES
			);

			ret.push_back(
				fcppt::cast::to_signed(
					_samples.get()
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
			sge::opengl::context::use<
				sge::opengl::glx::visual::context
			>(
				_system_context
			).srgb_flag(),
			[
				&_format
			]{
				if(
					_format.srgb()
					==
					sge::renderer::pixel_format::srgb::yes
				)
					throw sge::renderer::unsupported(
						FCPPT_TEXT("sRGB visuals"),
						FCPPT_TEXT(""),
						FCPPT_TEXT("GLX_EXT_framebuffer_sRGB, GLX_ARB_framebuffer_sRGB")
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

	ret.push_back(
		None
	);

	return
		ret;
}
