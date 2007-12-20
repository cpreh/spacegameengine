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


#ifndef SGE_OPENGL_XF86_RESOLUTION_HPP_INCLUDED
#define SGE_OPENGL_XF86_RESOLUTION_HPP_INCLUDED

#include "../../shared_ptr.hpp"
#include "../../x_display.hpp"
#include <X11/extensions/xf86vmode.h>

namespace sge
{
namespace ogl
{

class xf86_resolution : boost::noncopyable {
public:
	xf86_resolution(x_display_ptr,
	                int screen,
	                const XF86VidModeModeInfo& new_mode,
	                const XF86VidModeModeInfo& old_mode);
	~xf86_resolution(); 
private:
	const x_display_ptr dsp;
	const int screen;
	const XF86VidModeModeInfo& old_mode;
};

typedef shared_ptr<xf86_resolution> xf86_resolution_ptr;

}
}

#endif
