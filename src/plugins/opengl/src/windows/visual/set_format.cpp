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


#include <sge/opengl/windows/gdi_device.hpp>
#include <sge/opengl/windows/visual/format.hpp>
#include <sge/opengl/windows/visual/set_format.hpp>
#include <sge/renderer/exception.hpp>
#include <awl/backends/windows/windows.hpp>
#include <fcppt/text.hpp>


void
sge::opengl::windows::visual::set_format(
	sge::opengl::windows::gdi_device const &_device,
	sge::opengl::windows::visual::format const _format,
	PIXELFORMATDESCRIPTOR const &_format_desc
)
{
	if(
		::SetPixelFormat(
			_device.hdc(),
			_format.get(),
			&_format_desc
		)
		== FALSE
	)
		throw sge::renderer::exception(
			FCPPT_TEXT("SetPixelFormat() failed")
		);
}
