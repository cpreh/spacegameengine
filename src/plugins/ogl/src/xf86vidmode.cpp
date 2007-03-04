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


#include <cstddef>
#include <stdexcept>
#include <iostream>
#include "../../../math.hpp"
#include "../xf86vidmode.hpp"

sge::ogl::xf86_vidmode_array::xf86_vidmode_array(const x_display& dsp, const int screen)
{
	int event_base, error_base;
	if(XF86VidModeQueryExtension(dsp.get(), &event_base, &error_base) == False)
	{
		std::cerr << "Warning: xf86 video modes queried but extension is not present!\n";
		sz = 0;
		return;
	}

	int mode_count;
	if(XF86VidModeGetAllModeLines(dsp.get(),screen,&mode_count,modes.pointer_to()) == False)
		throw std::runtime_error("XF86VidModeGetAllModeLines() failed");
	sz = mode_count >= 0 ? mode_count : 0;
}

const XF86VidModeModeInfo& sge::ogl::xf86_vidmode_array::operator[](const size_type index) const
{
	return *(*modes)[index];
}

unsigned sge::ogl::xf86_vidmode_array::refresh_rate(const XF86VidModeModeInfo& mode)
{
	return round_div_int(1000 * mode.dotclock, unsigned(mode.htotal * mode.vtotal));
}

sge::ogl::xf86_vidmode_array::size_type sge::ogl::xf86_vidmode_array::size() const
{
	return sz;
}
