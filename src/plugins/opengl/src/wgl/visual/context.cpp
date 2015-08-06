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


#include <sge/opengl/optional_int.hpp>
#include <sge/opengl/context/system/base.hpp>
#include <sge/opengl/context/system/id.hpp>
#include <sge/opengl/context/system/make_id.hpp>
#include <sge/opengl/convert/from_gl_bool.hpp>
#include <sge/opengl/wgl/visual/context.hpp>
#include <sge/opengl/wgl/visual/optional_pixel_format_types.hpp>
#include <sge/opengl/wgl/visual/pixel_format_types.hpp>
#include <fcppt/preprocessor/disable_gcc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>
#include <fcppt/config/external_begin.hpp>
#include <GL/wglew.h>
#include <fcppt/config/external_end.hpp>


FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_GCC_WARNING(-Wold-style-cast)

sge::opengl::wgl::visual::context::context()
:
	sge::opengl::context::system::base(),
	pixel_format_types_(
		sge::opengl::convert::from_gl_bool(
			WGLEW_ARB_pixel_format
		)
		?
			sge::opengl::wgl::visual::optional_pixel_format_types(
				sge::opengl::wgl::visual::pixel_format_types(
					sge::opengl::wgl::visual::pixel_format_types::draw_to_window_flag(
						WGL_DRAW_TO_WINDOW_ARB
					),
					sge::opengl::wgl::visual::pixel_format_types::support_opengl_flag(
						WGL_SUPPORT_OPENGL_ARB
					),
					sge::opengl::wgl::visual::pixel_format_types::double_buffer_flag(
						WGL_DOUBLE_BUFFER_ARB
					),
					sge::opengl::wgl::visual::pixel_format_types::pixel_type_flag(
						WGL_PIXEL_TYPE_ARB
					),
					sge::opengl::wgl::visual::pixel_format_types::pixel_type_rgba_flag(
						WGL_TYPE_RGBA_ARB
					),
					sge::opengl::wgl::visual::pixel_format_types::color_bits_flag(
						WGL_COLOR_BITS_ARB
					),
					sge::opengl::wgl::visual::pixel_format_types::depth_bits_flag(
						WGL_DEPTH_BITS_ARB
					),
					sge::opengl::wgl::visual::pixel_format_types::stencil_bits_flag(
						WGL_STENCIL_BITS_ARB
					),
					sge::opengl::wgl::visual::pixel_format_types::wgl_choose_pixel_format(
						wglChoosePixelFormatARB
					)
				)
			)
		:
			sge::opengl::convert::from_gl_bool(
				WGLEW_EXT_pixel_format
			)
			?
				sge::opengl::wgl::visual::optional_pixel_format_types(
					sge::opengl::wgl::visual::pixel_format_types(
						sge::opengl::wgl::visual::pixel_format_types::draw_to_window_flag(
							WGL_DRAW_TO_WINDOW_EXT
						),
						sge::opengl::wgl::visual::pixel_format_types::support_opengl_flag(
							WGL_SUPPORT_OPENGL_EXT
						),
						sge::opengl::wgl::visual::pixel_format_types::double_buffer_flag(
							WGL_DOUBLE_BUFFER_EXT
						),
						sge::opengl::wgl::visual::pixel_format_types::pixel_type_flag(
							WGL_PIXEL_TYPE_EXT
						),
						sge::opengl::wgl::visual::pixel_format_types::pixel_type_rgba_flag(
							WGL_TYPE_RGBA_EXT
						),
						sge::opengl::wgl::visual::pixel_format_types::color_bits_flag(
							WGL_COLOR_BITS_EXT
						),
						sge::opengl::wgl::visual::pixel_format_types::depth_bits_flag(
							WGL_DEPTH_BITS_EXT
						),
						sge::opengl::wgl::visual::pixel_format_types::stencil_bits_flag(
							WGL_STENCIL_BITS_EXT
						),
						sge::opengl::wgl::visual::pixel_format_types::wgl_choose_pixel_format(
							wglChoosePixelFormatEXT
						)
					)
				)
			:
				sge::opengl::wgl::visual::optional_pixel_format_types()
	),
	multi_sample_flag_(
		sge::opengl::convert::from_gl_bool(
			WGLEW_ARB_multisample
		)
		?
			sge::opengl::optional_int(
				WGL_SAMPLE_BUFFERS_ARB
			)
		:
			sge::opengl::convert::from_gl_bool(
				WGLEW_EXT_multisample
			)
			?
				sge::opengl::optional_int(
					WGL_SAMPLE_BUFFERS_EXT
				)
			:
				sge::opengl::optional_int()
	),
	srgb_flag_(
		sge::opengl::convert::from_gl_bool(
			WGLEW_ARB_framebuffer_sRGB
		)
		?
			sge::opengl::optional_int(
				WGL_FRAMEBUFFER_SRGB_CAPABLE_ARB
			)
		:
			sge::opengl::convert::from_gl_bool(
				WGLEW_EXT_framebuffer_sRGB
			)
			?
				sge::opengl::optional_int(
					WGL_FRAMEBUFFER_SRGB_CAPABLE_EXT
				)
			:
				sge::opengl::optional_int()
	)
{
}

FCPPT_PP_POP_WARNING

sge::opengl::wgl::visual::context::~context()
{
}

sge::opengl::wgl::visual::optional_pixel_format_types const
sge::opengl::wgl::visual::context::pixel_format_types() const
{
	return
		pixel_format_types_;
}

sge::opengl::optional_int const
sge::opengl::wgl::visual::context::multi_sample_flag() const
{
	return
		multi_sample_flag_;
}

sge::opengl::optional_int const
sge::opengl::wgl::visual::context::srgb_flag() const
{
	return
		srgb_flag_;
}

sge::opengl::context::system::id const
sge::opengl::wgl::visual::context::static_id(
	sge::opengl::context::system::make_id()
);
