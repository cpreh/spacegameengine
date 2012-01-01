/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2012 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#ifndef SGE_X11INPUT_CURSOR_PIXMAP_HPP_INCLUDED
#define SGE_X11INPUT_CURSOR_PIXMAP_HPP_INCLUDED

#include <sge/x11input/pixmap_fwd.hpp>
#include <sge/x11input/cursor/image.hpp>
#include <sge/x11input/cursor/pixmap_fwd.hpp>
#include <awl/backends/x11/display_fwd.hpp>
#include <fcppt/noncopyable.hpp>


namespace sge
{
namespace x11input
{
namespace cursor
{

class pixmap
{
	FCPPT_NONCOPYABLE(
		pixmap
	);
public:
	pixmap(
		awl::backends::x11::display &,
		x11input::pixmap const &
	);

	~pixmap();

	cursor::image const
	get() const;
private:
	awl::backends::x11::display &display_;

	cursor::image const cursor_;
};

}
}
}

#endif
