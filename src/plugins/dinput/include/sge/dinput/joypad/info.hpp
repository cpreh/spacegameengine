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


#ifndef SGE_DINPUT_JOYPAD_INFO_HPP_INCLUDED
#define SGE_DINPUT_JOYPAD_INFO_HPP_INCLUDED

#include <sge/dinput/joypad/absolute_axis_map.hpp>
#include <sge/dinput/joypad/button_map.hpp>
#include <sge/dinput/joypad/info_fwd.hpp>
#include <sge/dinput/joypad/relative_axis_map.hpp>
#include <sge/input/joypad/info.hpp>


namespace sge
{
namespace dinput
{
namespace joypad
{

class info
{
public:
	info(
		sge::input::joypad::info const &,
		sge::dinput::joypad::absolute_axis_map const &,
		sge::dinput::joypad::button_map const &,
		sge::dinput::joypad::relative_axis_map const &
	);

	sge::input::joypad::info const &
	input_info() const;

	sge::dinput::joypad::absolute_axis_map const &
	absolute_axis_map() const;

	sge::dinput::joypad::button_map const &
	button_map() const;

	sge::dinput::joypad::relative_axis_map const &
	relative_axis_map() const;
private:
	sge::input::joypad::info input_info_;

	sge::dinput::joypad::absolute_axis_map absolute_axis_map_;

	sge::dinput::joypad::button_map button_map_;

	sge::dinput::joypad::relative_axis_map relative_axis_map_;
};

}
}
}

#endif
