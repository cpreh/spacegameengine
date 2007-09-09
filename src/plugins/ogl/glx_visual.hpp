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


#ifndef SGE_OGL_GLX_VISUAL_HPP_INCLUDED
#define SGE_OGL_GLX_VISUAL_HPP_INCLUDED

#include "../../shared_ptr.hpp"
#include "../../x_display.hpp"
#include "../../x_deleter.hpp"
#include <X11/Xutil.h>

namespace sge
{
namespace ogl
{

class glx_visual {
public:
	glx_visual(x_display_ptr, int screen, const int* attributes);
	const XVisualInfo& visual_info() const;
private:
	typedef shared_ptr<XVisualInfo, x_deleter> x_visualinfo_ptr;
	x_visualinfo_ptr vi;
};

}
}

#endif
