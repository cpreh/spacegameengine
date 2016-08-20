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


#ifndef SGE_DINPUT_JOYPAD_FF_EFFECT_HPP_INCLUDED
#define SGE_DINPUT_JOYPAD_FF_EFFECT_HPP_INCLUDED

#include <sge/dinput/di.hpp>
#include <sge/dinput/joypad/button_map.hpp>
#include <sge/dinput/joypad/ff/dinput_effect_unique_ptr.hpp>
#include <sge/dinput/joypad/ff/scoped_download.hpp>
#include <sge/input/joypad/ff/effect.hpp>
#include <sge/input/joypad/ff/optional_play_count_fwd.hpp>
#include <sge/input/joypad/ff/parameters_fwd.hpp>
#include <fcppt/noncopyable.hpp>


namespace sge
{
namespace dinput
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
		IDirectInputDevice8 &,
		sge::dinput::joypad::button_map const &,
		sge::input::joypad::ff::parameters const &
	);

	~effect()
	override;
private:
	void
	play(
		sge::input::joypad::ff::optional_play_count
	)
	override;

	void
	stop()
	override;

	sge::dinput::joypad::ff::dinput_effect_unique_ptr const effect_;

	sge::dinput::joypad::ff::scoped_download const download_;
};

}
}
}
}

#endif
