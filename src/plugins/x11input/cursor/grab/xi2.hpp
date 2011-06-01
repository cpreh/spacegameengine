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


#ifndef SGE_X11INPUT_CURSOR_GRAB_XI2_HPP_INCLUDED
#define SGE_X11INPUT_CURSOR_GRAB_XI2_HPP_INCLUDED

#include <sge/x11input/config.hpp>
#if defined(SGE_X11INPUT_HAVE_XI_2_1)
#include "../confine.hpp"
#include "../../device/id.hpp"
#include <awl/backends/x11/window/instance_fwd.hpp>
#include <fcppt/noncopyable.hpp>

namespace sge
{
namespace x11input
{
namespace cursor
{
namespace grab
{

class xi2
:
	public cursor::confine
{
	FCPPT_NONCOPYABLE(
		xi2
	);
public:
	xi2(
		awl::backends::x11::window::instance &,
		x11input::device::id
	);

	~xi2();
private:
	awl::backends::x11::window::instance &window_;

	x11input::device::id const id_;
};

}
}
}
}

#endif

#endif
