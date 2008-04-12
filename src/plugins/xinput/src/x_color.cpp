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


#include <X11/Xlib.h>
#include "../x_color.hpp"
#include <sge/exception.hpp>
	
sge::xinput::x_color::x_color(const x_display_ptr dsp, Colormap colormap)
 : dsp(dsp),
   colormap(colormap)
{
	XColor dummy;
	if(XAllocNamedColor(dsp->get(), colormap, "black", &_color, &dummy ) == 0)
		throw exception(SGE_TEXT("XAllocNamedColor() failed!"));
}

sge::xinput::x_color::~x_color()
{
	XFreeColors(dsp->get(), colormap, &_color.pixel, 1, 0);
}

XColor sge::xinput::x_color::color() const
{
	return _color;
}
