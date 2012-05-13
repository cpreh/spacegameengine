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


#include <sge/opengl/device_state/context.hpp>
#include <sge/opengl/wgl/make_current.hpp>
#include <sge/opengl/windows/context.hpp>
#include <sge/opengl/windows/gdi_device.hpp>
#include <awl/backends/windows/window/object.hpp>
#include <fcppt/null_ptr.hpp>


sge::opengl::windows::context::context(
	awl::backends::windows::window::object &_window
)
:
	hdc_(
		_window.hwnd(),
		sge::opengl::windows::gdi_device::get_tag()
	),
	wgl_context_(
		hdc_
	)
{
}

sge::opengl::windows::context::~context()
{
}

void
sge::opengl::windows::context::activate()
{
	sge::opengl::wgl::make_current(
		hdc_.hdc(),
		wgl_context_.hglrc()
	);
}

void
sge::opengl::windows::context::deactivate()
{
	sge::opengl::wgl::make_current(
		fcppt::null_ptr(),
		fcppt::null_ptr()
	);
}

sge::opengl::windows::gdi_device const &
sge::opengl::windows::context::dc() const
{
	return
		hdc_;
}
