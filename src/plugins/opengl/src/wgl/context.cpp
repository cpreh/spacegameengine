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


#include <sge/opengl/wgl/context.hpp>
#include <sge/opengl/windows/gdi_device.hpp>
#include <sge/opengl/wgl/make_current.hpp>
#include <sge/renderer/exception.hpp>
#include <sge/renderer/parameters/vsync.hpp>
#include <awl/backends/windows/windows.hpp>
#include <awl/backends/windows/window/object.hpp>
#include <fcppt/null_ptr.hpp>
#include <fcppt/text.hpp>


sge::opengl::wgl::context::context(
	awl::backends::windows::window::object &_window
)
:
	gdi_device_(
		_window.hwnd(),
		sge::opengl::windows::gdi_device::get_tag()
	),
	glrc_(
		::wglCreateContext(
			gdi_device_.hdc()
		)
	)
{
	if(
		!glrc_
	)
		throw sge::renderer::exception(
			FCPPT_TEXT("wglCreateContext() failed!")
		);
}

sge::opengl::wgl::context::~context()
{
	::wglDeleteContext(
		glrc_
	);
}

void
sge::opengl::wgl::context::activate()
{
	sge::opengl::wgl::make_current(
		gdi_device_.hdc(),
		glrc_
	);
}

void
sge::opengl::wgl::context::deactivate()
{
	sge::opengl::wgl::make_current(
		fcppt::null_ptr(),
		fcppt::null_ptr()
	);
}

void
sge::opengl::wgl::context::begin_rendering()
{
}

void
sge::opengl::wgl::context::end_rendering()
{
	if(
		::wglSwapLayerBuffers(
			gdi_device_.hdc(),
			WGL_SWAP_MAIN_PLANE
		)
		== FALSE
	)
		throw sge::renderer::exception(
			FCPPT_TEXT("wglSwapLayerBuffers() failed!")
		);
}

void
sge::opengl::wgl::context::vsync(
	sge::renderer::parameters::vsync::type const _vsync
)
{
}
