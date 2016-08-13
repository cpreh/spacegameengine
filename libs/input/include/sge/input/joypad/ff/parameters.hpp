/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2016 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#ifndef SGE_INPUT_JOYPAD_FF_PARAMETERS_HPP_INCLUDED
#define SGE_INPUT_JOYPAD_FF_PARAMETERS_HPP_INCLUDED

#include <sge/input/detail/symbol.hpp>
#include <sge/input/joypad/ff/delay.hpp>
#include <sge/input/joypad/ff/direction.hpp>
#include <sge/input/joypad/ff/optional_duration.hpp>
#include <sge/input/joypad/ff/optional_trigger.hpp>
#include <sge/input/joypad/ff/parameters_fwd.hpp>
#include <sge/input/joypad/ff/variant.hpp>


namespace sge
{
namespace input
{
namespace joypad
{
namespace ff
{

class parameters
{
public:
	SGE_INPUT_DETAIL_SYMBOL
	parameters(
		sge::input::joypad::ff::direction,
		sge::input::joypad::ff::optional_trigger const &,
		sge::input::joypad::ff::optional_duration const &,
		sge::input::joypad::ff::delay,
		sge::input::joypad::ff::variant const &
	);

	SGE_INPUT_DETAIL_SYMBOL
	sge::input::joypad::ff::direction
	direction() const;

	SGE_INPUT_DETAIL_SYMBOL
	sge::input::joypad::ff::optional_trigger const &
	trigger() const;

	SGE_INPUT_DETAIL_SYMBOL
	sge::input::joypad::ff::optional_duration const &
	duration() const;

	SGE_INPUT_DETAIL_SYMBOL
	sge::input::joypad::ff::delay
	delay() const;

	SGE_INPUT_DETAIL_SYMBOL
	sge::input::joypad::ff::variant const &
	variant() const;
private:
	sge::input::joypad::ff::direction direction_;

	sge::input::joypad::ff::optional_trigger trigger_;

	sge::input::joypad::ff::optional_duration duration_;

	sge::input::joypad::ff::delay delay_;

	sge::input::joypad::ff::variant variant_;
};

}
}
}
}

#endif
