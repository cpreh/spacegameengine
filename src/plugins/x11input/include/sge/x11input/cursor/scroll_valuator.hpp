/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2015 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#ifndef SGE_X11INPUT_CURSOR_SCROLL_VALUATOR_HPP_INCLUDED
#define SGE_X11INPUT_CURSOR_SCROLL_VALUATOR_HPP_INCLUDED

#include <sge/input/cursor/scroll_code.hpp>
#include <sge/x11input/cursor/scroll_valuator_fwd.hpp>
#include <sge/x11input/device/valuator_value.hpp>


namespace sge
{
namespace x11input
{
namespace cursor
{

class scroll_valuator
{
public:
	scroll_valuator(
		sge::x11input::device::valuator_value,
		sge::input::cursor::scroll_code
	);

	sge::x11input::device::valuator_value const
	last_value() const;

	sge::input::cursor::scroll_code
	code() const;

	void
	last_value(
		sge::x11input::device::valuator_value
	);
private:
	sge::x11input::device::valuator_value value_;

	sge::input::cursor::scroll_code code_;
};

}
}
}

#endif
