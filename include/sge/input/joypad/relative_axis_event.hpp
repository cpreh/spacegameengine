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


#ifndef SGE_INPUT_JOYPAD_RELATIVE_AXIS_EVENT_HPP_INCLUDED
#define SGE_INPUT_JOYPAD_RELATIVE_AXIS_EVENT_HPP_INCLUDED

#include <sge/input/detail/symbol.hpp>
#include <sge/input/joypad/axis_value.hpp>
#include <sge/input/joypad/relative_axis.hpp>
#include <sge/input/joypad/relative_axis_event_fwd.hpp>


namespace sge
{
namespace input
{
namespace joypad
{

class relative_axis_event
{
public:
	SGE_INPUT_DETAIL_SYMBOL
	relative_axis_event(
		sge::input::joypad::relative_axis const &,
		sge::input::joypad::axis_value
	);

	SGE_INPUT_DETAIL_SYMBOL
	sge::input::joypad::relative_axis const &
	axis() const;

	SGE_INPUT_DETAIL_SYMBOL
	sge::input::joypad::axis_value
	value() const;
private:
	sge::input::joypad::relative_axis axis_;

	sge::input::joypad::axis_value axis_value_;
};

}
}
}

#endif
