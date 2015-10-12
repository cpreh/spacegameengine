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
#include <sge/opengl/glx/visual/context.hpp>
#include <fcppt/preprocessor/disable_gcc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>
#include <fcppt/config/external_begin.hpp>
#include <GL/glxew.h>
#include <fcppt/config/external_end.hpp>


FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_GCC_WARNING(-Wold-style-cast)

sge::opengl::glx::visual::context::context()
:
	sge::opengl::context::system::base(),
	srgb_flag_(
		sge::opengl::convert::from_gl_bool(
			GLXEW_EXT_framebuffer_sRGB
		)
		?
			sge::opengl::optional_int(
				GLX_FRAMEBUFFER_SRGB_CAPABLE_EXT
			)
		:
			sge::opengl::convert::from_gl_bool(
				GLXEW_ARB_framebuffer_sRGB
			)
			?
				sge::opengl::optional_int(
					GLX_FRAMEBUFFER_SRGB_CAPABLE_ARB
				)
			:
				sge::opengl::optional_int()
	)
{
}

FCPPT_PP_POP_WARNING

sge::opengl::glx::visual::context::~context()
{
}

sge::opengl::optional_int
sge::opengl::glx::visual::context::srgb_flag() const
{
	return
		srgb_flag_;
}

sge::opengl::context::system::id const
sge::opengl::glx::visual::context::static_id(
	sge::opengl::context::system::make_id()
);
