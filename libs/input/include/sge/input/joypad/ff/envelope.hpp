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


#ifndef SGE_INPUT_JOYPAD_FF_ENVELOPE_HPP_INCLUDED
#define SGE_INPUT_JOYPAD_FF_ENVELOPE_HPP_INCLUDED

#include <sge/input/detail/symbol.hpp>
#include <sge/input/joypad/ff/attack_level.hpp>
#include <sge/input/joypad/ff/attack_time.hpp>
#include <sge/input/joypad/ff/envelope_fwd.hpp>
#include <sge/input/joypad/ff/fade_level.hpp>
#include <sge/input/joypad/ff/fade_time.hpp>


namespace sge
{
namespace input
{
namespace joypad
{
namespace ff
{

class envelope
{
public:
	SGE_INPUT_DETAIL_SYMBOL
	envelope(
		sge::input::joypad::ff::attack_level,
		sge::input::joypad::ff::attack_time,
		sge::input::joypad::ff::fade_level,
		sge::input::joypad::ff::fade_time
	);

	SGE_INPUT_DETAIL_SYMBOL
	sge::input::joypad::ff::attack_level
	attack_level() const;

	SGE_INPUT_DETAIL_SYMBOL
	sge::input::joypad::ff::attack_time
	attack_time() const;

	SGE_INPUT_DETAIL_SYMBOL
	sge::input::joypad::ff::fade_level
	fade_level() const;

	SGE_INPUT_DETAIL_SYMBOL
	sge::input::joypad::ff::fade_time
	fade_time() const;
private:
	sge::input::joypad::ff::attack_level attack_level_;

	sge::input::joypad::ff::attack_time attack_time_;

	sge::input::joypad::ff::fade_level fade_level_;

	sge::input::joypad::ff::fade_time fade_time_;
};

}
}
}
}

#endif
