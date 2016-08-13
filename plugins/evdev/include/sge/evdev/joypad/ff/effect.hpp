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


#ifndef SGE_EVDEV_JOYPAD_FF_EFFECT_HPP_INCLUDED
#define SGE_EVDEV_JOYPAD_FF_EFFECT_HPP_INCLUDED

#include <sge/evdev/device/fd_fwd.hpp>
#include <sge/evdev/joypad/button/event_map.hpp>
#include <sge/evdev/joypad/ff/uploaded_effect.hpp>
#include <sge/input/joypad/ff/effect.hpp>
#include <sge/input/joypad/ff/optional_play_count_fwd.hpp>
#include <sge/input/joypad/ff/parameters_fwd.hpp>
#include <fcppt/noncopyable.hpp>


namespace sge
{
namespace evdev
{
namespace joypad
{
namespace ff
{

class effect
:
	public
		sge::input::joypad::ff::effect
{
	FCPPT_NONCOPYABLE(
		effect
	);
public:
	effect(
		sge::evdev::device::fd const &,
		sge::evdev::joypad::button::event_map const &,
		sge::input::joypad::ff::parameters const &
	);

	~effect()
	override;

	void
	play(
		sge::input::joypad::ff::optional_play_count
	)
	override;

	void
	stop()
	override;
private:
	sge::evdev::device::fd const &fd_;

	sge::evdev::joypad::ff::uploaded_effect const uploaded_effect_;
};

}
}
}
}

#endif
