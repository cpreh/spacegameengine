/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2014 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#ifndef SGE_INPUT_CURSOR_SCROLL_EVENT_HPP_INCLUDED
#define SGE_INPUT_CURSOR_SCROLL_EVENT_HPP_INCLUDED

#include <sge/input/detail/symbol.hpp>
#include <sge/input/cursor/scroll_code.hpp>
#include <sge/input/cursor/scroll_event_fwd.hpp>
#include <sge/input/cursor/scroll_value.hpp>


namespace sge
{
namespace input
{
namespace cursor
{

class scroll_event
{
public:
	SGE_INPUT_DETAIL_SYMBOL
	scroll_event(
		sge::input::cursor::scroll_code,
		sge::input::cursor::scroll_value
	);

	SGE_INPUT_DETAIL_SYMBOL
	sge::input::cursor::scroll_code
	code() const;

	SGE_INPUT_DETAIL_SYMBOL
	sge::input::cursor::scroll_value
	value() const;
private:
	sge::input::cursor::scroll_code code_;

	sge::input::cursor::scroll_value value_;
};

}
}
}

#endif
