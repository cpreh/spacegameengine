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


#ifndef SGE_INPUT_JOYPAD_INFO_HPP_INCLUDED
#define SGE_INPUT_JOYPAD_INFO_HPP_INCLUDED

#include <sge/input/joypad/info_fwd.hpp>
#include <sge/input/joypad/absolute_axis_info_container.hpp>
#include <sge/input/joypad/button_info_container.hpp>
#include <sge/input/joypad/relative_axis_info_container.hpp>
#include <sge/input/symbol.hpp>

namespace sge
{
namespace input
{
namespace joypad
{

class info
{
public:
	SGE_INPUT_SYMBOL
	info(
		input::joypad::absolute_axis_info_container const &,
		input::joypad::button_info_container const &,
		input::joypad::relative_axis_info_container const &
	);

	SGE_INPUT_SYMBOL
	input::joypad::absolute_axis_info_container const &
	absolute_axis() const;

	SGE_INPUT_SYMBOL
	input::joypad::button_info_container const &
	buttons() const;

	SGE_INPUT_SYMBOL
	input::joypad::relative_axis_info_container const &
	relative_axis() const;
private:
	input::joypad::absolute_axis_info_container absolute_axis_;

	input::joypad::button_info_container buttons_;

	input::joypad::relative_axis_info_container relative_axis_;
};

}
}
}

#endif
