/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2009 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include "../check_dga_mouse.hpp"
#include <sge/x11/window.hpp>
#ifdef SGE_USE_DGA
#include <X11/extensions/Xxf86dga.h>
#include <sge/x11/display.hpp>
#include <sge/exception.hpp>
#include <fcppt/text.hpp>
#endif

bool sge::x11input::check_dga_mouse(
	x11::window_ptr
#ifdef SGE_USE_DGA
	const wnd
#endif
)

{
#ifdef SGE_USE_DGA
	int flags;
	if(XF86DGAQueryDirectVideo(
		wnd->display()->get(),
		wnd->screen(),
		&flags)
	== false)
		throw exception(
			FCPPT_TEXT("XF86DGAQueryDirectVideo() failed!"));
	return !(flags & XF86DGADirectMouse);
#else
	return false;
#endif
}
