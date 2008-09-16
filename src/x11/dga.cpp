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


#include <sge/config.h>
#include <sge/x11/dga.hpp>
#ifdef SGE_USE_DGA
#include <X11/extensions/xf86dga.h>

sge::x11::dga_guard::dga_guard(
	display_ptr const dsp,
	int const screen)
 : dsp(dsp),
   screen(screen),
   enabled(false)
{
	enable(true);
}

sge::x11::dga_guard::~dga_guard()
{
	enable(false);
}

void sge::x11::dga_guard::enable(
	bool const b)
{
	if(enabled == b)
		return;

	XF86DGADirectVideo(dsp->get(), screen, b ? XF86DGADirectMouse : 0);

	enabled = b;
}
#endif
