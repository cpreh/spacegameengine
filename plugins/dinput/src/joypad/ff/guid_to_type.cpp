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


#include <sge/dinput/di.hpp>
#include <sge/dinput/joypad/ff/guid_to_type.hpp>
#include <sge/dinput/joypad/ff/optional_type.hpp>
#include <sge/input/joypad/ff/type.hpp>


sge::dinput::joypad::ff::optional_type
sge::dinput::joypad::ff::guid_to_type(
	REFGUID _guid
)
{
	if(
		_guid
		==
		GUID_ConstantForce
	)
		return
			sge::dinput::joypad::ff::optional_type{
				sge::input::joypad::ff::type::constant
			};

	if(
		_guid
		==
		GUID_Spring
	)
		return
			sge::dinput::joypad::ff::optional_type{
				sge::input::joypad::ff::type::spring
			};

	if(
		_guid
		==
		GUID_Friction
	)
		return
			sge::dinput::joypad::ff::optional_type{
				sge::input::joypad::ff::type::friction
			};

	if(
		_guid
		==
		GUID_Damper
	)
		return
			sge::dinput::joypad::ff::optional_type{
				sge::input::joypad::ff::type::damper
			};

	if(
		_guid
		==
		GUID_Inertia
	)
		return
			sge::dinput::joypad::ff::optional_type{
				sge::input::joypad::ff::type::inertia
			};

	if(
		_guid
		==
		GUID_RampForce
	)
		return
			sge::dinput::joypad::ff::optional_type{
				sge::input::joypad::ff::type::ramp
			};

	if(
		_guid
		==
		GUID_Square
	)
		return
			sge::dinput::joypad::ff::optional_type{
				sge::input::joypad::ff::type::square
			};

	if(
		_guid
		==
		GUID_Sine
	)
		return
			sge::dinput::joypad::ff::optional_type{
				sge::input::joypad::ff::type::sine
			};

	if(
		_guid
		==
		GUID_SawtoothUp
	)
		return
			sge::dinput::joypad::ff::optional_type{
				sge::input::joypad::ff::type::saw_up
			};

	if(
		_guid
		==
		GUID_SawtoothDown
	)
		return
			sge::dinput::joypad::ff::optional_type{
				sge::input::joypad::ff::type::saw_down
			};

	if(
		_guid
		==
		GUID_CustomForce
	)
		return
			sge::dinput::joypad::ff::optional_type{
				sge::input::joypad::ff::type::custom
			};

	return
		sge::dinput::joypad::ff::optional_type{};
}
