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


#include "../../../config.h"
#ifdef SGE_LINUX_PLATFORM
#include "../../../exception.hpp"
#include "../../../iostream.hpp"
#include "../../../ostream.hpp"
#include "../../../math/round_div_int.hpp"
#include "../../../renderer/display_mode.hpp"
#include "../xf86vidmode.hpp"

sge::ogl::xf86_vidmode_array::xf86_vidmode_array(const x_display_ptr dsp, const int screen)
: dsp(dsp),
  screen(screen)
{
	int event_base, error_base;
	if(XF86VidModeQueryExtension(dsp->get(), &event_base, &error_base) == False)
	{
		sge::cerr << SGE_TEXT("Warning: xf86 video modes queried but extension is not present!\n");
		sz = 0;
		return;
	}

	int mode_count;
	XF86VidModeModeInfo** ret;	
	if(XF86VidModeGetAllModeLines(dsp->get(), screen, &mode_count, &ret) == False)
		throw exception(SGE_TEXT("XF86VidModeGetAllModeLines() failed"));
	modes.reset(ret);
	sz = mode_count >= 0 ? mode_count : 0;
}

const XF86VidModeModeInfo& sge::ogl::xf86_vidmode_array::operator[](const size_type index) const
{
	return (*modes)[index];
}

unsigned sge::ogl::xf86_vidmode_array::refresh_rate(const XF86VidModeModeInfo& mode)
{
	return math::round_div_int(1000 * mode.dotclock, unsigned(mode.htotal * mode.vtotal));
}

sge::ogl::xf86_vidmode_array::size_type sge::ogl::xf86_vidmode_array::size() const
{
	return sz;
}

sge::ogl::xf86_resolution_ptr sge::ogl::xf86_vidmode_array::switch_to_mode(const display_mode& pmode) const
{
	int best = -1;
	for(xf86_vidmode_array::size_type i = 1; i < size(); ++i)
	{
		const XF86VidModeModeInfo& mode = (*this)[i];
		const unsigned rate = refresh_rate(mode);

		if(mode.hdisplay == pmode.width() &&
		   mode.vdisplay == pmode.height() &&
		   rate  >= pmode.refresh_rate &&
		   (best == -1 || rate >= refresh_rate((*this)[best])))
			best = static_cast<int>(i);
	}
	
	if(best != -1)
		return xf86_resolution_ptr(new xf86_resolution(dsp, screen, (*this)[best], (*this)[0]));
	return xf86_resolution_ptr();
}

#endif
