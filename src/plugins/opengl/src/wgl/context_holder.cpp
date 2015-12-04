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


#include <sge/opengl/wgl/context_holder.hpp>
#include <sge/opengl/windows/gdi_device.hpp>
#include <sge/renderer/exception.hpp>
#include <awl/backends/windows/windows.hpp>
#include <fcppt/text.hpp>


sge::opengl::wgl::context_holder::context_holder(
	sge::opengl::windows::gdi_device const &_gdi_device
)
:
	glrc_(
		::wglCreateContext(
			_gdi_device.hdc()
		)
	)
{
	if(
		glrc_
		==
		nullptr
	)
		throw
			sge::renderer::exception{
				FCPPT_TEXT("wglCreateContext() failed!")
			};
}

sge::opengl::wgl::context_holder::~context_holder()
{
	::wglDeleteContext(
		glrc_
	);
}

HGLRC
sge::opengl::wgl::context_holder::get() const
{
	return
		glrc_;
}
