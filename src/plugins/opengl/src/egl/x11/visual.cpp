/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2014 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#include <sge/opengl/egl/visual/base.hpp>
#include <sge/opengl/egl/x11/create_visual_info.hpp>
#include <sge/opengl/egl/x11/visual.hpp>
#include <sge/renderer/pixel_format/object_fwd.hpp>
#include <awl/backends/x11/display_fwd.hpp>
#include <awl/backends/x11/visual/wrapped.hpp>
#include <fcppt/config/external_begin.hpp>
#include <EGL/egl.h>
#include <fcppt/config/external_end.hpp>


sge::opengl::egl::x11::visual::visual(
	awl::backends::x11::display const &_display,
	EGLDisplay const _egl_display,
	sge::renderer::pixel_format::object const &_pixel_format
)
:
	sge::opengl::egl::visual::base(
		_egl_display,
		_pixel_format
	),
	awl::backends::x11::visual::wrapped(
		sge::opengl::egl::x11::create_visual_info(
			_display,
			_egl_display,
			this->config()
		)
	)
{
}

sge::opengl::egl::x11::visual::~visual()
{
}
