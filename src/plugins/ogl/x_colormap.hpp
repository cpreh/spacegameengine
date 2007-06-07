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


#ifndef SGE_OGL_X_COLORMAP_HPP_INCLUDED
#define SGE_OGL_X_COLORMAP_HPP_INCLUDED

#include <boost/noncopyable.hpp>
#include "../../x_display.hpp"
#include <X11/Xutil.h>

namespace sge
{
namespace ogl
{

class x_colormap : boost::noncopyable {
public:
	x_colormap(x_display_ptr, const XVisualInfo&);
	~x_colormap();
	Colormap& colormap();
private:
	const x_display_ptr dsp;
	Colormap c;
};

}
}

#endif
