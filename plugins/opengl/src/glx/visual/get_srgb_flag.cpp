/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2016 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#include <sge/opengl/glx/extension.hpp>
#include <sge/opengl/glx/extension_set.hpp>
#include <sge/opengl/glx/extension_supported.hpp>
#include <sge/opengl/glx/visual/get_srgb_flag.hpp>
#include <sge/opengl/glx/visual/optional_srgb_flag.hpp>
#include <sge/opengl/glx/visual/srgb_flag.hpp>
#include <fcppt/config/external_begin.hpp>
#include <GL/glx.h>
#include <fcppt/config/external_end.hpp>


sge::opengl::glx::visual::optional_srgb_flag
sge::opengl::glx::visual::get_srgb_flag(
	sge::opengl::glx::extension_set const &_extensions
)
{
	return
		sge::opengl::glx::extension_supported(
			_extensions,
			sge::opengl::glx::extension{
				"GLX_EXT_framebuffer_sRGB"
			}
		)
		?
			sge::opengl::glx::visual::optional_srgb_flag{
				sge::opengl::glx::visual::srgb_flag{
					GLX_FRAMEBUFFER_SRGB_CAPABLE_EXT
				}
			}
		:
			sge::opengl::glx::extension_supported(
				_extensions,
				sge::opengl::glx::extension{
					"GLX_ARB_framebuffer_sRGB"
				}
			)
			?
				sge::opengl::glx::visual::optional_srgb_flag{
					sge::opengl::glx::visual::srgb_flag{
						GLX_FRAMEBUFFER_SRGB_CAPABLE_ARB
					}
				}
			:
				sge::opengl::glx::visual::optional_srgb_flag{}
		;
}
