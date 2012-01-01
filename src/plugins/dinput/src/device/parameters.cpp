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


#include <sge/dinput/device/parameters.hpp>

sge::dinput::device::parameters::parameters(
	IDirectInput8 *const _instance,
	fcppt::string const &_name,
	GUID const _guid,
	awl::backends::windows::window::instance &_window,
	awl::backends::windows::system::event::handle &_event_handle
)
:
	instance_(_instance),
	name_(_name),
	guid_(_guid),
	window_(_window),
	event_handle_(_event_handle)
{
}

IDirectInput8 *
sge::dinput::device::parameters::instance() const
{
	return instance_;
}

fcppt::string const
sge::dinput::device::parameters::name() const
{
	return name_;
}

GUID
sge::dinput::device::parameters::guid() const
{
	return guid_;
}

awl::backends::windows::window::instance &
sge::dinput::device::parameters::window() const
{
	return window_;
}

awl::backends::windows::system::event::handle &
sge::dinput::device::parameters::event_handle() const
{
	return event_handle_;
}
