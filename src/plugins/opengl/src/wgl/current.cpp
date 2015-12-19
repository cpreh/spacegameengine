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


#include <sge/opengl/backend/current.hpp>
#include <sge/opengl/wgl/current.hpp>
#include <sge/opengl/wgl/get_proc_address.hpp>
#include <sge/opengl/windows/gdi_device.hpp>
#include <sge/renderer/exception.hpp>
#include <sge/renderer/display_mode/vsync.hpp>
#include <awl/backends/windows/windows.hpp>
#include <fcppt/text.hpp>


sge::opengl::wgl::current::current(
	sge::opengl::windows::gdi_device const &_gdi_device
)
:
	sge::opengl::backend::current(),
	gdi_device_(
		_gdi_device
	)
{
}

sge::opengl::wgl::current::~current()
{
}

sge::opengl::backend::fun_ptr
sge::opengl::wgl::current::load_function(
	std::string const &_name
) const
{
	return
		reinterpret_cast<
			sge::opengl::backend::fun_ptr
		>(
			sge::opengl::wgl::get_proc_address(
				_name
			)
		);
}
	
void
sge::opengl::wgl::current::begin_rendering()
{
}

void
sge::opengl::wgl::current::end_rendering()
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
sge::opengl::wgl::current::vsync(
	sge::renderer::display_mode::vsync const _vsync
)
{
}
