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


#ifndef SGE_OGL_XF86VIDMODE_HPP_INCLUDED
#define SGE_OGL_XF86VIDMODE_HPP_INCLUDED

#include <cstddef>
#include <X11/Xlib.h>
#include <X11/extensions/xf86vmode.h>
#include "../../x.hpp"
#include "glx.hpp"

namespace sge
{

namespace ogl
{

class xf86_vidmode_array {
public:
	typedef std::size_t size_type;
	xf86_vidmode_array(const x_display& dsp, const int screen);
	const XF86VidModeModeInfo& operator[](size_type index) const;
	static unsigned refresh_rate(const XF86VidModeModeInfo&);
	size_type size() const;
private:
	x_resource<XF86VidModeModeInfo**> modes;
	size_type sz;
};

}
}

#endif
