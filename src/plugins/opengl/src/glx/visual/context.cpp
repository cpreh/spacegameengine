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


#include <sge/opengl/optional_int.hpp>
#include <sge/opengl/context/system/base.hpp>
#include <sge/opengl/context/system/id.hpp>
#include <sge/opengl/context/system/make_id.hpp>
#include <sge/opengl/glx/visual/context.hpp>
#include <fcppt/config/external_begin.hpp>
#include <GL/glx.h>
#include <fcppt/config/external_end.hpp>


sge::opengl::glx::visual::context::context()
:
	sge::opengl::context::system::base(),
	flag_(
		// FIXME!
/*
		sge::opengl::glew::is_supported(
			"GLX_EXT_framebuffer_sRGB"
		)
		?*/
			sge::opengl::optional_int(
				GLX_FRAMEBUFFER_SRGB_CAPABLE_EXT
			)
		/*:
			sge::opengl::glew::is_supported(
				"GLX_ARB_framebuffer_sRGB"
			)
			?
				sge::opengl::optional_int(
					GLX_FRAMEBUFFER_SRGB_CAPABLE_ARB
				)
			:
				sge::opengl::optional_int()*/
	)
{
}

sge::opengl::glx::visual::context::~context()
{
}

sge::opengl::optional_int const
sge::opengl::glx::visual::context::flag() const
{
	return flag_;
}

sge::opengl::context::system::id const
sge::opengl::glx::visual::context::static_id(
	sge::opengl::context::system::make_id()
);
