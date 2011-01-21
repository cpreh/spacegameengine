/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2011 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#ifndef SGE_X11INPUT_PIXMAP_CURSOR_HPP_INCLUDED
#define SGE_X11INPUT_PIXMAP_CURSOR_HPP_INCLUDED

#include "pixmap_cursor_fwd.hpp"
#include <awl/backends/x11/display_ptr.hpp>
#include <fcppt/noncopyable.hpp>
#include <X11/Xlib.h>

namespace sge
{
namespace x11input
{

class pixmap_cursor
{
	FCPPT_NONCOPYABLE(
		pixmap_cursor
	)
public:
	pixmap_cursor(
		awl::backends::x11::display_ptr,
		Pixmap
	);

	~pixmap_cursor();

	Cursor
	get() const;
private:
	awl::backends::x11::display_ptr const display_;

	Cursor cursor_;
};

}
}

#endif
