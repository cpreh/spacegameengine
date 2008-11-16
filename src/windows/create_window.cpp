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


#include <sge/windows/create_window.hpp>
#include <sge/windows/choose_and_set_pixel_format.hpp>
#include <sge/windows/gdi_device.hpp>
#include <sge/windows/window.hpp>

sge::window::instance_ptr const
sge::windows::create_window(
	sge::window::parameters const &param)
{
	renderer::parameters const &rparam(
		param.param());

	windows::window_ptr const wnd(
		new windows::window(
			rparam().mode().size(),
			param.title()));

	windows::choose_and_set_pixel_format(
		windows::gdi_device(
			wnd->hwnd(),
			windows::gdi_device::get_tag()),
		PFD_DRAW_TO_WINDOW |
		PFD_SUPPORT_OPENGL |
		PFD_DOUBLEBUFFER,
		PFD_TYPE_RGBA,
		static_cast<BYTE>(rparam.mode().bit_depth()),
		static_cast<BYTE>(rparam.dbuffer()),
		static_cast<BYTE>(rparam.sbuffer()));

	return wnd;
}
