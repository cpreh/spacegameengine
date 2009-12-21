/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2009 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#ifndef SGE_OPENGL_XF86VMODE_MODES_HPP_INCLUDED
#define SGE_OPENGL_XF86VMODE_MODES_HPP_INCLUDED

#include <X11/Xlib.h>
#include <X11/extensions/xf86vmode.h>
#include "resolution_fwd.hpp"
#include <sge/x11/deleter.hpp>
#include <sge/x11/display_ptr.hpp>
#include <fcppt/shared_ptr.hpp>
#include <fcppt/noncopyable.hpp>
#include <cstddef>

namespace sge
{
namespace opengl
{
namespace xf86vmode
{

class modes {
	FCPPT_NONCOPYABLE(modes)
public:
	typedef std::size_t size_type;

	modes(
		sge::x11::display_ptr dsp,
		int screen);

	XF86VidModeModeInfo const &
	operator[](
		size_type index) const;

	size_type size() const;

	sge::x11::display_ptr const display() const;
	int screen() const;
private:
	sge::x11::display_ptr const dsp;

	int const screen_;

	typedef fcppt::shared_ptr<
		XF86VidModeModeInfo *,
		sge::x11::deleter
	> vidmode_ptr;

	vidmode_ptr modes_;

	size_type sz;
};

}
}
}

#endif
