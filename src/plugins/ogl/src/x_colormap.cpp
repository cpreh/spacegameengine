/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006  Carl Philipp Reh (sefi@s-e-f-i.de)

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/


#include "../../../types.hpp"
#ifdef SGE_LINUX_PLATFORM
#include "../../../exception.hpp"
#include "../x_colormap.hpp"

sge::ogl::x_colormap::x_colormap(const x_display_ptr dsp, const XVisualInfo& vi)
: dsp(dsp),
  c(XCreateColormap(dsp->get(), RootWindow(dsp->get(), vi.screen), vi.visual, AllocNone))
{
	if(colormap() == 0)
		throw exception("XCreateColormap() failed");
}

sge::ogl::x_colormap::~x_colormap()
{
	XFreeColormap(dsp->get(), colormap());
}

Colormap& sge::ogl::x_colormap::colormap()
{
	return c;
}

#endif
