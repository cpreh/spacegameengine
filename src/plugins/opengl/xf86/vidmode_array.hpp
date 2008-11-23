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


#ifndef SGE_OPENGL_XF86_VIDMODE_ARRAY_HPP_INCLUDED
#define SGE_OPENGL_XF86_VIDMODE_ARRAY_HPP_INCLUDED

#include <X11/Xlib.h>
#include <X11/extensions/xf86vmode.h>
#include "resolution_fwd.hpp"
#include <sge/x11/deleter.hpp>
#include <sge/x11/display_fwd.hpp>
#include <sge/shared_ptr.hpp>
#include <sge/export.hpp>
#include <boost/noncopyable.hpp>
#include <cstddef>

namespace sge
{
namespace renderer
{
struct display_mode;
}

namespace ogl
{
namespace xf86
{

class vidmode_array : boost::noncopyable {
public:
	typedef std::size_t size_type;

	SGE_SYMBOL vidmode_array(
		sge::x11::display_ptr dsp,
		int screen);
	SGE_SYMBOL XF86VidModeModeInfo const &
	operator[](
		size_type index) const;

	SGE_SYMBOL static unsigned
	refresh_rate(
		XF86VidModeModeInfo const &);
	SGE_SYMBOL size_type size() const;
	SGE_SYMBOL resolution_ptr const
	switch_to_mode(
		renderer::display_mode const &) const;
private:
	sge::x11::display_ptr const dsp;
	int const screen;
	typedef shared_ptr<
		XF86VidModeModeInfo*,
		sge::x11::deleter
	> vidmode_ptr;

	vidmode_ptr modes;
	size_type sz;
};

}
}
}

#endif
