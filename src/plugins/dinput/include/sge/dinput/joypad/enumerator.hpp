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


#ifndef SGE_DINPUT_JOYPAD_ENUMERATOR_HPP_INCLUDED
#define SGE_DINPUT_JOYPAD_ENUMERATOR_HPP_INCLUDED

#include <sge/dinput/di.hpp>
#include <sge/dinput/device/enumerator.hpp>
#include <sge/dinput/joypad/absolute_axis_map.hpp>
#include <sge/dinput/joypad/button_map.hpp>
#include <sge/dinput/joypad/relative_axis_map.hpp>
#include <sge/input/joypad/absolute_axis_info_container.hpp>
#include <sge/input/joypad/button_info_container.hpp>
#include <sge/input/joypad/relative_axis_info_container.hpp>
#include <fcppt/noncopyable.hpp>


namespace sge
{
namespace dinput
{
namespace joypad
{

class enumerator
:
	public sge::dinput::device::enumerator
{
	FCPPT_NONCOPYABLE(
		enumerator
	);
public:
	explicit
	enumerator(
		IDirectInputDevice8 &
	);

	~enumerator();

	sge::input::joypad::absolute_axis_info_container::vector const &
	absolute_axis() const;

	sge::input::joypad::button_info_container::vector const &
	buttons() const;

	sge::input::joypad::relative_axis_info_container::vector const &
	relative_axis() const;

	sge::dinput::joypad::absolute_axis_map const &
	absolute_axis_map() const;

	sge::dinput::joypad::button_map const &
	button_map() const;

	sge::dinput::joypad::relative_axis_map const &
	relative_axis_map() const;
private:
	void
	dispatch(
		DIDEVICEOBJECTINSTANCE const &
	);

	IDirectInputDevice8 &device_;

	sge::input::joypad::absolute_axis_info_container::vector absolute_axis_;

	sge::input::joypad::button_info_container::vector buttons_;

	sge::input::joypad::relative_axis_info_container::vector relative_axis_;

	sge::dinput::joypad::absolute_axis_map absolute_axis_map_;

	sge::dinput::joypad::button_map button_map_;

	sge::dinput::joypad::relative_axis_map relative_axis_map_;
};

}
}
}

#endif
