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


#ifndef SGE_OGL_XF86VIDMODE_HPP_INCLUDED
#define SGE_OGL_XF86VIDMODE_HPP_INCLUDED

#include <cstddef>
#include <boost/noncopyable.hpp>
#include "../../shared_ptr.hpp"
#include "../../x_deleter.hpp"
#include "../../x_display.hpp"
#include "../../renderer/types.hpp"
#include "xf86_resolution.hpp"
#include <X11/Xlib.h>
#include <X11/extensions/xf86vmode.h>

namespace sge
{
struct display_mode;
namespace ogl
{

class xf86_vidmode_array : boost::noncopyable {
public:
	typedef std::size_t size_type;

	xf86_vidmode_array(x_display_ptr dsp, const int screen);
	const XF86VidModeModeInfo& operator[](size_type index) const;
	static unsigned refresh_rate(const XF86VidModeModeInfo&);
	size_type size() const;
	xf86_resolution_ptr switch_to_mode(const display_mode&) const;
private:
	const x_display_ptr dsp;
	const int screen;
	typedef shared_ptr<XF86VidModeModeInfo*, x_deleter> x_vidmode_ptr;
	x_vidmode_ptr modes;
	size_type sz;
};

}
}

#endif
