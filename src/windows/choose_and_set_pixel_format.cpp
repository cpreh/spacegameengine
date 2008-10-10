/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2007  Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include <sge/windows/choose_pixel_format.hpp>
#include <sge/windows/device_context.hpp>
#include <sge/exception.hpp>
#include <sge/text.hpp>

void sge::windows::choose_and_set_pixel_format(
	device_context const &dc,
	DWORD const flags,
	BYTE const pixel_type,
	BYTE const depth,
	BYTE const depth_buffer,
	BYTE const stencil_buffer)
{
	PIXELFORMATDESCRIPTOR const pfd = {
		sizeof(PIXELFORMATDESCRIPTOR),  // Size Of This Pixel Format Descriptor
			1,                      // Version Number
			flags,
			pixel_type,             // Request An RGBA Format
			depth,                  // Select Our Color Depth
			0, 0, 0, 0, 0, 0,       // Color Bits Ignored
			0,                      // No Alpha Buffer
			0,                      // Shift Bit Ignored
			0,                      // No Accumulation Buffer
			0, 0, 0, 0,             // Accumulation Bits Ignored
			depth_buffer,
			stencil_buffer,
			0,                      // No Auxiliary Buffer
			PFD_MAIN_PLANE,         // Main Drawing Layer
			0,                      // Reserved
			0, 0, 0                 // Layer Masks Ignored
	};

	int const format = ChoosePixelFormat(
		dc.hdc(),
		&pfd);
	
	if(format == 0)
		throw exception(
			SGE_TEXT("ChoosePixelFormat() failed"));
	
	if(SetPixelFormat(dc.hdc(), format, &pfd) == FALSE)
		throw exception(
			SGE_TEXT("SetPixelFormat() failed"));
}
